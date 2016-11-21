//
// Created by Aaron on 2016/11/21.
//

#include "park.h"

//自定义栈的出栈操作
CarInfo StackPop(CarStack &carStack) {

    if (carStack.top != -1) {  //只要栈不为空
        //返回栈顶元素，数组大小减一
        return carStack.elements[carStack.top--];
    } else {
        cout << "栈已空，无法继续出栈" << endl;
//        return NULL;
    }
}

//自定义栈的进栈操作
void StackPush(CarStack &carStack, CarInfo carInfo) {
    if (carStack.top != carStack.max_size) {//只要栈不为满，就可以继续添加元素
        carStack.elements[carStack.top++] = carInfo;
    } else {
        cout << "栈已满，无法继续进行入栈操作" << endl;
    }
}

//自定义队列的入队操作
void QueuePush(CarQueue &carQueue, CarInfo carInfo) {
    cout << "进来了" << endl;
    if (carQueue.front == NULL) {//队列为空
        cout << "为什么会出错？" << endl;
        carQueue.front = carQueue.rear = new CarQueueNode(carInfo);

    } else
        carQueue.rear = carQueue.rear->link = new CarQueueNode(carInfo);
    carQueue.current_size++;
}

//自定义队列的出队操作
CarInfo QueuePop(CarQueue &carQueue) {
    if (carQueue.front != NULL) {//判断队列是否为空
        CarQueueNode *carQueueNode = carQueue.front;
        CarInfo carInfo = carQueue.front->date;
        carQueue.front = carQueue.front->link;
        if (carQueue.front == NULL)//如果此时队列为空，更新队列的信息
            carQueue.rear = NULL;
        delete carQueueNode;
        carQueue.current_size--;
        return carInfo;
    } else
        cout << "队列已空，无法进行出队操作" << endl;
}

void Park() {
    int max_size = 1;
    CarStack parking_stack(max_size), temp_parking_stack(max_size);
    CarQueue waiting_queue;
    waiting_queue.current_size = 0;
    waiting_queue.front = waiting_queue.rear = NULL;
    bool flag = true;
    while (flag) {
        char choose;
        cout << "**             ** 停车场管理程序                 **" << endl;
        cout << "===================================================" << endl;
        cout << "**                                               **" << endl;
        cout << "**   A --- 汽车 进 车场   D --- 汽车 出 车场     **" << endl;
        cout << "**                                               **" << endl;
        cout << "**           E --- 退出   程序                   **" << endl;
        cout << "===================================================" << endl;
        cout << "请选择 :(A,D,E): ";
        cin >> choose;
        switch (choose) {
            case 'A':
                EnterParking(parking_stack, waiting_queue);
                break;
            case 'D':
                DepartParking(parking_stack, temp_parking_stack, waiting_queue);
                break;
            case 'E':
                flag = false;
                break;
        }
    }
}

//汽车进入停车场
void EnterParking(CarStack &parking_stack, CarQueue &waiting_queue) {
    int car_number, arrive_time;
    cout << "车牌号为（以数字的形式输入）：" << endl;
    cin >> car_number;
    cout << "请输入进入车库的时间" << endl;
    cin >> arrive_time;
    CarInfo carInfo(car_number, arrive_time);
    if (parking_stack.top < parking_stack.max_size - 1) {//停车场还有空位

        StackPush(parking_stack, carInfo);
        cout << "车牌号为 " << car_number << "的汽车已经进入停车场，位于 "
             << parking_stack.top + 1 << "号车道" << endl;
    } else {
        cout << "车多了" << endl;
        QueuePush(waiting_queue, carInfo);
        cout << "因为停车场已满， 车牌号为 " << car_number << "的汽车停于便道的"
             << waiting_queue.current_size << "个位置上" << endl;
    }
}

//汽车离开停车场
void DepartParking(CarStack &parking_stack, CarStack &temp_parking_stack, CarQueue &waiting_queue) {
    int car_number, arrive_time, depart_time, money;

    cout << "车牌号为（以数字的形式输入）：" << endl;
    cin >> car_number;
    cout << "请输入离开车库的时间" << endl;
    cin >> depart_time;
    CarInfo enter_car, depart_car(car_number, depart_time);
//    CarQueueNode
    while (true) {
        enter_car = StackPop(parking_stack);
        StackPush(temp_parking_stack, enter_car);
        if (enter_car.number == car_number) {//找到了要倒出的汽车
            money = depart_time - enter_car.time;
            break;
        }
    }
    depart_car = StackPop(temp_parking_stack);//弹出要出停车场的汽车
    cout << "车牌号为 " << car_number << "的车已经离去，以下为收据" << endl;
    cout << "=================================收据=====================================" << endl;
    cout << "车牌号\n" << "进入停车场时间\n" << "离开停车场时间\n" << "停留时间\n" << "缴费金额" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << car_number << "\n" << depart_car.time << "\n" << depart_time << "\n" << depart_time - depart_car.time
         << "\n" << money << endl;

    while (temp_parking_stack.top != 0) {//把临时停车场的车全部倒回去---简直跟傻逼一样这个停车场设计
        enter_car = StackPop(temp_parking_stack);
        StackPush(parking_stack, enter_car);
    }
    if (parking_stack.top < parking_stack.max_size && waiting_queue.current_size != 0) {//停车场有空位，并且有车辆在等待
        enter_car = QueuePop(waiting_queue);
        enter_car.time = depart_time;
        StackPush(parking_stack, enter_car);
        cout << "车牌号为 " << enter_car.number << "的汽车从通道进入停车场，位于" << parking_stack.top + 1 << " 号车道上" << endl;
    }
}