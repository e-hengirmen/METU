#include "the4.h"

int recursive_sln(int i, int*& arr, int &number_of_calls){ //direct recursive
    number_of_calls+=1;
    if(i<0)return 0;
    if(i==0)return arr[0];
    if(i==1)return std::max(arr[0],arr[1]);
    if(i==2)return std::max(arr[2],std::max(arr[0],arr[1]));
    
    int x,y,z,res;
    
    x=recursive_sln(i-1,arr,number_of_calls);
    z=recursive_sln(i-3,arr,number_of_calls);

    
    res=std::max(x,z+arr[i]);

    //your code here

    return res; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}



int memoization_sln(int i, int*& arr, int*& mem){ //memoization
    if(i==0)return arr[0];
    if(i==1)return std::max(arr[0],arr[1]);
    if(i==2)return std::max(arr[2],std::max(arr[0],arr[1]));
    
    int x,y,z;
    if(mem[i-1]==-1){
        mem[i-1]=memoization_sln(i-1,arr,mem);
    }
    x=mem[i-1];
    
    if(mem[i-3]==-1){
        mem[i-3]=memoization_sln(i-3,arr,mem);
    }
    z=mem[i-3];
    
    mem[i]=std::max(x,z+arr[i]);
    
    
    //your code here

    return mem[i]; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}




int dp_sln(int size, int*& arr, int*& mem){ //dynamic programming
    
    if(!size)return 0;
    mem[0]=arr[0];
    if(size==1)return arr[0];
    mem[1]=std::max(arr[0],arr[1]);
    if(size==2)return mem[1];
    mem[2]=std::max(mem[1],arr[2]);
    
    for(int i=3;i<size;i++)
        mem[i]=std::max(arr[i]+mem[i-3],mem[i-1]);
    
    
    
    //your code here
    

    return mem[size-1]; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}

