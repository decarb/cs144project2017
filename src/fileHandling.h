/*
 * fileHandling.h
 *
 *  Created on: 29 Aug 2017
 *      Author: Luke Skywalker
 */

#ifndef FILEHANDLING_H_
#define FILEHANDLING_H_

void readMetadataFromFile(ApartmentData *data1, ApartmentData *data2, ApartmentData *data3);
void readUsageFromFile(double usage1[], double usage2[], double usage3[]);
void writeBuildingReport(double apartment1Usage[], double apartment2Usage[], double apartment3Usage[], ApartmentData apartment1Data, ApartmentData apartment2Data, ApartmentData apartment3Data, char *filename);
void saveCompactUsage(double usage[], int apartment);

#endif /* FILEHANDLING_H_ */
