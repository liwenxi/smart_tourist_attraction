//
//  main.cpp
//  smart_tourist_attraction
//
//  Created by 李文熙 on 16/11/7.
//  Copyright © 2016年 李文熙. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "graph.h"

using std::cout;
using std::cin;
using std::endl;



int main(int argc, const char * argv[]) {
    int choose;
    int32_t path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];                       //path用来存储经过的路径
    double D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];                           //D用来存储两个顶点之间的距离
    ALGraph G, G1;
    cout << endl;
    while (true) {
        cout << "===========================\n";
        cout << "  欢迎使用景区信息管理系统\n";
        cout << "      ***请选择菜单***\n";
        cout << "===========================\n";
        cout << "1、创建景区景点分布图\n";
        cout << "2、输出景区景点分布图\n";
        cout << "3、输出导游路线图\n";
        cout << "4、输出到有路线图中的回路\n";
        cout << "5、求两个景点间的最短路径和最短距离\n";
        cout << "6、输出道路修建规划图\n";
        cout << "7、停车场车辆进出记录信息\n";
        cout << "0、退出系统\n\n";
        cout << "请输入您要选择的菜单项：";
        cin >> choose;
        switch (choose) {
        case 1:
            system("clear");
            CreatGraph(G);
            system("clear");
            break;
        case 2:
            system("clear");
            OutputGraph(G);
            system("clear");
            break;
        case 3:
            system("clear");
            CreatTourSortGraph(G, G1);
            system("clear");
            break;
        case 4:
            system("clear");
            break;
        case 5:
            system("clear");
            MiniDistanse(G, path, D);
            system("clear");
            break;
        case 6:
            system("clear");
            MiniSpanTree(G, G.vertices[0].name);
            system("clear");
            break;
        case 7:
            system("clear");
            break;
        case 0:
            system("clear");
            break;
                
        default:
            system("clear");
            cout << "\a";
            cout << "    输入错误，请重新输入\n";
            break;
        }
    }
        
    return 0;
}



