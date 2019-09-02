class solution:
    def findKthLargest(self, nums, k):
        length=len(nums)
        if(length<6):
            nums.sort()
            print('sort')
            return nums[length-k]
        l=length//5
        j=0
        li=list()
        for i in range(l):
            temp=list()
            for i in range(5):
                temp.append(nums[j])
                j+=1
            li.append(temp)
        M=list()
        for item in li:
            item.sort()
            M.append(item[2])
        m=self.findKthLargest(M,l//2+1)
        # M.sort()
        # m=M[int(l/2)]
        A=list()
        S1=list()
        S2=list()
        for item in li:
            if item[2]<m:
                S1+=item[:3]
                A+=item[3:]
            elif item[2]>m:
                S2+=item[2:]
                A+=item[:2]
            else:
                S1+=item[:2]
                S2+=item[3:]
        for i in range(length%5):
            temp=nums[5*l+i]
            if(temp<m):
                S1.append(temp)
            else:
                S2.append(temp)
        if k==len(S2)+1:
            return m
        elif k<len(S2):
            return self.findKthLargest(S2,k)
        else:
            return self.findKthLargest(S1,k-len(S2)+1)
nums=[7,6,5,4,3,2,1]
k=2
s=solution()
res=s.findKthLargest(nums,k)
print(res)