package javax.servlet.Filter;

import java.util.LinkedList;
import java.util.Queue;

public class FilterConfig {
    Queue<Filter> filter=new LinkedList<>();
    public void add(Filter s){
        filter.offer(s);
    }
    public Filter poll(){
        return filter.poll();
    }
    public boolean isEmpty(){
        return filter.isEmpty();
    }
}
