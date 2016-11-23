//
// Created by Aaron on 2016/11/21.
//

#ifndef NEWDSPROGRAM_PARK_H
#define NEWDSPROGRAM_PARK_H

#define PARK_MAX_SIZE 3

#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <cstdio>
#include <ctime>

using namespace std;

//停车场车辆信息的存储结构
struct CarInfo {
    string number;//汽车的车牌号
    time_t time;//汽车的到达时间
    CarInfo() {}

    CarInfo(string num, time_t t) : number(num), time(t) {}
};

//自定义栈
struct CarStack {
    int top;             //栈顶数组指针
    CarInfo *elements;   //栈数组
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

////自定义的数据结构，用来存储所有已经进入停车场的汽车车牌号
//struct CarNumBook{
//    string car_num;
//    CarNumBook *link;
//    CarNumBook(string num):car_num(num),link(NULL){}
//    CarNumBook():car_num(""),link(NULL){}
//};

///////////////////////////////函数定义///////////////////////////////////////////
//初始化栈--成功返回true，否则false--为停车场初始化用的
bool StackInit(CarStack &carStack);

////初始化栈--成功返回true，否则false--为停车场初始化用的
//bool StackInit(CarStack &carStack,int size);

//自定义栈的进栈操作--成功返回true，否则false
bool StackPush(CarStack &carStack, CarInfo carInfo);

//自定义栈的出栈操作
bool StackPop(CarStack &carStack, CarInfo &carInfo);

//初始化队列
bool QueueInit(CarQueue &carQueue);

//自定义队列的入队操作
void QueuePush(CarQueue &carQueue, CarInfo carInfo);

//自定义队列的出队操作
bool QueuePop(CarQueue &carQueue, CarInfo &carInfo);

//汽车进入停车场
void EnterParking(CarStack &parking_stack, CarQueue &waiting_queue);

//汽车离开停车场
void DepartParking(CarStack &parking_stack, CarStack &temp_parking_stack, CarQueue &waiting_queue);

////根据车牌号查找车是否存在
//bool FindByCarNum(CarNumBook *carNumBook,string num);
//
////插入一条信息
//void InsertCarNum(CarNumBook *carNumBook,string num);
//
////删除一条数据
//void DeleteCarNum(CarNumBook *carNumBook,string num);


#endif //NEWDSPROGRAM_PARK_H
