package javax.servlet.http;

import javax.servlet.process.HttpProcess;
import javax.servlet.process.TomcatUI;
import javax.swing.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.servlet.*;

public class HttpServletResponse extends ServletResponse{
    private String path=HttpServer.Web_Root;
    private OutputStream out=null;
    private HttpServletRequest request=null;
    private JTextArea textArea;
    private String contentType="text/html";
    private boolean isSentResponse;
    private boolean isSentContentType;
    private SimpleDateFormat sdf=new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
    /**
     * 构造函数
     * @param stream 输出流
     * @param request
     */
    public HttpServletResponse(OutputStream stream,HttpServletRequest request){
        out=stream;
        this.request=request;
        isSentResponse =false;
        isSentContentType=false;
    }

    /**
     * 处理静态请求
     * @throws Exception
     */
    public void accessStaticResources() throws Exception {
        //根据请求URI找到用户对应请求的资源文件
        File staticResource = new File(path + request.getUrl());
        //资源存在
//        System.out.println(staticResource.getPath());
        if (staticResource.exists() && staticResource.isFile()) {
//            out.write("HTTP-1.1 200 OK\r\n".getBytes());
            sentOK();
            writeFile(staticResource);

        }else if (staticResource.exists()&&staticResource.isDirectory()){
            sentOK();
            writeCatalog(staticResource);
        }
        else {//资源不存在
            staticResource = new File(path + "/404.html");
            out.write("HTTP-1.1 404 File Not Found".getBytes());
            writeFile(staticResource);
        }
    }

    /**
     * 静态文件请求
     * @param file
     * @throws IOException
     */
    private void writeFile(File file) throws IOException {
        try {
            DataInputStream din=new DataInputStream(new FileInputStream(file));
            int len=(int)file.length();
            byte[] buf=new byte[len];
            din.readFully(buf);
            out.write(("Content-Length:"+len+"\r\n").getBytes());
            if (file.getName().contains(".html")||file.getName().contains(".jsp")){
                out.write("Content-Type:text/html\r\n\r\n".getBytes());
            }else {
                out.write("Content-Type:image/jpg\r\n\r\n".getBytes());
            }
            out.write(buf);
            out.flush();
            out.close();
        }catch (Exception e){
//            TomcatUI.addLog(e.toString());
            e.printStackTrace();
        }
    }

    /**
     * 目录请求
     * @param f
     */
    private void writeCatalog(File f){
        StringBuffer s=new StringBuffer("<!DOCTYPE html>\n" +
                "<html lang=\"en\">\n" +
                "<head>\n" +
                "    <meta charset=\"UTF-8\">\n" +
                "    <title>Java Final Lab</title>\n" +
                "</head>\n" +
                "<body>\n");
        File[] fs=f.listFiles();
        StringBuffer s1=new StringBuffer(request.getUrl());
//        System.out.println(s1);
        s.append("<h2>"+s1.toString()+"的索引</h2>\n<hr>");
        if (s1.length()>0&&s1.charAt(s1.length()-1)!='\\'&&s1.charAt(s1.length()-1)!='/'){
            s1.append('\\');
        }
        s.append("<table cellspacing=\"30\">\n<tr><th>名称</th><th>大小</th><th>修改日期</th></th>\n");
        for (File tmp:fs){
//            s.append("<li>");
//            s.append("<a href=\""+s1+tmp.getName()+"\">"+tmp.getName()+"</a>\n");
//            s.append("</li>");
//            s.append("<br>");
            s.append("<tr><td>");
            s.append("<a href=\""+s1+tmp.getName()+"\">"+tmp.getName()+"</a>");
            s.append("</td><td>");
            s.append(tmp.length()==0?"文件夹":tmp.length()+"B");
            s.append("</td><td>");
            s.append(sdf.format(new Date(tmp.lastModified())));
            s.append("</td></tr>\n");
        }
        s.append("</table>");
        s.append("\n</body>\n</html>");
        try {
//            out.write(("Content-Length:"+s.length()+"\r\n").getBytes());
            out.write("Content-Type:text/html;charset=utf-8\r\n\r\n".getBytes());
            out.write(s.toString().getBytes());
            out.flush();
            out.close();
        }catch (Exception e){
            TomcatUI.addLog(e.toString());
//            e.printStackTrace();
//            System.out.println("无法写入");
        }
    }
//    public void sendText(String s1)throws Exception{
//        write("HTTP-1.1 200 OK\r\n");
//        write("Content-Type:text/html\r\n\r\n");
//
//        StringBuffer s=new StringBuffer("<!DOCTYPE html>\n" +
//                "<html lang=\"en\">\n" +
//                "<head>\n" +
//                "    <meta charset=\"UTF-8\">\n" +
//                "    <title>Java Final Lab</title>\n" +
//                "</head>\n" +
//                "<body>\n");
//        s.append(s1);
//        s.append("\n</body>\n</html>");
//        write(s.toString());
//        flush();
//    }

    /**
     * 输出一个字符串
     * @param s
     * @throws Exception
     */
    public void write(String s)throws Exception{
        out.write(s.getBytes());
    }

    /**
     * 将缓冲区的内容输出
     * @throws Exception
     */
    public void flush()throws Exception{
        out.flush();
    }
    public String getContentType() {
        return contentType;
    }

    /**
     * 输出状态码
     * @throws Exception
     */
    public void sentOK()throws Exception{
        if (!isSentResponse){
            isSentResponse =true;
            write("HTTP-1.1 200 OK\n");
        }
    }

    /**
     * 输出文件类型
     * @throws Exception
     */
    public void sentContenType()throws Exception{
        if (!isSentContentType){
            isSentContentType=true;
            write("Content-Type:"+contentType+"\r\n\r\n");
        }
    }

    /**
     * 设置文件类型
     * @param s
     */
    public void setContentType(String s){
        this.contentType=s;
//        sentContenType();
    }

    /**
     * 获取一个输出流的PrintWriter对象
     * @return
     */
    public PrintWriter getWriter(){
        return new PrintWriter(out);
    }

    /**
     * 重定向到指定url
     * @param s
     */
    public void sendRedirect(String s){
        //TODO
        request.setUrl("/"+s);
        request.setMethod("GET");
        System.out.println("sendRedirect");
        HttpProcess.process(request,this);
    }
}
