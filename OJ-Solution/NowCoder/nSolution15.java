package nowcoder;

//class ListNode {
//    int val;
//    ListNode next = null;
//
//    ListNode(int val) {
//        this.val = val;
//    }
//}
public class nSolution15 {
    public ListNode FindKthToTail(ListNode head,int k) {
        if(head==null)return head;
        ListNode p1=head;
        int count=0;
        int i=k;
        while (k--!=0&&p1!=null){
            p1=p1.next;
            count++;
        }
        ListNode p2=head;
        while (p1!=null){
            p1=p1.next;
            p2=p2.next;count++;
        }
        if(count<i)return null;//之前没有保存k，k在上面被修改未发现
        return p2;
    }
}
