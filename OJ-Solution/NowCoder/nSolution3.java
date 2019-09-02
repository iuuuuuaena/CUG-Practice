package nowcoder;
import java.util.ArrayList;
import java.util.Stack;

public class nSolution3 {
    public ArrayList<Integer> printListFromTailToHead(ListNode listNode) {
        Stack<Integer> s=new Stack<>();
        ArrayList<Integer> arry=new ArrayList<>();
        while (listNode!=null){
            s.push(listNode.val);
            listNode=listNode.next;
        }
        while (!s.empty()){
            arry.add(s.pop());
        }
        return arry;
    }
}
