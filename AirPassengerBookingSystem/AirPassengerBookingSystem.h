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

//��������ö��
enum Week {
    Mon = 1, Tues = 2, Wed = 3, Thur = 4, Fri = 5, Sat = 6, Sun = 7
};

//�˿ͽڵ�
typedef struct CustomerNode {
    char name[10];//�ͻ�����
    int clientTickets;//�ͻ���Ʊ��
    char identification[18];//�ͻ����֤����
    int rank;//��λ�ȼ�
    CustomerNode* next;
} CustomerNode, * CustomerLinkList;

//�򲹶����еĽڵ�
typedef struct WaitPassenger {
    char name[10];//����
    char identification[18]; //���֤
    int preTickets;//Ԥ����Ʊ��
    struct WaitPassenger* next;
} WaitQNode, * PWait;

//�򲹶���
typedef struct Queue {
    PWait front;//�Ⱥ��油�ͻ��������ͷָ��
    PWait rear;//�Ⱥ��油�ͻ��������βָ��
} WaitLinkQueue;

//��װ�˿͵� ���� ���֤�� ��Ʊ��,���ں򲹿ͻ�����ʱ�ѹؼ��ַ��� 
typedef struct NameAndNumAndID {
    char name[10];//����
    char identification[18]; //���֤����
    int num;//��Ʊ��
}NameAndNumAndID;

//����ڵ�
typedef struct Flight {
    int ID;//����ID���൱��������
    char startPoint[20];//���վ��
    char destination[20];//�յ�վ��
    char planeNum[20];//�ɻ���
    char day[20];//�������ڣ����ڼ���
    int totalTickets;//��Ա����(��Ʊ��)
    int left;//����Ʊ��
    int leftEconomicTicket; //����Ʊʣ����
    int leftBusinessTicket; //����Ʊʣ����
    Flight* next;
    CustomerLinkList cusLinkList;//��Ա������ָ���Ա���������ͷָ��
    WaitLinkQueue economicWaitQueue;//���òպ򲹣��Ⱥ��油�Ŀͻ�������ָ��һ������
    WaitLinkQueue businessWaitQueue;//����պ򲹣��Ⱥ��油�Ŀͻ�������ָ��һ������
} Flight, FlightNode, * PFlight;

/**
 * ��ʼ���Ѷ�Ʊ�˿�ָ������
 * @param cusLinkList �����г�Ա�����ͷָ��
 * @return �Ƿ�ɹ�
 */
Status initCustomerLinkList(CustomerLinkList& cusLinkList);

/**
 * ��ʼ����ͷ���ĺ�������
 * @param q ������ָ��
 * @return �Ƿ�ɹ�
 */
Status initWaitQueue(WaitLinkQueue& q);

/**
 * �����������
 * @param q ��������
 * @param name ����
 * @param amount ��Ʊ��
 * @param identification ���֤��
 * @return ��������
*/
WaitLinkQueue enWaitQueue(WaitLinkQueue& q, char name[], int amount, char identification[]);

/**
 * �������г���
 * @param q ��������
 * @param NameAndNumAndID ��������Ʊ�������֤�ķ�װ�ṹ��
 * @return ���ӽ��
*/
Status deWaitQueue(WaitLinkQueue& q, NameAndNumAndID& NameAndNumAndID);

/**
 * ��ʼ����������
 */
Status initFlight();

/**
 * ���ݺ���ID��ѯ���ಢ��ָ����ʽ����
 * @return  ����ָ��
 */
Flight* find();

/**
 * ���ĳһ������Ϣ
 * @param p ����ڵ�
 */
void showSingleFlight(Flight* p);

/**
 * ��ӡȫ��������Ϣ
 * @param pflight ������Ǻ��������ͷָ��
 */
void showAllFlight(Flight* pflight);

/**
 * ��֤����Ա����
 * @return ���ز������
 */
Status adminVerify();

/**
  * ����Ա
  * ��Ӻ���
  * ͷ���뷨
  * @return ���ز����Ƿ�ɹ�
  */
Status adminInsertFlight();

/**
  * ����Ա
  * ɾ������
  * @return ���ز����Ƿ�ɹ�
  */
Status adminDeleteFlight();

/**
 * ����Ա
 * ��ѯĳһ����Ŀͻ���Ϣ
 */
void adminShowCustomerInfo();

/**
 * ��������ʱ�������ڵĸ���������1��������һ��7���������գ�
 * @param inputDay 1-7
 * @param day ������������ڱ���
 * @return ���ز���״̬�������Ƿ�Ϸ�
 */
Status inputDay(int inputDay, char day[]);

/**
 * �û�
 * ������㡢�յ�վ�����������Ϣ
 */
void userSearchFlight();

/**
 * ����ͬһ·�ߵ���������
 * @return �Ƿ���ҳɹ�
 */
Status showSameFlight(Flight* flight);
/**
 * �û�
 * �Ƽ���Ʊ
 * @param flight ԭ���࣬��������ѡ��ͬһ·�ߵ���ͬ����ID�ĺ���
 */
void userRecommendBookTicket(Flight* flight);

/**
 * ��Ʊ�ɹ�֮�󣬽��˿���Ϣ���뵽��Ӧ����Ķ�Ʊ�˿�����
 * @param head �˿�����ͷָ��
 * @param amount �ó˿Ͷ�Ʊ������
 * @param name �˿͵�����
 * @param rank ��Ʊ�ĵȼ�
 * @return  �˿�����ͷָ��
 */
CustomerLinkList insertCustomerLinklist(CustomerLinkList& head, int amount, char name[], char identification[], int rank);

/** 
 * �û�
 * ��Ʊģ��
 */
void userBookTicket();

/**
 * �û�
 * ��Ʊģ��
 */
void userRefundTicket();


/**
 * �ܲ˵�
 */
void menu();

/**
 *  �û��˵�
 */
void userMenu();

/**
 * ����Ա�˵�
 */
void administratorMenu();