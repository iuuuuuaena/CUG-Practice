package LeetCode;
/*
给定一个字符串 (s) 和一个字符模式 (p)。实现支持 '.' 和 '*' 的正则表达式匹配。
'.' 匹配任意单个字符。
'*' 匹配零个或多个前面的元素。
 */
import java.lang.String;
//public class leetcode10 {
//    public boolean isMatch(String s, String p) {
//        if (s.equals(p)){
//            return true;
//        }
//        int len_s=s.length();
//        int len_p=p.length();
//        if (len_s==0&&len_p!=0){
//            return false;
//        }
//        if (len_s>len_p){
//            return false;
//        }
//        boolean dp[][]=new boolean[len_s][len_p];
//        if (p.charAt(0)!='.'&&s.charAt(0)!=p.charAt(0)){
//            return false;
//        }
//        dp[0][0]=true;
//        int i,j;
//        boolean temp;
//        for(i=1;i<len_s;i++) {
//            for (j = i - 1; j >=0; j--) {
//                dp[i][j] = false;
//            }
//        }
//        for(i=1;i<len_s;i++){
//            for (j=i;j<len_p;j++){
//                if (p.charAt(j)=='.'){
//                    dp[i][j]=dp[i-1][j-1];
//                }else if(p.charAt(j)=='*'){
//                    if (p.charAt(j-1)!='.'&&p.charAt(j-1)!=s.charAt(i)){
//                        temp=false;
//                    }else {
//                        temp=true;
//                    }
//                    dp[i][j]=dp[i][j-1]||temp;
//                    if(j>=2){
//                        dp[i][j]=dp[i][j]||dp[i][j-2];
//                    }
//                }else {
//                    dp[i][j]=dp[i-1][j-1]&&(s.charAt(i)==p.charAt(j));
//                }
//            }
//        }
//        return dp[len_s-1][len_p-1];
//    }
//}
public class leetcode10 {
    public boolean isMatch(String s, String p) {
        int len_s=s.length();
        int len_p=p.length();
        if (len_s==0&&len_p==0){
            return false;
        }
        boolean dp[][]=new boolean[len_s+1][len_p+1];
        dp[0][0]=true;
        for (int i=0;i<len_p;i++){
            if(p.charAt(i)=='*'&&dp[0][i-1]){
                dp[0][i+1]=true;
            }
        }
        int i,j;
        for(i=1;i<=len_s;i++){
            for (j=1;j<=len_p;j++){
                if (p.charAt(j)=='.'){
                    dp[i][j]=dp[i-1][j-1];
                }else if(p.charAt(j)=='*'){
                    if (p.charAt(j-1)!=s.charAt(i)&&p.charAt(j-1)!='.'){
                        dp[i][j]=dp[i][j-2];
                    }else {
                        dp[i][j]=(dp[i][j-1]||dp[i-1][j]||dp[i][j-2]);
                    }
                }else {
                    dp[i][j]=dp[i-1][j-1]&&(s.charAt(i)==p.charAt(j));
                }
            }
        }
        return dp[len_s][len_p];
    }
}