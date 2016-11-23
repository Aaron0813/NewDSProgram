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

//ͣ����������Ϣ�Ĵ洢�ṹ
struct CarInfo {
    string number;//�����ĳ��ƺ�
    time_t time;//�����ĵ���ʱ��
    CarInfo() {}

    CarInfo(string num, time_t t) : number(num), time(t) {}
};

//�Զ���ջ
struct CarStack {
    int top;             //ջ������ָ��
    CarInfo *elements;   //ջ����
};

//�Զ�����еĻ����ڵ�
struct CarQueueNode {
    CarInfo date;
    CarQueueNode *link;

    CarQueueNode(CarInfo carInfo) {
        date = carInfo;
        link = NULL;
    }
};

//�Զ������
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

////�Զ�������ݽṹ�������洢�����Ѿ�����ͣ�������������ƺ�
//struct CarNumBook{
//    string car_num;
//    CarNumBook *link;
//    CarNumBook(string num):car_num(num),link(NULL){}
//    CarNumBook():car_num(""),link(NULL){}
//};

///////////////////////////////��������///////////////////////////////////////////
//��ʼ��ջ--�ɹ�����true������false--Ϊͣ������ʼ���õ�
bool StackInit(CarStack &carStack);

////��ʼ��ջ--�ɹ�����true������false--Ϊͣ������ʼ���õ�
//bool StackInit(CarStack &carStack,int size);

//�Զ���ջ�Ľ�ջ����--�ɹ�����true������false
bool StackPush(CarStack &carStack, CarInfo carInfo);

//�Զ���ջ�ĳ�ջ����
bool StackPop(CarStack &carStack, CarInfo &carInfo);

//��ʼ������
bool QueueInit(CarQueue &carQueue);

//�Զ�����е���Ӳ���
void QueuePush(CarQueue &carQueue, CarInfo carInfo);

//�Զ�����еĳ��Ӳ���
bool QueuePop(CarQueue &carQueue, CarInfo &carInfo);

//��������ͣ����
void EnterParking(CarStack &parking_stack, CarQueue &waiting_queue);

//�����뿪ͣ����
void DepartParking(CarStack &parking_stack, CarStack &temp_parking_stack, CarQueue &waiting_queue);

////���ݳ��ƺŲ��ҳ��Ƿ����
//bool FindByCarNum(CarNumBook *carNumBook,string num);
//
////����һ����Ϣ
//void InsertCarNum(CarNumBook *carNumBook,string num);
//
////ɾ��һ������
//void DeleteCarNum(CarNumBook *carNumBook,string num);


#endif //NEWDSPROGRAM_PARK_H
