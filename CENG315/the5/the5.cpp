#include "the5.h"
// do not add extra libraries here

/*
W: the width of the field
L: the length of the field
partitions: 2D Boolean array for partitions, if a partition of w x l exists then partitions[x][y] is true.
numberOfCalls/numberOfIterations: method specific control parameter
*/

int recursiveMethod(int W, int L, bool** partitions, int* numberOfCalls){
    
    (*numberOfCalls)++;
    if(partitions[W][L])return 0;
    
    int res=W*L;
    int res2;
    for(int i=1;i<=W/2;i++){
        res2=recursiveMethod(W-i,L,partitions,numberOfCalls)+
             recursiveMethod(i,L,partitions,numberOfCalls);
        if(res2<res)res=res2;
    }
    for(int i=1;i<=L/2;i++){
        res2=recursiveMethod(W,L-i,partitions,numberOfCalls)+
             recursiveMethod(W,i,partitions,numberOfCalls);
        if(res2<res)res=res2;
    }
	return res; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}

int memoHelp(int W,int L,int** arr,bool **partitions,int*numberOfCalls){
    (*numberOfCalls)++;
    if(partitions[W][L])return 0;
    if(arr[W][L]!=-1)return arr[W][L];
    
    int res=W*L;
    int res2;
    for(int i=1;i<=W/2;i++){
        res2=memoHelp(W-i,L,arr,partitions,numberOfCalls)+
             memoHelp(i,L,arr,partitions,numberOfCalls);
        if(res2<res)res=res2;
    }
    for(int i=1;i<=L/2;i++){
        res2=memoHelp(W,L-i,arr,partitions,numberOfCalls)+
             memoHelp(W,i,arr,partitions,numberOfCalls);
        if(res2<res)res=res2;
    }
    arr[W][L]=res;
	return res;
}

int memoizationMethod(int W, int L, bool** partitions, int* numberOfCalls){
    
    int **arr=new int*[W+1];
    for(int i=0;i<W+1;i++){
        arr[i]=new int[L+1];
        for (int j = 0; j < L+1; j++){
			arr[i][j] = -1;
		}
    }
    (*numberOfCalls)++;
    int res=memoHelp(W,L,arr,partitions,numberOfCalls);
    
    for(int i=0;i<W+1;i++){
        delete[] arr[i];
    }
    delete[] arr;
    
	return res; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}

int bottomUpMethod(int W, int L, bool** partitions, int* numberOfIterations){
    
    int **arr=new int*[W+1];
    for(int i=0;i<W+1;i++){
        arr[i]=new int[L+1];
    }
    
    for(int i=1;i<=W;i++){
        for(int k=1;k<=L;k++){
            if(partitions[i][k]){
                arr[i][k]=0;
            }
            else{
                arr[i][k]=i*k;
                int res2;
                for(int i2=0;i2<i;i2++){
                    (*numberOfIterations)++;
                    res2=arr[i-i2][k]+arr[i2][k];
                    if(res2<arr[i][k])arr[i][k]=res2;
                }
                for(int i2=0;i2<k;i2++){
                    (*numberOfIterations)++;
                    res2=arr[i][k-i2]+arr[i][i2];
                    if(res2<arr[i][k])arr[i][k]=res2;
                }
            }
            
        }
    }
    
    
    
    int res=arr[W][L];
    
    for(int i=0;i<W+1;i++){
        delete[] arr[i];
    }
    delete[] arr;
    
	return res;// this is a dummy return value. YOU SHOULD CHANGE THIS!
}
