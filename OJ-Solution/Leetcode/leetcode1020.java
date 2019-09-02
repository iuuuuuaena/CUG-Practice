package LeetCode;

public class leetcode1020 {
    public boolean canThreePartsEqualSum(int[] A) {
        int sum=0;
        for (int i=0;i<A.length;i++){
            sum+=A[i];
        }
        if (sum%3!=0){
            return false;
        }
        int aim=sum/3;
        int i=0;
        int temp=0;
        while (i<A.length){
            temp+=A[i];
            i++;
            if (temp==aim){
                break;
            }
        }
        if (temp!=aim){
            return false;
        }
        int j=i;
        temp=0;
        while (j<A.length){
            temp+=A[j];
            j++;
            if (temp==aim){
                break;
            }
        }
        if (temp!=aim){
            return false;
        }
        return (i>0&&i<j&&j<A.length);
    }
}
