#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define NUM_BLOCKS 32
#define NUM_THREADS 512
#define K 50
#define MAX_ITER

using namespace std;

void printS( int S[]){
	int i = 0;
	for (i; i<K-1; i++){
		cout << S[i] << " ";
	}
	cout << S[K-1] << endl;
}	


int diagonalsOK(int q,int i, int S[]){
	int j = 1;
	for (j; j<=i; j++){
		if (S[i-j] == q-j | S[i-j] == q+j){
			return 0;
		} 		
	}	
	return 1;
}

int sum(int row[], int len){
	int i = 0;
	int s = 0;
	for (i; i<len; i++){
		s += row[i];
	}
	return s;
}

void solvePuzzle(int* S, int k){
	// Initialize varaibles
	//int S[k];
	int D[k];
	int N[k][k];
	
	int i = 0;
	int j = 0;

	int q; 
	
	// Set to start values
	for (i; i<k; i++){
		S[i] = -1;
		D[i] = 0;
		for (j;j<k;j++){
			N[i][j] = 0;
		}
		j = 0;
	}

	// Prepare values and rnd num
	i = 0;
	
	int max_iter = 3000;
	// Solve puzzle
	for (int iter=0; iter < max_iter; iter++){
	
		q = rand() % k;
	
		
		if (D[q] == 0 & N[i][q] == 0){ // Row clear and not tried before 
			N[i][q] = 1;
			if (diagonalsOK(q,i,S)==1){
				S[i] = q;
				D[q] = 1;
				i++;
				if (i==k){ // Finished!
					break;
				}
			}
		}
		if (sum(N[i],k) + sum(D,k) == k){
			D[S[i-1]] = 0;
			S[i-1] = -1;
			// Set N[i] = 0;
			j = 0;
			for (j;j<k;j++){
				N[i][j] = 0;
			}		
			i--; // Backtrack
		}
		iter++;
	}
}
int main(){
	int solutions[NUM_BLOCKS*NUM_THREADS][K];
	int num_solutions = NUM_BLOCKS*NUM_THREADS;
	int solution_count = 0;
	srand(time(NULL));
	for (int i = 0; i < num_solutions; i++){
		solvePuzzle(&(solutions[i][0]), K);
		if (solutions[i][K-1] !=-1){
			solution_count++;
		}
		//printS(solutions[i]);
	}
	cout << solution_count << endl;
}
