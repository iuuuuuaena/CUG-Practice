package Client;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

import Player.Player;
import Player.PlayerList;

public class Game implements Runnable
{

    CSocket cSocket;
    public Game(Socket socket)
    {
        cSocket = new CSocket(socket);
        new Thread(cSocket).start();
    }

    @Override
    public void run()
    {
        try 
        {
        	Scanner scanner = new Scanner(System.in);
            System.out.print("command> ");
            while(scanner.hasNext())
            {
                String command = scanner.nextLine();
                handleCommand(command);
                Thread.sleep(500);
                System.out.print("command> ");
            }
            scanner.close();
		} catch (Exception e) {
			System.out.println("sleep error");
		}
    }

    public void handleCommand(String command)
    {
        String[] commands = command.split(" ");
        if(commands[0].equalsIgnoreCase("login"))
        {
            if(commands.length>=2)
                cSocket.sendLogin(commands[1]);
        }
        else if(commands[0].equalsIgnoreCase("move"))
        {
            if(commands[1].equalsIgnoreCase("north"))
                cSocket.sendMove((byte)0);
            else if(commands[1].equalsIgnoreCase("south"))
                cSocket.sendMove((byte)1);
            else if(commands[1].equalsIgnoreCase("east"))
                cSocket.sendMove((byte)2);
            else if(commands[1].equalsIgnoreCase("west"))
                cSocket.sendMove((byte)3);
        }
        else if(commands[0].equalsIgnoreCase("attack"))
        {
            Player victim = PlayerList.m_playerMap.get(commands[1]);
            if(victim!=null && !victim.getName().equals(cSocket.m_myPlayer.getName())
                    && victim.getPosition().x > cSocket.m_myPlayer.getPosition().x-5
                    && victim.getPosition().x < cSocket.m_myPlayer.getPosition().x+5
                    && victim.getPosition().y > cSocket.m_myPlayer.getPosition().y-5
                    && victim.getPosition().y < cSocket.m_myPlayer.getPosition().y+5)
            {
                System.out.println("I attack someone");
                cSocket.sendAttack(commands[1]);
            }
        }
        else if(commands[0].equalsIgnoreCase("speak"))
        {

        }
        else if(commands[0].equalsIgnoreCase("logout"))
        {
            cSocket.sendLogout();
        }

    }
}
