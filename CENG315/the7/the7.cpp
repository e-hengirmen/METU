#include "the7.h"

using namespace std;

struct graph{
    int n;
    vector<pair<int,int>> *nblist;  //first is node second is weight
    bool *visited;
    int cost;
    int *prev;
    
    
    
    graph(int x):n(x){
        nblist=new vector<pair<int,int>>[n];
        visited=new bool[n];
        prev=new int[n];
        
    }
    ~graph(){
        delete[] nblist;
        delete[] visited;
        delete[] prev;
    }
    
    void addEdge(int a,int b,int c){
        nblist[a].push_back({b,c});
        nblist[b].push_back({a,c});
    }
    void djikstra(int source,int dest){
        cost=0;
        int dist[n];
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        for(int i=0;i<n;i++){
            visited[i]=false;
            dist[i]=INT_MAX;
        }
        
        dist[source]=0;
        pq.push({0,source});
        
        //initialization above
        while(!pq.empty()){
            int currentDist=pq.top().first;
            int currentNode=pq.top().second;
            pq.pop();
            if(visited[currentNode]==true)continue;
            visited[currentNode]=true;
            if(currentNode==dest){
                cost=currentDist;
                return;
            }
            
            
            vector<pair<int,int>> &nb=nblist[currentNode];
            for(unsigned int i=0;i<nb.size();i++){
                int nextNode=nb[i].first;
                if(visited[nextNode])continue;
                int nextDist=nb[i].second+currentDist;
                if(nextDist<dist[nextNode]){
                    dist[nextNode]=nextDist;
                    pq.push({nextDist,nextNode});
                    prev[nextNode]=currentNode;
                }
            }
        }
        
        
        
    }
    void writepath(vector<int> &path,int source,int dest){
        stack<int> st;
        int x=dest;
        while(prev[x]!=source){
            x=prev[x];
            st.push(x);
        }
        
        path.push_back(source);
        while(st.empty()==false){
            path.push_back(st.top());
            st.pop();
        }
        path.push_back(dest);
    }
};

void FindRoute(int n, std::vector<Road> roads, int s, int d, int x, int y) {
  // You can change these variables. These are here for demo only.
  std::vector<int> path;
  int cost = INT_MAX;
  // Write your code here...
  graph g(n);
  for(unsigned int i=0;i<roads.size();i++){
        g.addEdge(roads[i].endpoints.first,roads[i].endpoints.second,roads[i].time);
  }
  
  g.djikstra(s,x);
  int costSX=g.cost;
  vector<int> pathSX;
  g.writepath(pathSX,s,x);
  
  g.djikstra(s,y);
  int costSY=g.cost;
  vector<int> pathSY;
  g.writepath(pathSY,s,y);
  
  g.djikstra(x,y);
  int costXY=g.cost;
  vector<int> pathXY;
  g.writepath(pathXY,x,y);
  
  g.djikstra(x,d);
  int costXD=g.cost;
  vector<int> pathXD;
  g.writepath(pathXD,x,d);
  
  g.djikstra(y,d);
  int costYD=g.cost;
  vector<int> pathYD;
  g.writepath(pathYD,y,d);
  
  if(costSX+costYD<costSY+costXD){
      cost=costSX+costYD+costXY;
      path.insert(path.end(), pathSX.begin(), pathSX.end()-1);
      path.insert(path.end(), pathXY.begin(), pathXY.end()-1);
      path.insert(path.end(), pathYD.begin(), pathYD.end());
  }
  else{
      cost=costSY+costXD+costXY;
      path.insert(path.end(), pathSY.begin(), pathSY.end()-1);
      path.insert(path.end(), pathXY.rbegin(), pathXY.rend()-1);
      path.insert(path.end(), pathXD.begin(), pathXD.end());
  }
  
  
  // Your output should be like this. You can change this as long as you keep
  // the output format. PrintRange function helps you print elements of
  // containers with iteratos (e.g., std::vector).
  std::cout << cost << " ";
  PrintRange(path.begin(), path.end());
  std::cout << std::endl;
}