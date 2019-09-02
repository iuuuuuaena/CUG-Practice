import sys
class Solution:
    def findMedianSortedArrays(self, nums1, nums2):
        len1=len(nums1)
        len2=len(nums2)
        length=len1+len2
        if (length)%2!=0:
            return self.findk(nums1,nums2,length//2+1)
        else:
            return (self.findk(nums1,nums2,length//2)+self.findk(nums1,nums2,length//2+1))/2

    def findk(self, nums1, nums2,k):
        if len(nums1)==0:return nums2[k-1]
        if len(nums2)==0:return nums1[k-1]
        if k==1:
            return min(nums1[0],nums2[0])
        mid1=sys.maxsize
        mid2=sys.maxsize
        if (k+1)//2-1<len(nums1):mid1=nums1[(k+1)//2-1]
        if (k+1)//2-1<len(nums2):mid2=nums2[(k+1)//2-1]#第一次错了，k没有加1
        if mid1==mid2:return mid1
        elif mid1<mid2:
            return self.findk(nums1[k//2:],nums2,k-k//2)
        else:
            return self.findk(nums1,nums2[k//2:],k-k//2)
a=Solution()
print(a.findMedianSortedArrays([1,2],[1,2]))