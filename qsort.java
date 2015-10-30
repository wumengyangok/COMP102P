package com.wumengyangok;

import java.util.Scanner;

/*This file is for the practise in Algorithm*/
public class Main {
    //QuickSort
    public static void qsort(int a[], int l, int r){
        if (l==r)
            return;
        int i=l, j=r;
        int p=i;
        while (i<j){
            if (a[i]<a[j]) {
                int temp=a[i];
                a[i]=a[p];
                a[p]=temp;
                i++;p++;
            }else{
                i++;
            }
        }
        int temp=a[j];
        a[j]=a[p];
        a[p]=temp;
        if(p>l)
            qsort(a,l,p-1);
        if(p<r)
            qsort(a,p+1,r);
    }
    public static void main(String[] args) {
        int n=0;
        Scanner scanner=new Scanner(System.in);
        n=scanner.nextInt();
        int[] array=new int[n];
        for (int i = 0; i <n ; i++) {
            array[i]=scanner.nextInt();
        }
        qsort(array,0,n-1);
        for (int i = 0; i <n ; i++) {
            System.out.print(array[i]+" ");
        }
    }
}
