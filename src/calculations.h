/*
 * calculations.h
 *
 *  Created on: 29 Aug 2017
 *      Author: Luke Skywalker
 */

#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

double getTotalWaterUsage(double waterUsage[]);
double getTotalBill(double waterUsage[], double tariff);
int checkForLeak(double waterUsage[]);  // returns the day (1 to 30) on which the leak occurs, or 0 if there is no leak

#endif /* CALCULATIONS_H_ */
