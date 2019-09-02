package javax.servlet.http;

import java.io.InputStream;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import javax.servlet.Filter.Filter;
import javax.servlet.Filter.FilterConfig;
import javax.servlet.process.RequestDispatcher;
import javax.servlet.ServletRequest;
import javax.servlet.process.TomcatUI;

/**
 * HttpServletRequest类
 * @author 徐鸿飞
 * @version 2.2
 */
public class HttpServletRequest extends ServletRequest {
    private String url="";
    private String method="";
    private Map<String,String> postMap=new HashMap<>();
    private Map<String,String> attributeMap=new HashMap<>();
    private Map<String,String> headerMap=new HashMap<>();
    private InputStream in;
    private String content;
    private HttpSession session=new HttpSession();
    private FilterConfig filterConfig;

    /**
     * HttpServletRequest的构造函数，将输入流的内容读到一个字符串
     * @param in 传入socket的输入流
     * @throws Exception
     *
     */
    public HttpServletRequest(InputStream in)throws Exception{
        this.in=in;
        try {
            StringBuffer stringBuffer=new StringBuffer();
            byte[] bytes=new byte[1024];
            int len=in.read(bytes);
            for (int i=0;i<len;++i){
                stringBuffer.append((char)bytes[i]);
            }
            content=stringBuffer.toString();
//            System.out.println(content);
        }catch (Exception e){
//            TomcatUI.addLog(e.toString());
            e.printStackTrace();
        }
        parse();
    }

    /**
     * 将读到的字符串进行解析
     */
    private void parse(){
        if (content.split("\\s").length>1){
            method=content.split("\\s")[0];
            url=content.split("\\s")[1];
            if (url.contains("?")){
                String[] strings=url.split("\\?");
                url=strings[0];
                if (strings[1].contains("&")){
                    String[] ss=strings[1].split("&");
                    for (String s1:ss){
                        if (s1.split("=").length>1){
                            postMap.put(s1.split("=")[0],s1.split("=")[1]);
                        }else {
                            postMap.put(s1.split("=")[0],"");
                        }
                    }
                }else {
                    if (strings[1].split("=").length>1){
                        postMap.put(strings[1].split("=")[0],strings[1].split("=")[1]);
                    }else {
                        postMap.put(strings[1].split("=")[0],"");
                    }
                }
            }
//        System.out.println(method+":"+url);
            TomcatUI.addLog(method+":"+url);
            String[] strings=content.split("\n");
            for (String s:strings){
                if (s.contains(":")){
                    headerMap.put(s.split(":")[0],s.split(":")[1]);
                }
            }
            if (strings[strings.length-1].contains("&")){
                String s=strings[strings.length-1];
                String[] ss=s.split("&");
                for (String s1:ss){
                    if (s1.split("=").length>1){
                        postMap.put(s1.split("=")[0],s1.split("=")[1]);
                    }else {
                        postMap.put(s1.split("=")[0],"");
                    }
                }
            }
        }
    }

    /**
     *
     * @return 请求的url
     */
    public String getUrl(){
        return url;
    }

    /**
     *
     * @return 请求的method
     */
    public String getMethod(){
        return method;
    }

    /**
     * 获取参数
     * @param s 参数名
     * @return 参数值
     */
    public String getParameter(String s){
        return postMap.get(s);
    }

    /**
     * 获取属性
     * @param s 属性名
     * @return 属性值
     */
    public String getAttribute(String s){
        return attributeMap.get(s);
    }

    /**
     * 设置属性
     * @param key 属性名
     * @param value 属性值
     */
    public void setAttribute(String key,String value){
        attributeMap.put(key, value);
    }

    /**
     * 获取HttpSession对象
     * @return 一个HttpSession对象
     */
    public HttpSession getSession(){
        //TODO
        return session;
    }

    /**
     * 返回请求给出的所有HTTP头标名称的枚举值
     * @return
     */
    public Enumeration<String> getHeaderNames(){
        Enumeration<String> headerNames;
        Vector<String> vector=new Vector<>();
        vector.addAll(headerMap.keySet());
        headerNames=vector.elements();
        return headerNames;
    }

    /**
     * 返回指定的HTTP头标
     * @param s 头标名
     * @return 头标值
     */
    public String getHeader(String s){
        return headerMap.get(s);
    }

    /**
     * 获取RequestDispatcher对象进行请求转发
     * @param s 转发的url
     * @return RequestDispatcher对象
     */
    public RequestDispatcher getRequestDispatcher(String s){
        //TODO
        return new RequestDispatcher(s);
    }

    /**
     * 设置url
     * @param url
     */
    public void setUrl(String url) {
        this.url = url;
    }

    /**
     * 设置方法
     * @param method
     */
    public void setMethod(String method) {
        this.method = method;
    }

    /**
     * 设置需要的Filter
     * @param filterConfig
     */
    public void setFilterConfig(FilterConfig filterConfig) {
        this.filterConfig = filterConfig;
    }
    public Filter poll(){
        return filterConfig.poll();
    }
    public boolean isEmpty(){
        return filterConfig.isEmpty();
    }
}