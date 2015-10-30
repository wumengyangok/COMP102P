package com.wumengyangok.java;

import com.sun.corba.se.spi.orbutil.fsm.Input;
import com.sun.tools.doclets.internal.toolkit.util.DocFinder;

import java.util.Scanner;
public class Main{
    static int[] dist=new int[100];
    static boolean[] visit=new boolean[100];
    static int numN=0,numE=0;
    static int startNode=0;
    public static int findNearest(){
        int nearestNode=0;
        int min=100000;
        for (int i = 0; i <numN ; i++) {
            if ((!visit[i]) && (dist[i] < min)) {
                nearestNode = i;
                min = dist[i];
            }
        }
        return nearestNode;
    }
    public static void dijkstra(Node[] node){
        int c=numN;
        while (c>0){
            int near=findNearest();
            visit[near]=true;
            for (int i = 1; i <=node[near].numNeighbor ; i++) {
                if((!visit[node[near].nameNeighbor[i]])&&(node[near].weight[i]+dist[near]<dist[node[near].nameNeighbor[i]]))
                    dist[node[near].nameNeighbor[i]]=node[near].weight[i]+dist[near];
            }
            c--;
        }
    }
	public static void main(String[] args) {
        //DijkstraJava
        System.out.print("Please input the number of nodes, edges and beginner:");
        //Input input=new Input();
        Scanner scanner=new Scanner(System.in);
        numN=scanner.nextInt();
        numE=scanner.nextInt();
        startNode=scanner.nextInt();
        Node[] node=new Node[numN];
        for (int i = 0; i <numN ; i++) {
            node[i]=new Node();
        }

        for (int i = 0; i <numE ; i++) {
            int start,end,weight;
            start=scanner.nextInt();
            end=scanner.nextInt();
            weight=scanner.nextInt();
            node[start].numNeighbor++;
            node[start].nameNeighbor[node[start].numNeighbor]=end;
            node[start].weight[node[start].numNeighbor]=weight;
        }
        for (int i = 0; i <numN ; i++) {
            if(i!=startNode){
                visit[i]=false;
                dist[i]=10000;
            }else{
                visit[i]=false;
                dist[i]=0;
            }
        }

        dijkstra(node);
        for (int i = 0; i <numN ; i++) {
            System.out.print(dist[i] + " ");
        }
    }
}
