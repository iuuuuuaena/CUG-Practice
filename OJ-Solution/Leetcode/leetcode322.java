package LeetCode;

import java.util.Arrays;

public class leetcode322 {
    public int coinChange(int[] coins, int amount) {
        if(amount==0){
            return 0;
        }
        int len=coins.length;
        if(len==0){
            return -1;
        }
        if(len==1){
            if(amount%coins[0]==0){
                return amount/coins[0];
            }
            else{
                return -1;
            }
        }
        int newLen=0;
        for(int i=0;i<len;i++){
            int temp=amount/coins[i];
            newLen+=temp;
        }
        int[] new_coins=new int[newLen];
        int j=0;
        for(int i=0;i<len;i++){
            int temp=amount/coins[i];
            for (int k=0;k<temp;k++){
                new_coins[j]=coins[i];
                j++;
            }
        }
        int[][] dp=new int[newLen][amount+1];
        int[][] arr=new int[newLen][amount+1];
        for(int i=0;i<newLen;i++){
            Arrays.fill(arr[i],0);
        }
        dp[0][0]=0;
        for (int i=1;i<amount+1;i++){
            dp[0][i]=Integer.MIN_VALUE;
        }
        for (int i=1;i<newLen;i++){
            for (j=new_coins[i];j<amount+1;j++){
                if(dp[i-1][j]>dp[i-1][j-new_coins[i]]+new_coins[i]){
                    dp[i][j]=dp[i-1][j];
                    arr[i][j]=arr[i-1][j];
                }else {
                    dp[i][j]=dp[i-1][j-new_coins[i]]+new_coins[i];
                    arr[i][j]=arr[i-1][j-new_coins[i]]+1;
                }
            }
        }
        if (dp[newLen-1][amount]!=amount){
            return -1;
        }else {
            return arr[newLen-1][amount];
        }
    }
}
