package Packet;

import java.nio.ByteBuffer;

public class packet
{
    public byte m_version;
    public short m_totalLen;
    public byte m_type;
    public byte[] m_message;

    public byte[] toByte()
    {
        byte[] res = new byte[m_totalLen];
        res[0] = m_version;
        ByteBuffer buffer = ByteBuffer.allocate(2);
        buffer.putShort(m_totalLen);
        res[1] = buffer.array()[0];
        res[2] = buffer.array()[1];
        res[3] = m_type;

        for(int i = 4;i < res.length;i++)
            res[i] = m_message[i-4];
        return res;
    }
}
