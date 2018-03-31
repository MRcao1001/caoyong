#ifndef _LIST_H_
#define _LIST_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

//用户基本信息结构
typedef struct perInfo
{
    char name[32];  //姓名
    long cardID;    //银行卡号
    long ID;        //身份证号
    int passwd;     //密码
    int phoneNum;   //电话号码
    long balance;   //余额
}perInfo;

//用户节点结构
typedef struct userNode
{
    struct perInfo data;    //数据域
    struct userNode *pNext; //指针域
}userNode;

//宏定义信息结构长度
#define INFO_LEN sizeof(struct perInfo)
//宏定义节点结构长度
#define NODE_LEN sizeof(struct userNode)

//创建节点
userNode *makeNode();
//添加用户
int addUser(userNode *, perInfo);
//销户---按卡号销户(也可按其他信息销户,如姓名)
int deleteUser(userNode *, long cardID);
//查询---可以按姓名,卡号等进行查询
userNode *lookupUser(userNode *, long cardID);
//修改用户信息---按卡号修改
int updateUser(userNode *, long cardID);
//查看所有用户
void showAllUser(userNode *);
//信息保存---写文件
void writeToFile(userNode *);
//信息加载---读文件
userNode *readFromFile();
//链表的销毁---程序结束前释放所有 malloc 的空间
void destroyList(userNode *);
//数据域数据的获取
int getData(perInfo *);

#endif
