#include "the6.h"
// Don't add any additional includes

/*
  N: Number of racers
  updates: Updates you have heard
*/

using namespace std;

struct graph{
    
    int n;      //element count
    vector<int> *nblist;
    bool *visited;
    int time=0;
    //int *END,*START;
    queue<int> resQue;       //strongly connected component if exists
    stack<int> endStack;
    int *prev;
    int *indegree;

    
    graph(int x):n(x){
        nblist=new vector<int>[n];
        visited=new bool[n];
        //END=new int[n];
        //START=new int[n];
        prev=new int[n];
        
        for(int i=0;i<n;i++){
            visited[i]=false;
        }
    }
    ~graph(){
        delete[] nblist;
        delete[] visited;
        delete[] prev;
        //delete[] END;
        //delete[] START;
    }
    
    void addEdge(int a,int b){
        nblist[a].push_back(b);
    }
    
    void DFS1(int current){
        
        visited[current]=true;
        //START[current]=time;
        // time++;
        
        for(unsigned int i=0;i<nblist[current].size();i++){
            int next=nblist[current][i];
            if(!visited[next]){
                DFS1(next);
            }
        }
        
        //END[current]=time;
        endStack.push(current);
        // time++;
        
    }
    
    void prepare(){
        
        
        vector<int> *templist=nblist;
        nblist=new vector<int>[n];
        
        for(int i=0;i<n;i++){
            for(unsigned int k=0;k<templist[i].size();k++){
                addEdge(templist[i][k],i);      //reversing edges
            }
        }
        delete[] templist;
        
        for(int i=0;i<n;i++)visited[i]=false;
        time=0;                               //set time and visited
        
    }
    bool DFS2(){
        
        bool res=true;
        while(!endStack.empty()&&res==true){
            int current=endStack.top();
            endStack.pop();      //finding next
            if(!visited[current]){
                res=DFS3(current);          //res==true means there is still order
                if(res==false)return false;
            }
        }
        return true;
        
    }
    
    bool DFS3(int current){
        
        visited[current]=true;
        
        for(unsigned int i=0;i<nblist[current].size();i++){
            int next=nblist[current][i];
            if(!visited[next]){
                
                findComponent(next,current);
                resQue.push(current);
                
                return false;
            }
        }
        
        return true;
    }

    bool findComponent(int current,int original){
        
        visited[current]=true;
        //resStack.push(current);
        
        for(unsigned int i=0;i<nblist[current].size();i++){
            int next=nblist[current][i];
            
            if(next==original){     /////////loopu tamamladıysak
                resQue.push(current);
                return true;
            }
            
            if(!visited[next]){
                
                bool nextRes=findComponent(next,original);
                if(nextRes==true){
                    resQue.push(current);
                    return true;
                }
            }
        }
        return false;
        
    }
    
    vector<int> TopologicalSort(){
        vector<int> res;
        queue<int> zeroQue;
        for(int i=0;i<n;i++){
            if(!indegree[i])zeroQue.push(i);
        }   //initial push

        while(zeroQue.empty()==false){
            int current=zeroQue.front();
            zeroQue.pop();
            res.push_back(current);
            for(unsigned int i=0;i<nblist[current].size();i++){
                int next=nblist[current][i];
                indegree[next]--;
                if(indegree[next]==0)zeroQue.push(next);       //if indegree becomes zero push
            }
        }

        return res;
    }
    
};

std::pair<bool, std::vector<int>>
RaceResult(int N, std::vector<std::pair<int, int>> updates) {
    
    graph g(N);
    for(unsigned int i=0;i<updates.size();i++){
        g.addEdge(updates[i].first,updates[i].second);
    }
    
    for(int i=0;i<N;i++){
        if(!g.visited[i]){
            g.DFS1(i);
        }
    }
    
    g.prepare();
    bool order=g.DFS2();
    //--------------case 1 true*************** there is an order
    if(order){

        delete[] g.nblist;
        g.nblist=new vector<int>[N];

        g.indegree=new int[N];
        for(int i=0;i<N;i++)g.indegree[i]=0;

        for(unsigned int i=0;i<updates.size();i++){     //Setting edges and indegree
            g.addEdge(updates[i].first,updates[i].second);
            g.indegree[updates[i].second]++;
        }
        vector<int> res(g.TopologicalSort());


        delete[] g.indegree;
        return{true,res};
    }
    
    //----------------case 2 false***********
   vector<int> res;
    int last=g.resQue.front();
    while(!g.resQue.empty()){
        res.push_back(g.resQue.front());
        g.resQue.pop();
    }
    res.push_back(last);
    return {false,res};
    //--------------------------------------
    
    
    
  return {true, {}}; // This is a dummy return value. YOU SHOULD CHANGE THIS!
}