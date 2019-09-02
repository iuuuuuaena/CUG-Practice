package Handle;

import java.nio.ByteBuffer;

public class Packet {
    //type:2
    public static byte[] get_Login_Reply(byte error_code,int hp,int exp,int x,int y){//x,y范围：byte
        byte[] bytes=new byte[12];
        bytes[0]=error_code;
        byte[] hp_bytes= ByteBuffer.allocate(4).putInt(hp).array();
//        for (int i=0;i<4;++i){
//            bytes[1+i]=hp_bytes[i];
//        }
        System.arraycopy(hp_bytes,0,bytes,1,4);
        byte[] exp_bytes=ByteBuffer.allocate(4).putInt(exp).array();
//        for (int i=0;i<4;++i){
//            bytes[5+i]=exp_bytes[i];
//        }
        System.arraycopy(exp_bytes,0,bytes,5,4);
        bytes[9]=(byte)x;
        bytes[10]=(byte)y;
        bytes[11]=0;
        return bytes;
    }
    //type:4
    public static byte[] get_Move_Notify(String name,int x,int y,int hp,int exp){
        byte[] bytes=new byte[20];
        byte[] name_bytes=name.getBytes();
        System.arraycopy(name_bytes,0,bytes,0,name_bytes.length);
//        for (int i=0;i<name.length();++i){
//            bytes[i]=(byte) name.charAt(i);
//        }
        bytes[10]=(byte)x;
        bytes[11]=(byte)y;
        byte[] hp_bytes= ByteBuffer.allocate(4).putInt(hp).array();
        System.arraycopy(hp_bytes,0,bytes,12,4);
        byte[] exp_bytes=ByteBuffer.allocate(4).putInt(exp).array();
        System.arraycopy(exp_bytes,0,bytes,16,4);
        return bytes;
    }
    //type:6
    public static byte[] get_Attack_Notify(String att_Name,String vic_name,int damage,int hp){
        byte[] bytes=new byte[28];
        byte[] att_Name_bytes=att_Name.getBytes();
        System.arraycopy(att_Name_bytes,0,bytes,0,att_Name_bytes.length);
//        for (int i=0;i<att_Name.length();++i){
//            bytes[i]=(byte) att_Name.charAt(i);
//        }
        byte[] vic_Name_bytes=vic_name.getBytes();
        System.arraycopy(vic_Name_bytes,0,bytes,10,vic_Name_bytes.length);
//        for (int i=0;i<vic_name.length();++i){
//            bytes[10+i]=(byte) vic_name.charAt(i);
//        }
        bytes[20]=(byte)damage;
        byte[] hp_bytes= ByteBuffer.allocate(4).putInt(hp).array();
        System.arraycopy(hp_bytes,0,bytes,21,4);
        return bytes;
    }
    //type:8
    public static byte[] get_Speak_Notify(String name,String Msg){
        byte[] msg=Msg.getBytes();
        int len=(10+msg.length+3)/4*4;
        byte[] bytes=new byte[len];
        byte[] name_bytes=name.getBytes();
        System.arraycopy(name_bytes,0,bytes,0,name_bytes.length);
        System.arraycopy(msg,0,bytes,10,msg.length);
        return bytes;
    }
    //type:10
    public static byte[] get_Logout_Notify(String name){
        byte[] name_bytes=name.getBytes();
        byte[] bytes=new byte[16];
        System.arraycopy(name_bytes,0,bytes,0,name_bytes.length);
        return bytes;
    }
    //type:11
    public static byte[] get_Invalid_State(byte error_code){
        byte[] bytes=new byte[4];
        bytes[0]=error_code;
        return bytes;
    }
    public static byte[] get_Head(int length,int msg_type){
        byte[] head=new byte[4];
        head[0]=4;
        System.arraycopy(ByteBuffer.allocate(2).putShort((short) length).array(),0,head,1,2);
        head[3]=(byte) msg_type;
        return head;
    }
    public static int byteArrayToInt(byte[] b) {
        return b[3] & 0xFF |
                (b[2] & 0xFF) << 8 |
                (b[1] & 0xFF) << 16 |
                (b[0] & 0xFF) << 24;
    }

    public static void main(String[] args) {
        byte a=10;
        System.out.println(a);
    }
}
