R = []
S = []
# G = [[], [2, 5, 6], [1, 3, 4], [2, 5], [2, 6], [1, 3, 6], [1, 4, 5]]
# G = [[], [2, 3], [1, 3], [1, 2, 4], [3]]
G = [[], [2, 3, 4], [1, 3, 4], [1, 2, 4, 5], [1, 2, 3, 5], [3, 4]]

def __reduce_to__(P, v):
    remove_list = []
    for item in P:
        if not G[v].__contains__(item):
            remove_list.append(item)
    for item in remove_list:
        P.remove(item)


def __is_empty__(X):
    if len(X) == 0:
        return True
    else:
        return False


def swarm(P, X):
    global R
    global S
    if (__is_empty__(P)) and (__is_empty__(X)):
        S.append(R)
        R = []
    elif __is_empty__(P):
        R = []
    else:
        while not __is_empty__(P):
            v = P[0]
            RR = R.copy()
            PP = P.copy()
            XX = X.copy()
            R.append(v)
            __reduce_to__(P, v)
            __reduce_to__(X, v)
            swarm(P, X)
            R = RR
            P = PP
            X = XX
            P.remove(v)
            X.append(v)
    return


swarm([1, 2, 3, 4, 5], [])
print(S)
