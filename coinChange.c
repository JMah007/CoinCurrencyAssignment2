#include <stdio.h>
#include <stdlib.h>
#include "coinCurrency.h"

int main(int argc, char* argv[])
{	
	const int MAXSIZE = 50; 
	
	int numIndividuals = 0;
	int numIndividuals2 = 0;
	int numMatches = 0;
	int continue_exit;
	
	char nameToSearch[MAXSIZE];
	int* indexArray = NULL;
	
	individual* individuals = NULL;
	numCoin* numCoins = NULL;
	
	FILE* source_file = NULL;
	FILE* destination_file = NULL;
	
	
	//Declare AU$ coins
	const int AU_COIN1 = 50;
	const int AU_COIN2 = 20;
	const int AU_COIN3 = 10;
	const int AU_COIN4 = 5;
	
	//Declare US$ coins
	const int US_COIN1 = 50;
	const int US_COIN2 = 25;
	const int US_COIN3 = 10;
	const int US_COIN4 = 1;
	
	//Declare Euro coins
	const int EURO_COIN1 = 20;
	const int EURO_COIN2 = 10;
	const int EURO_COIN3 = 5;
	const int EURO_COIN4 = 1;
	
	
	
	//1. Attempt to open file in read mode
	source_file = fopen(argv[1], "r");
	
	if(source_file != NULL){
		printf("File opened successfully\n");
		
	//2. If input file is successfully opened, call function ReadData to read data from source file
	individuals = ReadData (source_file, MAXSIZE, &numIndividuals);
	
	//3.Close the input file
	fclose(source_file);
	
	//4. Call function ComputeChange to calculate change for each currency per name
	numCoins = ComputeChange (individuals, numIndividuals,
					AU_COIN1, AU_COIN2, AU_COIN3, AU_COIN4, 
					US_COIN1, US_COIN2, US_COIN3, US_COIN4, 
					EURO_COIN1, EURO_COIN2, EURO_COIN3, EURO_COIN4);
	
	//5. Call ContinueExit to ask user if they want to continue
	continue_exit = ContinueExit ();
	
	while(continue_exit == 1){
		
		//6. Call GetName. If user chooses to exit, skip to step 10
		GetName (nameToSearch, MAXSIZE);
			
			
		//7. Call function SearchData to see if name exists in data
		indexArray = SearchData(individuals, nameToSearch, numIndividuals, &numMatches);
			
		
		//8. Call function to display results 
		DisplayResult (individuals, numCoins, numMatches, nameToSearch, indexArray,
					   AU_COIN1, AU_COIN2, AU_COIN3, AU_COIN4, 
					   US_COIN1, US_COIN2, US_COIN3, US_COIN4, 
					   EURO_COIN1, EURO_COIN2, EURO_COIN3, EURO_COIN4);
					   
					   
		//9. Call function ContinueExit to update the loop		   
		continue_exit = ContinueExit ();			   
							 }
								
	
	//10. Attempt to open file in write mode
	destination_file = fopen("change.csv", "w");

	//11. Call function WriteData to write all data from input file into the output file
	WriteData(destination_file, individuals, numCoins, numIndividuals);
	
	//12. Close output file
	fclose(destination_file);
	
	
	//Free all arrays
	free(individuals->name);
	free(individuals->currency);
	free(individuals);
	
	free(numCoins);
	free(indexArray);
}


	else{
		printf("Error, file could not be opened for reading\n");
	}
	
return(0);
}