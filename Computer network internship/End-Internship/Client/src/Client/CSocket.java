package Client;

import java.awt.Point;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import javax.management.BadAttributeValueExpException;

import Packet.packet;
import Player.Player;
import Player.PlayerList;
import Transfer.Transfer;

//import Packet.packet;

public class CSocket implements Runnable
{
    //tcp
    Socket m_socket;
    InputStream m_inpuInputStream;
    OutputStream m_outputOutputStream;

    packet m_packet;

    boolean close=false;//是否关闭

    Player m_myPlayer;
    public CSocket(Socket socket)
    {
        m_packet = new packet();
        m_socket = socket;

        try {
            m_inpuInputStream = m_socket.getInputStream();
            m_outputOutputStream = m_socket.getOutputStream();
        } catch (IOException e) {
            System.out.println("input output io error");
            e.printStackTrace();
            return;
        }

        System.out.println("connnet ok");
    }

    public void setVersion(byte version)
    {
        this.m_packet.m_version = version;
    }

    public void setType(byte type)
    {
        this.m_packet.m_type = type;
    }

    public void sendLogin(String playerName)
    {
        //init player
        this.m_myPlayer = new Player(playerName);
        PlayerList.m_playerMap.put(playerName,m_myPlayer);


        byte type = 1;
        System.out.println(type);
        setType(type);
        setVersion((byte)4);

        this.m_packet.m_message = new byte[12];
        this.m_packet.m_totalLen = 16;
        int count = 0;
        for(int i = 0;i < playerName.length();i++)
            this.m_packet.m_message[count++] = (byte)playerName.charAt(i);

        this.m_packet.m_message[9] = '\0';


        //tcp

        try {
            m_outputOutputStream.write(this.m_packet.toByte());
            m_outputOutputStream.flush();
        } catch (IOException e) {
            System.out.println("sendLogin error");
            e.printStackTrace();
        }
    }

    public void sendMove(byte direction)
    {
        setType((byte)3);
        setVersion((byte)4);

        this.m_packet.m_message = new byte[4];
        this.m_packet.m_totalLen = 8;

        this.m_packet.m_message[0] = direction;

        //tcp

        try {
            m_outputOutputStream.write(this.m_packet.toByte());
            m_outputOutputStream.flush();
        } catch (IOException e) {
            System.out.println("sendMove error");
            e.printStackTrace();
        }
    }

    public void sendAttack(String victimName)
    {
        setType((byte)5);
        setVersion((byte)4);

        this.m_packet.m_message = new byte[12];
        this.m_packet.m_totalLen = 16;
        int count = 0;
        for(int i = 0;i < victimName.length();i++)
            this.m_packet.m_message[count++] = (byte)victimName.charAt(i);

        this.m_packet.m_message[9] = '\0';


        //tcp
        
        try {
            m_outputOutputStream.write(this.m_packet.toByte());
            m_outputOutputStream.flush();
        } catch (IOException e) {
            System.out.println("sendAttack error");
            e.printStackTrace();
        }
    }

    public void sendLogout()
    {
        setType((byte)9);
        setVersion((byte)4);

        //this.m_packet.m_message = new byte[4];
        this.m_packet.m_totalLen = 4;

        //tcp
        try {
            byte[] a = this.m_packet.toByte();
            m_outputOutputStream.write(this.m_packet.toByte());
            m_outputOutputStream.flush();
            close=true;
        } catch (IOException e) {
            System.out.println("sendLogout error");
            e.printStackTrace();
        }
    }

    public void run()
    {
        recvMessage();
    }

    public void recvMessage()
    {
        try
        {
            while(true)
            {
                byte[] info = new byte[1024];

                if(m_inpuInputStream.read(info) != 0)
                    handleMessage(info);
            }
        } catch (IOException e) {
            System.out.println("recv io error");
            e.printStackTrace();
        }
    }

    public void handleMessage(byte[] message)
    {
        ByteBuffer bb = ByteBuffer.allocate(2);
        bb.order(ByteOrder.LITTLE_ENDIAN);
        bb.put(message[1]);
        bb.put(message[2]);
        short totalLen = bb.getShort(0);

        totalLen = message[2];
        message = java.util.Arrays.copyOf(message,totalLen);
        //System.arraycopy(message,0,message,0,totalLen);
 
        byte type = message[3];
        if(type == 2)
        {
            loginReply(message);
        }
        else if(type == 4)
        {
            moveNotify(message);
        }
        else if(type == 6)
        {
            attackNotify(message);
        }
        else if(type == 8)
        {
            //TODO:speak notify
        }
        else if(type == 10)
        {
            logoutNotify(message);
        }
        else if(type == 11)
        {
            invalidNotify(message);
        }
        
    }

    public void loginReply(byte[] message)
    {
        if(message[4] == 0)
        {
            System.out.println("welcome to the tiny world of warcraft");

            byte[] hpByte = new byte[4];
            byte[] expByte = new byte[4];
            System.arraycopy(message,5,hpByte,0,4);
            System.arraycopy(message,9,expByte,0,4);
            int hp = Transfer.byteArrayToInt(hpByte);
            int exp = Transfer.byteArrayToInt(expByte);
            int x = message[13];
            int y = message[14];

            this.m_myPlayer.setHP(hp);
            this.m_myPlayer.setEXP(exp);
            this.m_myPlayer.setPoint(x,y);
        }
        else if(message[4] == 1)
        {
            System.out.println("a play with the same name is already in the game");
        }
    }

    public void moveNotify(byte[] message)
    {
        int x = (int)message[14];
        int y = (int)message[15];

        byte[] nameByte = new byte[10];
        System.arraycopy(message, 4, nameByte, 0, 10);
        String name = new String(nameByte);
        name = name.trim();

        Point myPoint = m_myPlayer.getPosition();

        //get info
        byte[] hpByte = new byte[4];
        System.arraycopy(message, 16, hpByte, 0, 4);
        int hp = Transfer.byteArrayToInt(hpByte);

        byte[] expByte = new byte[4];
        System.arraycopy(message, 20, expByte, 0, 4);
        int exp = Transfer.byteArrayToInt(expByte);

        if(!PlayerList.m_playerMap.containsKey(name))
            PlayerList.m_playerMap.put(name,new Player(name));

        PlayerList.m_playerMap.get(name).setPoint(x,y);
        PlayerList.m_playerMap.get(name).setHP(hp);
        PlayerList.m_playerMap.get(name).setEXP(exp);

        if(x > myPoint.x-5 && x < myPoint.x+5 && y > myPoint.y-5 && y < myPoint.y+5)//鍦ㄨ绾胯寖鍥村唴
        {
            System.out.println(String.format("%s location(%d,%d),HP=%d,EXP=%d",name, x,y,hp,exp));
        }
    }

    public void attackNotify(byte[] message)
    {
        byte[] attackNameByte = new byte[10];
        byte[] victimNameByte = new byte[10];
        System.arraycopy(message, 4, attackNameByte, 0, 10);
        System.arraycopy(message, 14, victimNameByte, 0, 10);
        String attackName = new String(attackNameByte);
        String victimName = new String(victimNameByte);
        attackName=attackName.trim();
        victimName=victimName.trim();

        System.out.println(PlayerList.m_playerMap);
        System.out.println(attackName+" to "+victimName);
        if(PlayerList.m_playerMap.get(attackName) == null ||
        !PlayerList.m_playerMap.containsKey(victimName))
            return;

        Player attackPlayer = PlayerList.m_playerMap.get(attackName);
        Player victimPlayer = PlayerList.m_playerMap.get(victimName);
        Point attackerPoint = attackPlayer.getPosition();
        Point victimPoint = victimPlayer.getPosition();

        //鑾峰彇浼ゅ鍙奾p
        int damage = (int)message[24];
        byte[] hpByte = new byte[4];
        System.arraycopy(message, 25, hpByte, 0, 4);
        int hp = Transfer.byteArrayToInt(hpByte);

        Point myPoint = m_myPlayer.getPosition();
        if(attackerPoint.x > myPoint.x - 5 && attackerPoint.x < myPoint.x+5
                && attackerPoint.y > myPoint.y-5 && attackerPoint.y < myPoint.y+5
                &&victimPoint.x > myPoint.x - 5 && victimPoint.x < myPoint.x+5
                && victimPoint.y > myPoint.y-5 && victimPoint.y < myPoint.y+5)
        {
            if(hp != 0)
                System.out.println(String.format("%s damaged %s by %d,%s's hp is now %d",
                        attackPlayer.getName(),victimPlayer.getName(),damage,victimPlayer.getName(),hp));
            else if(hp == 0)
                System.out.println(String.format("%s killed %s",
                        attackPlayer.getName(),victimPlayer.getName()));
        }
    }

    public void logoutNotify(byte[] message)
    {
        byte[] nameByte = new byte[10];
        System.arraycopy(message, 4, nameByte, 0, 10);
        String name = new String(nameByte);
        name = name.trim();

        System.out.println(String.format("Player %s has left the tiny world of warcraft.", name));
        
        //close connect
        try {

			m_socket.close();
		} catch (IOException e) {
			System.out.println("close socket error");
			e.printStackTrace();
		}
        if (close){
            System.exit(0);
        }
    }

    public void invalidNotify(byte[] message)
    {
        int errorCode = (int)message[0];
        if(errorCode == 0)
            System.out.println("You must log in first");
        else if(errorCode == 1)
            System.out.println("You already logged in");
    }
}
