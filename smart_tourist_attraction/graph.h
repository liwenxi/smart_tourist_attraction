//
//  Header.h
//  smart_tourist_attraction
//
//  Created by 李文熙 on 16/11/8.
//  Copyright © 2016年 李文熙. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>

const int32_t MAX_VERTEX_NUM (20);

typedef struct ArcNode{
    int32_t adjvex;                                             //头结点
    ArcNode *next;                                              //下一个节点
    int32_t weight;                                             //权值

}ArcNode;//定义顶点信息

typedef struct VNode{
    std::string name;                                           //景点的名称
    std::string description;                                    //景点的介绍
    enum star {one_star, two_stars, three_stars, four_stars, five_stars};
    star welcome;                                               //景点的受欢迎程度
    bool resting_area;                                          //有无休息区
    bool restroom;                                              //有无公厕
    ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];//定义边信息

typedef struct{
    AdjList vertices;
    int32_t vexnum, arcnum;                                     //定义顶点的数量和边的数量
}ALGraph;//定义邻接表

struct {                                                        //定义prim算法的辅助数组
    int32_t adjvex;
    int32_t lowcost;
}closedge[MAX_VERTEX_NUM];

int32_t LocateVex(ALGraph &G, std::string LocateVex);           //返回地点的序号
std::string LocateVex(ALGraph &G, int32_t LocateVex);           //返回地点的名称

void CreatGraph(ALGraph &G);                                    //创建图的邻接表存储

void OutputGraph(ALGraph G);                                    //输出图的邻接表

void CreatTourSortGraph(ALGraph G, ALGraph &G1);                //输出导游线路图

void destroy_DFS_traversal();

void DFSTraverse(ALGraph G);                                    //深度遍历未遍历的节点

void DFS(ALGraph G, int32_t v);                                 //通过一个节点向下继续寻找未遍历的节点

bool IsEdge(ALGraph G, std::string v1, std::string v2);

bool TopoSort(ALGraph G1);                                      //判断导游图有无回路

void FindInDegree(ALGraph G1, int indegree[]);                  //查询入度

int32_t get_weight(ALGraph G, int32_t i, int32_t j);            //获取两点之间的权值

void MiniDistanse(ALGraph G1, int32_t path[][MAX_VERTEX_NUM], double D[][MAX_VERTEX_NUM]);          //求最短距离

void MiniSpanTree(ALGraph G, std::string name);                 //输出道路修建规划图

void ShortestPath_DIJ(ALGraph G, int path[][MAX_VERTEX_NUM], double D[][MAX_VERTEX_NUM]);        //计算最短路径

void ShortestPath_FLOYD(ALGraph G, int path[][MAX_VERTEX_NUM], double D[][MAX_VERTEX_NUM]);        //计算最短路径

void OutPutShortestPath(ALGraph G,int path[][MAX_VERTEX_NUM], double D[][MAX_VERTEX_NUM], int32_t i, int32_t j);      //求最短路径

void OutPutShortestPath(ALGraph G,int path[][MAX_VERTEX_NUM], double D[][MAX_VERTEX_NUM], std::string s1, std::string s2); //求最短路径


#endif /* Header_h */
