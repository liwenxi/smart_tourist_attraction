//
//  car.cpp
//  smart_tourist_attraction
//
//  Created by 李文熙 on 16/11/20.
//  Copyright © 2016年 李文熙. All rights reserved.
//

#include "car.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int MAX_STACK_NUM = 10;

void car_menu(){
    stackhead parking;
    while (true) {
        cout << "       **停车场管理系统**" << endl;
        cout << "===================================" << endl;
        cout << "**                               **" << endl;
        cout << "**    A--汽车进车场  D--汽车出车场   **" << endl;
        cout << "**                               **" << endl;
        cout << "**          E---退出程序           **" << endl;
        cout << "===================================" << endl;
        cout << "请选择：(A, D, E):";
        char32_t choose;
        choose = getchar();
        cin.get();
        switch (choose) {
            case 'A':
                enter_park(parking);
                break;
                
            case 'D':
                ;
                break;
                
            case 'E':
                break;
                
            default:
                break;
        }

    }
    }

void enter_park(stackhead &parking){
    zanInode *new_car;
    new_car = new zanInode;
    cout << "车牌号为：" << endl;
    cin >> (*new_car).number;
    cout << "进场的时刻：" << endl;
    cin >> (*new_car).ar_time;
}

void init_stackhead(stackhead &parking){
    parking.base = new zanInode[MAX_STACK_NUM];
    if (parking.base == NULL){
        std::cerr << "存储分配失败！" << endl;
        exit(1);
    }
    parking.top = parking.base;
    parking.stacksize_curren = MAX_STACK_NUM;
    
}

bool get_top(stackhead parking, zanInode &e){
    if (is_empty(parking)){
        return false;
    }else{
        e = (*parking.top);
        return true;
    }
}

bool is_empty(stackhead parking){
    if (parking.top == parking.base){
        return true;
    }else{
        return false;
    }
}
