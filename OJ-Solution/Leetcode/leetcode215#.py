class Solution:
    def findKthLargest(self, nums, k) :
        mid=nums[len(nums)//2]
        nums.pop(len(nums)//2)
        left=list()
        middle=list()
        right=list()
        for item in nums:
            if item<mid:
                left.append(item)
            elif item==mid:
                middle.append(item)
            else:
                right.append(item)
        if k>=len(right)+1 and k<=len(right)+len(middle)+1:
            return mid
        elif k<=len(right):
            return self.findKthLargest(right,k)
        else:
            return self.findKthLargest(left,k-len(middle)-len(right))
a=Solution()
a.findKthLargest([-1,2,0],2)