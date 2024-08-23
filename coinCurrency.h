#ifndef COINCURRENCY_H
#define COINCURRENCY_H

typedef struct individual{
	char* name;
	int amount;
	char* currency;
}individual;

typedef struct numCoin{
	int coin1;
	int coin2;
	int coin3;
	int coin4;
}numCoin;


individual* ReadData (FILE* file, int size, int* numLines);

void SetCoinValues (int currency, int currency1_coin1, int currency1_coin2, int currency1_coin3, int currency1_coin4, 
								  int currency2_coin1, int currency2_coin2, int currency2_coin3, int currency2_coin4, 
								  int currency3_coin1, int currency3_coin2, int currency3_coin3, int currency3_coin4,
					int* coin1, int* coin2, int* coin3, int* coin4);
					
void ReturnCoins (int amount_money, int coin1, int coin2, int coin3, int coin4,
					int* num_coin1, int* num_coin2, int* num_coin3, int* num_coin4);			
					
numCoin* ComputeChange (individual* arrayStruct, int numIndividuals,
					int currency1_coin1, int currency1_coin2, int currency1_coin3, int currency1_coin4, 
					int currency2_coin1, int currency2_coin2, int currency2_coin3, int currency2_coin4, 
					int currency3_coin1, int currency3_coin2, int currency3_coin3, int currency3_coin4);
																	
					
int ContinueExit ();
				
void GetName (char* name, int size);

int FindNumMatches (individual* arrayStruct, char* name, int numIndividuals);
	
int* SearchData (individual* arrayStruct, char* name, int numIndividuals, int* numMatches);



void DisplayResult (individual* arrayStruct, numCoin* arrayStruct2, int numMatches, char* name, int* array,
					int currency1_coin1, int currency1_coin2, int currency1_coin3, int currency1_coin4, 
					int currency2_coin1, int currency2_coin2, int currency2_coin3, int currency2_coin4, 
					int currency3_coin1, int currency3_coin2, int currency3_coin3, int currency3_coin4);
					
void WriteData(FILE* file, individual* arrayStruct, numCoin* arrayStruct2, int numIndividuals);		

#endif			
