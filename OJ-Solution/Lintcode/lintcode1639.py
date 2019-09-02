def KSubstring(stringIn, K):
    S=set()
    l=len(stringIn)
    for i in range(l-K+1):
        temp=stringIn[i:i+K]
        if len(temp)==len(set(temp)):
            S.add(temp)
    print(S)
    return len(S)

print(KSubstring("abacabc",3))