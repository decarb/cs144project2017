/*
 * stringHandling.c
 *
 *  Created on: 17 Aug 2017
 *      Author: Luke Skywalker
 * Description: Functions for dealing with strings.
 */

#include <stdio.h>
#include <string.h>

#define DEBUG 0


void csvToStrings(char *csvString, char *day, char *time, char *usage1, char *usage2, char *usage3)
{
	// Declare variables
	int i, j;
	char c;

	if (DEBUG)
		printf("csvToStrings: Length of string is %d\n", strlen(csvString));

	// Read day
	i = 0;
	j = 0;
	c = csvString[i++];
	while (c != ',')
	{
		day[j++] = c;
		c = csvString[i++];
	}
	day[j++] = '\0';
	if (DEBUG)
		printf("csvToStrings: day string: %s\n", day);

	// Read time
    j = 0;
    c = csvString[i++];
    while (c != ',')
    {
        time[j++] = c;
        c = csvString[i++];
    }
    time[j++] = '\0';
    if (DEBUG)
        printf("csvToStrings: time string: %s\n", time);

	// Read usage1
    j = 0;
    c = csvString[i++];
    while (c != ',')
    {
        usage1[j++] = c;
        c = csvString[i++];
    }
    usage1[j++] = '\0';
    if (DEBUG)
        printf("csvToStrings: usage1 string: %s\n", usage1);

	// Read usage2
    j = 0;
    c = csvString[i++];
    while (c != ',')
    {
        usage2[j++] = c;
        c = csvString[i++];
    }
    usage2[j++] = '\0';
    if (DEBUG)
        printf("csvToStrings: usage2 string: %s\n", usage2);

	// Read usage3
    j = 0;
    c = csvString[i++];
    while (c != '\0')
    {
        usage3[j++] = c;
        c = csvString[i++];
    }
    usage3[j++] = '\0';
    if (DEBUG)
        printf("csvToStrings: usage3 string: %s\n", usage3);
}
