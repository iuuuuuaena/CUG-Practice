class Solution:
    def permute(self, nums: list[int]) -> list[list[int]]:
        self.len = len(nums)
        if self.len==1:
            return [nums]
        self.list=list()
        self.per(nums)
        return self.list

    def per(self,nums):
        if len(nums)==1:
            return [[nums[0]]]
        elif self.len==len(nums):
            for i in range(len(nums)):
                temp=self.per(nums[:i]+nums[i+1:])
                for j in temp:
                    self.list.append([nums[i]]+j)
        else:
            a=list()
            for i in range(len(nums)):
                temp=self.per(nums[:i]+nums[i+1:])
                for j in temp:
                    a.append([nums[i]]+j)
            return a
