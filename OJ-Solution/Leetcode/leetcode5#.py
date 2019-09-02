# if(s[i]==s[i+1]):
#     dp[i][i+1]=True
# elif:
#     dp[i][i+1]=False
# class Solution:
#     def longestPalindrome(self, s):
#         l = len(s)
#         if l == 0 or l == 1:
#             return s
#         res = s[0]
#         res2 = ''
#         dp = [([0] * l) for i in range(l)]
#         for i in range(l - 1):
#             dp[i][i] = True
#             if (s[i] == s[i + 1]):
#                 dp[i][i + 1] = True
#                 res2 = s[i:i + 2]
#             else:
#                 dp[i][i + 1] = False
#         dp[l - 1][l - 1] = True
#         step = 3
#         run = True
#         while run:
#             if (step > l):
#                 break
#             run = False
#             for i in range(0,l - step):
#                 if s[i] == s[i + step - 1]:
#                     dp[i][i + step - 1] = dp[i + 1][i + step - 2]
#                     run = True
#                     res = s[i:i + step]
#                 else:
#                     dp[i][i + step - 1] = False
#                 if s[i] == s[i + step]:
#                     dp[i][i + step] = dp[i + 1][i + step - 1]
#                     run = True
#                     res = s[i:i + step+1]
#                 else:
#                     dp[i][i + step] = False
#             if s[l - 1] == s[l - step] and dp[l-step+1][l-2]:
#                 dp[l - step][l - 1] = True
#                 res2 = s[l - step:l]
#                 if run == False:
#                     break
#             else:dp[l - step][l - 1] = False
#             step += 2
#         if len(res) > len(res2):
#             return res
#         else:
#             return res2
class Solution:
    def longestPalindrome(self, s):
        l = len(s)
        if l == 0 or l == 1:
            return s
        res = s[0]
        dp = [([0] * l) for i in range(l)]
        for i in range(l - 1):
            dp[i][i] = True
            if (s[i] == s[i + 1]):
                dp[i][i + 1] = True
                res2 = s[i:i + 2]
            else:
                dp[i][i + 1] = False
        dp[l - 1][l - 1] = True
        step = 3
        run = True
        while True:
            if (step > l):
                break
            for i in range(l - step+1):
                if s[i] == s[i + step - 1] and dp[i + 1][i + step - 2]:
                    dp[i][i + step - 1] = True
                    res = s[i:i + step]
                else:
                    dp[i][i + step - 1] = False
            step += 1
        return res
a=Solution()
print(a.longestPalindrome('babadada'))