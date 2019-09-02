package LeetCode;

public class leetcode283 {
    public void moveZeroes(int[] nums) {
        int len=nums.length;
        int i;
        for(i=0;i<len;i++){
            if(nums[i]==0)break;
        }
        int j=i;
        while (i<len){
            if (nums[i]!=0){
                nums[j++]=i;
            }
            i++;
        }
        while (j<len){
            nums[j++]=0;
        }
    }
}
