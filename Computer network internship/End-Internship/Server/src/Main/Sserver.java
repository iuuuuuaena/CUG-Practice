package Main;

import Client.Clients;
import Handle.Handle;
import Handle.HandleHp;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class Sserver {

    private ServerSocket ssock;
    public static Clients clients=new Clients();
    public void run(int port){
        try {
//            byte[] b=new byte[]{(byte)*,(byte)*,(byte)*,(byte)*};
//            InetAddress address=InetAddress.getByAddress(b);
//            ssock=new ServerSocket(port,1024,address);
            ssock=new ServerSocket(port);
            //*Listening port is ready...
            System.out.println("*Listening port "+ port+" is ready...");
            System.out.println();
            new Thread(new HandleHp()).start();
            while (true){
                Socket socket=ssock.accept();
                System.out.println("new connection from "+socket.getInetAddress()+":"+socket.getPort());
                Handle handle=new Handle(socket);
                new Thread(handle).start();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private static void printHlpInfo(){
        System.out.println("! The server port number is not defined.");
        System.out.println("! Usage: ./server -p <port_number>");
    }
    public static void main(String[] args) {
//        if (args.length<2||!args[0].equals("-p")){
//            printHlpInfo();
//        }else {
//            new Main.Sserver().run(Integer.parseInt(args[1]));
//        }
        new Sserver().run(6666);
    }
}
