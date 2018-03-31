all:admin atm

OBJS:= list.o public.o interfaceUI.o
ADM_OBJS:=admin.o $(OBJS)
ATM_OBJS:=atm.o $(OBJS)

admin:$(ADM_OBJS)
	gcc $(ADM_OBJS) -o admin -Wall

atm:$(ATM_OBJS)
	gcc $(ATM_OBJS) -o atm -Wall

%.o:%.c
	gcc -c $< -o $@ -Wall

clean:
	rm -fr atm admin
	rm -fr $(ADM_OBJS)
	rm -fr $(ATM_OBJS)


