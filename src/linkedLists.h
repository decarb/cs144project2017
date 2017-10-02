/*
 * linkedLists.h
 *
 *  Created on: 29 Aug 2017
 *      Author: Luke Skywalker
 */

#ifndef LINKEDLISTS_H_
#define LINKEDLISTS_H_

struct listNode
{
    int monthHour;
    double usage;
    struct listNode *nextPtr;
};
typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

void addNode(ListNodePtr *startPtrPtr, int epoch, double usage);
void printList(ListNodePtr startPtr);  // can define this function to use for debugging
int monthHourOfMaxUsage(ListNodePtr startPtr);  // returns the hour in the month with the maximum usage

#endif /* LINKEDLISTS_H_ */
