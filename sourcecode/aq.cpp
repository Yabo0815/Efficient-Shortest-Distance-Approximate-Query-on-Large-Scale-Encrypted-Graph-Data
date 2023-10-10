//input: ./a.out [graphdataname] randomn_node_pairs_1k
//Function: compute accurate shortest distance between randoom 1k pairs
//Author  : dongxt
//Data    : 2023/8/1

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
   
      for(int j=0; j<vecNode.size(); j++) {
          nodeid = vecNode[j];
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
  vector<int> vecIntNode;
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
  if(ifs) {
      getline(ifs,buf);
      ss << buf;
      ss>>nodeid1>>nodeid2;
      ss.clear();
      vecIntNode = graph[nodeid1];
      vecIntNode.push_back(nodeid2);
      oldnodeid1 = nodeid1;
      oldnodeid2 = nodeid2;
      cout << "the first node pair is: " << nodeid1 << ", " << nodeid2 << endl;
      //add tonode list
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
          centernodeids[vecIntNode.size()] = oldnodeid1;
          printf("NoDe:%d,sIzE:%d DONGXT\n",oldnodeid1,vecIntNode.size());
          if(maxdegree<count) {
            maxdegree2 = maxdegree;
            maxdegree = count;
  //          center_nodeid2 = center_nodeid;
  //          center_nodeid = oldnodeid1;
          }
          count = 1;
          vecIntNode = graph[nodeid1];
          vecIntNode.push_back(nodeid2);
        }
        oldnodeid1 = nodeid1;
        oldnodeid2 = nodeid2;
      }
      graph[nodeid1] = vecIntNode;
      printf("NoDe:%d,sIzE:%d DONGXT\n",oldnodeid1,vecIntNode.size());
      centernodeids[vecIntNode.size()] = oldnodeid1;
      if(maxdegree<count) {
        maxdegree2 = maxdegree;
        maxdegree = count;
   //     center_nodeid2 = center_nodeid;
   //     center_nodeid = oldnodeid1;
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
    vecIntNode = it->second;
    for(int j=0; j<vecIntNode.size(); j++) {
      nodeid = vecIntNode[j];
      cout << " " << nodeid;
    }
    cout << endl;
  }
  //construct 2HCL
  queue<int> que;
  map<int,int> OneMapSD;
 
  //compute_2HCL_byPrunedBFS(graph, vAdjList); 
  int start_time, end_time;
  start_time = clock();
  int k = 32,i=0;
  int lenth = centernodeids.size();
  int center = centernodeids[lenth-k];
  map<int,int>::reverse_iterator rit = centernodeids.rbegin();
  for(rit = centernodeids.rbegin(); i<k;i++,rit++) {
      printf("k-level=%d\n",i);
      center = rit->second;
//      center = centernodeids[lenth-i];
      printf("center dongxt = %d\n",center);
      OneMapSD.clear();
      compute_BFS_for_District(graph, OneMapSD, i, center); 
      string filename;
      ofstream ofs;
      stringstream ss;
      ss << i;
      filename = graphdata + string("~") + ss.str() + "level";
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
