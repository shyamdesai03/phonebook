/*
* Shyam Desai
* ECSE - U1 Software Engineering
* shyam.desai@mail.mcgill.ca
* Submitted: 9th April, 2022
*/

#ifndef MINI5_H_
#define MINI5_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NAME_MAXLEN 50
#define BIRTHDATE_MAXLEN 12
#define PHONE_MAXLEN 15
#define PHONEBOOK_MAXLEN 10
#define MAXCHARS 100 //max characters to read in fgets() while taking in user input to avoid overflow and weird outputs

//function prototypes
int menu();

int loadCSV(char* fileName);
int saveCSV(char* fileName);
int addRecord(char* name, char* birthdate, char* phone);
int findRecord(char* name);
int listRecords();

void createDataTable(int index, int columnWidth, int phoneNumberLength);
int getPhonebookLength();
int isFileExists();

#endif
