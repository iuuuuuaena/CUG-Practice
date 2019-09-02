package Handle;

public class message {
    public static void show_prompt(){
        System.out.println("command>");
    }

    public static void on_client_connect_failure(){
        System.out.println("The gate to the tiny world of warcraft is not ready.");
    }

    public static void on_malformed_message_from_server(){
        System.out.println("Meteor is striking the world.");
    }

    public static void on_disconnection_from_server(){
        System.out.println("The gate to the tiny world of warcraft has disappeared.");
    }

    public static void on_not_visible(){
        System.out.println("The target is not visible.");
        show_prompt();
    }

    public static void on_login_reply(int error_code){
        if (error_code==0){
            System.out.println("Welcome to the tiny world of warcraft.");
        }else if (error_code==1){
            System.out.println("A Client.Player with the same name is already in the game.");
        }else {
            assert(false);
        }
        show_prompt();
    }

    public static void on_move_notify(char[] player_name,byte x,byte y,int hp,int exp){
        System.out.printf( "%s: location=(%d,%d), HP=%d, EXP=%d\n",
                String.valueOf(player_name), x, y, hp, exp);
    }

    public static void on_attack_notify(char[] attacker_name,char[] victim_name,int damage,int updated_hp){
        if (updated_hp<=0){
            System.out.printf("%s killed %s\n", String.valueOf(attacker_name), String.valueOf(victim_name));
        }
    }

    public static void on_speak_notify(char[] speaker,char[] message){
        System.out.printf( "%s: %s\n", String.valueOf(speaker), String.valueOf(message));
        show_prompt();
    }

    public static void on_exit_notify(char[] player_name){
        System.out.printf("Client.Player %s has left the tiny world of warcraft.\n", String.valueOf(player_name));
    }

    public static void on_invalid_state(int error_code){
        if (error_code==0){
            System.out.println("You must log in first.");
        }else if (error_code==1){
            System.out.println("You already logged in.");
        }else {
            assert(false);
        }
    }

    public static char[] message_on_server_port_bind_failure(){
        return "The gate cannot be opened there.".toCharArray();
    }


}
