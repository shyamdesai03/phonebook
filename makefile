program: mini5phone.o mini5main.o
	gcc -o phonebook mini5main.o mini5phone.o

mini5main.o: mini5main.c mini5.h
	gcc -c mini5main.c

mini5phone.o: mini5phone.c mini5.h
	gcc -c mini5phone.c
