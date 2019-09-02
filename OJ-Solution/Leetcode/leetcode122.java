package LeetCode;

public class leetcode122 {
    public int maxProfit(int[] prices) {
        if (prices.length==0){//刚开始未考虑
            return 0;
        }
        int min=prices[0];
        int res=0;
        for (int i=1;i<prices.length;i++){
            if (prices[i]>min){
                res+=prices[i]-min;
                min=prices[i];
                continue;
            }
            min=prices[i];
        }
        return res;
    }
}
