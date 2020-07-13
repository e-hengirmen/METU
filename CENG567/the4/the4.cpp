#include <iostream>
#include <stdio.h>
using namespace std;

double max_double(double a,double b){if(a>b)return a;return b;}

double solve(double *arr,int x,int y,int n,int *control){
    double (*parr)[n]=(double(*)[n])arr,next,temp,solved;

    if(parr[x][y]==100)                                 
    next=-1;                                            /*-1 symbolises unreachableness*/
    else
    next=parr[x][y];                                    /*direct reach length*/

    for(int i=0;i<n;i++){
        if(control[i]&&parr[x][i]!=100){                /*if it has not been visited and if there is an edge between them*/
            control[i]=0;
            solved=solve(arr,i,y,n,control);
            if(solved==-1){                             /*if y is unreachable from i continue*/
                control[i]=1;
                continue;
            }
            temp=parr[x][i]+solved;
            next=max_double(temp,next);
            control[i]=1;
        }
        
    }
    /*
    x to y 
    x to i + i to y in recursive

    100 symbolises no edge so
    if arr[x][i] is 100 than there is no edge
    */
    
    
    
    
    return next;
}

int main()
{
    int n,x,y;
    double ans;
    cin>>n>>x>>y;
    x--;
    y--;
    double arr[n][n],*limit;
    int control[n];                             /*control array for checking if this edge has been visited*/
    for(int *i=control;i<control+n;i++)*i=1;
    control[x]=0;
    control[y]=0;
    limit=*(arr+n);
    for(double *p=*arr;p<limit;p++)cin>>*p;
    

    ans=solve(*arr,x,y,n,control);              /*recursive solution function*/
    if(ans==-1)                                 
    cout<<"INF";                                /* if y is unreachable from x print INF*/
    else
    cout<<ans;
    cout<<endl;

    
    
    return 0;
}
