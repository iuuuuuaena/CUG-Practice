package javax.servlet.http;

import java.util.HashMap;
import java.util.Map;

public class HttpSession {
    Map<String,String> attributeMap=new HashMap<>();

    /**
     * 获取指定属性
     * @param s
     * @return
     */
    public Object getAttribute(String s){
        return attributeMap.get(s);
    }

    /**
     * 设置属性
     * @param key
     * @param value
     */
    public void setAttribute(String key,String value){
        attributeMap.put(key, value);
    }
}
