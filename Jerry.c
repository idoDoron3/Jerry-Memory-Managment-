
#include "Jerry.h"
#include <string.h>
#include <stdlib.h>

/* Input: char* name, double x, double y, double z
 * return: new uniqe planet
 * */
Planet* initPlanet( char* uniqe, double x, double y,double z)
{
	if(uniqe ==NULL || x<0 || y<0 || z<0)
		return NULL;

	Planet *newPlan = (Planet *)malloc(sizeof(Planet));
	if( newPlan == NULL)
	{
		printf("Memory Problem");
		free(newPlan);
		return NULL;
	}
	newPlan->name = (char *)malloc(strlen(uniqe)+1);
	strcpy(newPlan->name,uniqe);
	if(newPlan->name==NULL)
	{
		free(newPlan->name);
		free(newPlan);
		printf("Memory Problem");
		return NULL;
	}
	newPlan->x = x;
	newPlan->y =y;
	newPlan->z =z;

	return newPlan;
}
/* Input: planet* plane to delete
 *
 * */
void Destroy_planet(Planet* plane)
{
	free(plane->name);
	free(plane);
}
/* Input: char* name, planet*plae
 * return: new origin object
 * */
Origin* initOrigion( Planet* plane, char* name)
{

	if(plane == NULL || name == NULL)
		return NULL;

	Origin *newOrg = (Origin *)malloc(sizeof(Origin));
	if( newOrg == NULL)
	{
		printf("Memory Problem");
		free(newOrg);
		return NULL;
	}
	newOrg->org_planet = plane;
	if(newOrg->org_planet == NULL)
	{
		printf("Memory Problem");
		free(newOrg);
		return NULL;
	}
	newOrg->name = (char*)malloc(strlen(name)+1);
	strcpy(newOrg->name,name);;
	if(newOrg->name==NULL)
	{
		printf("Memory Problem");
		free(newOrg);
		return NULL;
	}
	return newOrg;
}
/* Input: origin* orig to delete
 *
 * */
void Destroy_origin(Origin* orig)
{
	free(orig->name);
	orig->org_planet = NULL;
	free(orig);
}

/* Input: char* id, int happy, origin*, Physical** capaci, int counter
 * return: new jerry object
 * */
Jerry* initJerry( char* id, int happines, Origin* org, PhysicalCh** capaci, int count_Physic)//initial jerry
{
	if(id == NULL || happines < 0 || org->org_planet == NULL || org->name == NULL)
		return NULL;
	Jerry *newJerr = (Jerry *)malloc(sizeof(Jerry));
	if(newJerr == NULL)
	{
		printf("Memory Problem");
		return NULL;
	}
	newJerr->id = (char *)malloc(strlen(id)+1);
	strcpy(newJerr->id, id);
	if(newJerr->id==NULL)
	{
		free(newJerr);
		printf("Memory Problem");
		return NULL;
	}
	newJerr->happiness = happines;

	newJerr->orig = org;
	if(newJerr == NULL)
	{
		free(newJerr->id);
		free(newJerr);
	}
	newJerr->capabale = NULL;
	newJerr->counter = count_Physic;

	return newJerr;
}

/* Input: char* name, double value
 * return: new character
 * */
PhysicalCh* initPhtsical( char* character, float value)
{
	if(character == NULL || value < 0)
		return NULL;
	PhysicalCh *newPhys = (PhysicalCh*)malloc(sizeof(PhysicalCh));
	if( newPhys == NULL)
	{
		printf("Memory Problem");
		return NULL;
	}
	newPhys->name = (char*)malloc(strlen(character)+1);
	strcpy(newPhys->name, character);
	if(newPhys->name == NULL)
	{
		printf("Memory Problem");
		free(newPhys);
		return NULL;
	}
	newPhys->value = value;

	return newPhys;
}
/* Input: physicalch* character to delete
 *
 * */
void Destroy_character(PhysicalCh* character1)
{
	free(character1->name);
	free(character1);
}

/* Input: Jerry* jerr1, char* name of character
 * return: bool type if the character exist
 * */
bool isPhysicexsist(Jerry* jerr1, char* character)
{
	if(jerr1->counter == 0)
		return false;
	else
	{
		for(int i =0; i < jerr1->counter; i++)
		{
			if(strcmp(jerr1->capabale[i]->name, character) == 0)
			{
				return true;
				break;
			}
		}
	}
	return false;
}

/* Input: Jerry* jerr1, char* name of character
 * return: status type if the adding succeed or failure
 * */
status addPhysical(Jerry* jerr1, PhysicalCh* character)
{
	if(jerr1->capabale == NULL)
	{
		jerr1->capabale = (PhysicalCh**)malloc(sizeof(PhysicalCh*));
		if(jerr1->capabale == NULL)
		{
			printf("Memory Problem");
			return failure;
		}
		jerr1->capabale[jerr1->counter]= character;
		jerr1->counter++;
		return success;
	}
	else
	{

		jerr1->capabale = (PhysicalCh**)realloc(jerr1->capabale,(jerr1->counter+1)*sizeof(PhysicalCh*));//new allocation +1 place
		if(jerr1->capabale == NULL)
		{
			Destroy_jerry(jerr1);
			printf("Memory Problem");
			return failure;
		}
		else
		{
			jerr1->capabale[jerr1->counter] = character;
			jerr1->counter = jerr1->counter+1;//add to counter
			return success;
		}
	}

}
/* Input: Jerry* jerr1, char* name of character
 * return: status type if the delete succeed or failure
 * */
status DeletePhysical(Jerry* jerr1, char* name)
{
	if(isPhysicexsist(jerr1, name)== false)
		return failure;
	if(jerr1->counter ==1 )
	{
		Destroy_character(jerr1->capabale[0]);
		jerr1->counter=0;
		return success;
	}
	int location = 0;
	for(; location < jerr1->counter; location++)
	{
		if( strcmp(jerr1->capabale[location]->name, name)==0)
			break;
	}
	PhysicalCh* delete = jerr1->capabale[location];
	if(location == jerr1->counter-1)
	{
		Destroy_character(jerr1->capabale[jerr1->counter-1]);
		jerr1->capabale = (PhysicalCh**)realloc(jerr1->capabale,(jerr1->counter-1)*sizeof(PhysicalCh*));//new allocation -1 place
		jerr1->counter = jerr1->counter-1;//reduce the counter
		return success;
	}
	else
	{
		for(; location < jerr1->counter-1; location++)
			{
				jerr1->capabale[location]=jerr1->capabale[location+1];
			}
			Destroy_character(delete);
			jerr1->capabale = (PhysicalCh**)realloc(jerr1->capabale,(jerr1->counter-1)*sizeof(PhysicalCh*));//new allocation -1 place
			jerr1->counter = jerr1->counter-1;//reduce the counter

			return success;
	}


}
/* Input: Jerry* jerr1 to print
 *print jerry
 * */
void PrintJerry(Jerry* jerr1)
{
	if(jerr1 == NULL)
		return;
	else
	{
		printf("Jerry , ID - %s : \n", jerr1->id);
		printf("Happiness level : %d \n", jerr1->happiness);
		printf("Origin : %s \n", jerr1->orig->name);
		PrintPlanet(jerr1->orig->org_planet);
		PrintPhysical(jerr1);
	}
}
/* Input: Jerry* jerr1 to delete
 *
 * */

void Destroy_jerry(Jerry* jerr1)
{
	free(jerr1->id);
	Destroy_origin(jerr1->orig);
	for( int i=0; i < jerr1->counter; i++)
		Destroy_character(jerr1->capabale[i]);
	free(jerr1->capabale);
	free(jerr1);
}

/* Input: Jerry* jerr1 print all of his characters
 *
 * */
void PrintPhysical(Jerry* jerr1)//assist function to print jerry
{
	if(jerr1 == NULL)
		return;
	if(jerr1->counter ==0)
		return;
	if(jerr1->counter==1)
	{
		printf("Jerry's physical Characteristics available : \n");
		printf("\t%s : %.2f \n",jerr1->capabale[0]->name, jerr1->capabale[0]->value);
	}
	else
	{
		printf("Jerry's physical Characteristics available : \n");
		printf("\t%s : %.2f , ",jerr1->capabale[0]->name, jerr1->capabale[0]->value);
		for(int i =1; i < jerr1->counter-1;i++)
		{
			printf("%s : %.2f , ",jerr1->capabale[i]->name, jerr1->capabale[i]->value);
		}
		printf("%s : %.2f \n",jerr1->capabale[jerr1->counter-1]->name, jerr1->capabale[jerr1->counter-1]->value);
	}
}

/* Input: planet* plane to print
 *
 * */
void PrintPlanet(Planet* plane)
{
	printf("Planet : %s (%.2f,%.2f,%.2f) \n", plane->name, plane->x, plane->y, plane->z);
}

