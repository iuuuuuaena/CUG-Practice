package LeetCode;

public class leetcode204 {
    public int countPrimes(int n) {
        int count=0;
        for (int i=0;i<n;i++){
            if (isPrimes(i))count++;
        }
        return count;
    }
    public boolean isPrimes(int a){
        int b=(int)Math.sqrt(a);
        for (int i=0;i<b;i++){
            if (a%i!=0)return false;
        }
        return true;
    }
}
