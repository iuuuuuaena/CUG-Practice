package Transfer;

public class Transfer
{
    public static int byteArrayToInt(byte[] b) {
        return b[3] & 0xFF |
                (b[2] & 0xFF) << 8 |
                (b[1] & 0xFF) << 16 |
                (b[0] & 0xFF) << 24;
    }

    public static short byteArrayToShort(byte[] b)
    {
        short res = 0;
        short s1 = (short)(b[0] & 0xff);
        short s2 = (short)(b[1] & 0xff);
        s2 <<= 8;
        res = (short)(s1|s2);
        return  res;
    }
}
