//
//  car.h
//  smart_tourist_attraction
//
//  Created by 李文熙 on 16/11/20.
//  Copyright © 2016年 李文熙. All rights reserved.
//

#ifndef car_h
#define car_h

typedef struct zanlind{
    int number;                                                         //汽车车号
    int ar_time;                                                        //汽车到达时间
}zanInode;

typedef struct{
    zanInode *base;                                                     //停车场的堆栈底
    zanInode *top;                                                      //停车场的堆栈顶
    int stacksize_curren;
}stackhead;

void car_menu();                                                        //停车场系统菜单

void enter_park(stackhead &parking);                                    //进入停车场

void init_stackhead(stackhead &parking);                                //初始化停车场

bool get_top(stackhead parking, zanInode &e);                           //获取栈顶元素

bool is_empty(stackhead parking);                                       //判断栈是否为空
#endif /* car_h */
