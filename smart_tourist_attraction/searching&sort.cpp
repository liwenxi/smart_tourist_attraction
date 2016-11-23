//
//  searching&sort.cpp
//  smart_tourist_attraction
//
//  Created by 李文熙 on 16/11/23.
//  Copyright © 2016年 李文熙. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <vector>

#include "graph.h"
#include "searching&sort.h"

using namespace std;

void info_menu(ALGraph &G){
    int32_t choose;
    while (true) {
        cout << "===========================\n";
        cout << "        景区介绍系统\n";
        cout << "      ***请选择菜单***\n";
        cout << "===========================\n";
        cout << "1、景点信息录入\n";
        cout << "2、打印所有景点及相关信息\n";
        cout << "3、查找景点相关信息\n";
        cout << "4、输出到有路线图中的回路\n";
        cout << "5、求两个景点间的最短路径和最短距离\n";
        cout << "0、退出系统\n\n";
        cout << "请输入您要选择的菜单项：";
        cin >> choose;
        if (cin.fail()){
            system("clear");
            cout << "    输入错误，请重新输入！\a" << endl;
            cin.clear();
            cin.ignore();
            continue;
        }
        
        switch (choose) {
            case 1:
                system("clear");
                creat_description(G);
                system("clear");
                break;
            case 2:
                system("clear");
                show_all(G);
                system("clear");
                break;
            case 3:
                system("clear");
                searching(G);
                system("clear");
                break;
            case 4:
                system("clear");
                DFSTraverse_loop(G);
                system("clear");
                break;
            case 5:
                system("clear");
//                MiniDistanse(G, path, D);
                system("clear");
                break;
            case 0:
                system("clear");
                //                cout << is_empty(wait_queue);
                break;
                
            default:
                system("clear");
                cout << "\a";
                cout << "    输入错误，请重新输入\n";
                break;
        }
    }
}

void creat_description(ALGraph &G){
    string name;                                                //景点的名称
    int32_t num;                                                //景点的序号
    char temp;                                                  //用作休息区等的判断
    int32_t tmp;                                                //用作欢迎度的读取
    cout << "景点名称：";
    cin >> name;
    if ((num = LocateVex(G, name)) == -1){
        cout << "没有该景点，请先插入该景点！" << endl;
        return;
    }
    cout << "景点介绍：";
    cin >> G.vertices[num].description;
    cout << "受欢迎度：(1/2/3/4/5)";
    cin >> tmp;
    switch (tmp) {
        case 1:
            G.vertices[num].welcome = VNode::one_star;
            break;
            
        case 2:
            G.vertices[num].welcome = VNode::two_stars;
            break;
            
        case 3:
            G.vertices[num].welcome = VNode::three_stars;
            break;
            
        case 4:
            G.vertices[num].welcome = VNode::four_stars;
            break;
            
        case 5:
            G.vertices[num].welcome = VNode::five_stars;
            break;
            
        default:
            cout << "Please keep calm\n";
            break;
    }
    cout << "休息区：(Y/N)";
    cin >> temp;
    if ('Y' == temp){
        G.vertices[num].resting_area = true;
    }else{
        G.vertices[num].resting_area = false;
    }
    cout << "公厕：(Y/N)";
    cin >> temp;
    if ('Y' == temp){
        G.vertices[num].resting_area = true;
    }else{
        G.vertices[num].resting_area = false;
    }

}
void show_all(ALGraph G){
    for (int32_t i = 0; i < G.vexnum; i++){
        show_description(G, i);
    }
}
void show_description(ALGraph G, int32_t num){
    cout << "景点名称：" << G.vertices[num].name << endl;
    cout << "景点介绍：" << G.vertices[num].description << endl;
    cout << "受欢迎度：" << G.vertices[num].welcome << endl;
    cout << "休息区：";
    if (G.vertices[num].resting_area){
        cout << "有" << endl;
    }else{
        cout << "无" << endl;
    }
    cout << "公厕：";
    if (G.vertices[num].restroom){
        cout << "有" << endl;
    }else{
        cout << "无" << endl;
    }
}

inline void NEXT(const string &T, vector<int> &next)
{
    //按模式串生成vector,next(T.size())
    next[0] = -1;
    for (int i=1; i<T.size(); i++)
    {
        int j = next[i-1];
        while (T[i] != T[j+1]&&j >= 0)
            j = next[j];//递推计算
        if (T[i] == T[j+1])
            next[i] = j+1;
        else
            next[i] = 0;
    }
}
inline string::size_type COUNT_KMP(const string &S, const string &T)
{
    //利用模式串T的next函数求T在主串S中的个数count的KMP算法
    //其中T非空，
    vector<int> next(T.size());
    NEXT(T, next);
    string::size_type index, count = 0;
    for(index = 0; index < S.size(); ++index){
        int pos = 0;
        string::size_type iter = index;
        while (pos < T.size() && iter<S.size()){
            if (S[iter] == T[pos]){
                ++iter;
                ++pos;
            }
            else{
                if(pos == 0)
                    ++iter;
                else
                    pos = next[pos-1]+1;
            }
        }//whileend
        if(pos == T.size() && (iter - index) == T.size())
            ++count;
    }//forend
    return count;
}

void searching(ALGraph G){
    string key;
    cout << "请输入搜索的关键词：";
    cin >> key;
    for (int32_t i = 0; i < G.vexnum; i++){
        if(COUNT_KMP(G.vertices[i].name, key) || COUNT_KMP(G.vertices[i].description, key)){
            show_description(G, i);
        }
    }
}
