/*
 * Jerry.h
 *
 *  Created on: 30 Nov 2022
 *      Author: ido
 */

#ifndef JERRY_H_
#define JERRY_H_
#include <stdio.h>
#include "Defs.h"

//definition of planet node
typedef struct Planet_t
{
	char* name;
	double x;
	double y;
	double z;
}Planet;

typedef struct Origin_t
{
	Planet* org_planet;
	char* name;
}Origin;

typedef struct PhysicalCharacteristics_t
{
	char* name;
	float value;
}PhysicalCh;

typedef struct Jerry_t
{
	char* id;
	int happiness;
	Origin* orig;
	PhysicalCh** capabale;
	int counter;

}Jerry;


//functions

Jerry* initJerry( char* , int, Origin*, PhysicalCh**, int);//initial jerry
void Destroy_jerry(Jerry*);
Planet* initPlanet( char*, double, double,double);
void Destroy_planet(Planet*);
PhysicalCh* initPhtsical( char*, float);
void Destroy_character(PhysicalCh*);
Origin* initOrigion( Planet*, char*);
void Destroy_origin(Origin*);
bool isPhysicexsist(Jerry*, char*);//check if physical character exist
status addPhysical(Jerry*, PhysicalCh*);
status DeletePhysical(Jerry*, char*);
void PrintJerry(Jerry*);

void PrintPhysical(Jerry*);//assist function to print jerry
void PrintPlanet(Planet*);

//create delete function to each of the elements


#endif /* JERRY_H_ */
