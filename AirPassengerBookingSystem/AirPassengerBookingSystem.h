#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define FALSE -1
#define TRUE 1

typedef int Status;

//航班日期枚举
enum Week {
    Mon = 1, Tues = 2, Wed = 3, Thur = 4, Fri = 5, Sat = 6, Sun = 7
};

//乘客节点
typedef struct CustomerNode {
    char name[10];//客户姓名
    int clientTickets;//客户订票量
    char identification[18];//客户身份证号码
    int rank;//舱位等级
    CustomerNode* next;
} CustomerNode, * CustomerLinkList;

//候补队列中的节点
typedef struct WaitPassenger {
    char name[10];//姓名
    char identification[18]; //身份证
    int preTickets;//预定的票量
    struct WaitPassenger* next;
} WaitQNode, * PWait;

//候补队列
typedef struct Queue {
    PWait front;//等候替补客户名单域的头指针
    PWait rear;//等候替补客户名单域的尾指针
} WaitLinkQueue;

//封装乘客的 姓名 身份证号 订票量,用于候补客户出队时把关键字返回 
typedef struct NameAndNumAndID {
    char name[10];//姓名
    char identification[18]; //身份证号码
    int num;//订票量
}NameAndNumAndID;

//航班节点
typedef struct Flight {
    int ID;//航班ID（相当于主键）
    char startPoint[20];//起点站名
    char destination[20];//终点站名
    char planeNum[20];//飞机号
    char day[20];//飞行日期（星期几）
    int totalTickets;//乘员定额(总票数)
    int left;//总余票量
    int leftEconomicTicket; //经济票剩余量
    int leftBusinessTicket; //商务票剩余量
    Flight* next;
    CustomerLinkList cusLinkList;//乘员名单域，指向乘员名单链表的头指针
    WaitLinkQueue economicWaitQueue;//经济舱候补，等候替补的客户名单域，指向一个队列
    WaitLinkQueue businessWaitQueue;//商务舱候补，等候替补的客户名单域，指向一个队列
} Flight, FlightNode, * PFlight;

/**
 * 初始化已订票乘客指针链表
 * @param cusLinkList 航班中乘员链表的头指针
 * @return 是否成功
 */
Status initCustomerLinkList(CustomerLinkList& cusLinkList);

/**
 * 初始化带头结点的候补链队列
 * @param q 链队列指针
 * @return 是否成功
 */
Status initWaitQueue(WaitLinkQueue& q);

/**
 * 候补链队列入队
 * @param q 候补链队列
 * @param name 姓名
 * @param amount 订票数
 * @param identification 身份证号
 * @return 候补链队列
*/
WaitLinkQueue enWaitQueue(WaitLinkQueue& q, char name[], int amount, char identification[]);

/**
 * 候补链队列出队
 * @param q 候补链队列
 * @param NameAndNumAndID 姓名、购票量、身份证的封装结构体
 * @return 出队结果
*/
Status deWaitQueue(WaitLinkQueue& q, NameAndNumAndID& NameAndNumAndID);

/**
 * 初始化航班链表
 */
Status initFlight();

/**
 * 根据航班ID查询航班并以指针形式返回
 * @return  航班指针
 */
Flight* find();

/**
 * 输出某一航班信息
 * @param p 航班节点
 */
void showSingleFlight(Flight* p);

/**
 * 打印全部航班信息
 * @param pflight 传入的是航班链表的头指针
 */
void showAllFlight(Flight* pflight);

/**
 * 验证管理员密码
 * @return 返回操作结果
 */
Status adminVerify();

/**
  * 管理员
  * 添加航班
  * 头插入法
  * @return 返回操作是否成功
  */
Status adminInsertFlight();

/**
  * 管理员
  * 删除航班
  * @return 返回操作是否成功
  */
Status adminDeleteFlight();

/**
 * 管理员
 * 查询某一航班的客户信息
 */
void adminShowCustomerInfo();

/**
 * 新增航班时输入日期的辅助函数（1代表星期一，7代表星期日）
 * @param inputDay 1-7
 * @param day 新增航班的日期变量
 * @return 返回操作状态，输入是否合法
 */
Status inputDay(int inputDay, char day[]);

/**
 * 用户
 * 根据起点、终点站名输出航线信息
 */
void userSearchFlight();

/**
 * 查找同一路线的其他航班
 * @return 是否查找成功
 */
Status showSameFlight(Flight* flight);
/**
 * 用户
 * 推荐订票
 * @param flight 原航班，用来辅助选出同一路线但不同航班ID的航班
 */
void userRecommendBookTicket(Flight* flight);

/**
 * 订票成功之后，将乘客信息插入到对应航班的订票乘客名单
 * @param head 乘客名单头指针
 * @param amount 该乘客订票的数量
 * @param name 乘客的姓名
 * @param rank 订票的等级
 * @return  乘客链表头指针
 */
CustomerLinkList insertCustomerLinklist(CustomerLinkList& head, int amount, char name[], char identification[], int rank);

/** 
 * 用户
 * 订票模块
 */
void userBookTicket();

/**
 * 用户
 * 退票模块
 */
void userRefundTicket();


/**
 * 总菜单
 */
void menu();

/**
 *  用户菜单
 */
void userMenu();

/**
 * 管理员菜单
 */
void administratorMenu();