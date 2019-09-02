package LeetCode;

public class leetcode10v {
    public boolean isMatch(String s, String p) {
        int lens = s.length(), lenp = p.length();
        boolean[][] dp = new boolean[lens+1][lenp+1];
        dp[0][0] = true;
        boolean temp;
        for(int i = 0; i <= lens; i++) {
            for(int j = 1; j <= lenp; j++) {
                if(p.charAt(j-1) == '*') {

                    dp[i][j] = dp[i][j-2] || (i > 0 && (s.charAt(i-1) == p.charAt(j-2) ||
                            p.charAt(j-2) == '.') && dp[i-1][j]);
                }else {
                    dp[i][j] = i > 0 && (s.charAt(i-1) == p.charAt(j-1) || p.charAt(j-1) == '.')
                            && dp[i-1][j-1];
                }
            }
        }
        return dp[lens][lenp];
    }
}
