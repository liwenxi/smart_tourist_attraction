//
//  graph.cpp
//  smart_tourist_attraction
//
//  Created by 李文熙 on 16/11/8.
//  Copyright © 2016年 李文熙. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <queue>
#include "graph.h"


using std::cout;
using std::cin;
using std::endl;


int32_t LocateVex(ALGraph &G, std::string LocateVex){                      //求景点名字对应的序号
    for (int32_t i = 0; i < G.vexnum; i++ ){
        if (G.vertices[i].name == LocateVex){
            return i;
        }
    }
    return -1;
}

std::string LocateVex(ALGraph &G, int32_t LocateVex){                      //重载序号对应的名字
    if (LocateVex <= G.vexnum){
        return G.vertices[LocateVex].name;
    }
    return NULL;
}

void CreatGraph(ALGraph &G){
    std::string vertice1, vertice2;                                        //一条边的两个端点
    int32_t v1, v2;                                                        //一条边的两个端点的位置
    int32_t weight;                                                        //权数
    cout << "请输入顶点数和边数：" ;
    cin >> G.vexnum >> G.arcnum;
    cout << endl;
    cout << "            请输入各顶点的信息" << endl << endl;
    cout << "请输入各定点的名字：";
    for (int32_t i = 0; i < G.vexnum; i++){
        cin >> G.vertices[i].name;
        G.vertices[i].firstarc = NULL;
    }
    for (int32_t i = 0; i < G.arcnum; i++){
        cout << "请输入第" << i+1 << "条边的两个顶点以及该边的权值：";
        cin >> vertice1 >> vertice2 >> weight;
        v1 = LocateVex(G, vertice1);
        v2 = LocateVex(G, vertice2);
        
        ArcNode *arc = new ArcNode;                                     //声明一个新的节点并分配一份空间
        (*arc).adjvex = v2;
        (*arc).weight = weight;
        (*arc).next = G.vertices[v1].firstarc;
        G.vertices[v1].firstarc = arc;
        
        arc = new ArcNode;                                              //再分配一块空间，存储另一个点
        (*arc).adjvex = v1;
        (*arc).weight = weight;
        (*arc).next = G.vertices[v2].firstarc;
        G.vertices[v2].firstarc = arc;
        
    }
}                                                                       //创建图的邻接表存储
void OutputGraph(ALGraph G){
    cout.setf(std::ios::left);
    cout << std::setw(6) << "";
    for (int32_t i = 0; i < G.vexnum; i++){                             //输出显示表格的第一行
        cout.setf(std::ios::left);
        cout <<  std::setw(10) << G.vertices[i].name;
    }
    {
        
        ArcNode *arc;
        for (int32_t i = 0; i < G.vexnum; i++){                         //对每一行的值进行一个循环判断
            cout << endl;
            cout.setf(std::ios::left);
            cout <<  std::setw(10) << G.vertices[i].name;
            for (int32_t j = 0; j < G.vexnum; j++){                     //对每一行中的单个词进行判断
                arc = G.vertices[i].firstarc;
                if (i == j){
                    cout.setf(std::ios::left);
                    cout << std::setw(6) << "0";
                    continue;
                }
                while (arc != NULL) {                                   //遍历寻找有没有权值
                    if ((*arc).adjvex == j){
                        cout.setf(std::ios::left);
                        cout << std::setw(6) << (*arc).weight;
                        break;
                    }else{
                        arc = (*arc).next;
                    }
                }
                if (arc == NULL){
                    cout.setf(std::ios::left);
                    cout << std::setw(6) << INT16_MAX;
                }
            }
        }
    }
    cout << endl;
    cin.get();
}                                                                       //输出图的邻接表

bool visted[MAX_VERTEX_NUM];                                            //访问标志数组
bool loop[MAX_VERTEX_NUM];

ArcNode *DFS_traversal = new ArcNode {NULL};
int32_t k;
int32_t l;
int32_t p[MAX_VERTEX_NUM];
int32_t vistnum;
char loop_array[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

void destroy_DFS_traversal(){
    ArcNode *arc, *dele;
    if (DFS_traversal == NULL){
        return;
    }
    arc = (*DFS_traversal).next;
    while (arc != NULL) {
        dele = arc;
        arc = (*arc).next;
        delete(dele);
    }
}

void DFSTraverse(ALGraph G){
    destroy_DFS_traversal();
    (*DFS_traversal).next = NULL;                                       //该链表用于存储导游图的路线
    for (int32_t i = 0; i < G.vexnum; i++){                             //对标志数组进行初始化
        visted[i] = false;
    }
    vistnum = 0;
    for (int32_t i = 0; i < G.vexnum; i++){
        if (!visted[i]){
            DFS(G, i);
        }
    }
}


void DFS(ALGraph G, int32_t v){                                         //从第v个点开始遍历
    visted[v] = true;
    ArcNode *arc;
    vistnum++;
    arc = new ArcNode;                                                  //遍历过程中将路径加到DFS_traversal中
    (*arc).adjvex = v;
    (*arc).next = (*DFS_traversal).next;
    (*DFS_traversal).next = arc;
    if (vistnum == G.vexnum)
        return ;
    for (ArcNode *arc = G.vertices[v].firstarc; arc != NULL; arc = (*arc).next){
        if (!visted[(*arc).adjvex]){
            DFS(G, (*arc).adjvex);
            if (vistnum == G.vexnum)
                return ;
            arc = new ArcNode;
            (*arc).adjvex = v;
            (*arc).next = (*DFS_traversal).next;
            (*DFS_traversal).next = arc;
        }
    }
}

void DFSTraverse_loop(ALGraph G){                                       //深度遍历回路
    for (int32_t i = 0; i < G.vexnum; i++){                             //对标志数组进行初始化
        visted[i] = false;
    }
    l = 0;
    for (int32_t i = 0; i < G.vexnum; i++){
        k = 0;
        p[0] = i;
        if (!visted[i]){
            DFS_loop(G, i);
        }
    }
}
void DFS_loop(ALGraph G, int32_t v){                                      //深度遍历回路
    visted[v] = true;
    for (ArcNode *arc = G.vertices[v].firstarc; arc != NULL; arc = (*arc).next){
        if ((*arc).adjvex > p[0] && !visted[(*arc).adjvex]){
            k++;
            p[k] = (*arc).adjvex;
            DFS_loop(G, (*arc).adjvex);
        }
        if (p[0] == (*arc).adjvex && k >1){
            l++;
            cout << "图中的第" << l << "个环：";
            for (int32_t j = 0; j < k+1; j++){
                cout << LocateVex(G, p[j]) << " ";
//                loop_array[l][j] = p[j];
            }

            cout << endl;
        }
    }
    visted[p[k]] = false;
    p[k] = 0;
    k--;
}
void CreatTourSortGraph(ALGraph G, ALGraph &G1){
    DFSTraverse(G);
    
    ArcNode *arc, *new_arc;                                                 //对导游路线进行逆向存储
    arc = (*DFS_traversal).next;
    new_arc = (*arc).next;
    while (new_arc != NULL) {
        (*arc).next = (*new_arc).next;
        (*new_arc).next = (*DFS_traversal).next;
        (*DFS_traversal).next = new_arc;
        new_arc = (*arc).next;
    }
    
    arc = (*DFS_traversal).next;                                            //按照导游图顺序输出
    while (arc != NULL) {
        cout << LocateVex(G, arc -> adjvex) << " ";
        arc = arc -> next;
    }
    
//    ArcNode *dele;                                                          //开始创建导游图
    G1.vexnum = G.vexnum;
    arc = (*DFS_traversal).next;
    for (int32_t i = 0; i < G1.vexnum; i++){
        G1.vertices[i].name = G.vertices[i].name;
        G1.vertices[i].firstarc = NULL;
    }
    while ((*arc).next != NULL) {
        new_arc = new ArcNode;
        (*new_arc).adjvex = (*arc).next->adjvex;
        (*new_arc).next = G1.vertices[(*arc).adjvex].firstarc;
        G1.vertices[(*arc).adjvex].firstarc = new_arc;
//        dele = arc;
        arc = (*arc).next;
    }
    
}

bool IsEdge (ALGraph G, std::string v1, std::string v2){
    int32_t vertice1 = LocateVex(G, v1);
    int32_t vertice2 = LocateVex(G, v2);
    ArcNode *arc = G.vertices[vertice1].firstarc;
    while (arc != NULL) {
        if ((*arc).adjvex == vertice2)
            return true;
        arc = (*arc).next;
    }
    return false;
}

//void FindInDegree(ALGraph G1, int indegree[]){
////    ArcNode *arc;
////    for (int32_t i = 0; i < G1.vexnum; i++){
////        arc = G1.vertices[i].firstarc;
////        while (arc != NULL){
////            //            if ((*arc).adjvex == )
////            /*to be continue*/
////        }
////    }
//    for(int i=0; i<G1.vexnum; i++)
//        indegree[i]=0;
//    
//    for(int32_t i=0; i<G1.vexnum; i++)
//    {
//        ArcNode *p=G1.vertices[i].firstarc;
//        while(p)
//        {
//            indegree[p->adjvex]++;
//            p=p->next;
//        }
//    }
//}


int32_t get_weight(ALGraph G, int32_t i, int32_t j){                                //取得两个点之间的权值
    if (i == j){
        return 0;
    }
    ArcNode *arc;
    arc = G.vertices[i].firstarc;
    while (arc != NULL){
        if ((*arc).adjvex == j){
            return (*arc).weight;
        }else{
            arc = (*arc).next;
        }
    }
    if (arc == NULL){
        return INT16_MAX;
    }
    return -1;
}
void MiniDistanse(ALGraph G, int32_t path[][MAX_VERTEX_NUM], double D[][MAX_VERTEX_NUM]){
    cout << "请输入要查询距离的两个景点的名称：";
    std::string s1, s2;
    cin >> s1 >> s2;
    int32_t i = LocateVex(G, s1);
    int32_t j = LocateVex(G, s2);
    cout << "最短路径为：" << endl;
    cout << "使用DIJ" << endl;
    ShortestPath_DIJ(G, path, D);
    OutPutShortestPath(G, path, D, i, j);
    cout << "使用FLOYD" << endl;
    ShortestPath_FLOYD(G, path, D);
    OutPutShortestPath(G, path, D, i, j);
    cout << "最短距离为：" << D[i][j] << endl;
    
}

void MiniSpanTree(ALGraph G, std::string name){
    cout << "道路修建规划图为：" << endl;
    int32_t first_node = LocateVex(G, name);
    for (int32_t i = 0; i < G.vexnum; i++){                         //对closedge进行初始化
        closedge[i].adjvex = first_node;
        closedge[i].lowcost = get_weight(G, first_node, i);
    }
    int32_t k = 0;
    for (int32_t i = 1; i < G.vexnum; i++){
        for (int32_t j = 0; j < G.vexnum; j++){                     //进行判断，找出最小的lowcost
            if (((closedge[k].lowcost > closedge[j].lowcost) && (closedge[j].lowcost != 0)) || (closedge[k].lowcost == 0)){
                k = j;
            }
        }
        cout << "从" << LocateVex(G, closedge[k].adjvex) << "到" << LocateVex(G, k)<< "修一段路" << endl;
        for (int32_t j = 0; j < G.vexnum; j++){
            if ((closedge[j].lowcost != 0) && (get_weight(G, k, j) < closedge[j].lowcost)){
                closedge[j].adjvex = k;
                closedge[j].lowcost = get_weight(G, k, j);
            }
        }
    }
}

void ShortestPath_FLOYD(ALGraph G, int path[][MAX_VERTEX_NUM], double D[][MAX_VERTEX_NUM]){
    ArcNode *arc;                                                   //将邻接表读取并转换成路径path和距离D两个矩阵
    for (int32_t i = 0; i < G.vexnum; i++){                         //对每一行的值进行一个循环判断
        for (int32_t j = 0; j < G.vexnum; j++){                     //对每一行中的单个词进行判断
            arc = G.vertices[i].firstarc;
            if (i == j){
                D[i][j] = 0;
                path[i][j] = i;
                continue;
            }
            while (arc != NULL) {                                   //遍历寻找有没有权值
                if ((*arc).adjvex == j){
                    D[i][j] = (*arc).weight;
                    path[i][j] = i;
                    break;
                }else{
                    arc = (*arc).next;
                }
            }
            if (arc == NULL){
                D[i][j] = INT16_MAX;
            }
        }
    }
    
    for (int32_t k = 0; k < G.vexnum; k++){                           //FLOYD动态规划
        for (int32_t i = 0; i < G.vexnum; i++){
            for (int32_t j = 0; j < G.vexnum; j++){
                if (D[i][k] + D[k][j] < D[i][j]){
                    D[i][j] = D[i][k] + D[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
    
}

void ShortestPath_DIJ(ALGraph G, int path[][MAX_VERTEX_NUM], double D[][MAX_VERTEX_NUM]){
    bool final[MAX_VERTEX_NUM][MAX_VERTEX_NUM] {false};
    int min;                                                        //迪杰特斯拉遍历时的最小值
    int min_num = 0;
    ArcNode *arc;                                                   //将邻接表读取并转换成路径path和距离D两个矩阵
    for (int32_t i = 0; i < G.vexnum; i++){                         //对每一行的值进行一个循环判断
        for (int32_t j = 0; j < G.vexnum; j++){                     //对每一行中的单个词进行判断
            arc = G.vertices[i].firstarc;
            if (i == j){
                D[i][j] = 0;
                path[i][j] = i;
                continue;
            }
            while (arc != NULL) {                                   //遍历寻找有没有权值
                if ((*arc).adjvex == j){
                    D[i][j] = (*arc).weight;
                    path[i][j] = i;
                    break;
                }else{
                    arc = (*arc).next;
                }
            }
            if (arc == NULL){
                D[i][j] = INT16_MAX;
            }
        }
    }
    
    for (int32_t i = 0; i < G.vexnum; i++){                         //先求出最小值，再根据最小值进行路径的更新，贪心算法
        for (int32_t j = 0; j < G.vexnum; j++){
            min = MAX_VERTEX_NUM;
            for (int32_t k = 0; k < G.vexnum; k++){
                if (!final[i][k] && D[i][k] < min){
                    min = D[i][k];
                    min_num = k;
                }
            }
            final[i][min_num] = true;
            for (int32_t k = 0; k < G.vexnum; k++){
                if (!final[i][k] && ((min + get_weight(G, min_num, k)) < D[i][k])){
                    D[i][k] = min + get_weight(G, min_num, k);
                    path[i][k] = min_num;
                }
            }
        }
    }
    
    
}

void OutPutShortestPath(ALGraph G, int path[][MAX_VERTEX_NUM], double D[][MAX_VERTEX_NUM], int i, int j){ //输出最短路径
    if (path[i][j] == i){
        cout << G.vertices[i].name << "--" << G.vertices[j].name << endl;
    }
    else{
        OutPutShortestPath(G, path, D, i, path[i][j]);
        OutPutShortestPath(G, path, D, path[i][j], j);
    }
}

void OutPutShortestPath(ALGraph G, int path[][MAX_VERTEX_NUM], double D[][MAX_VERTEX_NUM], std::string s1, std::string s2){
    int32_t i = LocateVex(G, s1);
    int32_t j = LocateVex(G, s2);
    if (path[i][j] == i){
        cout << G.vertices[i].name << "--" << G.vertices[j].name << endl;
    }
    else{
        OutPutShortestPath(G, path, D, i, path[i][j]);
        OutPutShortestPath(G, path, D, path[i][j], j);
    }
}


