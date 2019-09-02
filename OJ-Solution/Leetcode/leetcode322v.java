package LeetCode;
import java.lang.Integer;

//public class leetcode322v {
//    public int coinChange(int[] coins, int amount) {
//        int len=coins.length;
//        int[] dp=new int[amount+1];
//        dp[0]=0;
//        for (int i=1;i<amount+1;i++){
//            dp[i]=Integer.MAX_VALUE/2;
//        }
//        for (int i=0;i<len;i++){
//            for (int j=coins[i];j<amount+1;j++){
//                dp[j]=Integer.min(dp[j],dp[j-coins[i]]+1);
//            }
//        }
//        if (dp[amount]>=amount+1){
//            return -1;
//        }
//        return dp[amount];
//    }
//}
public class leetcode322v {
    public int coinChange(int[] coins, int amount) {
        int len=coins.length;
        int[][] dp=new int[len][amount+1];
        dp[0][0]=0;
        for (int i=1;i<amount+1;i++){
            dp[0][i]=Integer.MAX_VALUE/2;
        }
        for (int i=0;i<len;i++){
            for (int j=coins[i];j<amount+1;j++){
                dp[i][j]=Integer.min(dp[i][j],dp[i][j-coins[i]]+1);
            }
        }
        if (dp[len][amount]>=amount+1){
            return -1;
        }
        return dp[len][amount];
    }
}
