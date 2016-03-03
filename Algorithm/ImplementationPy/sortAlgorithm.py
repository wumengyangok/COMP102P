a=[5,6,4,3,32,4,5,6,7,82,3,4,5,6]
b=[2,3,4,1,2,4,5,6,7,8,4,3,2,15]
n=len(a)
def qsort(l,r):
    if l==r:
        return
    i=l
    j=r
    p=i
    while i<=j-1:
        if (a[i]<a[j]):
            a[i],a[p]=a[p],a[i]
            p=p+1
            i=i+1
        else:
            i=i+1
    a[p],a[j]=a[j],a[p]
    if p>l:
        qsort(l,p-1)
    if p<r:
        qsort(p+1,r)


def sort(a):
    for i in range(len(a)-1):
        for j in range(i+1,len(a)):
            if a[i]>a[j]:
                a[i],a[j]=a[j],a[i]
    return a


qsort(0,n-1)
b=sort(b)
print(a)
print(b)


