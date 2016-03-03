class Page(object):
    def __init__(self, father, minn, maxx):
        self.father = father
        self.minimumLeafNumber = minn
        self.maximumLeafNumber = maxx
        self.leaves = []
        self.children = []

    def __getLeaves__(self):
        return self.leaves

    def __getChildren__(self):
        return self.children

    def __addValue__(self, value):
        index = 0
        while index < len(self.leaves) and self.leaves[index] < value:
            index += 1
        self.leaves.insert(index, value)
        return index + 1

    def __addChildren__(self, child, index):
        self.children.insert(index, child)
        if child is not None:
            child.__setFather__(self)

    def __deleteChildren__(self, index):
        self.children.remove(self.children[index])

    def __ifOverFlew__(self):
        return len(self.leaves) > self.maximumLeafNumber

    def __getFather__(self):
        return self.father

    def __setFather__(self, father):
        self.father = father


class BTree(object):
    def __init__(self, n):
        self.n = n
        self.volume = 0
        self.root = None

    def __split__(self, page):
        n = self.n
        father = page.__getFather__()
        leaves = page.__getLeaves__()
        children = page.__getChildren__()
        if father is None:
            father = Page(None, 0, 2 * n)
            father.__addChildren__(self.root.__getChildren__()[0], 0)
            self.root = father

        index = father.__addValue__(page.__getLeaves__()[n])
        left = Page(father, n, n * 2)
        for i in range(0, n):
            left.__addChildren__(children[i], left.__addValue__(leaves[i]))
        left.__addChildren__(children[n], n)
        right = Page(father, n, n * 2)
        for i in range(n + 1, 2 * n + 1):
            right.__addChildren__(children[i], right.__addValue__(leaves[i]) - 1)
        right.__addChildren__(children[2 * n + 1], n)
        
        father.__deleteChildren__(index - 1)
        father.__addChildren__(left, index - 1)
        father.__addChildren__(right, index)

        if father.__ifOverFlew__():
            self.__split__(father)

    def __search__(self, key):
        search = self.root
        while search is not None:
            leaves = search.__getLeaves__()
            index = 0
            while key < leaves[index]:
                index += 1
            if key == leaves[index]:
                return True
            else:
                search = search.__getChildren__()[index]

        return False

    def __add__(self, key):
        if self.volume == 0:
            self.root = Page(None, 0, 2 * self.n)
            self.root.__addValue__(key)
            self.root.__addChildren__(None, 0)
            self.root.__addChildren__(None, 1)
            self.volume += 1
        else:
            if self.__search__(key):
                return
            self.volume += 1
            search = self.root
            while search.children[0] is not None:
                leaves = search.__getLeaves__()
                index = 0
                while index < len(leaves) and key > leaves[index]:
                    index += 1
                search = search.__getChildren__()[index]
            search.__addChildren__(None, search.__addValue__(key))
            if search.__ifOverFlew__():
                self.__split__(search)

# Test B-Tree n = 1
aBTree = BTree(1)
for j in range(1, 10):
    aBTree.__add__(j)
