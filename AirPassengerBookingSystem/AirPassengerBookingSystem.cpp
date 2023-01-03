#include "AirPassengerBookingSystem.h"

//航班链表的头指针
Flight* pFlight;

//基本航班
Flight basicFlight[7] = {
        {1, "广州", "北京", "A1111", "星期一", 10, 10, 5},
        {2, "广州", "北京", "A2222", "星期二", 8,  8,  4},
        {3, "北京", "广州", "B3333", "星期三", 10, 10, 5},
        {4, "北京", "广州", "B4444", "星期四", 8,  8,  4},
        {5, "广州", "上海", "C5555", "星期五", 10, 10, 5},
        {6, "深圳", "广州", "D6666", "星期六", 8,  8,  4},
        {7, "揭阳", "广州", "E7777", "星期日", 10, 10, 5}
};

/**
 * 初始化已订票乘客指针链表
 * @param cusLinkList 航班中乘员链表的头指针
 * @return 是否成功
 */
Status initCustomerLinkList(CustomerLinkList& cusLinkList) {
    cusLinkList = (CustomerNode*)malloc(sizeof(CustomerNode));
    if (NULL == cusLinkList)return OVERFLOW;
    cusLinkList->next = NULL;
    return OK;
}

/**
 * 初始化带头结点的候补链队列
 * @param q 链队列指针
 * @return 是否成功
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
 * 候补链队列入队
 * @param q 候补链队列
 * @param name 姓名
 * @param amount 订票数
 * @param identification 身份证号 
 * @return 候补链队列
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
 * 候补队列出队
 * @param q
 * @param waitName 姓名
 * @param waitIDNumber 身份证号
 * @param preBookingVolume 候补预定票量
 * @return 是否出队成功
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
 * 将basicFlight用头插入法插入到pFlight的链表中
 * @param basicFlight 里面存有基本航班
 * @return 返回操作是否成功
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
        //初始化乘客链表
        initCustomerLinkList(q->cusLinkList);
        initWaitQueue(q->economicWaitQueue);
        initWaitQueue(q->businessWaitQueue);

        q->next = p->next;
        p->next = q;
    }
    return OK;
}

/**
 * 初始化航班链表
 */
Status initFlight() {
    pFlight = (Flight*)malloc(sizeof(Flight));//申请头结点的空间
    if (NULL == pFlight) return OVERFLOW;
    pFlight->next = NULL;//将头结点h的指针域置为空

    //创建基本航班
    if (OK != createBasicFlight(basicFlight))return ERROR;

    return OK;
}

/**
 * 根据航班ID查询航班并以指针形式返回
 * @return  航班指针
 */
Flight* find() {
    int ID = 0;

    printf("请输入航班ID: ");
    scanf("%d", &ID);

    //头结点的下一个节点开始遍历
    Flight* p = pFlight->next;

    while (NULL != p) {
        if (ID == p->ID)return p;

        p = p->next;
    }
    return NULL;
}

/**
 * 输出某一航班信息
 * @param p 航班节点
 */
void showSingleFlight(Flight* p) {
    printf("起点站名\t终点站名\t航班ID\t飞机号\t飞行日期\t乘员定额\t余票量\t经济票剩余\t商务票剩余\n");
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
 * 打印全部航班信息
 * @param pflight 传入的是航班链表的头指针
 */
void showAllFlight(Flight* pflight) {
    Flight* p = pflight->next;
    system("cls");
    printf("航班ID\t起点站名\t终点站名\t飞机号\t飞行日期\t乘员定额\t余票量\t经济票剩余量\t商务票剩余量\n");
    while (NULL != p) {
        //调用Display函数打印出每个航班节点的信息
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
 * 验证管理员密码
 * @return 返回操作结果
 */
Status adminVerify() {
    char pwd[20] = "admin";//管理员密码
    char password[20];//待输入密码，用来验证
    printf("请输入管理员密码:\n");
    scanf("%s", password);
    if (strcmp(pwd, password)) {
        printf("密码错误，请重新输入:\n");
        return FALSE;
    }
    printf("验证成功\n");
    return TRUE;
}

/**
  * 管理员
  * 添加航班
  * 头插入法
  * @return 返回操作是否成功
  */
Status adminInsertFlight() {
    FlightNode* q;
    Flight* p = pFlight;
    int flag = 1;

    while (flag != 0) {
        q = (FlightNode*)malloc(sizeof(FlightNode));
        if (NULL == q)return OVERFLOW;

        printf("\t\t请依次输入以下内容\n");
        
        printf("\t\t请输入起点站名\n");
        scanf("%s", q->startPoint);
        printf("\t\t请输入终点站名\n");
        scanf("%s", q->destination);
        printf("\t\t请输入飞机号\n");
        scanf("%s", q->planeNum);
        printf("\t\t请输入飞行日期(1代表星期,2代表星期二.....7代表星期日)\n");
        int day1;
        scanf("%d", &day1);
        while (ERROR == inputDay(day1, q->day)) {
            printf("请输入合法数据(1-7)\n");
            scanf("%d", &day1);
        };

        printf("\t\t请输入乘客定额\n");
        scanf("%d", &q->totalTickets);
        q->left = q->totalTickets;

        printf("\t\t请输入经济票数目（同时也决定了商务票的数目）\n");
        scanf("%d", &q->leftEconomicTicket);
        //商务票数目 = 总票数目 - 经济票数目
        q->leftBusinessTicket = q->totalTickets - q->leftEconomicTicket;

        q->ID = pFlight->next->ID + 1;

        initCustomerLinkList(q->cusLinkList);
        //初始化
        initWaitQueue(q->economicWaitQueue);
        initWaitQueue(q->businessWaitQueue);

        q->next = p->next;
        p->next = q;

        printf("\t\t是否继续录入航班信息（任意数字继续，0表示停止）。\n");
        printf("\t\t请输入：");
        scanf("%d", &flag);
    }
    return OK;
}

/**
  * 管理员
  * 删除航班
  * @return 返回操作是否成功
  */
Status adminDeleteFlight() {
    int ID = 0;
    printf("请输入航班ID\n");
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
 * 管理员
 * 查询某一航班的客户信息
 */
void adminShowCustomerInfo() {
    Flight* flight = find();
    if (NULL == flight) {
        printf("没有这个航班\n");
        return;
    }
    CustomerLinkList p = flight->cusLinkList->next;
    if (NULL != p) {
        printf("客户姓名   订票数额   舱位等级（1经济舱，2商务舱）    身份证号码\n");
        while (p) {
            printf("%s\t\t%d\t\t%d\t\t\t%s\n", p->name, p->bookingvVolume, p->rank, p->IDNumber);
            p = p->next;
        }
    }
    else
        printf("该航班没有客户信息!!\n");
}

/**
 * 新增航班时输入日期的辅助函数（1代表星期一，7代表星期日）
 * @param inputDay 1-7
 * @param day 新增航班的日期变量
 * @return 返回操作状态，输入是否合法
 */
Status inputDay(int inputDay, char day[]) {
    switch (inputDay) {
    case Mon:
        strcpy(day, "星期一");
        break;
    case Tues:
        strcpy(day, "星期二");
        break;
    case Wed:
        strcpy(day, "星期三");
        break;
    case Thur:
        strcpy(day, "星期四");
        break;
    case Fri:
        strcpy(day, "星期五");
        break;
    case Sat:
        strcpy(day, "星期六");
        break;
    case Sun:
        strcpy(day, "星期日");
        break;
    default:
        return ERROR;
    }
    return OK;
}

/**
 * 根据客户提出的起点，终点站名输出航线信息
 */
void userSearchFlight() {
    char startPonit[10];
    char destination[10];
    int flag = 0;
    system("cls");
    printf("请输入起点站名: (若全部则输入0)\n");
    scanf("%s", startPonit);
    printf("请输入终点站名: (若全部则输入0)\n");
    scanf("%s", destination);
    struct Flight* p;
    p = pFlight->next;
    printf("航班ID\t起点站名\t终点站名\t飞机号\t飞行日期\t乘员定额\t余票量\t经济票剩余量\t商务票剩余量\n");

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
        printf("对不起，该航班未找到! \n");
}

/**
 * 查找同一路线的其他航班
 * @return 是否查找成功
 */
Status showSameFlight(Flight* flight) {
    //标记变量，是否找到同一路线的航班
    int flag = 0;
    struct Flight* p;
    p = pFlight->next;
    printf("\n正在寻找同一路线的航班...\n\n");
    printf("航班ID\t起点站名\t终点站名\t飞机号\t飞行日期\t乘员定额\t余票量\t经济票剩余量\t商务票剩余量\n");

    while (p != NULL) {
        //路线相同，且不是同一个航班，标记flag = 1，表示找到
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

    //没有相同路线的航班
    if (flag == 0)
        return FALSE;
    return TRUE;
}

/**
 * 推荐订票
 * @param flight 原航班，用来辅助选出同一路线但不同航班ID的航班
 */
void userRecommendBookTicket(Flight* flight) {
    Status status = showSameFlight(flight);
    if (status == FALSE)
        printf("对不起，没有相同起点和终点的航班了\n");
    else {
        printf("是否符合订票要求？（Y|N） \n");
        {
            getchar();//打消回车
            char r = getchar();
            if (r == 'Y' || r == 'y') {
                userBookTicket();
                system("PAUSE");
            }
            else {
                printf("不根据建议进行订票，现在将退回主菜单");
                system("PAUSE");
                userMenu();
            }
        }
    }
}


/**
 * 订票成功之后，将乘客信息插入到对应航班的订票乘客名单
 * @param head 乘客名单头指针
 * @param amount 该乘客订票的数量
 * @param name 乘客的姓名
 * @param rank 订票的等级
 * @return  乘客链表头指针
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
 * 订票模块
 */
void userBookTicket() {
    system("cls");

    Flight* flight = find();
    if (NULL == flight) {
        printf("没有这个航班, 请重新输入\n");
        userBookTicket();
    }

    printf("请输入你订票所需要的数量:");
    int amount = 0;
    scanf("%d", &amount);
    if (amount <= 0) {
        printf("非法字符\n");
        userBookTicket();
    }

    printf("请正确输入您的票的舱位等级（1代表经济舱，2或其他代表商务舱）:");
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
        //票数充足
        printf("请输入您的姓名:");
        scanf("%s", name);
        printf("请输入您的身份证号码:");
        scanf("%s", IDNumber);
        CustomerLinkList head = flight->cusLinkList;
        //订票成功，插入成员名单链表
        insertCustomerLinklist(head, name, IDNumber, amount, rank);
        for (int i = 0; i < amount; i++)
            printf("%s 的座位号是: %d\n", name, flight->totalTickets - flight->left + i + 1);
        flight->left -= amount;

        if (rank == 1)
            flight->leftEconomicTicket -= amount;
        else
            flight->leftBusinessTicket -= amount;

        printf("\n订票成功！祝您旅途愉快！欢迎再次光临\n");
    }
    else {
        //票数不足
        printf("该等级的票不足，订票失败\n");
        printf("\n已经没有更多的票，您需要排队等候吗?(Y/N)");
        getchar();//打消回车
        char choice = getchar();
        printf("%c",choice);
        if (choice == 'Y' || choice == 'y') {
            //排队候补
            printf("\n请输入您的姓名（排队订票客户）:");
            scanf("%s", name);
            printf("\n请输入您的身份证（排队订票客户）:");
            scanf("%s", IDNumber);
            if (rank == 1) {//进入经济舱排队队列
                flight->economicWaitQueue = enWaitQueue(flight->economicWaitQueue, name, amount, IDNumber);
            }
            else {//进入商务舱排队队列
                flight->businessWaitQueue = enWaitQueue(flight->businessWaitQueue, name, amount, IDNumber);
            }
            printf("\n排队成功!\n");
        }
        else {
            //不排队
            printf("\n是否根据建议订票？若是，则推荐相同的起点和终点的航班Y/N");
            getchar();//打消回车
            choice = getchar();
            printf("%c", choice);
            if (choice == 'Y' || choice == 'y') {
                //调用推荐函数
                userRecommendBookTicket(flight);
            }
            else {
                printf("\n欢迎您下次再次订购！\n");
                system("PAUSE");
                userMenu();
            }
        }
    }
}

/**
 *  退票模块 
 */
void userRefundTicket() {
    system("cls");

    struct Flight* flight = find();
    if (NULL == flight) {
        printf("没有这个航班, 请重新输入\n");
        userRefundTicket();
    }

    int rank;
    //p1为遍历指针，p2为辅助指针，指向p1的前驱
    CustomerNode* p1, * p2, * head;
    //客户姓名
    char name[20];
    //客户身份证
    char IDNumber[19];
    //head为该航班的的乘员名单域的头指针
    head = flight->cusLinkList;
    //带头结点的指针，head->next 开始遍历
    p1 = head->next;
    printf("请输入你的姓名: ");
    scanf("%s", name);
    printf("请输入你的身份证号码: ");
    scanf("%s", IDNumber);
    //根据客户姓名搜索客户是否订票
    p2 = head;
    while (NULL != p1) {
        if ((strcmp(name, p1->name) == 0) && (strcmp(IDNumber, p1->IDNumber) == 0)) break;
        p2 = p1;
        p1 = p1->next;
    }

    if (NULL == p1) {
        printf("对不起，你没有订过票或姓名和身份证不对应\n");
        return;
    }
    else {
        //退票成功
        rank = p1->rank;
        p2->next = p1->next;
        //加回该航班的剩余票
        flight->left += p1->bookingvVolume;
        if (rank == 1) {
            flight->leftEconomicTicket += p1->bookingvVolume;
        }
        else {
            flight->leftBusinessTicket += p1->bookingvVolume;
        }
        printf("%s  成功退票！\n", p1->name);
        free(p1);
    }

    WaitLinkQueue queue1 = flight->economicWaitQueue;
    WaitLinkQueue queue2 = flight->businessWaitQueue;

    char waitName[20] = "";
    char waitIDNumber[19] = "";
    int preBookingVolume = 0;
    //处理候票
    if (rank == 1) { 
        //经济舱
        for (; queue1.front->next != NULL && queue1.front->next->preBookingVolume <= flight->leftEconomicTicket;) {
            //候补客户队列出队
            deWaitQueue(flight->economicWaitQueue, waitName, waitIDNumber, preBookingVolume);
            int y;
            printf("有 经济舱票 剩余 , 尊敬的%s ：\n", waitName);
            printf("是否确认订票（1确认订票， 其他数字拒绝订票）\n");
            scanf("%d", &y);

            if (y == 1) {
                //排队订票成功
                for (int i = 0; i < preBookingVolume; i++)
                    printf("排队订票成功  %s 的座位号是:%d\n", waitName, (flight->left) - i);
                //剩余票减少
                flight->left -= preBookingVolume;
                flight->leftEconomicTicket -= preBookingVolume;
                //乘员名单链表插入排队订票成功的客户
                flight->cusLinkList = insertCustomerLinklist(flight->cusLinkList, waitName, waitIDNumber, preBookingVolume, rank);
            }
        }
    }
    else {
        //商务舱
        for (; queue2.front->next != NULL && queue2.front->next->preBookingVolume <= flight->leftBusinessTicket;) {
            //候补客户队列出队
            deWaitQueue(flight->businessWaitQueue, waitName, waitIDNumber, preBookingVolume);
            int y;
            printf("有 商务舱票 剩余 , 尊敬的%s ：\n", waitName);
            printf("是否确认订票（1确认订票， 其他数字拒绝订票\n");
            scanf("%d", &y);

            if (y == 1) {
                //排队订票成功
                for (int i = 0; i < preBookingVolume; i++)
                    printf("排队订票成功  %s 的座位号是:%d\n", waitName, (flight->left) - i);
                //剩余票减少
                flight->left -= preBookingVolume;
                flight->leftBusinessTicket -= preBookingVolume;
                //乘员名单链表插入排队订票成功的客户
                flight->cusLinkList = insertCustomerLinklist(flight->cusLinkList, waitName, waitIDNumber,
                    preBookingVolume, rank);
            }
        }
    }
}

/**
 * 搜索模块界面
 */
void userSearchFlightController() {
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");


    printf("                  Welcome To 搜索模块\n");
    printf("        ------------------------------------\n");
    printf("        |           1.搜索航班信息           | \n");
    printf("        |           2.返回上一层菜单         | \n");
    printf("        ------------------------------------|\n");
    printf("                 请输入您的选择:");

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
 * 订票模块界面
 */
void userBookTicketController() {
    system("cls");
    printf("\n");
    printf("\n");
    printf("             Welcome To 订票模块\n");
    printf("       -----------------------------------------------\n");
    printf("       |           1.客户订票                          |\n");
    printf("       |           2.根据起点和终点搜索航班             |\n");
    printf("       |           3.查询所有航班                       |\n");
    printf("       |           4.返回上一级菜单                    |\n");
    printf("       ------------------------------------------------\n");
    printf("                 请输入您的选择:");

    int choice;
    scanf("%d", &choice);
    
    switch (choice) {
    case 1:
        //订票
        userBookTicket();
        system("PAUSE");
        userBookTicketController();
        break;
    case 2:
        //输入起点和终点查询
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
 * 退票模块界面
 */
void userRefundTicketController() {
    system("cls");
    printf("\n");
    printf("\n");
    printf("               Welcome To 退票模块\n");
    printf("    -------------------------------------\n");
    printf("    |           1.办理退票手续            |\n");
    printf("    |           2.返回上一级菜单          |\n");
    printf("    --------------------------------------\n");
    printf("                            请输入您的选择:");

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
    printf("             |            感谢使用航空航班订票系统        |\n");
    printf("             |                                           |\n");
    printf("             |                    GoodBye！               \n");
    printf("             --------------------------------------------\n");
}

/**
 * 总菜单
 */
void menu() {
    system("cls");   
    printf("\n");
    printf("\n");
    printf("                               欢迎来到航空订票系统\n");
    printf("                        -------------------------------------\n");
    printf("                        |          1.  用户模块             |\n");
    printf("                        |          2.  管理员模块           |\n");
    printf("                        |          3.  退出                 |\n");
    printf("                        -------------------------------------\n");
    printf("                        |       21软卓 陈汛 3121005207      |\n");
    printf("                        |        完成时间:2022.12.24        |\n");
    printf("                        -------------------------------------\n");
    printf("                        请输入（1-3）否则无效！ 请输入您的选择:");

    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        userMenu();
        system("PAUSE");
        menu();
        break;
    case 2:
        //进入管理员模块
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
        //退出模块
        goodbye();
        return;
    default:
        menu();
    }
}

/**
 *  用户菜单
 */
void userMenu() {
    system("cls");

    printf("                               欢迎来到用户模块\n");
    printf("                        ------------------------------------\n");
    printf("                        |          1.  航班面板             |\n");
    printf("                        |          2.  搜索模块             |\n");
    printf("                        |          3.  订票模块             |\n");
    printf("                        |          4.  退票模块             |\n");
    printf("                        |          5.  退出                 |\n");
    printf("                        ------------------------------------\n");
    printf("                        请输入（1-5）否则无效！ 请输入您的选择:");

    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        //显示所有航班信息
        showAllFlight(pFlight);
        system("PAUSE");
        userMenu();
        break;
    case 2:
        //进入搜索模块
        userSearchFlightController();
        system("PAUSE");
        userMenu();
        break;
    case 3:
        //进入订票模块
        userBookTicketController();
        system("PAUSE");
        userMenu();
        break;
    case 4:
        //进入退票模块
        userRefundTicketController();
        system("PAUSE");
        userMenu();
        break;
    case 5:
        //退出模块
        menu();
        break;
    default:
        userMenu();
    }
}

/**
 * 管理员模块
 * 管理员界面函数
 */
void administratorMenu() {
    printf("                          欢迎来到管理员模块\n");
    printf("                ------------------------------------\n");
    printf("                |           1.航班面板              |\n");
    printf("                |           2.客户信息              |\n");
    printf("                |           3.增加航班              |\n");
    printf("                |           4.删除航班              |\n");
    printf("                |           5.返回上一级            |\n");
    printf("                ------------------------------------|\n");
    printf("                 请输入您的选择:");
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
            printf("删除成功\n");
        }
        else {
            printf("没有这个航班，删除失败！\n");
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