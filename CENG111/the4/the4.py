def translation(L,maxy):
    for i in L[1:]:
        if type(i)==int:
            if i>maxy:
                maxy=i
        if type(i)==list:
            i,kontrol=translation(i,0)
            if kontrol>maxy:
                maxy=kontrol
    if type(L[1])!=int:
        L.insert(1,maxy)
    return L,maxy

def answer(L,L1,upperLimit):
    x=upperLimit
    for i in L:
        if type(i)==str:
            if L[1]<x:
                L1.append([L[0],L[1]])
                x=L[1]
        elif type(i)==list:
            L1=answer(i,L1,x)
    return L1

def chalchiuhtlicue(L):
    L,a=translation(L,0)
    L1=[[] for i in range(L[1])]
    L2=answer(L,[],999999999999999999999999999999999999999999999999999999999999999999)
    for i in L2:
        L1[i[1]-1].append(i[0])
    return L1