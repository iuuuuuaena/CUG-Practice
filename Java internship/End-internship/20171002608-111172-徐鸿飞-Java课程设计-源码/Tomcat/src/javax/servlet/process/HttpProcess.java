package javax.servlet.process;


import javax.servlet.*;
import javax.servlet.Filter.Filter;
import javax.servlet.http.*;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class HttpProcess implements Runnable{
    private Socket socket;
    private String path= HttpServer.Web_Root;
    public HttpProcess(Socket socket){
        this.socket=socket;
    }

    /**
     * 为每个链接创建Request和Response对象
     */
    private void process(){
        try{
            InputStream in=socket.getInputStream();
            OutputStream out=socket.getOutputStream();
            HttpServletRequest request=new HttpServletRequest(in);
            HttpServletResponse response=new HttpServletResponse(out,request);
            FilterProcess.process(request,response);
//            process(request,response);
        }catch (Exception e){
//            TomcatUI.addLog(e.toString());
            e.printStackTrace();
        }
    }

    /**
     * 对不同类型链接分别进行处理
     * @param request 链接的HttpServletRequest对象
     * @param response 链接的HttpServletResponse对象
     */
    public static void process(HttpServletRequest request,HttpServletResponse response){
        try {
            if (request.getUrl().contains(".jsp")){
//                System.out.println("jsp Servlet");
                if (!HttpServer.servletMapping.keySet().contains(request.getUrl().substring(0,request.getUrl().length()-4))){
//                    System.out.println("jsp Servlet");
                    TomcatUI.addLog("jsp Servlet");
                    JspProcess jspProcess=new JspProcess();
                    jspProcess.process(request,response);
                }
                request.setUrl(request.getUrl().substring(0,request.getUrl().length()-4));
                ServletProcess servletProcess=new ServletProcess();
                servletProcess.process(request,response);
            }
            else if (!HttpServer.servletMapping.keySet().contains(request.getUrl())){
//            if (!request.getMethod().contains("POST")){
//                System.out.println("静态页面");
                TomcatUI.addLog("静态页面");
                response.accessStaticResources();
            }else {
//                System.out.println("非jsp Servlet");
                TomcatUI.addLog("非jsp Servlet");
                ServletProcess servletProcess=new ServletProcess();
                servletProcess.process(request,response);
            }
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    @Override
    public void run() {
        process();
    }
}
