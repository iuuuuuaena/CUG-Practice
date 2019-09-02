package LeetCode;



/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class leetcode19 {
    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode p1=head;
        for (int i=0;i<n;i++){
            p1=p1.next;
        }
        ListNode p2=head;
        if (p1!= null){
            p1=p1.next;
        }else {
            return head.next;
        }
        while (p1!=null){
            p1=p1.next;
            p2=p2.next;
        }
        p2.next=p2.next.next;
        return head;
    }
}