package javax.servlet.process;

import javax.servlet.*;
import javax.servlet.http.*;


import javax.servlet.http.HttpServlet;

import java.io.File;

public class ServletProcess {
    public ServletProcess(){

    }

    /**
     * 处理链接为Servlet的请求
     * @param request 链接的HttpServletRequest对象
     * @param response 链接的HttpServletResponse对象
     */
    public void process(HttpServletRequest request, HttpServletResponse response){
        try {
            if (HttpServer.servletMapping.containsKey(request.getUrl())){
                String servletName=HttpServer.servletMapping.get(request.getUrl());
                String value=HttpServer.servletMap.get(servletName);
//                System.out.println(servletName);
                if (exists(servletName+".class")||!servletName.contains("_jsp")){
                    Class<?> clazz=Class.forName(value);
                    HttpServlet servlet=(HttpServlet)clazz.getDeclaredConstructor().newInstance();
                    servlet.init();
                    TomcatUI.addLog("ServletProcess类:reflection:"+value);
                    servlet.service(request,response);
                }else {
//                    System.out.println("ServletProcess类:go to DynamicCompilation");
                    TomcatUI.addLog("ServletProcess类:go to DynamicCompilation");
                    DynamicCompilation dynamicCompilation=new DynamicCompilation(servletName+".java");
                    dynamicCompilation.process(request,response);
                }
            }else {
//                System.out.println("ServletProcess-accessStaticResources");
                TomcatUI.addLog("ServletProcess-accessStaticResources");
                response.accessStaticResources();
            }
        }catch (Exception e){
//            TomcatUI.addLog(e.toString());
            e.printStackTrace();
        }
    }
    private boolean exists(String path){
        File f=new File(DynamicCompilation.CLASS_PATH+"/"+path);
//        File f2=new File(DynamicCompilation.JAVA_PATH+"\\"+path);
//        System.out.println(f.getPath());
        if (f.exists()){
            return true;
        }else return false;
    }
}
