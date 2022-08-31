#include "mini5.h"

//declare phonebook data structure with extern visibility to sync data across with mini5phone.c; was unusable when declared in mini5.h
extern struct PHONE_RECORD {
	char name[NAME_MAXLEN];
	char birthdate[BIRTHDATE_MAXLEN];
	char phone[PHONE_MAXLEN];
} phonebook[PHONEBOOK_MAXLEN];

int menu() {
	char option[2]; //define character array to hold user choice for menu prompt

	printf("Phonebook Menu: (1)Add, (2)Find, (3)List, (4)Quit> "); //display phonebook menu prompt
	fgets(option, MAXCHARS, stdin); //take user choice

	return (atoi(option));
}

int main() {
	loadCSV("phonebook.csv"); //load data from the phonebook.csv file by passing it as a parameter to the mini5phone.c method loadCSV()

        //define buffer character arrays to hold user input
	char nameInputFind[MAXCHARS];
	char nameToFind[MAXCHARS];
	
	char nameInputAdd[MAXCHARS];
	char birthInput[MAXCHARS];
	char phoneInput[MAXCHARS];

	char nameToAdd[MAXCHARS];
	char birthdateToAdd[MAXCHARS];
	char phoneToAdd[MAXCHARS];

	int option; //declare integer variable to store user choice
	do { //keep calling menu() and call the respective mini5phone.c methods after parsing the data until the user quits the program
		option = menu(); //store user choice
		switch(option) {
			case 1: //Add Option
				if(getPhonebookLength() < PHONEBOOK_MAXLEN) { //check if phonebook struct isn't empty before taking user input

					//take user input and store in character arrays
					printf("Name: ");
					fgets(nameInputAdd, MAXCHARS, stdin);
					printf("Birth: ");
					fgets(birthInput, MAXCHARS, stdin);
					printf("Phone: ");
					fgets(phoneInput, MAXCHARS, stdin);
					
					//the terminal symbol in fgets is a newline character; strtok gets the first part of the data without the newline character and stores it the character array
					strcpy(nameToAdd, strtok(nameInputAdd, "\n"));
					strcpy(birthdateToAdd, strtok(birthInput, "\n"));
					strcpy(phoneToAdd, strtok(phoneInput, "\n"));

					//truncates data to the number of character that will fit in the phonebook character arrays by appending the last index to a null character
					nameToAdd[NAME_MAXLEN-1] = 0;
					birthdateToAdd[BIRTHDATE_MAXLEN-1] = 0;
					phoneToAdd[PHONE_MAXLEN-1] = 0;

					//pass values as parameters to the mini5phone.c method addRecord()
					addRecord(nameToAdd, birthdateToAdd, phoneToAdd);
					break;
				} else {
					printf("No more space in the CSV file\n"); //phonebook struct has 10 entries, so print it's full
					break;
				}

			case 2: //Find Option
				if(getPhonebookLength() != 0) { //check if phonebook struct isn't empty before taking user input

					//take user input and store in a character array
					printf("Find name: ");
					fgets(nameInputFind, MAXCHARS, stdin);

					strcpy(nameToFind, strtok(nameInputFind, "\n")); //removes newline character from data
					nameToFind[NAME_MAXLEN-1] = 0; //truncate input to first 49 characters

					findRecord(nameToFind); //pass name as parameter to the miniphone.c method findRecord()
					break;
				}  else {
					if(!isFileExists()) { //if fileExists = 0, then file didn't exist before program execution and there's nothing to list
						printf("Phonebook.csv does not exist\n"); //print the phonebook doesn't exist
					} else printf("Phonebook.csv is empty\n"); //print the phonebook is emptry since nothing copied to phonebook struct thus phonebook length is 0
					break;
				}

			case 3: //List Option
				listRecords(); //display all the data within the phonebook struct array data by passing its address to the mini5phone.c method listRecords()
				break;

			case 4: //Quit Option
				saveCSV("phonebook.csv"); //overwrite data from the struct array into the phonebook.csv file by passing it as a parameter to the mini5phone.c method saveCSV()
				printf("End of phonebook program\n");
				break;

			default:
				printf("Invalid Input\n"); //print an error when the user selects one of the options not listed by menu()
				break;
		}
	} while(option != 4); //exit the do-while loop when the user decides to exit the program

	return 0; //successful program execution
}
