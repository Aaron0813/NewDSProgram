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

//ͣ����������Ϣ�Ĵ洢�ṹ
struct CarInfo {
    int number;//�����ĳ��ƺ�
    int time;//�����ĵ���ʱ��
    CarInfo() {}

    CarInfo(int num, int time) : number(num), time(time) {}
};

struct CarStack {
    int top;//ջ������ָ��
    CarInfo *elements;//ջ����
    int max_size;

    CarStack(int max_sz) {
        if (max_sz > 0) {
            max_size = max_sz;
            elements = new CarInfo[max_size];
            top = -1;
        } else
            cout << "��ʼ��ʧ�ܣ�ͣ��������ͣ�������������0" << endl;
    }
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

///////////////////////////////��������///////////////////////////////////////////
//�Զ���ջ�ĳ�ջ����
CarInfo StackPop(CarStack &carStack);

//�Զ���ջ�Ľ�ջ����
void StackPush(CarStack &carStack, CarInfo carInfo);

//�Զ�����е���Ӳ���
void QueuePush(CarQueue &carQueue, CarInfo carInfo);

//�Զ�����еĳ��Ӳ���
CarInfo QueuePop(CarQueue &carQueue);

//ͣ����������ں���
void Park();

//��������ͣ����
void EnterParking(CarStack &parking_stack, CarQueue &waiting_queue);

//�����뿪ͣ����
void DepartParking(CarStack &parking_stack, CarStack &temp_parking_stack, CarQueue &waiting_queue);

#endif //NEWDSPROGRAM_PARK_H
