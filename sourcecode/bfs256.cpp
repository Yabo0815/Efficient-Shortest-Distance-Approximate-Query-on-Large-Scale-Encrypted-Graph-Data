#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits.h>
#include <map>
#include <time.h>
#include <stdlib.h>
#include <set>

#define DEBUG 0
#define LOG 0

//#include <list>
using namespace std;
using std::vector;
using std::pair;
int radius(0),maxdegree(0),center_nodeid;
int maxdegree2(0),center_nodeid2;
float radius2(0);
queue<int> que_tmp_node;
vector<int> centernodeids;
vector<int> centernodedegree;
set<int> myset;
vector<int> vecNode;

struct CToNode
{
   int t_node;
   int mindis;
};

struct SNodeSD
{
   int node;
   int dis;
};

int compute_BFS_for_District(map<int, vector<int> >& _graph, map<int,int>& OneMapSD,int k,int center) {

  int dis=0,p=0,unodeid=0,nodeid=0,degree=0,maxdegree=0;
  SNodeSD aNodeSD;
  radius = 0;
  radius2 = 0;

  center_nodeid = center;
  cout << "find " << k << " center: " << center_nodeid << endl;
  que_tmp_node.push(center_nodeid);
  OneMapSD[center_nodeid] = 0;
  cout << "set map[" << center_nodeid << "] as " << OneMapSD[nodeid] << endl;
  
  //get bFs BeGiN FrOm cENTER NODE 2
  //cout << "find center 2: " << center_nodeid2 << endl;
  //que_tmp_node.push(center_nodeid2);
  //OneMapSD[center_nodeid2] = 0;
  //cout << "set map[" << center_nodeid2 << "] as " << OneMapSD[nodeid] << endl;

  vector<int> vecNode;

  while(!que_tmp_node.empty()) {
      unodeid = que_tmp_node.front();
      que_tmp_node.pop();
      
      vecNode = _graph[unodeid]; 
   
      for(int i=0;i<vecNode.size();i++) {
          nodeid = vecNode[i];
          if(!OneMapSD[nodeid]) {
            OneMapSD[nodeid] = OneMapSD[unodeid] + 1;
//            if(OneMapSD[nodeid]>radius) {
//              radius = OneMapSD[nodeid];
//            }
            que_tmp_node.push(nodeid);
          }
          //cout << "add node:" << nodeid << " dis:" << OneMapSD[nodeid] << endl;
      }

  }

  OneMapSD[center_nodeid] = 0;
  //OneMapSD[center_nodeid2] = 0;
  cout << "find center 2: " << center_nodeid2 << endl;
  que_tmp_node.push(center_nodeid2);
  return 0;
}


int main(int argc, char* argv[]){
  time_t time_start, time_end;
  time_start = time(NULL);
  ifstream ifs;
  string buf;
  stringstream ss;
  vector<CToNode> vecToNode;
  map< int, vector<int> > graph;
  char* graphdata;
  if(argc > 1) {
    graphdata = argv[1];
    cout << "graphdata is: " << graphdata << endl;
  }
  //list<int,vector<int> > vecList;
  int nodeid(0),nodeid1(0),nodeid2(0),count(1),oldnodeid1(0),oldnodeid2(0),edges(1);
  ifs.open(graphdata,ios::in);
  //read the graph as undirected graph, and store it in [graph]
  if(ifs) {
      //add tonode list
      while(getline(ifs,buf)) {
        ss << buf;
        ss>>nodeid1>>nodeid2;
        ss.clear();
        edges++;
        vecNode = graph[nodeid1];
        vecNode.push_back(nodeid2);
        graph[nodeid1] = vecNode;
      }
  } 
  else {
    cout<<"open file failed" << endl;
  }

  ifs.close();
  const int clen = count;
  //for each node, print node list linked to current node
  cout << "print initial graph:" << endl; 
    for(map<int,vector<int> >::iterator it=graph.begin(); it != graph.end(); it++) {
    cout << "nodeid:" << it->first;
    vecNode = it->second;
    for(int i=0;i<vecNode.size();i++) {
        nodeid = vecNode[i];
      cout << " " << nodeid;
    }
    cout << endl;
  }
  //construct 2HCL
  queue<int> que;
  map<int,int> OneMapSD;

  //find k centers and store it into centernodeids
  int k = 256,i=0,itmp,j;
  //store graph[nodeid]:set.size() into centerdegree, sotre ids into centernodeids
  for(map<int,vector<int> >::iterator it=graph.begin(); it != graph.end(); it++) {
    itmp = it->first;
    vecNode = it->second;
    centernodeids.push_back(itmp);
    centernodedegree.push_back(vecNode.size());
  }
  //设k为256与节点数的最小值
  int lenth = centernodeids.size();
  if(lenth < k)
    k = lenth;
  //冒泡找到k个center并由大到小存到centernodeids中
  for(i=0;i<k;i++) {
    for(j=k-1;j>i;j--) {
      if(centernodedegree[j]>centernodedegree[j-1]) {
         itmp = centernodeids[j];
         centernodeids[j]=centernodeids[j-1];
         centernodeids[j-1]=itmp;
         itmp = centernodedegree[j];
         centernodedegree[j]=centernodedegree[j-1];
         centernodedegree[j-1]=itmp;
      }
    }
  }
  
  //compute k-level BFS for undirected 
  int start_time, end_time;
  start_time = clock();
  int center;
  for(i = 0; i<k ;i++) {
      printf("k-level=%d\n",i);
      center = centernodeids[i];
      OneMapSD.clear();
      compute_BFS_for_District(graph, OneMapSD, i, center); 
      string filename;
      ofstream ofs;
      stringstream ss;
      ss << i;
      filename = graphdata + string("~") + ss.str() + "ulevel";
      cout << "the " << i << "-level center is: " << center << endl; 
      cout << "write " << i << "level map into file[" << filename << "]" << endl;
      ofs.open(filename.c_str(),std::ofstream::out);
      for(map<int,int>::iterator it=OneMapSD.begin(); it != OneMapSD.end(); it++) 
    {
      ofs << it->first << " " << it->second << endl;
    }
      ofs.close();
      cout << "write success" << endl;
  }
  end_time = clock();
  
  cout << "There are total " << OneMapSD.size() << " nodes" << endl;
  cout << "There are total " << edges << " edges" << endl;
  cout << "There cost " << end_time - start_time << " us." << endl;
  cout << "The radius is:  " << radius << endl;
  cout << "The center_nodeid is:  " << center_nodeid<< endl;
  //print OneMapBFS
  cout << "print OneMapBFS:" << endl; 
  int radius=0,_size=0;
    for(map<int,int>::iterator it=OneMapSD.begin(); it != OneMapSD.end(); it++) {
    //cout << "nodeid:" << it->first;
    //cout << " ,dis:" << it->second;
    _size++;
    if(it->second > radius) {
      radius = it->second;
    }
    radius2 += it->second;
    cout << endl;
  }
    if(0!=_size) {
      radius2 = radius2/_size;
    }
    cout << "radius is: " << radius << endl;
    cout << "radius2 is: " << radius2 << endl;
    cout << "_size is: " << _size << endl;
}


#undef LOG 
#undef DEBUG
