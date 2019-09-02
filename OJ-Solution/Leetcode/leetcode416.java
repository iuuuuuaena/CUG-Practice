package LeetCode;
import java.lang.Integer;
public class leetcode416 {
    public boolean canPartition(int[] nums) {
        int sum=0;
        int len=nums.length;
        for (int i=0;i<len;i++){
            sum+=nums[i];
        }
        if (sum%2!=0){
            return false;
        }
        int aims=sum/2;//背包的重量
        int[][] dp=new int[len][aims+1];
        dp[0][0]=0;
        for (int i=1;i<aims+1;i++){
            dp[0][i]=Integer.MIN_VALUE;
        }
        for (int i=1;i<len;i++){
            for(int j=nums[i];j<=aims;j++){
                dp[i][j]=Integer.max(dp[i-1][j],dp[i-1][j-nums[i]]+nums[i]);
            }
        }
        return dp[len-1][aims]==aims;
    }
}
