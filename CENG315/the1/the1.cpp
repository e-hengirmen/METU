#include "the1.h"


//You can add your own helper functions

int sillySort(int* arr, long &comparison, long & swap, int size) 
{

    int num_of_calls=1;
	
	if(size<2)return num_of_calls;
	if(size==2){
	    comparison++;
	    if(arr[0]>arr[1]){
	        int x=arr[0];
	        arr[0]=arr[1];
	        arr[1]=x;
	        swap++;
	    }
	    return num_of_calls;
	}
	int q1=size/4;
	//8->q1=2  0 1  --- 2 3 --- 4 5 ---- 6 7
    num_of_calls+=sillySort(arr,comparison,swap,size/2);
    num_of_calls+=sillySort(arr+q1,comparison,swap,size/2);
    num_of_calls+=sillySort(arr+2*q1,comparison,swap,size/2);
    num_of_calls+=sillySort(arr,comparison,swap,size/2);
    num_of_calls+=sillySort(arr+q1,comparison,swap,size/2);
    num_of_calls+=sillySort(arr,comparison,swap,size/2);
	//Your code here
	
	return num_of_calls;
}


int crossMergeSort(int *arr, long &comparison, int size)
{
	
	int num_of_calls=1;
	
	if(size<2)return num_of_calls;
	if(size==2){
	    comparison++;
	    if(arr[0]>arr[1]){
	        int x=arr[0];
	        arr[0]=arr[1];
	        arr[1]=x;
	    }
	    return num_of_calls;
	}
	int q1=size/4;
	num_of_calls+=crossMergeSort(arr,comparison,q1);
	num_of_calls+=crossMergeSort(arr+q1,comparison,q1);
	num_of_calls+=crossMergeSort(arr+2*q1,comparison,q1);
	num_of_calls+=crossMergeSort(arr+3*q1,comparison,q1);
	// Your code here
	
	int h1[size/2],h2[size/2];
	int *x1,*x2,*lim1,*lim2;
	//---------------h1----------
	x1=arr;
	x2=arr+2*q1;
	lim1=x1+q1;
	lim2=x2+q1;
	int i=0;
	while(x1<lim1&&x2<lim2){
	    comparison++;
	    if(*x1<=*x2){
	        h1[i]=*x1;
	        x1++;
	    }
	    else{
	        h1[i]=*x2;
	        x2++;
	    }
	    i++;
	}
	if(x1==lim1)x1=x2,lim1=lim2;
	for(;x1<lim1;x1++,i++)h1[i]=*x1;
	//---------------h1----------
	
	
	//---------------h2----------
	x1=arr+q1;
	x2=arr+3*q1;
	lim1=x1+q1;
	lim2=x2+q1;
	i=0;
	while(x1<lim1&&x2<lim2){
	    comparison++;
	    if(*x1<=*x2){
	        h2[i]=*x1;
	        x1++;
	    }
	    else{
	        h2[i]=*x2;
	        x2++;
	    }
	    i++;
	}
	if(x1==lim1)x1=x2,lim1=lim2;
	for(;x1<lim1;x1++,i++)h2[i]=*x1;
	//---------------h2----------
	
	//---------------last----------
	x1=h1;
	x2=h2;
	lim1=h1+2*q1;
	lim2=h2+2*q1;
	i=0;
	while(x1<lim1&&x2<lim2){
	    comparison++;
	    if(*x1<=*x2){
	        arr[i]=*x1;
	        x1++;
	    }
	    else{
	        arr[i]=*x2;
	        x2++;
	    }
	    i++;
	}
	if(x1==lim1)x1=x2,lim1=lim2;
	for(;x1<lim1;x1++,i++)arr[i]=*x1;
	//---------------last----------
	//I should have written a merge function :(
	
	
	return num_of_calls;
	
}