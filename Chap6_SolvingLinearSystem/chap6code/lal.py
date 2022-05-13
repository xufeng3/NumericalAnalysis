import numpy as np

def ldl(a):
    n = a.shape[0]
    l = np.zeros(shape=(n,n)).astype(np.float64)
    l += np.diag(np.ones(shape=n))
    d = np.zeros(shape=n).astype(np.float64)
    v = np.zeros(shape=n).astype(np.float64)

    for i in range(n):
        for j in range(i):
            v[j] = l[i,j]*d[j]
        d[i] = a[i,i]-np.dot(v[0:i],l[i,0:i])
        for j in range(i+1, n):
            l[j,i]=(a[j,i]-np.dot(l[j,0:i],v[0:i]))/d[i]

    print(l)
    print(d)


def ll(a):
    n = a.shape[0]
    l = np.diag(np.sqrt(np.diag(a)))
    l[1:n, 0] = a[1:n, 0]/l[0,0]
    print(l)
    for i in range(1,n-1):
        l[i,i]=np.sqrt(a[i,i]-np.dot(l[i,0:i],l[i,0:i]))
        for j in range(i+1, n):
            l[j,i]=(a[j,i]-np.dot(l[j,0:i],l[i,0:i]))/l[i,i]
    l[n-1,n-1]= np.sqrt(a[n-1,n-1]-np.dot(l[n-1,0:n-1],l[n-1,0:n-1]))
    print(l)


if __name__ == '__main__':
    a = np.array([[4,-1,1],
                  [-1,4.25,2.75],
                  [1,2.75,3.5]]).astype(np.float64)
    ll(a)

    c = np.array(
[[6,2,1,-1],
[2,4,1,0],
[1,1,4,-1],
[-1,0,-1,3]]).astype(np.float64)
    ldl(c)
    ll(c)
