package javax.servlet.http;

import javax.servlet.*;
import javax.servlet.process.*;
import javax.swing.*;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;


public class HttpServlet {

    public HttpServlet(){
        //TODO
    }
    public void init(){
        //TODO
    }
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)throws ServletException, IOException {
        //TODO
    }
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)throws ServletException, IOException {
        //TODO
    }

    /**
     * HttpServlet中的service函数,处理请求
     * @param request
     * @param response
     *
     */
    public void service(HttpServletRequest request,HttpServletResponse response){
        try {
            response.sentOK();
            response.sentContenType();
            if (request.getMethod().equals("GET")){
                doGet(request,response);
            }else if (request.getMethod().equals("POST")){
                doPost(request,response);
            }
            response.flush();
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    public void destroy(){

    }
}