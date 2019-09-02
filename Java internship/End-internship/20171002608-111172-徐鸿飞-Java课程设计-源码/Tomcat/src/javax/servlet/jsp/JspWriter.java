package javax.servlet.jsp;

import java.io.IOException;
import java.io.*;
import java.nio.charset.Charset;

public abstract class JspWriter extends Writer {

    private int bufferSize;
    private boolean autoFlush;
    private boolean trouble = false;
    protected Writer out;
    private PrintStream psOut = null;

    protected JspWriter(int bufferSize, boolean autoFlush) {
        this.bufferSize = bufferSize;
        this.autoFlush = autoFlush;
    }
    public JspWriter(Writer out,
                       boolean autoFlush) {
        super(out);
        this.out = out;
        this.autoFlush = autoFlush;
    }
    public JspWriter(OutputStream out) {
        this(out, false);
    }
    public JspWriter(OutputStream out, boolean autoFlush) {
        this(out, autoFlush, Charset.defaultCharset());
    }
    public JspWriter(OutputStream out, boolean autoFlush, Charset charset) {
        this(new BufferedWriter(new OutputStreamWriter(out, charset)), autoFlush);

        // save print stream for error propagation
        if (out instanceof java.io.PrintStream) {
            psOut = (PrintStream) out;
        }
    }
    public void print(Object o){

    }
    public void println(Object o){

    }

    @Override
    public void write(char[] cbuf, int off, int len) throws IOException {

    }

    @Override
    public void flush() throws IOException {
        try {
            synchronized (lock) {
                ensureOpen();
                out.flush();
            }
        }
        catch (IOException x) {
            trouble = true;
        }
    }

    @Override
    public void close() throws IOException {
        try {
            synchronized (lock) {
                if (out == null)
                    return;
                out.close();
                out = null;
            }
        }
        catch (IOException x) {
            trouble = true;
        }
    }
    private void ensureOpen() throws IOException {
        if (out == null)
            throw new IOException("Stream closed");
    }
}
