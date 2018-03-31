#include "./list.h"
#include "./public.h"

/***********************************
*函 数 名：
*功能实现：
*输入参数：
*返 回 值：
************************************/
userNode *makeNode()
{
    userNode *newNode = (userNode*)malloc(NODE_LEN);
    if(NULL == newNode)
        newNode = (userNode*)malloc(NODE_LEN);
    newNode->pNext = NULL;
    return newNode;
}

//获得数据域的基本信息
int getData(perInfo *temp)
{
    system("clear");
    printf("\n\n\t\t       信息录入\n");
    printf("\t=========================================\n");
    printf("\t\t姓名: ");
    mygets(temp->name, sizeof(temp->name));

    printf("\t\t卡号: ");
    temp->cardID = myscanf();

    printf("\t\t身份证号: ");
    temp->ID = myscanf();

    //密码初始化为: 111111
    temp->passwd = 111111;

    printf("\t\t电话: ");
    temp->phoneNum = myscanf();

    printf("\t\t金额: ");
    temp->balance = myscanf();

    return 0;
}

//添加用户---头插法
int addUser(userNode *pHead, perInfo data)
{
    if(NULL == pHead)
    {
        printf("\n\t%s:the link is empty!\n", __func__);
        return -1;
    }

    //申请新的节点并初始化数据域
    userNode *newNode = makeNode();
    //getData(&newNode->data);
    newNode->data = data;

    //创建链表
    newNode->pNext = pHead->pNext;
    pHead->pNext = newNode;
    newNode = NULL;
    return 0;
}

//销毁用户 --- 按 cardID
int deleteUser(userNode *pHead, long cardID)
{
    if(NULL == pHead || NULL == pHead->pNext)
    {
        printf("\n\t%s:the link is empty!\n", __func__);
        return -1;
    }

    userNode *pPre = pHead;
    userNode *pCur = pHead->pNext;

    while(NULL != pCur)
    {
        if(cardID == pCur->data.cardID)
        {
            pPre->pNext = pCur->pNext;
            free(pCur);
            pCur = NULL;
            return 1;       //找到并删除,返回 1
        }
        pCur = pCur->pNext;
        pPre = pPre->pNext;
    }
    if(NULL == pCur)
        return 0;           //未找到cardID匹配信息,返回 0
    return 1;
}

//修改用户信息 --- 按 cardID,返回用户信息节点
int updateUser(userNode *pHead, long cardID)
{
    return 0;
}

//查找用户信息 --- 按 cardID,返回用户信息节点
userNode *lookupUser(userNode *pHead, long cardID)
{
    if(NULL == pHead || NULL == pHead->pNext)
    {
        printf("\n\t%s:the link is empty!\n", __func__);
        return NULL;
    }
    
    userNode *temp = pHead->pNext;
    while(NULL != temp)
    {
        if(cardID == temp->data.cardID)
            return temp;
        temp = temp->pNext;
    }
    return NULL;
}

//显示所有用户
void showAllUser(userNode *pHead)
{
    if(NULL == pHead || NULL == pHead->pNext)
    {
        printf("\n\t%s:the link is empty!\n", __func__);
        return;
    }
    userNode *p = pHead->pNext;
    while(NULL != p)
    {
        printf("\t%s\t%ld\t%ld\t%d\t%ld\n", 
                        p->data.name, 
                        p->data.cardID, 
                        p->data.ID, 
                        p->data.phoneNum, 
                        p->data.balance);
        p = p->pNext;
    }
    return;
}

//保存数据---写文件
void writeToFile(userNode *pHead)
{
    if(NULL == pHead || NULL == pHead->pNext)
    {
        printf("\n\tthere is not info to save!\n");
        return;
    }
    FILE *fpw = fopen("user.dat", "w");
    if(NULL == fpw)
    {
        perror("fopen error");
        return;
    }

    userNode *temp = pHead->pNext;
    int ret = 0;
    while(NULL != temp)
    {
        ret = fwrite(&temp->data, INFO_LEN, 1, fpw);
        if(ret < 0)
            break;
        temp = temp->pNext;
    }

    fclose(fpw);
    return;
}

//加载数据---读文件
userNode *readFromFile()
{
    FILE *fpr = fopen("./user.dat", "r");
    if(NULL == fpr)
    {
        perror("fopen error");
        exit(1);
    }
    userNode *pHead = makeNode();
    userNode *newNode = makeNode();

    while(fread(&newNode->data, INFO_LEN, 1, fpr) > 0)
    {
        newNode->pNext = pHead->pNext;
        pHead->pNext = newNode;
        newNode = makeNode();
    }
    free(newNode);
    newNode = NULL;
    fclose(fpr);
    return pHead;
}

//销毁用户数据链表
void destroyList(userNode *pHead)
{
    if(NULL == pHead)
    {
        printf("\n\t%s:the list is empty!\n", __func__);
        return;
    }

    userNode *p = NULL;
    while(NULL != pHead)
    {
        p = pHead;
        pHead = pHead->pNext;
        free(p);
    }
    p = NULL;
    return;
}

