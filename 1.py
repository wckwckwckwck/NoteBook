import math

p = 1
for i in range(1,11):
# 000
    s1 =0
    s2 =0
    for i in range(1,p+1):
        s1 += math.sqrt(i)
        s2 += 1/math.sqrt(i)

    s = s1*s2/p/p 
    p=p*10
    print(str(p)+" " +str(s) )