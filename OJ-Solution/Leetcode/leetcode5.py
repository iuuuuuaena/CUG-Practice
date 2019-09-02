class Solution:
    def longestPalindrome(self, s: str) -> str:
        self.length = len(s)
        self.c = [([0] * (self.length+1)) for i in range(self.length+1)]
        self.b = [([0] * (self.length+1)) for i in range(self.length+1)]
        self.res=list()
        self.LCSLength(s, s[::-1])
        self.LCS(self.length,self.length,s)
        return ''.join(self.res)

    def LCSLength(self, x, y):
        for i in range(self.length+1):
            self.c[i][0] = 0
            self.c[0][i] = 0
        for i in range(1, self.length+1):
            for j in range(1, self.length+1):
                if x[i-1] == y[j-1]:
                    self.c[i][j] = self.c[i - 1][j - 1] + 1
                    self.b[i][j] = 1
                elif self.c[i - 1][j] >= self.c[i][j - 1]:
                    self.c[i][j] = self.c[i - 1][j]
                    self.b[i][j] = 2
                else:
                    self.c[i][j] = self.c[i][j - 1]
                    self.b[i][j] = 3
    def LCS(self,i,j,s):
        if i==0 or j==0:return
        if self.b[i][j]==1:
            self.LCS(i-1,j-1,s)
            self.res.append(s[i])
        elif self.b[i][j]==2:
            self.LCS(i-1,j,s)
        else:
            self.LCS(i,j-1,s)
a=Solution()
res=a.longestPalindrome('babad')
print(res)