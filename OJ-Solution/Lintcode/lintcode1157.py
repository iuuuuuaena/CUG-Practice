def findUnsortedSubarray(nums):
    #nums=[2, 6, 4, 8, 10, 9, 15]
    numsold=nums[:]
    nums.sort()
    res=0
    length=len(nums)
    i=0
    while numsold[i]==nums[i]:
        res+=1
        i+=1
        if(length==i):
            return 0
    i=1
    while numsold[-i]==nums[-i]:
        res+=1
        i+=1
    return length-res
findUnsortedSubarray([2, 6, 4, 8, 10, 9, 15])