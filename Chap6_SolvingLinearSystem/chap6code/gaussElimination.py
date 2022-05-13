import numpy as np



def gauss(a, rounding = 32):
    n = a.shape[0]
    seq = np.arange(n)
    res = np.ones_like(seq).astype(np.float64)
    a = np.round(a, 3)

    for i in range(n-1):
        p = i
        while (a[p, i] == 0):
            p += 1
        if (p==n):
            return "Solution not unique!"
        if not (p==i):
            a[[p, i]]=a[[i, p]] # swap 2 rows
            seq[[p, i]]=seq[[i, p]]
        for j in range(i+1, n):
            a[j] -= a[j][i] / a[i][i] * a[i]

        a = np.round(a, 3)
        # print(a)


    if (a[n - 1][n - 1] == 0):
        return "Solution not unique!"

    res[n-1] = a[n - 1][n] / a[n - 1][n - 1]
    for i in range(n-1, -1, -1):
        tmp = a[i][n]
        for j in range(i+1, n):
            tmp -= a[i][j] * res[j]
        res[i] = tmp / a[i][i]

    # res2 = np.ones_like(res).astype(np.float64)
    # res2[seq] = res
    # print(res2)
    # print(res)
    return res

    # return resSorted


def gauss1(a, rounding = 32):
    n = a.shape[0]
    seq = np.arange(n)
    res = np.ones_like(seq).astype(np.float64)

    a = np.round(a, rounding)

    for i in range(n-1):

        p = np.argmax(abs(a[i:n-1,i]))+i
        if (p==n):
            return "Solution not unique!"
        if not (p==i):
            a[[p, i]]=a[[i, p]] # swap 2 rows
            seq[[p, i]]=seq[[i, p]]
        for j in range(i+1, n):
            a[j] -= a[j][i] / a[i][i] * a[i]

        a = np.round(a, rounding)
        # print(a)

    if (a[n - 1][n - 1] == 0):
        return "Solution not unique!"

    res[n-1] = a[n - 1][n] / a[n - 1][n - 1]


    for i in range(n-1, -1, -1):
        tmp = a[i][n]
        for j in range(i+1, n):
            tmp -= a[i][j] * res[j]
        res[i] = tmp / a[i][i]

    # print(res)
    # print(seq)
    # res2 = np.ones_like(res).astype(np.float64)
    # res2[seq] = res
    # print(res2)
    return res


def gauss2(a, rounding = 32):
    n = a.shape[0]
    seq = np.arange(n)
    res = np.ones_like(seq).astype(np.float64)

    a = np.round(a, rounding)

    for i in range(n-1):
        q = np.max(abs(a[i, i:n-1]))
        p = np.argmax(abs(a[i:n-1,i])/q)+i
        if (p==n):
            return "Solution not unique!"
        if not (p==i):
            a[[p, i]]=a[[i, p]] # swap 2 rows
            seq[[p, i]]=seq[[i, p]]
        for j in range(i+1, n):
            a[j] -= a[j][i] / a[i][i] * a[i]

        a = np.round(a, rounding)
        # print(a)

    if (a[n - 1][n - 1] == 0):
        return "Solution not unique!"

    res[n-1] = a[n - 1][n] / a[n - 1][n - 1]


    for i in range(n-1, -1, -1):
        tmp = a[i][n]
        for j in range(i+1, n):
            tmp -= a[i][j] * res[j]
        res[i] = tmp / a[i][i]

    # print(res)
    # print(seq)
    # res2 = np.ones_like(res).astype(np.float64)
    # res2[seq] = res
    # print(res2)
    return res

if __name__ == '__main__':
    # a = np.array([[1,1,0,3,4],
    #                [2,1,-1,1,1],
    #                 [3,-1,-1,2,-3],
    #                 [-1,2,3,-1,4]]).astype(np.float64)
    # print(gauss1(a))
    #
    # print(gauss(a))
    # print(gauss2(a))


    # p3574c = np.array([[1,1/2,1/3,1/4,1/6],
    #                   [1 / 2, 1 / 3, 1 / 4, 1/5,1/7],
    #                   [1 / 3, 1 / 4, 1/5, 1 / 6, 1/8],
    #                   [ 1 / 4, 1/5, 1 / 6,1/7,1/9]]).astype(np.float64)
    # res = gauss1(p3574c)
    # print(res)
    # print(np.matmul(p3574c[:,0:4],res))
    # print(p3574c[:,4])
    #
    # p3574d = np.array([[2,1,-1,1,-3,7],
    #                    [1,0,2,-1,1,2],
    #                    [0,-2,-1,1,-1,-5],
    #                    [3,1,-4,0,5,6],
    #                    [1,-1,-1,-1,1,3]]).astype(np.float64)
    # res = gauss1(p3574d)
    # print(res)
    # print(np.matmul(p3574d[:,0:5],res))
    # print(p3574d[:,5])


    a = np.array( [[3.03,-12.1,14,-119],
                   [-3.03,12.1,-7,120],
                   [6.11,-14.2,21,-139]]).astype(np.float64)
    res = gauss(a)
    print(res)

    print(gauss(a, 3))
    # res2 = gauss1(a, 3)
    # print(gauss1(a, 3))
    # print(gauss2(a,3))

