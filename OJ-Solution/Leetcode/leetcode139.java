package LeetCode;
import java.util.List;
public class leetcode139 {
    public boolean wordBreak(String s, List<String> wordDict) {
        int lens=s.length();
        boolean[] dp=new boolean[lens+1];
        dp[0]=true;
        for (int i=1;i<=lens;i++){
            for (int j=0;j<i;j++){
                if(dp[j]&&wordDict.contains(s.substring(j,i))){
                    dp[i]=true;
                    break;
                }else {
                    dp[i]=false;
                }
            }
        }
        return dp[lens];
    }
}
