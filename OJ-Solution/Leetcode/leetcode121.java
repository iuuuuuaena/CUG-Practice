package LeetCode;
import java.lang.Integer;


public class leetcode121 {
    public int maxProfit(int[] prices) {
        int min=Integer.MAX_VALUE;
        int max=Integer.MIN_VALUE;
        int value=0;
        int temp;
        for (int i=0;i<prices.length;i++){
            temp=min;
            min=Integer.min(min,prices[i]);
            if (temp!=min){
                max=Integer.MIN_VALUE;
            }
            max=Integer.max(max,prices[i]);
            value=Integer.max(value,max-min);
        }
        return value;
    }
}
