#include "AirPassengerBookingSystem.h"

//���������ͷָ��
Flight* pFlight;

//��������
Flight basicFlight[7] = {
        {1, "����", "����", "A1111", "����һ", 10, 10, 5},
        {2, "����", "����", "A2222", "���ڶ�", 8,  8,  4},
        {3, "����", "����", "B3333", "������", 10, 10, 5},
        {4, "����", "����", "B4444", "������", 8,  8,  4},
        {5, "����", "�Ϻ�", "C5555", "������", 10, 10, 5},
        {6, "����", "����", "D6666", "������", 8,  8,  4},
        {7, "����", "����", "E7777", "������", 10, 10, 5}
};

/**
 * ��ʼ���Ѷ�Ʊ�˿�ָ������
 * @param cusLinkList �����г�Ա�����ͷָ��
 * @return �Ƿ�ɹ�
 */
Status initCustomerLinkList(CustomerLinkList& cusLinkList) {
    cusLinkList = (CustomerNode*)malloc(sizeof(CustomerNode));
    if (NULL == cusLinkList)return OVERFLOW;
    cusLinkList->next = NULL;
    return OK;
}

/**
 * ��ʼ����ͷ���ĺ�������
 * @param q ������ָ��
 * @return �Ƿ�ɹ�
 */
Status initWaitQueue(WaitLinkQueue& q) {
    WaitQNode* p;
    p = (WaitQNode*)malloc(sizeof(WaitQNode));
    if (NULL == p) return OVERFLOW;

    p->next = NULL;
    q.front = q.rear = p;
    return OK;
}

/**
 * �����������
 * @param q ��������
 * @param name ����
 * @param amount ��Ʊ��
 * @param identification ���֤�� 
 * @return ��������
*/
WaitLinkQueue enWaitQueue(WaitLinkQueue& q, char name[], int preBookingVolume, char IDNumber[]) {
    PWait newPassenger;
    newPassenger = (PWait)malloc(sizeof(WaitQNode));
    strcpy(newPassenger->name, name);
    strcpy(newPassenger->IDNumber, IDNumber);
    newPassenger->preBookingVolume = preBookingVolume;
    newPassenger->next = NULL;

    q.rear->next = newPassenger;
    q.rear = newPassenger;

    return q;
}

/**
 * �򲹶��г���
 * @param q
 * @param waitName ����
 * @param waitIDNumber ���֤��
 * @param preBookingVolume ��Ԥ��Ʊ��
 * @return �Ƿ���ӳɹ�
*/
Status deWaitQueue(WaitLinkQueue& q, char waitName[], char waitIDNumber[], int& preBookingVolume) {
    WaitQNode* p = q.front->next;
    
    if (q.front == q.rear) return ERROR;
    
    q.front->next = p->next;
    
    if (NULL == q.front->next) {
        q.rear = q.front;
    }

    preBookingVolume = p->preBookingVolume;
    strcpy(waitName, p->name);
    strcpy(waitIDNumber, p->IDNumber);
    free(p);

    return OK;
}

/**
 * ��basicFlight��ͷ���뷨���뵽pFlight��������
 * @param basicFlight ������л�������
 * @return ���ز����Ƿ�ɹ�
 */
Status createBasicFlight(PFlight basicFlight) {
    Flight* p = pFlight, * q;

    for (int i = 0; i < 7; i++) {
        q = (Flight*)malloc(sizeof(Flight));
        if (NULL == q)return OVERFLOW;

        q->ID = basicFlight[i].ID;
        strcpy(q->startPoint, basicFlight[i].startPoint);
        strcpy(q->destination, basicFlight[i].destination);
        strcpy(q->planeNum, basicFlight[i].planeNum);
        strcpy(q->day, basicFlight[i].day);
        q->totalTickets = basicFlight[i].totalTickets;
        q->left = basicFlight[i].totalTickets;
        q->leftEconomicTicket = basicFlight[i].leftEconomicTicket;
        q->leftBusinessTicket = basicFlight[i].totalTickets - basicFlight[i].leftEconomicTicket;
        //��ʼ���˿�����
        initCustomerLinkList(q->cusLinkList);
        initWaitQueue(q->economicWaitQueue);
        initWaitQueue(q->businessWaitQueue);

        q->next = p->next;
        p->next = q;
    }
    return OK;
}

/**
 * ��ʼ����������
 */
Status initFlight() {
    pFlight = (Flight*)malloc(sizeof(Flight));//����ͷ���Ŀռ�
    if (NULL == pFlight) return OVERFLOW;
    pFlight->next = NULL;//��ͷ���h��ָ������Ϊ��

    //������������
    if (OK != createBasicFlight(basicFlight))return ERROR;

    return OK;
}

/**
 * ���ݺ���ID��ѯ���ಢ��ָ����ʽ����
 * @return  ����ָ��
 */
Flight* find() {
    int ID = 0;

    printf("�����뺽��ID: ");
    scanf("%d", &ID);

    //ͷ������һ���ڵ㿪ʼ����
    Flight* p = pFlight->next;

    while (NULL != p) {
        if (ID == p->ID)return p;

        p = p->next;
    }
    return NULL;
}

/**
 * ���ĳһ������Ϣ
 * @param p ����ڵ�
 */
void showSingleFlight(Flight* p) {
    printf("���վ��\t�յ�վ��\t����ID\t�ɻ���\t��������\t��Ա����\t��Ʊ��\t����Ʊʣ��\t����Ʊʣ��\n");
    printf("%3d\t%8s\t%8s\t%s\t%4s\t\t%3d\t%10d\t%10d\t%10d\n",
        p->ID,
        p->startPoint,
        p->destination,
        p->planeNum,
        p->day,
        p->totalTickets,
        p->left,
        p->leftEconomicTicket,
        p->leftBusinessTicket);
    printf("\n\n");
}

/**
 * ��ӡȫ��������Ϣ
 * @param pflight ������Ǻ��������ͷָ��
 */
void showAllFlight(Flight* pflight) {
    Flight* p = pflight->next;
    system("cls");
    printf("����ID\t���վ��\t�յ�վ��\t�ɻ���\t��������\t��Ա����\t��Ʊ��\t����Ʊʣ����\t����Ʊʣ����\n");
    while (NULL != p) {
        //����Display������ӡ��ÿ������ڵ����Ϣ
        printf("%3d\t%8s\t%8s\t%s\t%4s\t\t%3d\t%10d\t%10d\t%10d\n",
            p->ID,
            p->startPoint,
            p->destination,
            p->planeNum,
            p->day,
            p->totalTickets,
            p->left,
            p->leftEconomicTicket,
            p->leftBusinessTicket);
        p = p->next;
    }
    printf("\n\n");
}

/**
 * ��֤����Ա����
 * @return ���ز������
 */
Status adminVerify() {
    char pwd[20] = "admin";//����Ա����
    char password[20];//���������룬������֤
    printf("���������Ա����:\n");
    scanf("%s", password);
    if (strcmp(pwd, password)) {
        printf("�����������������:\n");
        return FALSE;
    }
    printf("��֤�ɹ�\n");
    return TRUE;
}

/**
  * ����Ա
  * ��Ӻ���
  * ͷ���뷨
  * @return ���ز����Ƿ�ɹ�
  */
Status adminInsertFlight() {
    FlightNode* q;
    Flight* p = pFlight;
    int flag = 1;

    while (flag != 0) {
        q = (FlightNode*)malloc(sizeof(FlightNode));
        if (NULL == q)return OVERFLOW;

        printf("\t\t������������������\n");
        
        printf("\t\t���������վ��\n");
        scanf("%s", q->startPoint);
        printf("\t\t�������յ�վ��\n");
        scanf("%s", q->destination);
        printf("\t\t������ɻ���\n");
        scanf("%s", q->planeNum);
        printf("\t\t�������������(1��������,2�������ڶ�.....7����������)\n");
        int day1;
        scanf("%d", &day1);
        while (ERROR == inputDay(day1, q->day)) {
            printf("������Ϸ�����(1-7)\n");
            scanf("%d", &day1);
        };

        printf("\t\t������˿Ͷ���\n");
        scanf("%d", &q->totalTickets);
        q->left = q->totalTickets;

        printf("\t\t�����뾭��Ʊ��Ŀ��ͬʱҲ����������Ʊ����Ŀ��\n");
        scanf("%d", &q->leftEconomicTicket);
        //����Ʊ��Ŀ = ��Ʊ��Ŀ - ����Ʊ��Ŀ
        q->leftBusinessTicket = q->totalTickets - q->leftEconomicTicket;

        q->ID = pFlight->next->ID + 1;

        initCustomerLinkList(q->cusLinkList);
        //��ʼ��
        initWaitQueue(q->economicWaitQueue);
        initWaitQueue(q->businessWaitQueue);

        q->next = p->next;
        p->next = q;

        printf("\t\t�Ƿ����¼�뺽����Ϣ���������ּ�����0��ʾֹͣ����\n");
        printf("\t\t�����룺");
        scanf("%d", &flag);
    }
    return OK;
}

/**
  * ����Ա
  * ɾ������
  * @return ���ز����Ƿ�ɹ�
  */
Status adminDeleteFlight() {
    int ID = 0;
    printf("�����뺽��ID\n");
    scanf("%d", &ID);
    PFlight pre = pFlight;
    PFlight p = pre->next;

    while (p != NULL) {
        if (ID == p->ID) {
            pre->next = p->next;
            free(p);
            return OK;
        }
        pre = p;
        p = p->next;
    }
    return ERROR;

}

/**
 * ����Ա
 * ��ѯĳһ����Ŀͻ���Ϣ
 */
void adminShowCustomerInfo() {
    Flight* flight = find();
    if (NULL == flight) {
        printf("û���������\n");
        return;
    }
    CustomerLinkList p = flight->cusLinkList->next;
    if (NULL != p) {
        printf("�ͻ�����   ��Ʊ����   ��λ�ȼ���1���òգ�2����գ�    ���֤����\n");
        while (p) {
            printf("%s\t\t%d\t\t%d\t\t\t%s\n", p->name, p->bookingvVolume, p->rank, p->IDNumber);
            p = p->next;
        }
    }
    else
        printf("�ú���û�пͻ���Ϣ!!\n");
}

/**
 * ��������ʱ�������ڵĸ���������1��������һ��7���������գ�
 * @param inputDay 1-7
 * @param day ������������ڱ���
 * @return ���ز���״̬�������Ƿ�Ϸ�
 */
Status inputDay(int inputDay, char day[]) {
    switch (inputDay) {
    case Mon:
        strcpy(day, "����һ");
        break;
    case Tues:
        strcpy(day, "���ڶ�");
        break;
    case Wed:
        strcpy(day, "������");
        break;
    case Thur:
        strcpy(day, "������");
        break;
    case Fri:
        strcpy(day, "������");
        break;
    case Sat:
        strcpy(day, "������");
        break;
    case Sun:
        strcpy(day, "������");
        break;
    default:
        return ERROR;
    }
    return OK;
}

/**
 * ���ݿͻ��������㣬�յ�վ�����������Ϣ
 */
void userSearchFlight() {
    char startPonit[10];
    char destination[10];
    int flag = 0;
    system("cls");
    printf("���������վ��: (��ȫ��������0)\n");
    scanf("%s", startPonit);
    printf("�������յ�վ��: (��ȫ��������0)\n");
    scanf("%s", destination);
    struct Flight* p;
    p = pFlight->next;
    printf("����ID\t���վ��\t�յ�վ��\t�ɻ���\t��������\t��Ա����\t��Ʊ��\t����Ʊʣ����\t����Ʊʣ����\n");

    while (NULL != p) {
        if (((strcmp(startPonit, "0") == 0) || (strcmp(startPonit, p->startPoint) == 0))
            && ((strcmp(destination, "0") == 0) || (strcmp(destination, p->destination) == 0))) {
            flag = 1;
            printf("%3d\t%8s\t%8s\t%s\t%4s\t\t%3d\t%10d\t%10d\t%10d\n",
                p->ID,
                p->startPoint,
                p->destination,
                p->planeNum,
                p->day,
                p->totalTickets,
                p->left,
                p->leftEconomicTicket,
                p->leftBusinessTicket);
        }
        p = p->next;
    }

    printf("\n\n");

    if (flag == 0)
        printf("�Բ��𣬸ú���δ�ҵ�! \n");
}

/**
 * ����ͬһ·�ߵ���������
 * @return �Ƿ���ҳɹ�
 */
Status showSameFlight(Flight* flight) {
    //��Ǳ������Ƿ��ҵ�ͬһ·�ߵĺ���
    int flag = 0;
    struct Flight* p;
    p = pFlight->next;
    printf("\n����Ѱ��ͬһ·�ߵĺ���...\n\n");
    printf("����ID\t���վ��\t�յ�վ��\t�ɻ���\t��������\t��Ա����\t��Ʊ��\t����Ʊʣ����\t����Ʊʣ����\n");

    while (p != NULL) {
        //·����ͬ���Ҳ���ͬһ�����࣬���flag = 1����ʾ�ҵ�
        if (strcmp(flight->destination, p->destination) == 0 && strcmp(flight->startPoint, p->startPoint) == 0 && p != flight) {
            flag = 1;
            printf("%3d\t%8s\t%8s\t%s\t%4s\t\t%3d\t%10d\t%10d\t%10d\n",
                p->ID,
                p->startPoint,
                p->destination,
                p->planeNum,
                p->day,
                p->totalTickets,
                p->left,
                p->leftEconomicTicket,
                p->leftBusinessTicket);
        }
        p = p->next;

    }
    printf("\n\n");

    //û����ͬ·�ߵĺ���
    if (flag == 0)
        return FALSE;
    return TRUE;
}

/**
 * �Ƽ���Ʊ
 * @param flight ԭ���࣬��������ѡ��ͬһ·�ߵ���ͬ����ID�ĺ���
 */
void userRecommendBookTicket(Flight* flight) {
    Status status = showSameFlight(flight);
    if (status == FALSE)
        printf("�Բ���û����ͬ�����յ�ĺ�����\n");
    else {
        printf("�Ƿ���϶�ƱҪ�󣿣�Y|N�� \n");
        {
            getchar();//�����س�
            char r = getchar();
            if (r == 'Y' || r == 'y') {
                userBookTicket();
                system("PAUSE");
            }
            else {
                printf("�����ݽ�����ж�Ʊ�����ڽ��˻����˵�");
                system("PAUSE");
                userMenu();
            }
        }
    }
}


/**
 * ��Ʊ�ɹ�֮�󣬽��˿���Ϣ���뵽��Ӧ����Ķ�Ʊ�˿�����
 * @param head �˿�����ͷָ��
 * @param amount �ó˿Ͷ�Ʊ������
 * @param name �˿͵�����
 * @param rank ��Ʊ�ĵȼ�
 * @return  �˿�����ͷָ��
 */
CustomerLinkList insertCustomerLinklist(CustomerLinkList& head, char name[], char IDNumber[], int bookingVolume, int rank) {
    CustomerLinkList newCustomer = (CustomerNode*)malloc(sizeof(CustomerNode));
    if (NULL == newCustomer) return NULL;

    strcpy(newCustomer->name, name);
    strcpy(newCustomer->IDNumber, IDNumber);
    newCustomer->bookingvVolume = bookingVolume;
    newCustomer->rank = rank;

    newCustomer->next = head->next;
    head->next = newCustomer;
    
    return head;
}

/**
 * ��Ʊģ��
 */
void userBookTicket() {
    system("cls");

    Flight* flight = find();
    if (NULL == flight) {
        printf("û���������, ����������\n");
        userBookTicket();
    }

    printf("�������㶩Ʊ����Ҫ������:");
    int amount = 0;
    scanf("%d", &amount);
    if (amount <= 0) {
        printf("�Ƿ��ַ�\n");
        userBookTicket();
    }

    printf("����ȷ��������Ʊ�Ĳ�λ�ȼ���1�����òգ�2��������������գ�:");
    int rank = 2;
    int tickets = 0;
    char name[20];
    char IDNumber[19];
    scanf("%d", &rank);
    if (rank == 1)
        tickets = flight->leftEconomicTicket;
    else
        tickets = flight->leftBusinessTicket;
    if (amount <= tickets) {
        //Ʊ������
        printf("��������������:");
        scanf("%s", name);
        printf("�������������֤����:");
        scanf("%s", IDNumber);
        CustomerLinkList head = flight->cusLinkList;
        //��Ʊ�ɹ��������Ա��������
        insertCustomerLinklist(head, name, IDNumber, amount, rank);
        for (int i = 0; i < amount; i++)
            printf("%s ����λ����: %d\n", name, flight->totalTickets - flight->left + i + 1);
        flight->left -= amount;

        if (rank == 1)
            flight->leftEconomicTicket -= amount;
        else
            flight->leftBusinessTicket -= amount;

        printf("\n��Ʊ�ɹ���ף����;��죡��ӭ�ٴι���\n");
    }
    else {
        //Ʊ������
        printf("�õȼ���Ʊ���㣬��Ʊʧ��\n");
        printf("\n�Ѿ�û�и����Ʊ������Ҫ�ŶӵȺ���?(Y/N)");
        getchar();//�����س�
        char choice = getchar();
        printf("%c",choice);
        if (choice == 'Y' || choice == 'y') {
            //�ŶӺ�
            printf("\n�����������������ŶӶ�Ʊ�ͻ���:");
            scanf("%s", name);
            printf("\n�������������֤���ŶӶ�Ʊ�ͻ���:");
            scanf("%s", IDNumber);
            if (rank == 1) {//���뾭�ò��ŶӶ���
                flight->economicWaitQueue = enWaitQueue(flight->economicWaitQueue, name, amount, IDNumber);
            }
            else {//����������ŶӶ���
                flight->businessWaitQueue = enWaitQueue(flight->businessWaitQueue, name, amount, IDNumber);
            }
            printf("\n�Ŷӳɹ�!\n");
        }
        else {
            //���Ŷ�
            printf("\n�Ƿ���ݽ��鶩Ʊ�����ǣ����Ƽ���ͬ�������յ�ĺ���Y/N");
            getchar();//�����س�
            choice = getchar();
            printf("%c", choice);
            if (choice == 'Y' || choice == 'y') {
                //�����Ƽ�����
                userRecommendBookTicket(flight);
            }
            else {
                printf("\n��ӭ���´��ٴζ�����\n");
                system("PAUSE");
                userMenu();
            }
        }
    }
}

/**
 *  ��Ʊģ�� 
 */
void userRefundTicket() {
    system("cls");

    struct Flight* flight = find();
    if (NULL == flight) {
        printf("û���������, ����������\n");
        userRefundTicket();
    }

    int rank;
    //p1Ϊ����ָ�룬p2Ϊ����ָ�룬ָ��p1��ǰ��
    CustomerNode* p1, * p2, * head;
    //�ͻ�����
    char name[20];
    //�ͻ����֤
    char IDNumber[19];
    //headΪ�ú���ĵĳ�Ա�������ͷָ��
    head = flight->cusLinkList;
    //��ͷ����ָ�룬head->next ��ʼ����
    p1 = head->next;
    printf("�������������: ");
    scanf("%s", name);
    printf("������������֤����: ");
    scanf("%s", IDNumber);
    //���ݿͻ����������ͻ��Ƿ�Ʊ
    p2 = head;
    while (NULL != p1) {
        if ((strcmp(name, p1->name) == 0) && (strcmp(IDNumber, p1->IDNumber) == 0)) break;
        p2 = p1;
        p1 = p1->next;
    }

    if (NULL == p1) {
        printf("�Բ�����û�ж���Ʊ�����������֤����Ӧ\n");
        return;
    }
    else {
        //��Ʊ�ɹ�
        rank = p1->rank;
        p2->next = p1->next;
        //�ӻظú����ʣ��Ʊ
        flight->left += p1->bookingvVolume;
        if (rank == 1) {
            flight->leftEconomicTicket += p1->bookingvVolume;
        }
        else {
            flight->leftBusinessTicket += p1->bookingvVolume;
        }
        printf("%s  �ɹ���Ʊ��\n", p1->name);
        free(p1);
    }

    WaitLinkQueue queue1 = flight->economicWaitQueue;
    WaitLinkQueue queue2 = flight->businessWaitQueue;

    char waitName[20] = "";
    char waitIDNumber[19] = "";
    int preBookingVolume = 0;
    //�����Ʊ
    if (rank == 1) { 
        //���ò�
        for (; queue1.front->next != NULL && queue1.front->next->preBookingVolume <= flight->leftEconomicTicket;) {
            //�򲹿ͻ����г���
            deWaitQueue(flight->economicWaitQueue, waitName, waitIDNumber, preBookingVolume);
            int y;
            printf("�� ���ò�Ʊ ʣ�� , �𾴵�%s ��\n", waitName);
            printf("�Ƿ�ȷ�϶�Ʊ��1ȷ�϶�Ʊ�� �������־ܾ���Ʊ��\n");
            scanf("%d", &y);

            if (y == 1) {
                //�ŶӶ�Ʊ�ɹ�
                for (int i = 0; i < preBookingVolume; i++)
                    printf("�ŶӶ�Ʊ�ɹ�  %s ����λ����:%d\n", waitName, (flight->left) - i);
                //ʣ��Ʊ����
                flight->left -= preBookingVolume;
                flight->leftEconomicTicket -= preBookingVolume;
                //��Ա������������ŶӶ�Ʊ�ɹ��Ŀͻ�
                flight->cusLinkList = insertCustomerLinklist(flight->cusLinkList, waitName, waitIDNumber, preBookingVolume, rank);
            }
        }
    }
    else {
        //�����
        for (; queue2.front->next != NULL && queue2.front->next->preBookingVolume <= flight->leftBusinessTicket;) {
            //�򲹿ͻ����г���
            deWaitQueue(flight->businessWaitQueue, waitName, waitIDNumber, preBookingVolume);
            int y;
            printf("�� �����Ʊ ʣ�� , �𾴵�%s ��\n", waitName);
            printf("�Ƿ�ȷ�϶�Ʊ��1ȷ�϶�Ʊ�� �������־ܾ���Ʊ\n");
            scanf("%d", &y);

            if (y == 1) {
                //�ŶӶ�Ʊ�ɹ�
                for (int i = 0; i < preBookingVolume; i++)
                    printf("�ŶӶ�Ʊ�ɹ�  %s ����λ����:%d\n", waitName, (flight->left) - i);
                //ʣ��Ʊ����
                flight->left -= preBookingVolume;
                flight->leftBusinessTicket -= preBookingVolume;
                //��Ա������������ŶӶ�Ʊ�ɹ��Ŀͻ�
                flight->cusLinkList = insertCustomerLinklist(flight->cusLinkList, waitName, waitIDNumber,
                    preBookingVolume, rank);
            }
        }
    }
}

/**
 * ����ģ�����
 */
void userSearchFlightController() {
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");


    printf("                  Welcome To ����ģ��\n");
    printf("        ------------------------------------\n");
    printf("        |           1.����������Ϣ           | \n");
    printf("        |           2.������һ��˵�         | \n");
    printf("        ------------------------------------|\n");
    printf("                 ����������ѡ��:");

    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        userSearchFlight();
        system("PAUSE");
        userSearchFlightController();
        break;
    case 2:
        userMenu();
        break;
    default:
        userSearchFlightController();
    }
}

/**
 * ��Ʊģ�����
 */
void userBookTicketController() {
    system("cls");
    printf("\n");
    printf("\n");
    printf("             Welcome To ��Ʊģ��\n");
    printf("       -----------------------------------------------\n");
    printf("       |           1.�ͻ���Ʊ                          |\n");
    printf("       |           2.���������յ���������             |\n");
    printf("       |           3.��ѯ���к���                       |\n");
    printf("       |           4.������һ���˵�                    |\n");
    printf("       ------------------------------------------------\n");
    printf("                 ����������ѡ��:");

    int choice;
    scanf("%d", &choice);
    
    switch (choice) {
    case 1:
        //��Ʊ
        userBookTicket();
        system("PAUSE");
        userBookTicketController();
        break;
    case 2:
        //���������յ��ѯ
        userSearchFlight();
        system("PAUSE");
        userBookTicketController();
        break;
    case 3:
        showAllFlight(pFlight);
        system("PAUSE");
        userBookTicketController();
        break;
    case 4:
        userMenu();
        break;
    default:
        userBookTicketController();
    }
}

/**
 * ��Ʊģ�����
 */
void userRefundTicketController() {
    system("cls");
    printf("\n");
    printf("\n");
    printf("               Welcome To ��Ʊģ��\n");
    printf("    -------------------------------------\n");
    printf("    |           1.������Ʊ����            |\n");
    printf("    |           2.������һ���˵�          |\n");
    printf("    --------------------------------------\n");
    printf("                            ����������ѡ��:");

    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        userRefundTicket();
        system("PAUSE");
        userRefundTicketController();
        break;
    case 2:
        userMenu();
        break;
    default:
        userRefundTicketController();
    }
}

void goodbye() {
    system("cls");
    printf("\n");
    printf("\n");
    printf("             ---------------------------------------------\n");
    printf("             |            ��лʹ�ú��պ��ඩƱϵͳ        |\n");
    printf("             |                                           |\n");
    printf("             |                    GoodBye��               \n");
    printf("             --------------------------------------------\n");
}

/**
 * �ܲ˵�
 */
void menu() {
    system("cls");   
    printf("\n");
    printf("\n");
    printf("                               ��ӭ�������ն�Ʊϵͳ\n");
    printf("                        -------------------------------------\n");
    printf("                        |          1.  �û�ģ��             |\n");
    printf("                        |          2.  ����Աģ��           |\n");
    printf("                        |          3.  �˳�                 |\n");
    printf("                        -------------------------------------\n");
    printf("                        |       21��׿ ��Ѵ 3121005207      |\n");
    printf("                        |        ���ʱ��:2022.12.24        |\n");
    printf("                        -------------------------------------\n");
    printf("                        �����루1-3��������Ч�� ����������ѡ��:");

    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        userMenu();
        system("PAUSE");
        menu();
        break;
    case 2:
        //�������Աģ��
        while (1) {
            Status status;
            status = adminVerify();
            if (TRUE == status)
                break;
        }
        administratorMenu();
        system("PAUSE");
        menu();
        break;
    case 3:
        //�˳�ģ��
        goodbye();
        return;
    default:
        menu();
    }
}

/**
 *  �û��˵�
 */
void userMenu() {
    system("cls");

    printf("                               ��ӭ�����û�ģ��\n");
    printf("                        ------------------------------------\n");
    printf("                        |          1.  �������             |\n");
    printf("                        |          2.  ����ģ��             |\n");
    printf("                        |          3.  ��Ʊģ��             |\n");
    printf("                        |          4.  ��Ʊģ��             |\n");
    printf("                        |          5.  �˳�                 |\n");
    printf("                        ------------------------------------\n");
    printf("                        �����루1-5��������Ч�� ����������ѡ��:");

    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        //��ʾ���к�����Ϣ
        showAllFlight(pFlight);
        system("PAUSE");
        userMenu();
        break;
    case 2:
        //��������ģ��
        userSearchFlightController();
        system("PAUSE");
        userMenu();
        break;
    case 3:
        //���붩Ʊģ��
        userBookTicketController();
        system("PAUSE");
        userMenu();
        break;
    case 4:
        //������Ʊģ��
        userRefundTicketController();
        system("PAUSE");
        userMenu();
        break;
    case 5:
        //�˳�ģ��
        menu();
        break;
    default:
        userMenu();
    }
}

/**
 * ����Աģ��
 * ����Ա���溯��
 */
void administratorMenu() {
    printf("                          ��ӭ��������Աģ��\n");
    printf("                ------------------------------------\n");
    printf("                |           1.�������              |\n");
    printf("                |           2.�ͻ���Ϣ              |\n");
    printf("                |           3.���Ӻ���              |\n");
    printf("                |           4.ɾ������              |\n");
    printf("                |           5.������һ��            |\n");
    printf("                ------------------------------------|\n");
    printf("                 ����������ѡ��:");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        showAllFlight(pFlight);
        system("PAUSE");
        administratorMenu();
        break;
    case 2:
        adminShowCustomerInfo();
        administratorMenu();
        break;
    case 3:
        adminInsertFlight();
        administratorMenu();
        break;
    case 4:
        if (OK == adminDeleteFlight()) {
            printf("ɾ���ɹ�\n");
        }
        else {
            printf("û��������࣬ɾ��ʧ�ܣ�\n");
        };
        administratorMenu();
        break;
    case 5:
        menu();
        break;
    default:
        administratorMenu();
    }
}

void run() {
    initFlight();
    menu();
}

int main() {
    run();
    return 0;
}