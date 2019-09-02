def dataSegmentation(str):
    length=len(str)
    res=list()
    i=0
    while i<length:
        if str[i]==' ':
            i+=1
            continue
        elif str[i]>='a' and str[i]<='z':
            temp=str[i]
            i+=1
            if i<length:
                while str[i]>='a' and str[i]<='z':
                    temp=temp+str[i]
                    i+=1
                    if i>=length:
                        break
            res.append(temp)
        else:
            res.append(str[i])
            i+=1
    return res