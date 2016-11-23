//
// Created by Aaron on 2016/11/21.
//


#include "park.h"


//初始化栈
bool StackInit(CarStack &carStack) {
    carStack.elements = new CarInfo[PARK_MAX_SIZE];
    if (!carStack.elements)//初始化失败
        return false;
    else {//初始化成功，返回正确值
        carStack.top = -1;
        return true;
    }
}

//自定义栈的进栈操作
bool StackPush(CarStack &carStack, CarInfo carInfo) {
    if (carStack.top != PARK_MAX_SIZE) {//只要栈不为满，就可以继续添加元素
        carStack.top++;
        carStack.elements[carStack.top] = carInfo;
        return true;
    } else {
        cout << "栈已满，无法继续进行入栈操作" << endl;
        return false;
    }
}


//自定义栈的出栈操作
bool StackPop(CarStack &carStack, CarInfo &carInfo) {

    if (carStack.top != -1) {  //只要栈不为空
        //返回栈顶元素，数组大小减一
        carInfo = carStack.elements[carStack.top];
        carStack.top--;
        return true;
    } else {
//        cout << "栈已空，无法继续出栈" << endl;
        return false;
    }
}

//初始化队列
bool QueueInit(CarQueue &carQueue) {
    carQueue.front = carQueue.rear = NULL;
    carQueue.current_size = 0;
    return true;
}

//自定义队列的入队操作
void QueuePush(CarQueue &carQueue, CarInfo carInfo) {
    if (carQueue.front == NULL) {//当前队列为空，创建第一个结点
        carQueue.front = carQueue.rear = new CarQueueNode(carInfo);
    } else
        carQueue.rear = carQueue.rear->link = new CarQueueNode(carInfo);
    carQueue.current_size++;//更新队列大小
}

//自定义队列的出队操作
bool QueuePop(CarQueue &carQueue, CarInfo &carInfo) {
    if (carQueue.front != carQueue.rear) {//判断队列是否为空
        CarQueueNode *carQueueNode = carQueue.front;//取得当前栈顶元素
        carInfo = carQueue.front->date;//返回数据
        carQueueNode->link = NULL;//将顶部元素移除队列
        carQueue.front->link = NULL;//更新栈顶指针
        if (carQueue.rear == carQueueNode)//如果此时队列为空，更新队列的信息
            carQueue.rear = NULL;
        delete carQueueNode;
        carQueue.current_size--;
        return true;
    } else {
        cout << "队列已空，无法进行出队操作" << endl;
        return false;
    }

}

//汽车进入停车场
void EnterParking(CarStack &parking_stack, CarQueue &waiting_queue) {
//    string car_number;
//    time_t arrive_time;
    CarInfo carInfo;
//    while (true) {
//        cout << "请输入车牌号：" << endl;
//        cin >> car_number;
//        if (""==carNumBook.car_num) {
//            cout<<"进入判断"<<endl;
//            carNumBook.car_num=car_number;
//            break;
//        } else {
//            if (!FindByCarNum(carNumBook, car_number)) {
//                InsertCarNum(carNumBook, car_number);
//                break;
//            } else
//                cout << "车牌号重复，请重新输入" << endl;
//        }
//    }

    cout << "请输入车牌号：" << endl;
    cin >> carInfo.number;
    //获取当前系统时间
    carInfo.time = time(NULL);
//    cout << arrive_time << endl;

    if (parking_stack.top < PARK_MAX_SIZE - 1) {//停车场还有空位
        cout << "还有空" << endl;
        StackPush(parking_stack, carInfo);
        cout << "车牌号为 " << carInfo.number << "的汽车已经进入停车场，位于 "
             << parking_stack.top + 1 << "号车道" << endl;
    } else {
        cout << "车多了" << endl;
        QueuePush(waiting_queue, carInfo);
        cout << "因为停车场已满， 车牌号为 " << carInfo.number << "的汽车停于便道的"
             << waiting_queue.current_size << "个位置上" << endl;
    }
}

//汽车离开停车场
void DepartParking(CarStack &parking_stack, CarStack &temp_parking_stack, CarQueue &waiting_queue) {
    string car_number;
    time_t arrive_time, depart_time;
    int money;
    bool flag = false;//标志是否找到要出栈的车辆
    if (parking_stack.top != -1) {//当前栈不为空，可以进行出栈操作
        cout << "车牌号为：" << endl;
        cin >> car_number;
        depart_time = time(NULL);

        CarInfo temp;

        StackPop(parking_stack, temp);
        while (temp.number != car_number) {
            if (parking_stack.top == -1) {//没有找到要出来的车
                cout << "请确认你的车确实在这个停车场!!!" << endl;
                while (temp_parking_stack.top != -1) {//把临时停车场的车全部倒回去---简直跟傻逼一样这个停车场设计
                    StackPop(temp_parking_stack, temp);
                    StackPush(parking_stack, temp);
                }
                return;
            }
            StackPush(temp_parking_stack, temp);
            StackPop(parking_stack, temp);
        }

        money = depart_time - temp.time;
        cout << "车牌号为 " << car_number << "的车已经离去，以下为收据" << endl;
        cout << "=================================收据=====================================" << endl;
        cout << "车牌号\t" << "进入停车场时间\t" << "离开停车场时间\t" << "停留时间\t" << "缴费金额" << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        cout << car_number << "\t" << temp.time << "\t" << depart_time << "\t" << depart_time - depart_car.time
             << "\t" << money << endl;
        while (temp_parking_stack.top != -1) {//把临时停车场的车全部倒回去---简直跟傻逼一样这个停车场设计
            StackPop(temp_parking_stack, temp);
            StackPush(parking_stack, temp);
        }
        cout << "等待队列的长度为  " << waiting_queue.current_size << endl;
        if (parking_stack.top < PARK_MAX_SIZE - 1 && waiting_queue.current_size != 0) {//停车场有空位，并且有车辆在等待
            QueuePop(waiting_queue, temp);
            cout << "从队列出来的车辆的车牌号为  " << temp.number << endl;
            temp.time = depart_time;
            StackPush(parking_stack, temp);
            cout << "车牌号为 " << temp.number << "的汽车从通道进入停车场，位于" << parking_stack.top + 1 << " 号车道上" << endl;
        }
    } else {
        cout << "当前停车场为空！！！" << endl;
    }
}


void Park() {
//    CarNumBook carNumBook;
    CarStack parking_stack, temp_parking_stack;
    CarQueue waiting_queue;
    StackInit(parking_stack);
    StackInit(temp_parking_stack);
    QueueInit(waiting_queue);
    bool flag = true;
    while (flag) {
        string choose;
        cout << "**             ** 停车场管理程序                 **" << endl;
        cout << "===================================================" << endl;
        cout << "**                                               **" << endl;
        cout << "**   A --- 汽车 进 车场   D --- 汽车 出 车场     **" << endl;
        cout << "**                                               **" << endl;
        cout << "**           E --- 退出   程序                   **" << endl;
        cout << "===================================================" << endl;
        cout << "请选择 :(A,D,E): ";
        cin >> choose;
        if ("A" == choose) {
            EnterParking(parking_stack, waiting_queue);
        } else if ("D" == choose) {
            DepartParking(parking_stack, temp_parking_stack, waiting_queue);
        } else if ("E" == choose) {
            flag = false;
        } else {
            cout << "输入有误，请重新输入" << endl;
        }
    }
}












//

////根据车牌号查找车是否存在
//bool FindByCarNum(CarNumBook &carNumBook, string num) {
//    CarNumBook temp;
//    for (temp = carNumBook; temp; temp = temp.link)//遍历信息表
//        if (num == temp->car_num)
//            return true;
//    return false;
//}
//
////插入一条信息
//void InsertCarNum(CarNumBook *carNumBook, string num) {
//    CarNumBook *temp = new CarNumBook(num);
//    temp->link = carNumBook->link;
//    carNumBook->link = temp;
//}
//
////删除一条数据
//void DeleteCarNum(CarNumBook *carNumBook, string num) {
//    CarNumBook *pre,*temp;
//    bool flag = false;
//    for (pre = carNumBook;; pre = pre->link) {
//        if (pre->link->car_num == num) {
//            flag = true;
//            break;
//        }
//    }
//    //找到了所要删除节点的前一个节点
//    if (flag == true) {
//        temp=pre->link;//要删除的节点
//        pre->link=temp->link;//跳过要删除的节点---即为删除节点
//        delete temp;//删除节点数据
//    }
//}


