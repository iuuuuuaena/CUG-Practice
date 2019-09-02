package LeetCode;


import java.util.Arrays;

public class leetcode169 {
    public int majorityElement(int[] nums) {
        Arrays.sort(nums);
        return nums[nums.length/2];
    }
}
