#include "./atm.h"
#include "./interfaceUI.h"
#include "./public.h"

int getNewPasawd()
{
    int oldPasswd = 0;
    int newPasswd = 0;
    while(1)
    {
        system("clear");
        printf("\n\n\n==========================\n");
        printf("\n\t输入新密码: ");
        oldPasswd = myscanf();
        printf("\n\t再次确认密码: ");
        newPasswd = myscanf();
        if(oldPasswd == newPasswd)
        {
            return newPasswd;
        }
        else 
        {
            printf("\n\t两次输入密码不一致!\n\t请重新输入!\n");
            sleep(1);
        }
    }
    return 0;
}

int modifyPasswd(userNode *temp)
{
    int oldPasswd = 0;
    while(1)
    {
        system("clear");
        printf("\n\n\n==========================\n");
        printf("\t输入原密码: ");
        oldPasswd = myscanf();
        if(0 == oldPasswd)
        {
            return 0;
        }
        else if(oldPasswd == temp->data.passwd)
        {
            temp->data.passwd = getNewPasawd();
            return 1;
        }
        else
        {
            printf("\n\t密码输入错误!\n");
            sleep(1);
        }
    }
    return 0;
}

int takeMoney(userNode *temp)
{
    long money = 0;
    while(1)
    {
        system("clear");
        printf("\n\n\n==========================\n");
        printf("\t取出金额: ");
        money = myscanf();
        //保证取出金额小于余额同时取出的钱数是 100 的倍数
        if((money < temp->data.balance) && (money % 100 == 0))
        {
            temp->data.balance -= money;
            break;
        }
        else
        {
            printf("\n\t输入金额有误!重新输入！\n");
            sleep(1);
        }
    }
    return 0;
}

int saveMoney(userNode *temp)
{
    long money = 0;
    while(1)
    {
        system("clear");
        printf("\n\n\n\t==============================================\n");
        printf("\t\t存入金额: ");
        money = myscanf();
        if(money%100 == 0)
        {
            temp->data.balance += money;
            break;
        }
        else
        {
            printf("\n\n\t金额有误!\n\t重新确定金额!\n");
            sleep(1);
        }
    }
    return 0;
}

int checkBalance(userNode *temp)
{
    system("clear");
    printf("\n\n\n\t============================================\n");
    printf("\n\t\t当前余额: %ld$\n", temp->data.balance);
    sleep(1);
    return 0;
}

int atmFunc(userNode *pHead, userNode *temp)
{
    char ch = '\0';
    mygets(&ch,2);
    switch(ch)
    {
        case BALANCE:
        {
            checkBalance(temp);
            break;
        }
        case TAKE_MONEY:
        {
            takeMoney(temp);
            break;
        }
        case SAVE_MONEY:
        {
            saveMoney(temp);
            checkBalance(temp);
            break;
        }
        case MODIFY_PASWD:
        {
            if(modifyPasswd(temp))
                printf("\n\t修改成功!\n");
            else
                printf("\n\t修改失败!\n");
            break;
        }
        case EXIT_ATM:
        {
            return 1;
        }
    }
    return 0;
}

int loginSuccessful(userNode *pHead, userNode *temp)
{
    while(1)
    {
        system("clear");
        atmUI();
        if(atmFunc(pHead, temp))
            break;
    }

    return 0;
}

userNode *accountCheck(userNode *pHead, long cardId, long passwd)
{
    userNode *temp = pHead->pNext;
    while(NULL != temp)
    {
        if(temp->data.cardID == cardId && temp->data.passwd == passwd)
        {
            printf("\t登录成功!\n");
            sleep(1);
            return temp;
            //loginSuccessful(pHead);
        }
        temp = temp->pNext;
    }
    if(NULL == temp)
    {
        printf("\t账号或密码错误!\n");
        sleep(1);
        return NULL;
    }
    return NULL;
}

void loginUI(userNode *pHead)
{
    long cardId = 0;
    long passwd = 0;
    userNode *temp = NULL;

    while(1)
    {
        system("clear");
        printf("\n\n\n\t输入卡号: ");
        cardId = myscanf();
        printf("\t输入密码: ");
        passwd = myscanf();
        //密码和帐号的匹配
        if((temp = accountCheck(pHead, cardId, passwd)) != NULL)
        {
            loginSuccessful(pHead, temp);
            writeToFile(pHead);
            destroyList(pHead);
        }
    }
    return ;
}



int main(void)
{
    userNode *pHead = readFromFile();

    loginUI(pHead);
    
    return 0;
}


