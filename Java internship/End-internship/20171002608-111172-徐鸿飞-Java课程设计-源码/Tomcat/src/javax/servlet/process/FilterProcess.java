package javax.servlet.process;

import javax.servlet.Filter.Filter;
import javax.servlet.Filter.FilterChain;
import javax.servlet.Filter.FilterConfig;
import javax.servlet.HttpServer;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class FilterProcess {
    public static void process(HttpServletRequest request, HttpServletResponse response){
        FilterConfig filterConfig=new FilterConfig();
        try {
            if (HttpServer.filterMapping.containsKey(request.getUrl())){
                String filterName=HttpServer.filterMapping.get(request.getUrl());
                String value=HttpServer.filterMap.get(filterName);
                Class<?> clazz=Class.forName(value);
                Filter filter=(Filter)clazz.getConstructor().newInstance();

            }
            if (HttpServer.filterMapping.containsKey("/*")){
                String filterName=HttpServer.filterMapping.get("/*");
                String value=HttpServer.filterMap.get(filterName);
                Class<?> clazz=Class.forName(value);
                Filter filter=(Filter)clazz.getConstructor().newInstance();
                filterConfig.add(filter);
            }
            request.setFilterConfig(filterConfig);
            Filter filter=filterConfig.poll();
            filter.doFilter(request,response,new FilterChain());
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
