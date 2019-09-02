package LeetCode;

//两两递归合并
public class leetcode23 {
    public ListNode mergeKLists(ListNode[] lists) {
        int len=lists.length;
        if(lists==null || len==0)return null;
        return fz(lists,0,len-1);
    }
    public ListNode fz(ListNode[] lists,int j,int k){
        if(k>=j)return lists[j];
        int mid=(k-j)/2+j;
        ListNode l1=fz(lists,j,mid);
        ListNode l2=fz(lists,mid+1,k);
        return merge2Lists(l1,l2);
    }
    public ListNode merge2Lists(ListNode l1,ListNode l2){
        if(l1==null)return l2;
        if(l2==null)return l1;
        ListNode p1=l1,p2=l2;
        ListNode current=new ListNode(0);
        ListNode first=current;
        while (p1!=null&&p2!=null){
            if(p1.val<=p2.val){
                current.next=p1;
                p1=p1.next;
                current=current.next;
            }
            else {
                current.next=p2;
                p2=p2.next;
                current=current.next;
            }
        }
        ListNode p=(p1!=null)? p1:p2;
        while (p!=null){
            current.next=p;
            p=p.next;
            current=current.next;
        }
        return first.next;
    }
}
//直接合并版本
class Solution23 {
    public ListNode mergeKLists(ListNode[] lists) {
        int n=lists.length;
        if(n==0)return null;
        ListNode temp;
        int min=2^31-1;
        int index=0;
        boolean end=true;
        for (int i=0;i<n;i++){
            if (lists[i]==null)continue;
            if(min>lists[i].val){
                min=lists[i].val;
                index=i;
            }
            end=false;
        }
        if (end)return null;
        lists[index]=lists[index].next;
        ListNode head=new ListNode(min);
        temp=head;
        while (true){
            min=2^31-1;
            index=0;
            end=true;
            for (int i=0;i<n;i++){
                if (lists[i]==null)continue;
                if(min>lists[i].val){
                    min=lists[i].val;
                    index=i;
                }
                end=false;
            }
            if(end)break;
            if(lists[index]!=null)lists[index]=lists[index].next;
            temp.next=new ListNode(min);temp=temp.next;
        }
        return head;
    }
}

//        int i=0,j=0;
//        while (i<len){
//            if (lists[i]!=null){
//                lists[j++]=lists[i];
//            }
//            i++;
//        }
//        len=j;
//        if(len==0)return null;
//        while (len!=1){
//            int newlen=0;
//            if(len%2==0){
//                for (i=0;i<len;i+=2){
//                    lists[i]=merge2Lists(lists[i],lists[i+1]);
//                }
//                newlen=len/2;
//            }else {
//                for (i=0;i<len-1;i+=2){
//                    lists[i]=merge2Lists(lists[i],lists[i+1]);
//                }
//                lists[len/2]=lists[len-1];
//                newlen=len/2+1;
//            }
//            len=newlen;
//        }