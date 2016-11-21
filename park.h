//
// Created by Aaron on 2016/11/21.
//

#ifndef NEWDSPROGRAM_PARK_H
#define NEWDSPROGRAM_PARK_H

#include <string>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

//停车场车辆信息的存储结构
struct CarInfo {
    int number;//汽车的车牌号
    int time;//汽车的到达时间
    CarInfo() {}

    CarInfo(int num, int time) : number(num), time(time) {}
};

struct CarStack {
    int top;//栈顶数组指针
    CarInfo *elements;//栈数组
    int max_size;

    CarStack(int max_sz) {
        if (max_sz > 0) {
            max_size = max_sz;
            elements = new CarInfo[max_size];
            top = -1;
        } else
            cout << "初始化失败，停车场最大可停车数量必须大于0" << endl;
    }
};

//自定义队列的基本节点
struct CarQueueNode {
    CarInfo date;
    CarQueueNode *link;

    CarQueueNode(CarInfo carInfo) {
        date = carInfo;
        link = NULL;
    }
};

//自定义队列
struct CarQueue {
    CarQueueNode *front;
    CarQueueNode *rear;
    int current_size;
//    CarQueue(){
//        current_size=0;
//        front=rear=NULL;
//    }
//    ~CarQueue(){
//        CarQueueNode *p;
//        while (front!=NULL){
//            p=front;
//            front=front->link;
//            delete p;
//        }
//    }
};

///////////////////////////////函数定义///////////////////////////////////////////
//自定义栈的出栈操作
CarInfo StackPop(CarStack &carStack);

//自定义栈的进栈操作
void StackPush(CarStack &carStack, CarInfo carInfo);

//自定义队列的入队操作
void QueuePush(CarQueue &carQueue, CarInfo carInfo);

//自定义队列的出队操作
CarInfo QueuePop(CarQueue &carQueue);

//停车场程序入口函数
void Park();

//汽车进入停车场
void EnterParking(CarStack &parking_stack, CarQueue &waiting_queue);

//汽车离开停车场
void DepartParking(CarStack &parking_stack, CarStack &temp_parking_stack, CarQueue &waiting_queue);

#endif //NEWDSPROGRAM_PARK_H
