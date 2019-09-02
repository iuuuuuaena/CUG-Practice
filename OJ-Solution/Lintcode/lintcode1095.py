def maximumSwap(num):
    # Write your code here
    s = str(num)
    temp = s
    a = 0
    while temp != '':
        index = 0
        max=0
        for i in range(len(temp)):
            if(eval(temp[i])>=max):
                max = eval(temp[i])
                index=i
        if eval(temp[0]) == max:
            a += 1
            temp = temp[1:]#上一次错了，写反了
        else:
            temp=temp[:index]+temp[0]+temp[index+1:]
            temp=str(max)+temp[1:]
            res=s[0:a]+temp
            return eval(res)
    return eval(s)
res=maximumSwap(931604)
print(res)