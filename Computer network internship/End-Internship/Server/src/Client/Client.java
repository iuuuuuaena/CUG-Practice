package Client;

import java.net.Socket;

public class Client {
    private Socket socket;
    private Player player;

    public Client(Player player, Socket socket){
        this.player=player;
        this.socket=socket;
    }
    public Player getPlayer() {
        return player;
    }

    public Socket getSocket() {
        return socket;
    }

    public void setSocket(Socket socket) {
        this.socket = socket;
    }
}