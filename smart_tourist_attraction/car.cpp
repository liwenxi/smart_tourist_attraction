//
//  car.cpp
//  smart_tourist_attraction
//
//  Created by 李文熙 on 16/11/20.
//  Copyright © 2016年 李文熙. All rights reserved.
//

#include "car.h"
#include <iostream>
#include<ctime>

using std::cout;
using std::cin;
using std::endl;

const int MAX_STACK_NUM = 10;

LinkQueue wait_queue;

void car_menu(){                                                                        //总菜单
    stackhead parking;
    init_stackhead(parking);                                                            //对停车场和候车道进行初始化
    init_queue(wait_queue);
    char choose;
    while (true) {
        cout << "       **停车场管理系统**" << endl;
        cout << "===================================" << endl;
        cout << "**                               **" << endl;
        cout << "**    A--汽车进车场  D--汽车出车场   **" << endl;
        cout << "**                               **" << endl;
        cout << "**          E---退出程序           **" << endl;
        cout << "===================================" << endl;
        cout << "请选择：(A, D, E):";
        cin >> choose;
        switch (choose) {
            case 'A':
                enter_park(parking);
                break;
                
            case 'D':
                leave_park(parking);
                break;
                
            case 'E':
                return;
                break;
                
            default:
                cout << "输入错误" << endl;
                break;
        }

    }
}

int park_num = 0;

void enter_park(stackhead &parking){
    zanInode new_car;                                                                  //创建车辆的信息
    cout << "车牌号为：";
    cin >> new_car.number;
    while(cin.fail())
    {
        cout << "输入错误，请重新输入！\a" << endl;
        cin.clear();
        cin.ignore();
        cout << "车牌号为：";
        cin >> new_car.number;
    }
    cout << "进场的时刻：";
    cout << (new_car.ar_time = int (time(NULL))) << endl;
    if (push(parking, new_car)){
        park_num++;
        cout << new_car.number << "车已进入停车场，停靠在第" << park_num << "个车位" << endl;
    }else{
        cout << "停车场已满，请等待" << endl;
        enter_queue(wait_queue, new_car);
    }
}

void leave_park(stackhead &parking){
    zanInode new_car;                                                                  //创建车辆的信息
    cout << "车牌号为：";
    cin >> new_car.number;
    while(cin.fail())
    {
        cout << "输入错误，请重新输入！\a" << endl;
        cin.clear();
        cin.ignore();
        cout << "车牌号为：";
        cin >> new_car.number;
    }
//    cout << "出场的时刻：" << (new_car.ar_time = int (time(NULL))) << endl;
    new_car.ar_time = int (time(NULL));
    for (int32_t i = 0; i < parking.stacksize_curren; i++){
        zanInode temp;
        if (pop(parking, temp)){
            if (temp.number == new_car.number){
                cout << new_car.number << "车开出停车场，费用" << (new_car.ar_time - temp.ar_time) * 0.01 << "元" << endl;
                park_num--;
                break;
            }else{
                park_num--;
                insert_queue(wait_queue, temp);
            }
        }else{
            cout << "查无此车" << endl;
            break;
        }
    }
    
    for (int32_t i = 0; i < parking.stacksize_curren; i++){
        zanInode temp;
        if (!dele_queue(wait_queue, temp)){
            cout << "something wrong\n";
            break;
        }
        if (push(parking, temp)){
            park_num++;
            cout << temp.number << "车已进入停车场，停靠在第" << park_num << "个车位" << endl;
        }else{
//            cout << "停车场已满，请等待" << endl;
            break;
        }
    }
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

bool push(stackhead &parking, zanInode &e){
    if (parking.top - parking.base >= parking.stacksize_curren){                        //栈满
        return false;
    }
    *parking.top ++ = e;
    return true;
}

bool pop(stackhead &parking, zanInode &e){
    if (is_empty(parking)){
        return false;
    }
    e = * --parking.top;
    return true;
}

void init_queue(LinkQueue &Q){
    Q.front = Q.rear = new QNode();
    if (Q.front == NULL){
        std::cerr << "存储分配失败！" << endl;
        exit(1);
    }
    (*Q.front).next = NULL;
}

bool enter_queue(LinkQueue &Q, zanInode e){
    QueuePtr p = new QNode();
    (*p).data = e;
    (*p).next = NULL;
    (*Q.rear).next = p;
    Q.rear = p;
    return true;
}

bool dele_queue(LinkQueue &Q, zanInode &e){
    if (Q.rear == Q.front){
        return false;
    }
    QueuePtr p = (*Q.front).next;
    e = (*p).data;
    (*Q.front).next = (*p).next;
    if (Q.rear == p){
        Q.rear = Q.front;
    }
//    delete(p);
    return true;
}

bool insert_queue(LinkQueue &Q, zanInode e){
    QueuePtr p = new QNode();
    if (Q.rear == Q.front){
        enter_queue(Q, e);
        return true;
    }
    (*p).data = e;
    (*p).next = (*Q.front).next;
    (*Q.front).next = p;
    return true;
}
