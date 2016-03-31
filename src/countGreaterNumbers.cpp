/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/


#include<stddef.h>
struct transaction {
	int amount;
	char date[11];
	char description[20];
};

int invalidNum(char ch){
	if (ch<'0' || ch>'9')	return 1;
	return 0;
}
int leapYearFail(int d, int m, int y){
	if (
		((y % 4 == 0) && m == 2 && d>29) ||
		((y % 4 != 0) && m == 2 && d>28)
		)	return 1;
	return 0;

}
int strlen(char * str){
	int iter;
	for (iter = 0; str[iter] != '\0'; iter++){}
	return iter;
}
int isOlder(char *dob1, char *dob2) {
	int iter, year1 = 0, year2 = 0, month1 = 0, month2 = 0, date1 = 0, date2 = 0;
	if (strlen(dob1) != strlen(dob2)) return -1;
	for (iter = 6; iter < 10; iter++){
		if (invalidNum(dob1[iter]) || invalidNum(dob2[iter]))	return -1;
		year1 = (year1 * 10) + (dob1[iter] - '0');
		year2 = (year2 * 10) + (dob2[iter] - '0');
	}
	for (iter = 3; iter <= 4; iter++){
		month1 = (month1 * 10) + (dob1[iter] - '0');
		month2 = (month2 * 10) + (dob2[iter] - '0');
	}
	for (iter = 0; iter <= 1; iter++){
		date1 = (date1 * 10) + (dob1[iter] - '0');
		date2 = (date2 * 10) + (dob2[iter] - '0');
	}
	if (month1<1 || month1>12 || month2<1 || month2>12)	return -1;
	if (leapYearFail(date1, month1, year1) || leapYearFail(date1, month2, year2))	return -1;
	if (date1 < 1 || date1>31 || date2 < 1 || date2>31)	return -1;

	if (year1 < year2)	return 1;
	if (year1 > year2)	return 2;
	if (month1>month2) return 2;
	if (month1<month2) return 1;
	if (date1>date2) return 2;
	if (date1<date2) return 1;
	return 0;
}

int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
	if (len < 0 || date == NULL || Arr == NULL)	return -1;
	int iter;
	for (iter = 0; iter < len - 1; iter++){
		if (isOlder(date, Arr[iter].date) == 0){
			if (isOlder(date, Arr[iter + 1].date) == 0){
				continue;
			}
			iter++;
			break;
		}
		else if (isOlder(date, Arr[iter].date) == 1){
			if (isOlder(date, Arr[iter + 1].date) == 2){
				break;
			}
		}

	}
	if (iter == len - 1)	return 0;
	return len - iter;
}