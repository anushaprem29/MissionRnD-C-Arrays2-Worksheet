/*
OVERVIEW: You are given 2 bank statements that are ordered by date. 
Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.


ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};
int invalidNum2(char ch){
	if (ch<'0' || ch>'9')	return 1;
	return 0;
}

int leapYearFail2(int d, int m, int y){
	if (
		((y % 4 == 0) && m == 2 && d>29) ||
		((y % 4 != 0) && m == 2 && d>28)
		)	return 1;
	return 0;

}
int isOlder2(char *dob1, char *dob2) {
	int iter, year1 = 0, year2 = 0, month1 = 0, month2 = 0, date1 = 0, date2 = 0;
	if (strlen(dob1) != strlen(dob2)) return -1;
	for (iter = 6; iter < 10; iter++){
		if (invalidNum2(dob1[iter]) || invalidNum2(dob2[iter]))	return -1;
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
	if (leapYearFail2(date1, month1, year1) || leapYearFail2(date1, month2, year2))	return -1;
	if (date1 < 1 || date1>31 || date2 < 1 || date2>31)	return -1;

	if (year1 < year2)	return 1;
	if (year1 > year2)	return 2;
	if (month1>month2) return 2;
	if (month1<month2) return 1;
	if (date1>date2) return 2;
	if (date1<date2) return 1;
	return 0;
}

struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	int iter1 = 0, iter2 = 0, val, iter3 = 0;
	struct transaction  *Arr = (struct transaction *) malloc(sizeof(struct transaction) * 10);
	if (A == NULL || B == NULL || ALen < 0 || BLen < 0) return NULL;

	while (isOlder2(A[iter1].date, B[iter2].date) == 2){
		iter1++;
	}
	while (isOlder2(A[iter1].date, B[iter2].date) == 1){
		iter2++;
	}
	while (iter1 < ALen || iter2 < BLen){
		val = isOlder2(A[iter1].date, B[iter2].date);
		if (val == 0)
		{
			Arr[iter3].amount = A[iter1].amount;
			strcpy(Arr[iter3].date, A[iter1].date);
			strcpy(Arr[iter3].description, A[iter1].description);
			iter3++;
			iter1++;
			iter2++;
		}
		else if (val == 1){
			iter2++;
		}
		else{
			iter1++;
		}
	}
	if (iter3 == 0)	return NULL;
	return Arr;

}