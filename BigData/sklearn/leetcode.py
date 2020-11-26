# 1014. 最佳观光组合
class Solution:
    def maxScoreSightseeingPair(self, A: list) -> int:
        res = 0
        cur_max = A[0]
        for i in range(1, len(A)):
            res = max(res, A[i] - i + cur_max)
            cur_max = max(cur_max, A[i] + i)
        return res
