#include "the3.h"

// do not add extra libraries here


/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    ascending : true for ascending, false for descending 
    n         : number of elements in the array
    l         : the number of characters used in counting sort at each time
    
    you can use ceil function from cmath
    
*/

struct node{
    std::string s;
    node *next,*prev;
    node(std::string &ss):s(ss),next(nullptr),prev(nullptr){}
    node(std::string &ss,node *x):s(ss),next(nullptr),prev(x){}
};

struct slist{
    node *head,*tail;
    slist():head(nullptr),tail(nullptr){}
    void add(std::string &s){
        if(tail==nullptr)head=tail=new node(s);
        else{
            tail->next=new node(s,tail);
            tail=tail->next;
        }
    }
    ~slist(){
        while(head!=nullptr){
            tail=head;
            head=head->next;
            delete tail;
        }
    }
    void del(){
        if(head==nullptr)return;
        node *temp=head;
        head=head->next;
        delete temp;
        return;
    }
};



void countHelp(std::string arr[], bool ascending, int n, int l,int pos);
int radixSort(std::string arr[], bool ascending, int n, int l){
    
    for(int i=arr[0].size()-1;i>=0;i-=l)countHelp(arr, ascending,n,l, i);
    
    int strLength=arr[0].size();
    int res=(strLength/l)*(pow(26,l)+3*n);
    if(strLength%l)res+=pow(26,(strLength%l))+3*n;
    return res;    
    
}

int pow(int a,int b){
    int res=1;
    for(int i=0;i<b;i++)res*=a;
    return res;
}

int min(int a,int b){if(a>b)return b;return a;}

void countHelp(std::string arr[], bool ascending, int n, int l,int pos){
    l=min(l,pos+1);
    int k=pow(26,l);
    slist *C=new slist[k];
    
    for(int N=0;N<n;N++){
        int point=0;
        int multiplier=1;
        for(int i=pos;i>pos-l;i--){
            point+=multiplier*(arr[N][i]-'A');
            multiplier*=26;
        }
        if(ascending==0)point=k-point-1;
        C[point].add(arr[N]);
    }
    
    for(int i=0,arrPos=0;i<k;i++){
        while(C[i].head!=nullptr){
            arr[arrPos]=C[i].head->s;
            arrPos++;
            C[i].del();
        }
    }
    
    
    
    
    
    delete[] C;
}

