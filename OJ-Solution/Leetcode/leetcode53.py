class Solution:
    def maxSubArray(self, nums: list[int]) -> int:
        length=len(nums)
        if length==1:
            return nums[0]
        else:
            return self.maxSub(nums,0,length-1)
    def maxSub(self,nums,left,right):
        if(left==right):
            return nums[left]
        mid=(right-left)//2+left
        sumL=self.maxSub(nums,left,mid)
        sumR=self.maxSub(nums,mid+1,right)
        maxL=nums[mid]
        temp=maxL
        for i in range(mid):
            temp+=nums[mid-i-1]
            if temp>maxL:
                maxL=temp
        maxR=nums[mid+1]
        temp=maxR
        for i in range(mid+2,right+1):
            temp+=nums[i]
            if temp>maxR:
                maxR=temp
        sum=maxL+maxR
        if sumL>sum:
            sum=sumL
        if sumR>sum:
            sum=sumR
        return sum