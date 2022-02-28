#include "the2.h"

//You may write your own helper functions here

long absDiff(long x,long y){
    if((int)x-y>=0)return x-y;
    return y-x;
}

void qhelper(unsigned short* arr, long &swap, long & total_dist, double & max_dist, bool hoare, int size){
    //Your code here
    if(size<2)return;
    
    unsigned short temp;
    int dist;
    
    int index=-1;
    unsigned short pivot;
    if(hoare)pivot=arr[(size-1)/2];
    else pivot=arr[size-1];
    
    if(hoare){
        
        int j=size;
        
        while(1){
            index++;
            j--;
            while(arr[j]<pivot)j--;
            while(arr[index]>pivot)index++;
            if(index<j){
                temp=arr[index];
                arr[index]=arr[j];
                arr[j]=temp;
                
                dist=absDiff(index,j);
                if(max_dist<dist)max_dist=dist;
                total_dist+=dist;
                swap++;
            }
            else break;
        }
        qhelper(arr,swap,total_dist,max_dist,hoare,j+1);
        qhelper(arr+j+1,swap,total_dist,max_dist,hoare,size-j-1);
        /*unsigned short x=arr[(size-1)/2];
        int i=-1;
        int j=size;
        while(1){
            do{j--}while(arr[j]<x);
            do{i++}while(arr[i]>x);
            if(i<j){
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
                
                dist=absDiff(i,j);
                if(max_dist<dist)max_dist=dist;
                
                local_total_dist+=dist;
                local_swap++;
            }
            else break;
        }
        quickSort(arr,swap,avg_dist,max_dist,hoare,j+1);
        quickSort(arr+j+1,swap,avg_dist,max_dist,hoare,size-j-1);
        */
        
        
        
        
        
    }
    else{
        for(int j=0;j<=size-2;j++){
            if(arr[j]>=pivot){
                index++;
                temp=arr[index];
                arr[index]=arr[j];
                arr[j]=temp;
                
                dist=absDiff(index,j);
                if(max_dist<dist)max_dist=dist;
                total_dist+=dist;
                swap++;
            }
        }
        index++;
        temp=arr[index];
        arr[index]=arr[size-1];
        arr[size-1]=temp;
        
        dist=absDiff(index,size-1);
        if(max_dist<dist)max_dist=dist;
        total_dist+=dist;
        swap++;
        
        qhelper(arr,swap,total_dist,max_dist,hoare,index);
        qhelper(arr+index+1,swap,total_dist,max_dist,hoare,size-index-1);
    }
    
    //calculate avg_dist
    //add swap
}

void quickSort(unsigned short* arr, long &swap, double & avg_dist, double & max_dist, bool hoare, int size)
{
    long total_dist=0;
    qhelper(arr,swap,total_dist,max_dist,hoare,size);
    avg_dist=(double)total_dist/swap;
    if(!swap)avg_dist=0;
}

void quickSort3(unsigned short *arr, long &swap, long &comparison, int size) {
	
    if(size<2)return;
    unsigned short temp;
    int i=0,j=0,p=size-1;
    while(i<p){
        comparison++;
        if(arr[i]>arr[size-1]){
            swap++;
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
            i++;
            j++;
        }
        else if(arr[i]==arr[size-1]){
            comparison++; //delete if neccessary
            swap++;
            p--;
            temp=arr[i];
            arr[i]=arr[p];
            arr[p]=temp;
        }
        else{
            comparison++; //delete if neccessary
            i++;
        }
    }
    int m=p-j;
    if(m>size-p)m=size-p;
    for(int index1=j,index2=size-m;index2<size;index1++,index2++){
        swap++;
        temp=arr[index1];
        arr[index1]=arr[index2];
        arr[index2]=temp;
    }
    int L=j;
    int R=p-j;
    
    
    
    
    quickSort3(arr,swap,comparison,L);
    quickSort3(arr+size-R,swap,comparison,R);
	
}