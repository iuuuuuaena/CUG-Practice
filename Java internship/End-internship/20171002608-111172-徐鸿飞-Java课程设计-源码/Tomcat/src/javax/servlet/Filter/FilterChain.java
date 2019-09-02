package javax.servlet.Filter;

import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.process.HttpProcess;
import java.io.IOException;
import java.rmi.server.ExportException;

/**
 * 过滤链
 */
public class FilterChain{
    /**
     *
     * @param request 链接的HttpServletRequest对象
     * @param response 链接的HttpServletResponse对象
     * @throws IOException
     * @throws ServletException
     */
    public void doFilter(ServletRequest request, ServletResponse response)throws IOException, ServletException {
        HttpServletRequest request1=(HttpServletRequest)request;
        if (request1.isEmpty()){
            HttpProcess.process(request1, (HttpServletResponse)response);
        }else {
            Filter filter=request1.poll();
            filter.doFilter(request,response,new FilterChain());
        }
    }
}
