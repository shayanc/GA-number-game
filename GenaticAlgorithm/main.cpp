#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define RANDOM_NUM		((float)rand()/(RAND_MAX+1))

#define CROSSOVER_RATE            0.7
#define MUTATION_RATE             0.001
#define POP_SIZE                  100			//must be an even number
#define CHROMO_LENGTH             300
#define GENE_LENGTH               4
#define MAX_ALLOWABLE_GENERATIONS	400

//data structure for chromosones 
struct chromo_type {
	string bits;
	float fitness;
	chromo_type(): bits(""), fitness(0.0f) {};
	chromo_type(string bts, float ftns): bits(bts), fitness(ftns) {};
};

#include "functions.h"



int main() {
	//seed random number generator
	srand((int) time(NULL));

	cout << RANDOM_NUM << endl;
	
	
	cout << BinToDec("1") << endl;
	system("pause");
	return 0;
}

