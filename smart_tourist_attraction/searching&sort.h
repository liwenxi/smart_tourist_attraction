//
//  searching&sort.h
//  smart_tourist_attraction
//
//  Created by 李文熙 on 16/11/23.
//  Copyright © 2016年 李文熙. All rights reserved.
//

#ifndef searching_sort_h
#define searching_sort_h

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void info_menu(ALGraph &G);                                                         //景点信息的菜单

void creat_description(ALGraph &G);                                                 //创建景点的信息

void show_all(ALGraph G);                                                           //显示所有景点的信息

void show_description(ALGraph G, int32_t num);                                      //显示单个景点的信息

void searching(ALGraph G);                                                           //搜索函数

inline void NEXT(const string &T, vector<int> &next);

inline string::size_type COUNT_KMP(const string &S, const string &T);
#endif /* searching_sort_h */
