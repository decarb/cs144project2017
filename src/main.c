#include "main.h"

int main(void)
{
	setbuf(stdout, 0);

	int menuChoice = 0;
	int aptChoice = 0;
	char filename[30];

	ApartmentData apt1;
	double apt1Usage[30 * 24];

	ApartmentData apt2;
	double apt2Usage[30 * 24];

	ApartmentData apt3;
	double apt3Usage[30 * 24];

	readMetadataFromFile(&apt1, &apt2, &apt3);
	readUsageFromFile(apt1Usage, apt2Usage, apt3Usage);

	ListNodePtr apt1List = NULL;
	ListNodePtr apt2List = NULL;
	ListNodePtr apt3List = NULL;

	populateList(&apt1List, apt1Usage);
	populateList(&apt2List, apt2Usage);
	populateList(&apt3List, apt3Usage);

	printf("RP143 Water Calculator\n"
			"1. Print usage pattern for apartment\n"
			"2. Calculate and print total usage for apartment (in kL)\n"
			"3. Calculate and print total bill for apartment (in R)\n"
			"4. Print apartment usage report to screen\n"
			"5. Check building for leaks and print leak report\n"
			"6. Write building water usage report to text file\n"
			"7. Save or print compact binary usage file for apartment\n"
			"8. Determine and print hour with greatest usage for apartment\n"
			"10. Exit\n\n");

	printf("Choose an item from the menu: ");
	scanf("%d", &menuChoice);

	while(menuChoice != 10)
	{
		printf("\n");

		if (menuChoice != 5 && menuChoice != 6)
		{
			printf("Choose apartment (1, 2 or 3): ");
			scanf("%d", &aptChoice);

			printf("\n");
		}

		switch(menuChoice)
		{
		case 1:
			switch(aptChoice)
			{
			case 1:
				printWaterUsageReport(apt1Usage);
				break;
			case 2:
				printWaterUsageReport(apt2Usage);
				break;
			case 3:
				printWaterUsageReport(apt3Usage);
				break;
			}
			break;
		case 2:
			switch(aptChoice)
			{
			case 1:
				printf("Total usage for apartment 1: %.3lf kL", getTotalWaterUsage(apt1Usage));
				break;
			case 2:
				printf("Total usage for apartment 2: %.3lf kL", getTotalWaterUsage(apt2Usage));
				break;
			case 3:
				printf("Total usage for apartment 3: %.3lf kL", getTotalWaterUsage(apt3Usage));
				break;
			}
			break;
		case 3:
			switch(aptChoice)
			{
			case 1:
				printf("Total bill for apartment 1 for this month: R%.2lf", getTotalBill(apt1Usage, apt1.tariff));
				break;
			case 2:
				printf("Total bill for apartment 2 for this month: R%.2lf", getTotalBill(apt2Usage, apt2.tariff));
				break;
			case 3:
				printf("Total bill for apartment 3 for this month: R%.2lf", getTotalBill(apt3Usage, apt3.tariff));
				break;
			}
			break;
		case 4:
			switch(aptChoice)
			{
			case 1:
				printApartmentReport(apt1Usage, &apt1);
				break;
			case 2:
				printApartmentReport(apt2Usage, &apt2);
				break;
			case 3:
				printApartmentReport(apt3Usage, &apt3);
				break;
			}
			break;
		case 5:
			printf("Apartment 1: ");
			int leak = checkForLeak(apt1Usage);

			if (!leak) printf("No leak\n");
			else printf("Leak on day %d\n", leak);

			printf("Apartment 2: ");
			leak = checkForLeak(apt2Usage);

			if (!leak)printf("No leak\n");
			else printf("Leak on day %d\n", leak);

			printf("Apartment 3: ");
			leak = checkForLeak(apt3Usage);

			if (!leak) printf("No leak");
			else printf("Leak on day %d", leak);

			break;
		case 6:
			printf("Filename of text file: ");
			scanf("%s", filename);

			writeBuildingReport(apt1Usage, apt2Usage, apt3Usage, apt1, apt2, apt3, filename);
			break;
		case 7:
		{
			int choice;

			printf("Save (1) or print (2) compact usage file: ");
			scanf("%d", &choice);

			printf("\n");

			switch (choice)
			{
			case 1:
				switch (aptChoice)
				{
				case 1:
					saveCompactUsage(apt1Usage, 1);
					break;
				case 2:
					saveCompactUsage(apt2Usage, 2);
					break;
				case 3:
					saveCompactUsage(apt3Usage, 3);
					break;
				}
				break;
			case 2:
				readCompactUsage(aptChoice);
				break;
			}
		}
		break;
		case 8:
		{
			int maxHour;
			double usage;

			switch (aptChoice)
			{
			case 1:
				maxHour = monthHourOfMaxUsage(apt1List);
				usage = apt1Usage[maxHour];
				break;
			case 2:
				maxHour = monthHourOfMaxUsage(apt2List);
				usage = apt2Usage[maxHour];
				break;
			case 3:
				maxHour = monthHourOfMaxUsage(apt3List);
				usage = apt3Usage[maxHour];
				break;
			}

			printf("Maximum usage for apartment %d:\n", aptChoice);
			printf("Day %d %02d:00 : %.3lf kL", monthHourToDay(maxHour), monthHourToDailyHour(maxHour), usage);
		}
			break;
		}

		printf("\n\nChoose an item from the menu: ");
		scanf("%d", &menuChoice);
	}

	return 1;
}

int monthHourToDay(int monthHour)
{
	return (monthHour / 24) + 1;
}

int monthHourToDailyHour(int monthHour)
{
	return monthHour % 24;
}

void printWaterUsageReport(double* aptUsages)
{
	int i;

	printf("Active water usage report:\n");

	for (i = 0; i < 720; i++)
		if (aptUsages[i] != 0) printf("Day %02d %02d:00 : %.3lf kL\n", monthHourToDay(i), monthHourToDailyHour(i), aptUsages[i]);
}

double getTotalWaterUsage(double waterUsage[])
{
	int i;
	double total = 0;

	for (i = 0; i < 720; i++) total += waterUsage[i];

	return total;
}

double getTotalBill(double waterUsage[], double tariff)
{
	return getTotalWaterUsage(waterUsage) * tariff;
}

void printApartmentReport(double* aptUsages, ApartmentData* apt)
{
	printf("Apartment water usage report:\n"
			"Owner: %s %s\n"
			"Tariff for apartment: R%.2lf per kL\n"
			"Total usage for this month: %.3lf kL\n"
			"Total bill for this month: R%.2lf", apt->ownerName, apt->ownerSurname, apt->tariff, getTotalWaterUsage(aptUsages), getTotalBill(aptUsages, apt->tariff));
}

void readMetadataFromFile(ApartmentData *data1, ApartmentData *data2, ApartmentData *data3)
{
	char names[3][30];
	char surnames[3][30];
	double tariffs[3];

	FILE* file;
	file = fopen("apartments_metadata.txt", "r");

	if (file != NULL)
	{
		int i;

		for (i = 0; i < 3; i++) fscanf(file, "%s %s %lf\n", &names[i][0], &surnames[i][0], &tariffs[i]);
	}

	fclose(file);

	strcpy(data1->ownerName, names[0]);
	strcpy(data1->ownerSurname, surnames[0]);
	data1->tariff = tariffs[0];

	strcpy(data2->ownerName, names[1]);
	strcpy(data2->ownerSurname, surnames[1]);
	data2->tariff = tariffs[1];

	strcpy(data3->ownerName, names[2]);
	strcpy(data3->ownerSurname, surnames[2]);
	data3->tariff = tariffs[2];
}

void readUsageFromFile(double usage1[], double usage2[], double usage3[])
{
	char day[10], time[10], line[50], use1[10], use2[10], use3[10];

	FILE* file;
	file = fopen("water_usage.csv", "r");

	if (file != NULL)
	{
		fgets(line, sizeof(line), file); //GET FIRST LINE TO DISCARD - HEADING

		int i;
		for (i = 0; i < 720; i++)
		{
			fgets(line, sizeof(line), file);
			csvToStrings(line, day, time, use1, use2, use3);

			usage1[i] = atof(use1);
			usage2[i] = atof(use2);
			usage3[i] = atof(use3);
		}
	}

	fclose(file);
}

int checkForLeak(double waterUsage[])
{
	int i;
	double usage;
	for (i = 0; i < 720; i++)
	{
		if (monthHourToDailyHour(i) == 1 && waterUsage[i] != 0)
		{
			usage = waterUsage[i];

			if (waterUsage[i + 1] == usage && waterUsage[i + 2] == usage && waterUsage[i + 3] == usage)
				return monthHourToDay(i);
		}
	}

	return 0;
}

void writeBuildingReport(double apartment1Usage[], double apartment2Usage[], double apartment3Usage[], ApartmentData apartment1Data, ApartmentData apartment2Data, ApartmentData apartment3Data, char *filename)
{
	char ownerName[30];
	char ownerSurname[30];

	FILE* file;
	file = fopen(filename, "w");

	if (file != NULL)
	{
		double use1 = getTotalWaterUsage(apartment1Usage);
		double largest = use1;
		strcpy(ownerName, apartment1Data.ownerName);
		strcpy(ownerSurname, apartment1Data.ownerSurname);

		double use2 = getTotalWaterUsage(apartment2Usage);
		if (use2 > use1)
		{
			largest = use2;
			strcpy(ownerName, apartment2Data.ownerName);
			strcpy(ownerSurname, apartment2Data.ownerSurname);
		}

		double use3 = getTotalWaterUsage(apartment3Usage);
		if (use3 > use2)
		{
			largest = use3;
			strcpy(ownerName, apartment3Data.ownerName);
			strcpy(ownerSurname, apartment3Data.ownerSurname);
		}

		double totalUse = use1 + use2 + use3;
		double totalBill = getTotalBill(apartment1Usage, apartment1Data.tariff) + getTotalBill(apartment2Usage, apartment2Data.tariff) + getTotalBill(apartment3Usage, apartment3Data.tariff);

		fprintf(file, "Total usage: %.3lf kL\nTotal bill: R%.2lf\nMost usage: %s %s (%.3lf kL)", totalUse, totalBill, ownerName, ownerSurname, largest);

		printf("File saved as %s", filename);
	}
	else printf("File saving unsuccessful");

	fclose(file);
}

void saveCompactUsage(double usage[], int apartment)
{
	FILE* file;
	char filename[20];

	sprintf(filename, "compact_usage_%d.bin", apartment);
	file = fopen(filename, "wb");

	if (file != NULL)
	{
		int i;
		for (i = 0; i < 720; i++)
		{
			if (usage[i] != 0)
			{
				fwrite(&i, sizeof(int), 1, file);
				fwrite(&usage[i], sizeof(double), 1, file);
			}
		}

		printf("File saved as %s", filename);
	}
	else printf("File saving unsuccessful");

	fclose(file);
}

void readCompactUsage(int apartment)
{
	FILE* file;
	char filename[20];

	int hour;
	double usageSingle, pseudoUsage[720] = {0};

	sprintf(filename, "compact_usage_%d.bin", apartment);
	file = fopen(filename, "rb");

	if (file != NULL)
	{
		while (!feof(file))
		{
			fread(&hour, sizeof(int), 1, file);
			fread(&usageSingle, sizeof(double), 1, file);

			pseudoUsage[hour] = usageSingle;
		}

		printWaterUsageReport(pseudoUsage);
	}
	else printf("Binary file has not been created yet.");

	fclose(file);
}

void addNode(ListNodePtr *startPtrPtr, int monthHour, double usage)
{
	if ((*startPtrPtr) == NULL)
	{
		ListNodePtr newPtr = malloc(sizeof(ListNode));

		newPtr->monthHour = monthHour;
		newPtr->usage = usage;
		newPtr->nextPtr = NULL;

		(*startPtrPtr) = newPtr;
	}
	else
	{
		ListNodePtr current = *startPtrPtr;
		while (current->nextPtr != NULL) current = current->nextPtr;

		ListNodePtr newPtr = malloc(sizeof(ListNode));

		newPtr->monthHour = monthHour;
		newPtr->usage = usage;
		newPtr->nextPtr = NULL;

		current->nextPtr = newPtr;
	}
}

void printList(ListNodePtr startPtr)
{
	ListNodePtr current = startPtr;
	while (current->nextPtr != NULL)
	{
		printf("%d - %.3lf\n", current->monthHour, current->usage);
		current = current->nextPtr;
	}
}

void populateList(ListNodePtr* startPtrPtr, double usages[])
{
	int i;
	for (i = 0; i < 720; i++) if (usages[i] != 0) addNode(startPtrPtr, i, usages[i]);
}

int monthHourOfMaxUsage(ListNodePtr startPtr)
{
	ListNodePtr current = startPtr;
	ListNodePtr max = startPtr;

	while (current->nextPtr != NULL)
	{
		if (current->usage > max->usage) max = current;
		current = current->nextPtr;
	}

	return max->monthHour;
}
