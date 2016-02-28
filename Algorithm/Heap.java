package com.wumengyangok;

/**
 * Created by wumengyang on 26/02/2016.
 */
public class Heap {

    private int[] heap;
    private int length;
    private int maximum;

    Heap(int maximumLength) {
        this.maximum = maximumLength;
        heap = new int[maximum];
        length = 0;
    }

    private void downAdjust(int index) {

        int temp = heap[index];
        while((index * 2 + 1 <= length) && ((temp < heap[index * 2]) || (temp < heap[index * 2 + 1]))) {
            if (heap[index * 2] > heap[index * 2 + 1]) {
                heap[index] = heap[index * 2];
                index = index * 2;
            } else {
                heap[index] = heap[index * 2 + 1];
                index = index * 2 + 1;
            }
        }
        if (index * 2 == length) {
            if (temp < heap[length]) {
                heap[index] = heap[length];
                heap[length] = temp;
            } else {
                heap[index] = temp;
            }
        } else {
            heap[index] = temp;
        }

    }

    public void buildHeap() {
        for (int i = length / 2; i >= 1; i--) {
            downAdjust(i);
        }
    }

    public void addToTail(int newOne) {
        length++;
        try {
            heap[length] = newOne;
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Out of bound");
        }

    }

    public void addAndMaintainHeap(int newOne) {

        addToTail(newOne);
        int index = length;
        int temp = heap[index];
        while ((index / 2 > 0) && (heap[index / 2] < temp)) {
            heap[index] = heap[index / 2];
            index = index / 2;
        }
        heap[index] = temp;

    }

    public void sort() {

        int saveLength = length;
        buildHeap();
        for (int i = saveLength; i >= 1; i--) {
            int temp = heap[1];
            heap[1] = heap[length];
            heap[length] = temp;
            length--;
            downAdjust(1);
        }
        length = saveLength;

    }

    public void output() {
        for (int i = 1; i <= length; i++) {
            System.out.printf("%d ",heap[i]);
        }
        System.out.println();
    }

}
