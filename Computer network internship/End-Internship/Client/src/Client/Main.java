package Client;

import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.atomic.AtomicBoolean;

public class Main
{

    public static void main(String[] args)
    {
        try
        {
            String ip = "localhost";
            int port = 6666;
            if(args.length>=4)
            {
                if(args[0].equalsIgnoreCase("-p"))
                    port = Integer.parseInt(args[1]);

                if(args[2].equalsIgnoreCase("-s"))
                    ip = args[3];
            }
            Socket socket = new Socket(ip,port);
            new Thread(new Game(socket)).start();
        } catch (Exception e) {
            System.out.println("The gate to the tiny world of warcraft is not ready.");
//            e.printStackTrace();
        }
    }
}
