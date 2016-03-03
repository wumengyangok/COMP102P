class Heap(object):
    def __init__(self, heap):
        self.heap = heap
        self.length = len(heap)

    def __add__(self, other):
        list.append(self.heap, other)
        self.length += 1

    def __output__(self):
        print(self.heap)

    def __shift_down__(self, index):
        temp = self.heap[index]
        i = index
        j = 2 * i + 1
        n = self.length
        while j < n:
            if (j < n - 1) and (self.heap[j] < self.heap[j+1]):
                j += 1
            if temp < self.heap[j]:
                self.heap[i] = self.heap[j]
                i = j
                j = 2 * j + 1
            else:
                break
        self.heap[i] = temp

    def __build_heap__(self):
        i = self.length / 2
        i = int(i)
        while i >= 0:
            self.__shift_down__(i)
            i -= 1

    def __shift_up__(self):
        index = self.length - 1
        temp = self.heap[index]
        while (int(index / 2) >= 0) and (self.heap[int(index / 2)] < temp):
            self.heap[index] = self.heap[int((index - 1) / 2)]
            if index == 0:
                break
            index = int((index - 1) / 2)
        self.heap[index] = temp


aHeap = Heap([])
for i in range(1, 16):
    aHeap.__add__(i)
aHeap.__build_heap__()
aHeap.__output__()