package Handle;

import Client.Client;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Arrays;
import java.util.Random;
import Client.Player;
import Main.Sserver;


public class Handle implements Runnable{
    private Socket socket;

    private InputStream in;
    private OutputStream out;

    private Random random=new Random();
    private boolean flag=true;

    private String name;
    private Client client;
    private Player player;

    public Handle(Socket socket){
        try {
            this.socket=socket;
            in=socket.getInputStream();
            out=socket.getOutputStream();
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    private void handle_Login(byte[] bytes){
        if (name!=null){
            handle_Invalid((byte)1);
            return;
        }
        byte[] name_bytes=new byte[10];
        System.arraycopy(bytes,4,name_bytes,0,10);
        name=new String(name_bytes).trim();
        byte[] info;
        if (Sserver.clients.contains(name)&& Sserver.clients.getSocket(name)!=null){
            byte[] head=Packet.get_Head(16,2);
            byte[] login=Packet.get_Login_Reply((byte) 1, 0,0,0,0);
            info=concat(head,login);
        }else if (Sserver.clients.contains(name)){
            byte[] head=Packet.get_Head(16,2);
            client= Sserver.clients.getClient(name);
            client.setSocket(socket);
            player=client.getPlayer();
            Sserver.clients.add(player);
            byte[] login=Packet.get_Login_Reply((byte)0,player.getHP(),player.getEXP(),player.getPosition().x,player.getPosition().y);
            info=concat(head,login);
        }
        else {
            byte[] head=Packet.get_Head(16,2);
            int hp=random.nextInt(21)+100;
            int exp=0;
            int x=random.nextInt(100);
            int y=random.nextInt(100);
            byte[] login=Packet.get_Login_Reply((byte) 0, hp,exp,x,y);
            info=concat(head,login);
            player=new Player(name,hp,exp,x,y);
            client=new Client(player,socket);
            Sserver.clients.add(name,client);
            Sserver.clients.add(player);
        }
        try{
            out.write(info);
            out.flush();
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    private void handle_Move(byte[] bytes){
        if (name==null){
            handle_Invalid((byte)0);
            return;
        }
        byte[] head=Packet.get_Head(24,4);
        player.move((int)bytes[4]);
        byte[] move=Packet.get_Move_Notify(name,player.getPosition().x,player.getPosition().y,player.getHP(),player.getEXP());
        byte[] info=concat(head,move);
        broadcast(info);
    }
    private void handle_attack(byte[] bytes){
        if (name==null){
            handle_Invalid((byte)0);
            return;
        }
        byte[] head=Packet.get_Head(32,6);
        byte[] name_bytes=new byte[10];
        System.arraycopy(bytes,4,name_bytes,0,10);
        String vic_Name=new String(name_bytes).trim();
        if (vic_Name.equals(name)||!Sserver.clients.getNames().contains(vic_Name)){
            //TODO:忽略??
            return;
        }
        int damage=random.nextInt(11)+10;
        player.setEXP(player.getEXP()+damage);
        Player vic_Player= Sserver.clients.getClient(vic_Name).getPlayer();
        int hp=vic_Player.getHP()<=damage?random.nextInt():vic_Player.getHP()-damage;
        vic_Player.setHP(hp);
        byte[] attack=Packet.get_Attack_Notify(name,vic_Name,damage,hp);
        byte[] info=concat(head,attack);
        broadcast(info);
    }
    private void handle_Speak(byte[] bytes){
        if (name==null){
            handle_Invalid((byte)0);
            return;
        }
        String msg=new String(bytes).trim();
        byte[] speak=Packet.get_Speak_Notify(name,msg);
        byte[] head=Packet.get_Head(4+speak.length,8);
        byte[] info=concat(head,speak);
        broadcast(info);
    }
    private void handle_Logout(byte[] bytes){
        if (name==null){
            handle_Invalid((byte)0);
            return;
        }
        byte[] head=Packet.get_Head(16,10);
        byte[] logout=Packet.get_Logout_Notify(name);
        byte[] info=concat(head,logout);
        broadcast(info);
        try {
//            Sserver.clients.getSocket(name).close();
            Sserver.clients.remove(name);
            close_socket();
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    private void handle_Invalid(byte error_code){
        byte[] head=Packet.get_Head(8,11);
        byte[] invalid=Packet.get_Invalid_State(error_code);
        byte[] info=concat(head,invalid);
        try {
            socket.getOutputStream().write(info);
            socket.getOutputStream().flush();
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    private static byte[] concat(byte[] first, byte[] second) {
        byte[] result = Arrays.copyOf(first, first.length + second.length);
        System.arraycopy(second, 0, result, first.length, second.length);
        return result;
    }
    private void broadcast(byte[] info){
        try {
            for (Socket socket1: Sserver.clients.getSockets()){
                if (socket1==null)continue;
                socket1.getOutputStream().write(info);
                socket1.getOutputStream().flush();
            }
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    private void close_socket(){
        flag=false;
        try {
            socket.shutdownOutput();
            socket.shutdownInput();
            out.close();
            in.close();
            socket.close();
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    @Override
    public void run() {
        try {
            while (flag){
                if (!socket.isClosed()&&socket.isConnected()&&in!=null){
                    byte[] bytes=new byte[1024];
                    int res=in.read(bytes);
                    if (res<4)continue;//throw new Exception("msg lengyh <4");
                    System.out.println(bytes[3]);
                    if (bytes[3]==1){
                        handle_Login(bytes);
                    }
                    else if (bytes[3]==3){
                        handle_Move(bytes);
                    }
                    else if (bytes[3]==5){
                        handle_attack(bytes);
                    }else if (bytes[3]==7){
                        handle_Speak(bytes);
                    }else if (bytes[3]==9){
                        handle_Logout(bytes);
                    }else throw new Exception("Msg_type Error");
                }
            }
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
