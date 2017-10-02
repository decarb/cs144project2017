#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "apartments.h"
#include "calculations.h"
#include "fileHandling.h"
#include "linkedLists.h"
#include "stringHandling.h"
#include "time.h"
#include "week1Usages.h"

int main(void);
void printWaterUsageReport(double* aptUsages);
void printApartmentReport(double* aptUsages, ApartmentData* apt);
void readCompactUsage(int apartment);
void printList(ListNodePtr startPtr);
void populateList(ListNodePtr* startPtrPtr, double usages[]);
