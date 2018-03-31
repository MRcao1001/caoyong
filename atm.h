#ifndef _ATM_H_
#define _ATM_H_

#include "./list.h"

enum ATM_FUNC
{
    EXIT_ATM = '0',
    BALANCE,
    TAKE_MONEY,
    SAVE_MONEY,
    MODIFY_PASWD
};

void loginUI(userNode *pHead);
userNode *accountCheck(userNode *pHead, long cardId, long passwd);
int loginSuccessful(userNode *pHead, userNode *temp);
int atmFunc(userNode *pHead, userNode *temp);
int checkBalance(userNode *temp);
int saveMoney(userNode *temp);
int takeMoney(userNode *temp);
int modifyPasswd(userNode *temp);
int getNewPasawd();


#endif
