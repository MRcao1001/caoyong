#ifndef _ADMIN_H_
#define _ADMIN_H_

#include"./list.h"

enum AdminFunc
{
    EXIT_ADMIN,
    ADD_USER,
    DELETE_USER,
    UPDATE_USER,
    LOOKUP_USER,
    SHOWALL_USER
};

void mainMenu(userNode *);
int adminFunc(userNode *);
int deleteFunc(userNode *pHead);

int addFunc(userNode *pHead);
int lookupFunc(userNode *pHead);
int modifyFunc(userNode *pHead);




#endif
