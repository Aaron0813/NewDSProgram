//
// Created by Aaron on 2016/11/21.
//


#include "park.h"


//��ʼ��ջ
bool StackInit(CarStack &carStack) {
    carStack.elements = new CarInfo[PARK_MAX_SIZE];
    if (!carStack.elements)//��ʼ��ʧ��
        return false;
    else {//��ʼ���ɹ���������ȷֵ
        carStack.top = -1;
        return true;
    }
}

//�Զ���ջ�Ľ�ջ����
bool StackPush(CarStack &carStack, CarInfo carInfo) {
    if (carStack.top != PARK_MAX_SIZE) {//ֻҪջ��Ϊ�����Ϳ��Լ������Ԫ��
        carStack.top++;
        carStack.elements[carStack.top] = carInfo;
        return true;
    } else {
        cout << "ջ�������޷�����������ջ����" << endl;
        return false;
    }
}


//�Զ���ջ�ĳ�ջ����
bool StackPop(CarStack &carStack, CarInfo &carInfo) {

    if (carStack.top != -1) {  //ֻҪջ��Ϊ��
        //����ջ��Ԫ�أ������С��һ
        carInfo = carStack.elements[carStack.top];
        carStack.top--;
        return true;
    } else {
//        cout << "ջ�ѿգ��޷�������ջ" << endl;
        return false;
    }
}

//��ʼ������
bool QueueInit(CarQueue &carQueue) {
    carQueue.front = carQueue.rear = NULL;
    carQueue.current_size = 0;
    return true;
}

//�Զ�����е���Ӳ���
void QueuePush(CarQueue &carQueue, CarInfo carInfo) {
    if (carQueue.front == NULL) {//��ǰ����Ϊ�գ�������һ�����
        carQueue.front = carQueue.rear = new CarQueueNode(carInfo);
    } else
        carQueue.rear = carQueue.rear->link = new CarQueueNode(carInfo);
    carQueue.current_size++;//���¶��д�С
}

//�Զ�����еĳ��Ӳ���
bool QueuePop(CarQueue &carQueue, CarInfo &carInfo) {
    if (carQueue.front != carQueue.rear) {//�ж϶����Ƿ�Ϊ��
        CarQueueNode *carQueueNode = carQueue.front;//ȡ�õ�ǰջ��Ԫ��
        carInfo = carQueue.front->date;//��������
        carQueueNode->link = NULL;//������Ԫ���Ƴ�����
        carQueue.front->link = NULL;//����ջ��ָ��
        if (carQueue.rear == carQueueNode)//�����ʱ����Ϊ�գ����¶��е���Ϣ
            carQueue.rear = NULL;
        delete carQueueNode;
        carQueue.current_size--;
        return true;
    } else {
        cout << "�����ѿգ��޷����г��Ӳ���" << endl;
        return false;
    }

}

//��������ͣ����
void EnterParking(CarStack &parking_stack, CarQueue &waiting_queue) {
//    string car_number;
//    time_t arrive_time;
    CarInfo carInfo;
//    while (true) {
//        cout << "�����복�ƺţ�" << endl;
//        cin >> car_number;
//        if (""==carNumBook.car_num) {
//            cout<<"�����ж�"<<endl;
//            carNumBook.car_num=car_number;
//            break;
//        } else {
//            if (!FindByCarNum(carNumBook, car_number)) {
//                InsertCarNum(carNumBook, car_number);
//                break;
//            } else
//                cout << "���ƺ��ظ�������������" << endl;
//        }
//    }

    cout << "�����복�ƺţ�" << endl;
    cin >> carInfo.number;
    //��ȡ��ǰϵͳʱ��
    carInfo.time = time(NULL);
//    cout << arrive_time << endl;

    if (parking_stack.top < PARK_MAX_SIZE - 1) {//ͣ�������п�λ
        cout << "���п�" << endl;
        StackPush(parking_stack, carInfo);
        cout << "���ƺ�Ϊ " << carInfo.number << "�������Ѿ�����ͣ������λ�� "
             << parking_stack.top + 1 << "�ų���" << endl;
    } else {
        cout << "������" << endl;
        QueuePush(waiting_queue, carInfo);
        cout << "��Ϊͣ���������� ���ƺ�Ϊ " << carInfo.number << "������ͣ�ڱ����"
             << waiting_queue.current_size << "��λ����" << endl;
    }
}

//�����뿪ͣ����
void DepartParking(CarStack &parking_stack, CarStack &temp_parking_stack, CarQueue &waiting_queue) {
    string car_number;
    time_t arrive_time, depart_time;
    int money;
    bool flag = false;//��־�Ƿ��ҵ�Ҫ��ջ�ĳ���
    if (parking_stack.top != -1) {//��ǰջ��Ϊ�գ����Խ��г�ջ����
        cout << "���ƺ�Ϊ��" << endl;
        cin >> car_number;
        depart_time = time(NULL);

        CarInfo temp;

        StackPop(parking_stack, temp);
        while (temp.number != car_number) {
            if (parking_stack.top == -1) {//û���ҵ�Ҫ�����ĳ�
                cout << "��ȷ����ĳ�ȷʵ�����ͣ����!!!" << endl;
                while (temp_parking_stack.top != -1) {//����ʱͣ�����ĳ�ȫ������ȥ---��ֱ��ɵ��һ�����ͣ�������
                    StackPop(temp_parking_stack, temp);
                    StackPush(parking_stack, temp);
                }
                return;
            }
            StackPush(temp_parking_stack, temp);
            StackPop(parking_stack, temp);
        }

        money = depart_time - temp.time;
        cout << "���ƺ�Ϊ " << car_number << "�ĳ��Ѿ���ȥ������Ϊ�վ�" << endl;
        cout << "=================================�վ�=====================================" << endl;
        cout << "���ƺ�\t" << "����ͣ����ʱ��\t" << "�뿪ͣ����ʱ��\t" << "ͣ��ʱ��\t" << "�ɷѽ��" << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        cout << car_number << "\t" << temp.time << "\t" << depart_time << "\t" << depart_time - depart_car.time
             << "\t" << money << endl;
        while (temp_parking_stack.top != -1) {//����ʱͣ�����ĳ�ȫ������ȥ---��ֱ��ɵ��һ�����ͣ�������
            StackPop(temp_parking_stack, temp);
            StackPush(parking_stack, temp);
        }
        cout << "�ȴ����еĳ���Ϊ  " << waiting_queue.current_size << endl;
        if (parking_stack.top < PARK_MAX_SIZE - 1 && waiting_queue.current_size != 0) {//ͣ�����п�λ�������г����ڵȴ�
            QueuePop(waiting_queue, temp);
            cout << "�Ӷ��г����ĳ����ĳ��ƺ�Ϊ  " << temp.number << endl;
            temp.time = depart_time;
            StackPush(parking_stack, temp);
            cout << "���ƺ�Ϊ " << temp.number << "��������ͨ������ͣ������λ��" << parking_stack.top + 1 << " �ų�����" << endl;
        }
    } else {
        cout << "��ǰͣ����Ϊ�գ�����" << endl;
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
        cout << "**             ** ͣ�����������                 **" << endl;
        cout << "===================================================" << endl;
        cout << "**                                               **" << endl;
        cout << "**   A --- ���� �� ����   D --- ���� �� ����     **" << endl;
        cout << "**                                               **" << endl;
        cout << "**           E --- �˳�   ����                   **" << endl;
        cout << "===================================================" << endl;
        cout << "��ѡ�� :(A,D,E): ";
        cin >> choose;
        if ("A" == choose) {
            EnterParking(parking_stack, waiting_queue);
        } else if ("D" == choose) {
            DepartParking(parking_stack, temp_parking_stack, waiting_queue);
        } else if ("E" == choose) {
            flag = false;
        } else {
            cout << "������������������" << endl;
        }
    }
}












//

////���ݳ��ƺŲ��ҳ��Ƿ����
//bool FindByCarNum(CarNumBook &carNumBook, string num) {
//    CarNumBook temp;
//    for (temp = carNumBook; temp; temp = temp.link)//������Ϣ��
//        if (num == temp->car_num)
//            return true;
//    return false;
//}
//
////����һ����Ϣ
//void InsertCarNum(CarNumBook *carNumBook, string num) {
//    CarNumBook *temp = new CarNumBook(num);
//    temp->link = carNumBook->link;
//    carNumBook->link = temp;
//}
//
////ɾ��һ������
//void DeleteCarNum(CarNumBook *carNumBook, string num) {
//    CarNumBook *pre,*temp;
//    bool flag = false;
//    for (pre = carNumBook;; pre = pre->link) {
//        if (pre->link->car_num == num) {
//            flag = true;
//            break;
//        }
//    }
//    //�ҵ�����Ҫɾ���ڵ��ǰһ���ڵ�
//    if (flag == true) {
//        temp=pre->link;//Ҫɾ���Ľڵ�
//        pre->link=temp->link;//����Ҫɾ���Ľڵ�---��Ϊɾ���ڵ�
//        delete temp;//ɾ���ڵ�����
//    }
//}


