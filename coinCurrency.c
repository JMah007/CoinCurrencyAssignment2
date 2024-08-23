#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coinCurrency.h" 


	
individual* ReadData (FILE* file, int size, int* numLines)
{	
	individual* individuals = NULL;
	
	int counter = 0;
	int amount;
	char storage1[size];
	char storage2[size];
	char name[size];
	char currency[size];
	
	
	//Counts number of lines/names
	while (fscanf(file, "%s %d %s %s %s", name, &amount, storage1, storage2, currency) != EOF){
		
		*numLines = *numLines + 1;
																							  }
														
	//Allocate space for individuals
	individuals = (individual*) malloc ((*numLines) * sizeof(individual));
		
	//Position reading pointer at start of file	
	fseek(file, 0, SEEK_SET);
	

	//Stores data into arrays
	while (fscanf(file, "%s %d %s %s %s", name, &amount, storage1, storage2, currency) != EOF){
		
		//Allocate space for individuals.name and individuals.currency
		individuals[counter].name = (char*) malloc (strlen(name) * sizeof(char));
		individuals[counter].currency = (char*) malloc (strlen(currency) * sizeof(char));
		
		strcpy(individuals[counter].name, name);
		individuals[counter].amount = amount;
		strcpy(individuals[counter].currency, currency);
		
		//Checks if any lines have incorrect amount
		if ((individuals[counter].amount < 1) || (individuals[counter].amount > 95)){
			printf("Data file has incorrect value at line %d\n", counter + 1);
		} 
		
		counter = counter + 1;
																							  }
		
return individuals;
}	





numCoin* ComputeChange (individual* arrayStruct, int numIndividuals,
					int currency1_coin1, int currency1_coin2, int currency1_coin3, int currency1_coin4, 
					int currency2_coin1, int currency2_coin2, int currency2_coin3, int currency2_coin4, 
					int currency3_coin1, int currency3_coin2, int currency3_coin3, int currency3_coin4)
					
{			

	int currency;
	int i;
	int coinValue1, coinValue2, coinValue3, coinValue4;
	int num_coin1, num_coin2, num_coin3, num_coin4;
	
	numCoin* numCoins = NULL;
	
	//Dynamic allocation 
	numCoins = (numCoin*) malloc (numIndividuals * sizeof(numCoin));
	
	//Loops for each currency per individual
	for (i=0; i<numIndividuals; i++){
		
		if (strcmp(arrayStruct[i].currency, "AU$") == 0){
			currency = 1;
														}
		else
			if (strcmp(arrayStruct[i].currency, "US$") == 0){
				currency = 2;
															}
			else{
				currency = 3;
				}
				
	//Set the values of the 4 coins depending on what currency what chosen
		SetCoinValues(currency, currency1_coin1, currency1_coin2, currency1_coin3, currency1_coin4, 
					  currency2_coin1, currency2_coin2, currency2_coin3, currency2_coin4, 
					  currency3_coin1, currency3_coin2, currency3_coin3, currency3_coin4,
					  &coinValue1, &coinValue2, &coinValue3, &coinValue4);
		
		
	//Calculates number of each coin
	ReturnCoins(arrayStruct[i].amount, coinValue1, coinValue2, coinValue3, coinValue4,
				&num_coin1, &num_coin2, &num_coin3, &num_coin4);
	
	//Assign number of coins for each coin type
	numCoins[i].coin1 = num_coin1;
	numCoins[i].coin2 = num_coin2;
	numCoins[i].coin3 = num_coin3;
	numCoins[i].coin4 = num_coin4;
										}
																			
return numCoins;
}



void SetCoinValues (int currency, int currency1_coin1, int currency1_coin2, int currency1_coin3, int currency1_coin4, 
								  int currency2_coin1, int currency2_coin2, int currency2_coin3, int currency2_coin4, 
								  int currency3_coin1, int currency3_coin2, int currency3_coin3, int currency3_coin4,
					int* coin1, int* coin2, int* coin3, int* coin4)
{
						
	switch (currency){
		case 1:
		*coin1 = currency1_coin1;
		*coin2 = currency1_coin2;
		*coin3 = currency1_coin3;
		*coin4 = currency1_coin4;
		break;
		case 2:
		*coin1 = currency2_coin1;
		*coin2 = currency2_coin2;
		*coin3 = currency2_coin3;
		*coin4 = currency2_coin4;
		break;
		case 3:
		*coin1 = currency3_coin1;
		*coin2 = currency3_coin2;
		*coin3 = currency3_coin3;
		*coin4 = currency3_coin4;
					 }
						
	return;
}




void ReturnCoins (int amount_money, int coin1, int coin2, int coin3, int coin4,
					int* num_coin1, int* num_coin2, int* num_coin3, int* num_coin4)
{
		
	*num_coin1 = amount_money / (coin1);
	
	*num_coin2 = (amount_money % (coin1)) / (coin2);

	*num_coin3= (amount_money % (coin1) % (coin2)) / (coin3);
	
	*num_coin4 = (amount_money % (coin1) % (coin2) % (coin3)) / (coin4);
	
return;
}
			
					


int ContinueExit ()
{
	int status;
	
	printf("1. Enter a name\n2. Exit\n");
	scanf("%d%*c", &status);
	
	while ((status != 1) && (status != 2)){
		printf("Error, enter either 1 or 2");
		scanf("%d%*c", &status);
										  }
	
return status;
}



void GetName (char* name, int size)
{
	printf("Enter a name to search for: ");
	
	//Get name from user
	if (fgets (name, size, stdin) != NULL){
		name[strlen(name) - 1] = '\0';
										}
										
return;
}




int* SearchData (individual* arrayStruct, char* name, int numIndividuals, int* numMatches)
{
	int* indexArray = NULL;
	int status;
	int i;
	int index = 0;
	
	*numMatches = 0;
	
	//Find how many names match from data so that value can be used for dynamic allocation in the following step
	for (i=0; i<numIndividuals; i++){
	status = strcmp(name, arrayStruct[i].name);			  
				  
	if (status == 0){
		*numMatches = *numMatches + 1;
					}
										}								
										
	
	//Dynamic allocation for array carrying values of number of lines with name that matches user input
	indexArray = (int*) malloc (*numMatches * sizeof(int));
	
	for (i=0; i<numIndividuals; i++){
	status = strcmp(name, arrayStruct[i].name);	
	
	if (status == 0){
		indexArray[index] = i;
		index = index + 1;
					}
									}
		 
return indexArray;
}




void DisplayResult (individual* arrayStruct, numCoin* arrayStruct2, int numMatches, char* name, int* array,
					int currency1_coin1, int currency1_coin2, int currency1_coin3, int currency1_coin4, 
					int currency2_coin1, int currency2_coin2, int currency2_coin3, int currency2_coin4, 
					int currency3_coin1, int currency3_coin2, int currency3_coin3, int currency3_coin4)
{
	int lineNumber; 
	int currency;
	int i;
	int coinValue1, coinValue2, coinValue3, coinValue4;
	
	//If none of the names match then display suitable message
	if (numMatches == 0){
		printf("Name: %s\nNot Found\n\n", name);
						}
	

	else{

	printf("Customer:\n");

	for (i=0; i<numMatches; i++){
		
		lineNumber = array[i];
		
		if (strcmp(arrayStruct[lineNumber].currency, "AU$") == 0){
			currency = 1;
														}
		else
			if (strcmp(arrayStruct[lineNumber].currency, "US$") == 0){
				currency = 2;
															}
			else{
				currency = 3;
				}
	
	
		SetCoinValues (currency, currency1_coin1, currency1_coin2, currency1_coin3, currency1_coin4, 
					  currency2_coin1, currency2_coin2, currency2_coin3, currency2_coin4, 
					  currency3_coin1, currency3_coin2, currency3_coin3, currency3_coin4,
					  &coinValue1, &coinValue2, &coinValue3, &coinValue4);
		
		
		
		printf("%s %d cents in %s\n\n", arrayStruct[lineNumber].name, arrayStruct[lineNumber].amount, arrayStruct[lineNumber].currency);
		printf("Change:\n");
		
		if(arrayStruct2[lineNumber].coin1 > 0){
		printf("%d cents: %d\n\n", coinValue1, arrayStruct2[lineNumber].coin1);
											  }
		
		if(arrayStruct2[lineNumber].coin2 > 0){
		printf("%d cents: %d\n\n", coinValue2, arrayStruct2[lineNumber].coin2);
											  }
		
		if(arrayStruct2[lineNumber].coin3 > 0){
		printf("%d cents: %d\n\n", coinValue3, arrayStruct2[lineNumber].coin3);
											  }
		
		if(arrayStruct2[lineNumber].coin4 > 0){
		printf("%d cents: %d\n\n", coinValue4, arrayStruct2[lineNumber].coin4);
											  }
		
									
									}
		}
return;
}



void WriteData(FILE* file, individual* arrayStruct, numCoin* arrayStruct2, int numIndividuals)
{
	int i;
	
	for (i=0; i<numIndividuals; i++){
		fprintf(file, "%s, the change for %d cents in %s is %d, %d, %d, %d\n", arrayStruct[i].name, arrayStruct[i].amount, arrayStruct[i].currency, arrayStruct2[i].coin1, arrayStruct2[i].coin2, arrayStruct2[i].coin3, arrayStruct2[i].coin4);
	}
return;
}