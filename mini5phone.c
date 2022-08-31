#include "mini5.h"

int phonebookLength; //global variable to keep track of the number of elements in the phonebook
int fileExists = 1; //keep track of if the file exists before program execution

//phonebook data structure
struct PHONE_RECORD {
	char name[NAME_MAXLEN];
	char birthdate[BIRTHDATE_MAXLEN];
	char phone[PHONE_MAXLEN];
} phonebook[PHONEBOOK_MAXLEN];

//getter method for the phonebookLength, provides functionality to call in mini5main.c
int getPhonebookLength() {
	return phonebookLength;
}

//getter method for if the file exists, provides functionality to call in mini5main.c
int isFileExists() {
	return fileExists;
}

int loadCSV(char* fileName) {
	FILE *filePointer; //create file pointer
	filePointer = fopen(fileName, "r"); //open the file and set to read mode

	if(filePointer) { //if file exists
		char headerLine[MAXCHARS]; //create a temporary character array
		fgets(headerLine, MAXCHARS, filePointer); //read and discard the header line

		char buffer[MAXCHARS]; //declare buffer character array to process the file data line by line

		/*
		* while loop iterates through the file data until reached the end
		* fgets() returns a null value when reached the end of the file
		* filePointer tells fgets() to store the entire line of data into the buffer and moves the filePointer to the next line
		* was unable to use !feof(filePointer) as the while loop condition since it indicates if the EOF has already been reached, rather than check for the EOF
		*/
		while(fgets(buffer, MAXCHARS, filePointer)) {

			//split the buffer data into three tokens by using strtok() and setting ',' as the delimiter and '\n' as the delimiter to indicate the end of the buffer
			//copy the tokens into its respective place in the phonebook struct using strcpy
			char* token = strtok(buffer, ",");
			strcpy(phonebook[phonebookLength].name, token);

			token = strtok(NULL, ",");
			strcpy(phonebook[phonebookLength].birthdate, token);

			token = strtok(NULL, "\n");
			strcpy(phonebook[phonebookLength].phone, token);
		
			phonebookLength++; //increment the phonebook struct length to indicate the next empty position
		}
	} else { //if the file doesn't exist
		fileExists = 0; //remember that file didn't exist while loading
		filePointer = fopen(fileName, "w+"); //create a new file using the w+ writing mode
		return 1; //error code 1 because file didn't exist before program execution
	}
	fclose(filePointer); //close the file pointer
	return 0; //successful execution
}

int saveCSV(char* fileName) {
	FILE *filePointer; //create file pointer
	filePointer = fopen(fileName, "w"); //open the file and set to write mode

	fprintf(filePointer, "Name,birthdate,phone\n"); //write the header line into the file
	for(int i=0; i<getPhonebookLength(); i++) {
		fprintf(filePointer, "%s,%s,%s\n", phonebook[i].name,  phonebook[i].birthdate,  phonebook[i].phone); //iterate through the phonebook struct and print the data into the file
	}

	fclose(filePointer); //close the file pointer
	return 0; //successful execution
}

int addRecord(char* name, char* birthdate, char* phone) {
	strcpy(phonebook[getPhonebookLength()].name, name); //copy the name given by the user into the phonebook struct's name character array
	strcpy(phonebook[getPhonebookLength()].birthdate, birthdate); //copy the birthdate given by the user into the phonebook struct's birthdate character array
	strcpy(phonebook[getPhonebookLength()].phone, phone); //copy the phone given by the user into the phonebook struct's phone character array
	phonebookLength++; //increment the number of elements in the phonebook struct
	return 0; //successful execution
}

void createDataTable(int index, int columnWidth, int phoneNumberLength) {
	char truncatedName[MAXCHARS]; //declare character array to truncate names to fit the pretty format of the table
	strcpy(truncatedName, phonebook[index].name); //copy the phonebook struct name into a buffer character array

	if(strlen(phonebook[index].name) > columnWidth) { //if the name won't fit within the name column, truncate the character array by appending a null character at the end
		truncatedName[columnWidth] = 0;
	}
	printf("%s", truncatedName); //print name to the data table

	//determines the number of spaces needed to ensure birthdate is aligned in the data table
	int numberOfSpaces = columnWidth-strlen(truncatedName);
	for(int i=0; i<numberOfSpaces; i++) {
		printf(" ");
	} printf(" "); //always print one space separator between the data columns; lets data be readable even when length of name > columnWidth

	printf("%s", phonebook[index].birthdate); //print birthdate to the data table

	//determines the number of spaces needed to ensure phone number is aligned in the data table
	numberOfSpaces = columnWidth-strlen(phonebook[index].birthdate);
	for(int i=0; i<numberOfSpaces; i++) {
		printf(" ");
	} printf(" "); //always print one space separator between the data columns

	//determines the number of spaces needed to ensure phone number is right-justified in the data table as shown in the assignment handout
	numberOfSpaces = phoneNumberLength-strlen(phonebook[index].phone);
	for(int i=0; i<numberOfSpaces; i++) {
		printf(" ");
	}
	printf("%s\n", phonebook[index].phone); //print phone number to the data table
}

int findRecord(char* name) {
	int currentIndex = 0; //current index of the struct character array
	while(currentIndex < getPhonebookLength()) { //iterate through all the data in the phonebook struct
		if(!strcmp(phonebook[currentIndex].name, name)) { //if the name in the phonebook struct matches the name the user is searching for then strcmp returns 0, and if(!0) is equivalent to if(true)
			
			//declare static integers indication necessary information to match "pretty format" of the data table
			static int columnWidth = 17;
			static int phoneNumberLength = 14;

			printf("----NAME--------- ------BIRTH------ -----PHONE-------\n"); //header line of the data table
			createDataTable(currentIndex, columnWidth, phoneNumberLength); //create the data table
			return 0; //successful execution
		} else currentIndex++; //check the next data entry in the phonebook struct
	}
 
	printf("Does not exist\n"); //name couldn't found anywhere in the phonebook struct, print the record doesn't exist
	return 1; //error code 1 for search failure
}

int listRecords() {
	if(getPhonebookLength() != 0) { //if phonebook struct isn't empty

		//declare static integers indication necessary information to match "pretty format" of the data table
		static int columnWidth = 17;
		static int phoneNumberLength = 14;

		printf("----NAME--------- ------BIRTH------ -----PHONE-------\n"); //header line of the data table
		for(int i=0; i<getPhonebookLength(); i++) { //iterate through all the elements in the phonebook struct
			createDataTable(i, columnWidth, phoneNumberLength); //create the data table
		}
	} else { //handles the case where if 1) the file doesn't exist, 2) the file is empty, or 3) the file only has the header line, and no actual entry lines
		if(!isFileExists()) { //if fileExists = 0, then file didn't exist before program execution and there's nothing to list
			printf("Phonebook.csv does not exist\n"); //print the phonebook doesn't exist
		} else	printf("Phonebook.csv is empty\n"); //print the phonebook is emptry since nothing copied to phonebook struct thus phonebook length is 0
		return 1; //error code 1 for no data in the phonebook struct
	}

	return 0; //successful execution
}
