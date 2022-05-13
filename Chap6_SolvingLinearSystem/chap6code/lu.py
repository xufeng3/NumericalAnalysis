import numpy as np

def lu(a):
    # l_ii = 1
    n = a.shape[0]
    l = np.zeros(shape=(n,n)).astype(np.float64)
    l += np.diag(np.ones(shape=n))

    u = np.zeros(shape=(n,n)).astype(np.float64)
    u[0, 0] = a[0, 0]/l[0,0]
    for j in range(1,n):
        u[0,j] = a[0,j]/l[0,0]
        l[j,0] = a[j,0]/u[0,0]
    for i in range(1,n-1):
        u[i][i] = (a[i][i]-np.dot(l[i, 0:i],u[0:i, i]))/l[i,i]
        for j in range(i+1, n):
            u[i,j] = (a[i][j]-np.dot(l[i, 0:i],u[0:i, j]))/l[i,i]
            l[j,i] = (a[j][i]-np.dot(l[j, 0:i],u[0:i, i]))/u[i,i]
    u[n-1,n-1] = (a[n-1,n-1] -np.dot(l[n-1, 0:n],u[0:n, n-1]))/l[n-1,n-1]
    print('u',u)
    print('l',l)

    print(np.matmul(l,u))
    return 0


if __name__ == '__main__':
    a = np.array([[1, 1, 0, 3],
                  [2, 1, -1, 1],
                  [3, -1, -1, 2],
                  [-1, 2, 3, -1]]).astype(np.float64)
    lu(a)

    b = np.array([[2.1756,4.0231,-2.1732,5.1967],
[-4.0231,6,0,1.1973],
[-1,-5.2107,1.1111,0],
[6.0235,7,0,-4.1561]]).astype(np.float64)
    lu(b)



