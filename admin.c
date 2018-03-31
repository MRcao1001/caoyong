#include "./admin.h"
#include "./public.h"
#include "./interfaceUI.h"

//添加用户
int addFunc(userNode *pHead)
{
    perInfo data;
    memset(&data, '\0', INFO_LEN);
    getData(&data);
    addUser(pHead, data);
    return 0;
}

//删除用户
int deleteFunc(userNode *pHead)
{
    long cardID = 0;
    printf("\t输入卡号: ");
    cardID = myscanf();

    if(deleteUser(pHead, cardID))
    {
        printf("\n\t删除成功!\n");
        sleep(1);
    }
    else 
    {
        printf("\n\t用户不存在!\n");
        sleep(1);
    }

    return 0;
}

//修改用户信息 --- 此处仅以密码作为样例
int modifyFunc(userNode *pHead)
{
    long cardID = 0;
    printf("\t输入卡号: ");
    cardID = myscanf();
    userNode *p = lookupUser(pHead,cardID);
    if(NULL != p)
    {
        p->data.passwd = 111111;
        printf("\n\t初始化密码成功!\n");
    }
    else 
        printf("\n\t用户不存在!\n");
    return 0;
}

//查找用户
int lookupFunc(userNode *pHead)
{
    long cardID = 0;
    printf("\t输入卡号: ");
    cardID = myscanf();
    userNode *p = lookupUser(pHead,cardID);
    if(NULL != p)
    {
        printf("\t%s\t%ld\t%ld\t%d\t%d\t%ld\n", 
                        p->data.name, 
                        p->data.cardID, 
                        p->data.ID, 
                        p->data.passwd, 
                        p->data.phoneNum, 
                        p->data.balance);
    }
    else 
        printf("\n\t用户不存在!\n");
    return 0;
}

int adminFunc(userNode *pHead)
{
    int choice = myscanf();
    switch(choice)
    {
        case ADD_USER:
        {
            addFunc(pHead);
            break;
        }
        case DELETE_USER:
        {
            deleteFunc(pHead);
            sleep(1);
            break;
        }
        case UPDATE_USER:
        {
            modifyFunc(pHead);
            sleep(1);
            break;
        }
        case LOOKUP_USER:
        {
            lookupFunc(pHead);
            sleep(2);
            break;
        }
        case SHOWALL_USER:
        {
            showAllUser(pHead);
            sleep(1);
            break;
        }
        case EXIT_ADMIN:
        {
            printf("\n\t即将退出...\n");
            sleep(2);
            return 1;
        }
        default:
        {
            printf("\n\t输入错误!\n");
            sleep(1);
            break;
        }
    }
    return 0;
}

void mainMenu(userNode *pHead)
{
    while(1)
    {
        system("clear");
        adminUI();
        if(adminFunc(pHead))
            break;
    }
    return;
}

int main(void)
{
    userNode *pHead = readFromFile();

    mainMenu(pHead);

    writeToFile(pHead);
    destroyList(pHead);
    return 0;
}


