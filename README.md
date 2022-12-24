# AirPassengerBookingSystem

大二上数据结构课设：航空客运订票系统

## 问题描述

航空客运订票的业务活动包括：查询航线、客票预订和办理退票等。试设计一个航空客运订票系统，以使上述业务可以借助计算机来完成。

## 基本需求

(1)	每条航线所涉及的信息有：终点站名、航班号、飞机号、飞行周日(星期几)、乘员定额、余票量、已订票的客户名单(包括姓名、订票量、舱位等级 1，2 或 3)以及等候替补的客户名单(包括姓名、所需票量)；

(2) 作为示意系统，全部数据可以只放在内存中；

(3) 系统能实现的操作和功能如下：

① 查询航线：根据旅客提出的终点站名输出下列信息：航班号、飞机号、星期几飞行，最近一天航班的日期和余票额；

② 承办订票业务：根据客户提出的要求(航班号、订票数额)查询该航班票额情况，若尚有余票，则为客户办理订票手续，输出座位号；若已满员或余票额少于订票额，则需重新询问客户要求。若需要，可登记排队候补；

③ 承办退票业务：根据客户提供的情况(日期、航班)，为客户办理退票手续，然后查询该航班是否有人排队候补，首先询问排在第一的客户，若所退票额能满足他的要求，则为他办理订票手续，否则依次询问其它排队候补的客户。

## 选做内容

(1)	当客户订票要求不能满足时，系统可向客户提供到达同一目的地的其它航线情况。

(2)	增加管理员模块。包括管理员的验证，查看、增加、删除航班和查看某一航班的客户信息。
