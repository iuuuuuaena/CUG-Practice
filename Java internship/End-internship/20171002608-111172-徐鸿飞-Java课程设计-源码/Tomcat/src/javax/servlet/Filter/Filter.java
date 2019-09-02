package javax.servlet.Filter;

import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import java.io.IOException;

/**
 * Filter接口
 */
public interface Filter {
    public void destroy();
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)throws IOException, ServletException;
    public void init(FilterConfig fConfig) throws ServletException;
}
