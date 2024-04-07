/*
 * ManageJerries.c
 *
 *  Created on: 30 Nov 2022
 *      Author: ido
 */
#include "Jerry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void PrintAllJerries(Jerry ** , int);
void destroy_planetArr(Planet **, int);
void destroy_JerrisArr( Jerry ** , int);
void exit_program( Planet **,int , Jerry ** ,int);
bool FindByid(Jerry**,int ,char* );
bool findPanetByName(Planet**,int ,char*);
void ConvertToCapital(char*);

int main(int argc, char* argumen[])
{
	//read the received arguments
	int numOfPlanets = atoi(argumen[1]);
	int numOfJerries = atoi(argumen[2]);

	//open the file and read it , we can assume the file is exist
	FILE *confiFile = fopen(argumen[3], "r");

	Planet *Planet_arr[numOfPlanets];
	Jerry *jerry_arr[numOfJerries];

	char buffer[MAX_LENGTH_BUFFER];
	//read the first line
	fgets(buffer, sizeof(buffer), confiFile);
	for(int i =0; i< numOfPlanets; i++)
	{
		fgets(buffer, sizeof(buffer), confiFile);//read all the planets
		char *split1 = strtok(buffer, ",");//split every line to parameters
		double split2 = atof(strtok(NULL, ","));
		double split3 = atof(strtok(NULL, ","));
		double split4 = atof(strtok(NULL, "\n"));//finish line
		Planet_arr[i] = initPlanet(split1, split2, split3, split4);//create new planet////

		if(Planet_arr[i] == NULL)
		{
			exit_program(Planet_arr, numOfPlanets, jerry_arr, numOfJerries);
			exit(1);
		}
	}

	fgets(buffer, sizeof(buffer), confiFile);//read the jerries headline
	int j =0;
	while(fgets(buffer, sizeof(buffer), confiFile) != NULL)
	{

		if(buffer[0] != '\t')//new jerry
		{
			char* id = strtok(buffer, ",");
			char* org_name = strtok(NULL, ",");
			char* planet_name = strtok(NULL, ",");
			int happy = atof(strtok(NULL, "\n"));

			Planet* plane_curr;
			for(int i =0; i < numOfPlanets; i++)
			{
				if(strcmp(Planet_arr[i]->name, planet_name)==0)
				{
					plane_curr = Planet_arr[i];
					break;
				}
			}
			Origin* org_curr = initOrigion(plane_curr, org_name);//create the correct pointer for each origin
			jerry_arr[j] = initJerry(id, happy, org_curr, NULL, 0);
			if(jerry_arr[j] == NULL)
			{
				exit_program(Planet_arr, numOfPlanets, jerry_arr, numOfJerries);
				exit(1);
			}
			j++;//number of jerries
		}
		else
		{
			char* physic_name = strtok(buffer, ":");
			physic_name++;
			float physic_value = atof(strtok(NULL, "\n"));//finish line
			PhysicalCh* Physical_curr = initPhtsical(physic_name, physic_value);

			status ph = addPhysical(jerry_arr[j-1], Physical_curr);
			if(ph == noMemory)
			{
				exit_program(Planet_arr, numOfPlanets, jerry_arr, numOfJerries);
				exit(1);
			}
		}
	}
	fclose(confiFile);



	int ch =1;

	while( true ) {
		printf("AW JEEZ RICK, what do you want to do now ? \n");
		printf("1 : Print all Jerries \n");
		printf("2 : Print all Planets \n");
		printf("3 : Add physical characteristic to Jerry \n");
		printf("4 : Remove physical characteristic from Jerry \n");
		printf("5 : Print Jerries by a planet \n");
		printf("6 : Print Jerries by a physical characteristic \n");
		printf("7 : Go home \n");
		scanf("%s", buffer);
		ch = atoi(buffer);
		switch(ch)
		{
		case 1:  /* print all the jerries */
		{
			PrintAllJerries(jerry_arr, numOfJerries);
			break;
		}

		case 2:  /* print all the planets */
		{
			for(int i = 0; i < numOfPlanets; i++)
				PrintPlanet(Planet_arr[i]);
			break;
		}

		case 3:  /* add physical character*/
		{
			char jerry_id[MAX_LENGTH_BUFFER];
			printf("What is your Jerry's ID ? \n");
			scanf("%s", jerry_id);
			if( FindByid(jerry_arr,numOfJerries,jerry_id)==false)
			{
				printf("OH NO! I CAN'T FIND HIM RICK ! \n");
				break;
			}
			else
			{
				char physic_name[MAX_LENGTH_BUFFER];
				printf("What physical characteristic can you add to Jerry - %s ? \n",jerry_id);
				scanf("%s", physic_name);
				int k =0;
				for(; k<numOfJerries;k++)
				{
					if(strcmp(jerry_arr[k]->id, jerry_id)==0)
						break;
				}
				if(isPhysicexsist(jerry_arr[k],physic_name)==true)
				{
					ConvertToCapital(physic_name);
					printf("RICK I ALREADY KNOW HIS %s ! \n", physic_name);
					break;
				}

				else
				{
					float value_curr;
					printf("What is the value of his %s ? \n", physic_name);
					scanf("%f", &value_curr);
					PhysicalCh* new_physic = initPhtsical(physic_name, value_curr);
					if(new_physic == NULL)
					{
						exit_program(Planet_arr, numOfPlanets, jerry_arr, numOfJerries);
						exit(1);
					}
					else
					{
						status new_ph = addPhysical(jerry_arr[k],new_physic);
						if(new_ph == noMemory || jerry_arr[k] == NULL)
						{
							exit_program(Planet_arr, numOfPlanets, jerry_arr, numOfJerries);
							exit(1);
						}
						else
						{
							PrintJerry(jerry_arr[k]);
							break;
						}
					}
				}
			}
			break;
		}



		case 4:  /* remove physical character */
		{
			char jerry_id[MAX_LENGTH_BUFFER];
			printf("What is your Jerry's ID ? \n");
			scanf("%s", jerry_id);
			if(FindByid(jerry_arr,numOfJerries,jerry_id)==false)
			{
				printf("OH NO! I CAN'T FIND HIM RICK ! \n");
				break;
			}
			else
			{
				char physic_name[MAX_LENGTH_BUFFER];
				printf("What physical characteristic do you want to remove from Jerry - %s ? \n",jerry_id);
				scanf("%s", physic_name);

				int k =0;
				for(; k<numOfJerries;k++)
				{
					if(strcmp(jerry_arr[k]->id, jerry_id)==0)
						break;
				}
				if(isPhysicexsist(jerry_arr[k],physic_name)==false)
				{
					ConvertToCapital(physic_name);
					printf("RICK I DON'T KNOW HIS %s ! \n", physic_name);
					break;
				}
				else
				{
					DeletePhysical(jerry_arr[k], physic_name);
					PrintJerry(jerry_arr[k]);
				}
			}

			break;
		}
		case 5: //print jerries by planet
		{
			char planet_name[MAX_LENGTH_BUFFER];
			printf("What planet is your Jerry from ? \n");
			scanf("%s", planet_name);
			bool find = findPanetByName(Planet_arr, numOfPlanets,planet_name);
			if(find == false)
			{
				ConvertToCapital(planet_name);
				printf("RICK I NEVER HEARD ABOUT %s ! \n", planet_name);
				break;
			}
			else
			{
				int count_jerr = 0;
				for(int j= 0; j < numOfJerries; j++)
				{
					if(strcmp(jerry_arr[j]->orig->org_planet->name, planet_name)== 0)
					{
						PrintJerry(jerry_arr[j]);
						count_jerr++;
					}
				}
				if(count_jerr==0)
				{
					ConvertToCapital(planet_name);
					printf("OH NO! I DON'T KNOW ANY JERRIES FROM %s ! \n", planet_name);
				}
			}

			break;
		}

		case 6: //print jerries by physical character
		{
			char physic_name[MAX_LENGTH_BUFFER];
			printf("What do you know about your Jerry ? \n");
			scanf("%s", physic_name);
			int count_jerr=0;
			for(int j =0; j<numOfJerries; j++)
			{
				if(isPhysicexsist(jerry_arr[j], physic_name)== true)
				{
					PrintJerry(jerry_arr[j]);
					count_jerr++;
				}
			}
			if(count_jerr==0)
			{
				ConvertToCapital(physic_name);
				printf("OH NO! I DON'T KNOW ANY JERRY'S %s ! \n", physic_name);
			}
			break;
		}

		case 7: // delete everything
		{
			printf("AW JEEZ RICK, ALL THE JERRIES GOT FREE ! \n");
			exit_program(Planet_arr, numOfPlanets, jerry_arr, numOfJerries);
			exit(0);
		}

		default:
		{
			printf("RICK WE DON'T HAVE TIME FOR YOUR GAMES ! \n");
			break;
		}


		}
	}
	return 0;
}


/* Input: Jerry** jerr_arr to print
 *print all the jerries in the arr
 * */
void PrintAllJerries(Jerry ** jerr_arr, int size_Arr)
{
	for(int i = 0; i<size_Arr;i++)
		PrintJerry(jerr_arr[i]);
}
/* Input: planet** plane, int size
 *delete all the planet in the planet arr
 * */
void destroy_planetArr(Planet **plane, int Size)
{
	for(int i =0; i<Size; i++)
		Destroy_planet(plane[i]);
}

/* Input: Jerry** jerr, int size
 *delete all the jerries in the jerr arr
 * */
void destroy_JerrisArr( Jerry ** jerr, int size)
{
	for(int i =0; i<size; i++)
		Destroy_jerry(jerr[i]);

}
/* Input: Jerry** jerr, int sizej, planet** plane, int sizep
 *delete everything from the program in case of no memory or select 7 menu
 * */
void exit_program( Planet **plane, int Sizep, Jerry ** jerr, int sizej)
{
	destroy_JerrisArr(jerr, sizej);
	destroy_planetArr(plane, Sizep);

}
/* Input: Jerry** jerr, int sizej, char* id
 *return bool object if jerr exist in the arr of jerries
 * */
bool FindByid(Jerry** jer_arr, int size,char* id)
{
	for(int i =0; i<size; i++)
	{
		if(strcmp(jer_arr[i]->id,id)==0)
			return true;
	}
	return false;
}
/* Input: planet** plan_arr, int size, char* name
 *return bool object if planet exist in the arr of planets
 * */
bool findPanetByName(Planet** plan_arr, int size, char* name)
{
	for(int i =0; i<size; i++)
	{
		if(strcmp(plan_arr[i]->name,name)==0)
			return true;
	}
	return false;
}
/* Input: char* str
 *return the str with upper case
 * */
void ConvertToCapital(char* str)
{
	for(int i=0; i < strlen(str); i++)
	{
		if(str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
	}
}


