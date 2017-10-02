/*
 * apartments.h
 *
 *  Created on: 17 Aug 2017
 *      Author: Luke Skywalker
 */

#ifndef APARTMENTS_H_
#define APARTMENTS_H_

struct apartmentData
{
	char ownerName[30];
	char ownerSurname[30];
	double tariff;
};
typedef struct apartmentData ApartmentData;

#endif /* APARTMENTS_H_ */
