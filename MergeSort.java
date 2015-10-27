package com.wumengyangok;

import java.util.Scanner;

//MergeSort
public class Main {
    public static void merge(int front,int end,int head,int tail,int[] a){
        int[] temp= new int[tail-front+1];
        int i=front, j=head, n=0;
        while (!((i==0)&&(j==0))){
            if(a[i]<a[j]){
                temp[n]=a[i];
                n++;i++;
                if(i>end) i=0;
            }else {
                temp[n]=a[j];
                n++;j++;
                if(j>tail) j=0;
            }
        }
        n=0;
        for (int k = front; k <=tail ; k++) {
            a[k]=temp[n];
            n++;
        }
    }
    public static void mergeSort(int front, int end, int[] a){
        if(front==end) return;
        else {
            int k=(front+end)/2;
            mergeSort(front,k,a);
            mergeSort(k+1,end,a);
            merge(front,k,k+1,end,a);
        }
    }
    public static void main(String[] args) {
        int n=0;
        Scanner scanner=new Scanner(System.in);
        n=scanner.nextInt();
        int[] a=new int[n+1];
        for (int i = 1; i <=n ; i++) {
            a[i]=scanner.nextInt();
        }
        a[0]=Integer.MAX_VALUE;
        mergeSort(1,n,a);
        for (int i = 1; i <=n ; i++) {
            System.out.print(a[i]+" ");
        }
    }
}
