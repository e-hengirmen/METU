#include <iostream>
#include <cstdio>

using namespace std;

float MinFloat(float a,float b){if(a>b)return b;return a;}

void solve(float *I,float *res,int i,int j,int n,float a){
    float miny=*(I+i*n+j)+a,*limit=res+i*n+j;
    for(float *x=res+i*n+i,*y=res+(i+1)*n+j;x<limit;x++,y+=n){
        if(!*x){
            solve(I,res,i,x-res-i*n,n,a);
        }
        if(!*y){
            solve(I,res,x-res-i*n+1,j,n,a);
        }
        miny=MinFloat(miny,*x+*y);
    }
    *(res+i*n+j)=miny;
}

int main()
{
    int n;
    string s;
    float a;
    cin>>n>>a;
    float I[n][n],res[n][n];
    
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n;j++){
            if(j>i){
            cin>>I[i][j];
            res[i][j]=0;
            }
            else{
                cin>>s;
                I[i][j]=0;
            }
        }
    }
    for(int j=0;j<n;j++){
        I[n-1][j]=0;
        res[j][j]=a;
    }

   solve(*I,*res,0,n-1,n,a);
    
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i>j)
                cout<<"e ";
                else
                cout<<res[i][j]<<' ';
            }
        cout<<endl;
    }
    
}