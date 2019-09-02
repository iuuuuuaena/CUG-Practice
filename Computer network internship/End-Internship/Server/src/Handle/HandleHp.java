package Handle;


import Main.Sserver;

public class HandleHp implements Runnable{
    @Override
    public void run() {
        try {
            while (true){
                Thread.sleep(5000);
                for (String name: Sserver.clients.getNames()){
                    Sserver.clients.getClient(name).getPlayer().setHP(Sserver.clients.getClient(name).getPlayer().getHP()+1);
//                    System.out.println(name+":HP+1");
                }
            }
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
