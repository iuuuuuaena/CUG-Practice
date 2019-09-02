package LeetCode;

public class leetcode1022 {
    public int smallestRepunitDivByK(int K) {
        int i=1;
        int num=1;
        if (K%2==0){
            return -1;
        }
        while (num<Integer.MAX_VALUE){
            if (num%K==0){
                return i;
            }
            i++;
            num=10*num+1;
        }
        return -1;
    }
}
