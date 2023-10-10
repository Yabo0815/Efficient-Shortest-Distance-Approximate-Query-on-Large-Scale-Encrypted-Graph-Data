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
map< int, int> centernodeids;

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

int compute_BFS_for_District(map<int, vector<int> >& _graph, int nodeid1 ,int nodeid2) {

  map<int,int> OneMapSD;
  int p=0,unodeid=0,nodeid=0,degree=0,maxdegree=0;
  SNodeSD aNodeSD;
  int dis = INT_MAX;
  
  //cout << "nodeid1=" << nodeid1 << ",nodeid2=" << nodeid2 << endl;
  center_nodeid = nodeid1;
  //cout << "find " << k << " center: " << center_nodeid << endl;
  que_tmp_node.push(center_nodeid);
  OneMapSD[center_nodeid] = 0;

  vector<int> vecNode;

  while(!que_tmp_node.empty()) {
      unodeid = que_tmp_node.front();
      que_tmp_node.pop();
      
      vecNode = _graph[unodeid]; 
      for(int j=0; j<vecNode.size(); j++) {
          nodeid = vecNode[j];
          if(!OneMapSD[nodeid]) {
            OneMapSD[nodeid] = OneMapSD[unodeid] + 1;
            que_tmp_node.push(nodeid);
          }
   //          cout << "dongxt:" << "unode=" << unodeid << " nodeid=" << nodeid << ",center_nodeid=" << center_nodeid << ",nodeid2=" << nodeid2 << ",bfslevel=" << OneMapSD[nodeid] << ",dis=" << dis << endl;
         
          if(nodeid == nodeid2) {
             if(!OneMapSD[nodeid]) {
                dis = INT_MAX;
             }
             else
                dis = OneMapSD[nodeid];
             j=vecNode.size();
             queue<int> quec;
             que_tmp_node = quec;
          }
      }

  }
  return dis;
  //return OneMapSD[nodeid2];
}


int main(int argc, char* argv[]){
  time_t time_start, time_end;
  time_start = time(NULL);
  ifstream ifs;
  string buf;
  stringstream ss;
  vector<int> vecIntNode;
  vector<CToNode> vecToNode;
  map< int, vector<int> > graph;
  char* graphdata;
  char* randomfile;
  if(argc > 1) {
    graphdata = argv[1];
    //cout << "graphdata is: " << graphdata << endl;
  }
  if (argc > 2) {
    randomfile = argv[2];
    //cout << "random filename is: " << randomfile << endl;
  }
  //list<int,vector<int> > vecList;
  int nodeid(0),nodeid1(0),nodeid2(0),count(1),edges(1),oldnodeid1(0),oldnodeid2(0);
  int nodeids1[1000],nodeids2[1000];
  ifs.open(graphdata,ios::in);
  if(ifs) {
      getline(ifs,buf);
      ss << buf;
      ss>>nodeid1>>nodeid2;
      ss.clear();
      vecIntNode = graph[nodeid1];
      vecIntNode.push_back(nodeid2);
      oldnodeid1 = nodeid1;
      oldnodeid2 = nodeid2;
      while(getline(ifs,buf)) {
        ss << buf;
        ss>>nodeid1>>nodeid2;
        ss.clear();
        edges++;
        if(nodeid1 == oldnodeid1) {
          vecIntNode.push_back(nodeid2);
          count ++;
        }
        else {
          graph[oldnodeid1] = vecIntNode;
          if(maxdegree<count) {
            maxdegree = count;
          }
          count = 1;
          vecIntNode = graph[nodeid1];
          vecIntNode.push_back(nodeid2);
        }
        oldnodeid1 = nodeid1;
        oldnodeid2 = nodeid2;
      }
      graph[nodeid1] = vecIntNode;
  } 
  else {
    cout<<"open" << graphdata << "failed" << endl;
  }

  ifs.close();

  ifs.open(randomfile,ios::in);
  if(ifs) {
      int ith=0;
      while(getline(ifs,buf)) {
        ss << buf;
        ss>>nodeid1>>nodeid2;
        ss.clear();
        nodeids1[ith]=nodeid1;
        nodeids2[ith]=nodeid2;
        ith++;
      }
  } 
  else {
      cout << "open " << randomfile << " failed!" << endl;
  }
  ifs.close();
    //cout<<"open file failed" << endl;

  const int clen = count;
  //for each node, print node list linked to current node
  cout << "print initial graph:" << endl; 
    for(map<int,vector<int> >::iterator it=graph.begin(); it != graph.end(); it++) {
    cout << "nodeid:" << it->first;
    vecIntNode = it->second;
    for(int j=0; j<vecIntNode.size(); j++) {
      nodeid = vecIntNode[j];
      cout << " " << nodeid;
    }
    cout << endl;
  }
  //construct 2HCL
  queue<int> que;
 
  //compute_2HCL_byPrunedBFS(graph, vAdjList); 
  //int start_time, end_time;
  //start_time = clock();
  int k = 32,i=0;
  int lenth = centernodeids.size();
  int center = centernodeids[lenth-k];
  map<int,int>::reverse_iterator rit = centernodeids.rbegin();
  ofstream ofs;
  string filename;
  filename = string(graphdata) + string("-query_accurate_result");
  ofs.open(filename.c_str(),std::ofstream::out);
  //for(i=0;i<1000;i++) {
  for(i=0;i<1000;i++) {
      int dis=INT_MAX;
      nodeid1 = nodeids1[i];
      nodeid2 = nodeids2[i];
    //  cout << "dongxt:the " << i << "th pair query" << endl;
      dis = compute_BFS_for_District(graph, nodeid1, nodeid2 ); 
      ofs << dis << endl;
  }
  ofs.close();
  //end_time = clock();
  
}


#undef LOG 
#undef DEBUG
