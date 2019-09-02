class Solution:
    def permuteUnique(self, nums: list[int]) -> list[list[int]]:
        self.len=len(nums)
        if self.len==1:
            return [nums]
        self.list=list()
        self.per(nums)
        return self.list

    def per(self,nums):
        if len(nums)==1:
            return [[nums[0]]]
        elif self.len==len(nums):
            s1=set()
            for i in range(len(nums)):
                oldlen=len(s1)
                s1.add(nums[i])
                newlen=len(s1)
                if newlen>oldlen:
                    temp=self.per(nums[:i]+nums[i+1:])
                    for j in temp:
                        self.list.append([nums[i]]+j)
        else:
            a=list()
            s2=set()
            for i in range(len(nums)):
                oldlen=len(s2)
                s2.add(nums[i])
                newlen=len(s2)
                if newlen>oldlen:
                    temp=self.per(nums[:i]+nums[i+1:])
                    for j in temp:
                        a.append([nums[i]]+j)
            return a