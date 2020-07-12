import sys, resource
resource.setrlimit(resource.RLIMIT_STACK, (2**29,-1))
sys.setrecursionlimit(10**6)
f=open(sys.argv[1],"r")
map0=f.read().split("\n")
f.close()
f=open(sys.argv[2],"r")
rules=f.read().split("\n")
f.close()
gen1=int(sys.argv[3])
ruleCount=len(rules)
column=len(map0[0])
row=len(map0)    


def froblinator(operator,control,froblin):
    if operator=="=":
        return froblin==control
    elif operator==">":
        return froblin>control
    else:
        return froblin<control



def answer(map1,rules,gen):
    L=[[] for i in range(0,row)]
    for i in range(0,row):
        if i==0:
            imin=0
        else:
            imin=i-1
        if i==row-1:
            imax=i
        else:
            imax=i+1
        for j in range(0,column):
            if j==0:
                jmin=0
            else:
                jmin=j-1
            if j==column-1:
                jmax=j
            else:
                jmax=j+1


            cell=map1[i][j]
            froblin=0
            if map1[i][j]=="*":
                froblin-=1
            for irange in range(imin,imax+1):
                for jrange in range(jmin,jmax+1):
                    if map1[irange][jrange]=="*":
                        froblin+=1


            for ruler in range(0,ruleCount):
                if rules[ruler][0]==map1[i][j]:
                    if froblinator(rules[ruler][1],int(rules[ruler][2]),froblin):
                        cell=rules[ruler][3]
            L[i].append(cell)


    if gen==1:
        return L
    if L==map0:
        return L
    else:
        return answer(L,rules,gen-1)


if gen1==0:
    x=""
    for i in map0:
        x+=i+"\n"
    x=x[:-1]
else:
    L=answer(map0,rules,gen1)
    x=""
    for i in L:
        for j in i:
            x+=j
        x+="\n"
    x=x[:-1]

print x