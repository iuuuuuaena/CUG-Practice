package javax.servlet.process;

import javax.servlet.HttpServer;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * 转发请求
 */
public class RequestDispatcher {
    private String jsp_path="";
    public RequestDispatcher(String s){
        this.jsp_path= "/"+s;
    }
    public void forward(HttpServletRequest request, HttpServletResponse response){
        //TODO
        request.setUrl(jsp_path);
        HttpProcess.process(request,response);
    }
    public void setJsp_path(String jsp_path) {
        this.jsp_path = jsp_path;
    }
}
