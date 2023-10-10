#include<cstdio>
#include<iostream>
using namespace std;
const int maxSize = 10000;
const int INF = 100000000;
int n,m,s,G[maxSize][maxSize];
int d[maxSize];
bool vis[maxSize] = {false};

void Dijkstra(int s) {

   fill(d,d+maxSize,INF);
   d[s] = 0;
   for(int i=0; i<n; i++) {
       int u = -1, min = INF;
       for(int j=0; j<n; j++) {
           if(vis[j] == false && d[j] < min) {
               u = j;
               min = d[j];
           }
       }
       if(u==-1) return;
       vis[u] = true;
       for(int v=0; v<n; v++) {
           if(vis[v]==false && G[u][v] != INF && d[u]+G[u][v] < d[v]){
               d[v] = d[u]+G[u][v];
           }
        }
    }
}

int main(void) {
    int u,v,w;
    cin>>n>>m;
    fill(G[0],G[0]+maxSize*maxSize,INF);
    for(int i=0; i< m; i++) {
       cin>>u>>v;
       G[u][v]=1;
    }
    Dijkstra(s);
    int s,t;
    cout << "input two nodeids of start and target node:";
    cin>>s>>t;
    cout << "the distance of "<< s << "and "<< t << "is: " << G[s][t] << endl;
    return 0;
} 

