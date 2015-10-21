#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

//rand returns value between 0 and rand_max
#define RANDOM_NUM		((float)rand()/(RAND_MAX+1)) 


#define CROSSOVER_RATE            0.7
#define MUTATION_RATE             0.001
#define POP_SIZE                  100			//must be an even number
#define CHROMO_LENGTH             200
#define GENE_LENGTH               4
#define MAX_ALLOWABLE_GENERATIONS	300

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
	
	while(true) {
		chromo_type Population[POP_SIZE];
		//get a target number from the user. (no error checking)
		float Target;
		cout << "\nInput a target number: ";
		cin >> Target;
		cout << endl << endl;
		//first create a random population, all with zero fitness.
		for (int i=0; i<POP_SIZE; i++)
		{
			Population[i].bits	  = GetRandomBits(CHROMO_LENGTH);
			Population[i].fitness = 0.0f;
		}
		int GenerationsRequiredToFindASolution = 0;
		//we will set this flag if a solution has been found
		bool bFound = false;
		//enter the main GA loop
		while(!bFound)
		{
			//this is used during roulette wheel sampling
			float TotalFitness = 0.0f;
			// test and update the fitness of every chromosome in the population
			for (int i=0; i<POP_SIZE; i++) {
				Population[i].fitness = AssignFitness(Population[i].bits, Target);
				TotalFitness += Population[i].fitness;
			}
			// check to see if we have found any solutions (fitness will be 999)
			for (int i=0; i<POP_SIZE; i++){
				if (Population[i].fitness == 999.0f){
					cout << "\nSolution found in " << GenerationsRequiredToFindASolution << " generations!" << endl << endl;;
					PrintChromo(Population[i].bits);
					bFound = true;
					break;
				}
			}
			// create a new population by selecting two parents at a time and creating offspring
			// by applying crossover and mutation. Do this until the desired number of offspring
			// have been created. 
			//define some temporary storage for the new population we are about to create
			chromo_type temp[POP_SIZE];
			int cPop = 0;
	  
			//loop until we have created POP_SIZE new chromosomes
			while (cPop < POP_SIZE){
				// we are going to create the new population by grabbing members of the old population
				// two at a time via roulette wheel selection.
				string offspring1 = Roulette(TotalFitness, Population);
				string offspring2 = Roulette(TotalFitness, Population);
				//add crossover dependent on the crossover rate
				Crossover(offspring1, offspring2);
				//now mutate dependent on the mutation rate
				Mutate(offspring1);
				Mutate(offspring2);
				//add these offspring to the new population. (assigning zero as their
				//fitness scores)
				temp[cPop++] = chromo_type(offspring1, 0.0f);
				temp[cPop++] = chromo_type(offspring2, 0.0f);

			}//end loop

			//copy temp population into main population array
			for (int i=0; i<POP_SIZE; i++){
				Population[i] = temp[i];
			}
			++GenerationsRequiredToFindASolution;

			// exit app if no solution found within the maximum allowable number
			// of generations
			if (GenerationsRequiredToFindASolution > MAX_ALLOWABLE_GENERATIONS){
				cout << "No solutions found this run!";
				bFound = true;
			}
		}
		cout << "\n\n\n";
	}//end while



	system("pause");
	return 0;
}

