package javax.servlet;

import javax.servlet.process.*;
import javax.swing.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;

public class HttpServer implements Runnable{
    private boolean run=true;
    private static int port=80;
    private ServerSocket ssock;
    private JTextArea textArea;

    public static String Web_Root=System.getProperty("user.dir")+"/"+"WebContent";
    private static XMLReader xmlReader=new XMLReader();
    public static Map<String,String> servletMap =xmlReader.getServletMap();
    public static Map<String,String> servletMapping=xmlReader.getServletMapping();
    public static Map<String,String> filterMap=xmlReader.getFilterMap();
    public static Map<String,String> filterMapping=xmlReader.getFilterMapping();

    public HttpServer(){

    }
    public void close(){
        try {
            ssock.close();
        }catch (Exception e){
            TomcatUI.addLog(e.toString());
        }
    }

    /**
     * 服务器启动
     */
    @Override
    public void run() {
        run=true;
        try {
            ssock=new ServerSocket(port);
            TomcatUI.addLog("listening port "+port);
            while (run){
                Socket socket=ssock.accept();
                TomcatUI.addLog("new client has made socket connection");
                HttpProcess httpProcess=new HttpProcess(socket);
                new Thread(httpProcess).start();
            }
        }catch (Exception e){
            TomcatUI.addLog(e.toString());
        }
    }
    public static void setWeb_Root(String web_Root) {
        Web_Root = web_Root;
    }

    public static void setPort(int port) {
        HttpServer.port = port;
    }

    public static void main(String[] args) {
        new HttpServer().run();
    }
}