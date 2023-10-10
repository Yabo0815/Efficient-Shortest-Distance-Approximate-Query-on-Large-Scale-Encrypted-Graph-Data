# Efficient-Shortest-Distance-Approximate-Query-on-Large-Scale-Encrypted-Graph-Data


#功能：输入图，生成输出图的256个bfs
#输入：图
#输出：256个level文件
#命令
./bfs256.out graph
#生成无向图的256个ulevel文件
./undirected-bfs256.out graph
#生成有向图的256个dlevel文件
./directed-bfs256.out graph

======================================================

#功能：从图中生成随机n对节点
#输入：图，n
#输出：n对随机节点,写入[graph]-random-[n]
#命令：
python generate_random_n_pairs.py bri~1level 1000 

======================================================

#功能：从256个bfs文件中，查询随机节点对的最短路径
#输入：随便一个level文件 随机节点对
#输出：klevel方案的随机节点对的最短路径查询结果，存于[graph]-queryresult
#命令
python esday-256bfs.py bri~1level bri-random-1000
#查无向图 
python esday-undirected-256bfs.py bri~1ulevel bri-random-1000
#查有向图 
python esday-directed-256bfs.py bri~1dlevel bri-random-1000

======================================================

#功能：输入图，查询随机节点对的精确最短路径，写入文件[graphname]-query_accurate-result
#输入： a graph [grqc] and random pairs [random]
#输出： the accurate shortest distance between pairs,存于[graph]-query_accurate_result
#命令：
./aq.out ./dataset/result/grqc/grqc ./dataset/result/grqc/random

#对于无向图的查询
./aq-undirected.out ./dataset/result/grqc/grqc ./dataset/result/grqc/random
#对于有向图的查询
./aq-directed.out ./dataset/result/grqc/grqc ./dataset/result/grqc/random


