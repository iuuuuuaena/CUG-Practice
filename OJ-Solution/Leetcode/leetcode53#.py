class Solution:
    def maxSubArray(self, nums: list[int]) -> int:
        length=len(nums)
        dp=[0 for i in range(length)]
        dp[0]=nums[0]
        res=nums[0]
        for i in range(length):
            if(dp[i-1]<0):
                continue
            else:
                dp[i]=nums[i]+dp[i-1]
            res=max(res,dp[i])
        return res