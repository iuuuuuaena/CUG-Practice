package Client;

import java.io.*;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Clients {
    private static String ROOT_PATH=System.getProperty("user.dir")+"/"+"Users";
//    private Set<Client.Player> players=new HashSet<>();//在线玩家
    private Set<String> names=new HashSet<>();//在线玩家姓名
    private Map<String,Client> map=new HashMap<>();//所有玩家
    public Clients(){
        File root=new File(ROOT_PATH);
        try {
            if (!root.exists()){
                System.out.println(ROOT_PATH+" path not exists");
                root.mkdirs();
            }
            for (File f:root.listFiles()){
                FileInputStream inputStream=new FileInputStream(f);
                InputStreamReader reader=new InputStreamReader(inputStream,StandardCharsets.UTF_8);
                StringBuilder sb=new StringBuilder();
                while (reader.ready()){
                    sb.append((char)reader.read());
                }
                String[] strings=sb.toString().split("\n");
                if (strings.length!=3){
                    throw new Exception("File Error");
                }
                String name=f.getName();
                int HP=Integer.parseInt(strings[0].split(":")[1]);
                int EXP=Integer.parseInt(strings[1].split(":")[1]);
                String[] point=strings[2].split(":");
                int x=Integer.parseInt(point[1]);
                int y=Integer.parseInt(point[2]);
                Player player=new Player(name,HP,EXP,x,y);
                Client client=new Client(player,null);
                map.put(name,client);
            }
        }catch (Exception e){
            e.printStackTrace();
        }

    }
    public Set<Socket> getSockets(){
        Set<Socket> set=new HashSet<>();
        for (String s:names){
            set.add(map.get(s).getSocket());
        }
        return set;
    }
    public void add(String s,Client c){
        map.put(s,c);
    }
    public void remove(String s){
        try {
            if (!map.containsKey(s)){
                throw new Exception("No such player");
            }
            File f=new File(ROOT_PATH+"/"+s);
            System.out.println(ROOT_PATH+"/"+s);
            if (!f.exists()){
                f.createNewFile();
            }
            OutputStream outputStream=new FileOutputStream(f);
            OutputStreamWriter writer=new OutputStreamWriter(outputStream, StandardCharsets.UTF_8);
            Player player=map.get(s).getPlayer();
            writer.append("HP:"+player.getHP()+"\n");
            writer.append("EXP:"+player.getEXP()+"\n");
            writer.append("Position:"+player.getPosition().x+":"+player.getPosition().y);
            writer.close();
            outputStream.close();
//            players.remove(player);
            names.remove(s);
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    public boolean contains(String s){
        return map.containsKey(s);
    }
    public Socket getSocket(String s){
        return map.get(s).getSocket();
    }
//
//    public Set<Client.Player> getPlayers() {
//        return players;
//    }
    public void add(Player player){
//        players.add(player);
        names.add(player.getName());
    }
    public Client getClient(String s){
        return map.get(s);
    }
    public Set<String> getNames() {
        return names;
    }
}
