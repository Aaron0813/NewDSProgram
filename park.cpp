//
// Created by Aaron on 2016/11/21.
//

#include "park.h"

//�Զ���ջ�ĳ�ջ����
CarInfo StackPop(CarStack &carStack) {

    if (carStack.top != -1) {  //ֻҪջ��Ϊ��
        //����ջ��Ԫ�أ������С��һ
        return carStack.elements[carStack.top--];
    } else {
        cout << "ջ�ѿգ��޷�������ջ" << endl;
//        return NULL;
    }
}

//�Զ���ջ�Ľ�ջ����
void StackPush(CarStack &carStack, CarInfo carInfo) {
    if (carStack.top != carStack.max_size) {//ֻҪջ��Ϊ�����Ϳ��Լ������Ԫ��
        carStack.elements[carStack.top++] = carInfo;
    } else {
        cout << "ջ�������޷�����������ջ����" << endl;
    }
}

//�Զ�����е���Ӳ���
void QueuePush(CarQueue &carQueue, CarInfo carInfo) {
    cout << "������" << endl;
    if (carQueue.front == NULL) {//����Ϊ��
        cout << "Ϊʲô�����" << endl;
        carQueue.front = carQueue.rear = new CarQueueNode(carInfo);

    } else
        carQueue.rear = carQueue.rear->link = new CarQueueNode(carInfo);
    carQueue.current_size++;
}

//�Զ�����еĳ��Ӳ���
CarInfo QueuePop(CarQueue &carQueue) {
    if (carQueue.front != NULL) {//�ж϶����Ƿ�Ϊ��
        CarQueueNode *carQueueNode = carQueue.front;
        CarInfo carInfo = carQueue.front->date;
        carQueue.front = carQueue.front->link;
        if (carQueue.front == NULL)//�����ʱ����Ϊ�գ����¶��е���Ϣ
            carQueue.rear = NULL;
        delete carQueueNode;
        carQueue.current_size--;
        return carInfo;
    } else
        cout << "�����ѿգ��޷����г��Ӳ���" << endl;
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
        cout << "**             ** ͣ�����������                 **" << endl;
        cout << "===================================================" << endl;
        cout << "**                                               **" << endl;
        cout << "**   A --- ���� �� ����   D --- ���� �� ����     **" << endl;
        cout << "**                                               **" << endl;
        cout << "**           E --- �˳�   ����                   **" << endl;
        cout << "===================================================" << endl;
        cout << "��ѡ�� :(A,D,E): ";
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

//��������ͣ����
void EnterParking(CarStack &parking_stack, CarQueue &waiting_queue) {
    int car_number, arrive_time;
    cout << "���ƺ�Ϊ�������ֵ���ʽ���룩��" << endl;
    cin >> car_number;
    cout << "��������복���ʱ��" << endl;
    cin >> arrive_time;
    CarInfo carInfo(car_number, arrive_time);
    if (parking_stack.top < parking_stack.max_size - 1) {//ͣ�������п�λ

        StackPush(parking_stack, carInfo);
        cout << "���ƺ�Ϊ " << car_number << "�������Ѿ�����ͣ������λ�� "
             << parking_stack.top + 1 << "�ų���" << endl;
    } else {
        cout << "������" << endl;
        QueuePush(waiting_queue, carInfo);
        cout << "��Ϊͣ���������� ���ƺ�Ϊ " << car_number << "������ͣ�ڱ����"
             << waiting_queue.current_size << "��λ����" << endl;
    }
}

//�����뿪ͣ����
void DepartParking(CarStack &parking_stack, CarStack &temp_parking_stack, CarQueue &waiting_queue) {
    int car_number, arrive_time, depart_time, money;

    cout << "���ƺ�Ϊ�������ֵ���ʽ���룩��" << endl;
    cin >> car_number;
    cout << "�������뿪�����ʱ��" << endl;
    cin >> depart_time;
    CarInfo enter_car, depart_car(car_number, depart_time);
//    CarQueueNode
    while (true) {
        enter_car = StackPop(parking_stack);
        StackPush(temp_parking_stack, enter_car);
        if (enter_car.number == car_number) {//�ҵ���Ҫ����������
            money = depart_time - enter_car.time;
            break;
        }
    }
    depart_car = StackPop(temp_parking_stack);//����Ҫ��ͣ����������
    cout << "���ƺ�Ϊ " << car_number << "�ĳ��Ѿ���ȥ������Ϊ�վ�" << endl;
    cout << "=================================�վ�=====================================" << endl;
    cout << "���ƺ�\n" << "����ͣ����ʱ��\n" << "�뿪ͣ����ʱ��\n" << "ͣ��ʱ��\n" << "�ɷѽ��" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << car_number << "\n" << depart_car.time << "\n" << depart_time << "\n" << depart_time - depart_car.time
         << "\n" << money << endl;

    while (temp_parking_stack.top != 0) {//����ʱͣ�����ĳ�ȫ������ȥ---��ֱ��ɵ��һ�����ͣ�������
        enter_car = StackPop(temp_parking_stack);
        StackPush(parking_stack, enter_car);
    }
    if (parking_stack.top < parking_stack.max_size && waiting_queue.current_size != 0) {//ͣ�����п�λ�������г����ڵȴ�
        enter_car = QueuePop(waiting_queue);
        enter_car.time = depart_time;
        StackPush(parking_stack, enter_car);
        cout << "���ƺ�Ϊ " << enter_car.number << "��������ͨ������ͣ������λ��" << parking_stack.top + 1 << " �ų�����" << endl;
    }
}