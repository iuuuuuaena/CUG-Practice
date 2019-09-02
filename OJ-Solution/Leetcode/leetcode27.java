package LeetCode;

public class leetcode27 {
    public int removeElement(int[] nums,int val){
        int len=nums.length;
        int pos=len-1;
        for(int i=0;i<len;i++){
            if(nums[i]==val){
                while (pos>=0&&nums[pos]==val){//不能反
                    pos-=1;
                }
                if(pos>i){//需要判断
                    nums[i]=nums[pos];
                    pos-=1;
                }
                else {
                    break;
                }
            }
        }
        return pos+1;
    }
}
