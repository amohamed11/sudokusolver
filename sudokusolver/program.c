#include <stdio.h>
#include <stdbool.h>

const int size=9;

void file_opener(char* filename, int grid[size][size]){
	FILE* fp;
	int num, row, col;

	fp = fopen(filename,"r");

	for (row=0; row<size; row++){
		for (col=0; col<size; col++){
			fscanf(fp,"%1d", &num);
			/*fscanf(fp, "%*[^\n]");	*/
			grid[row][col] = num;
		}
	}

}


bool rowchecker(int sol, int row, int grid[size][size]){
	int i;

	for (i=0; i<size; i++){
		if (grid[row][i]==sol)
			return false;
	}
	return true;

}

bool colchecker(int sol, int col, int grid[size][size]){
	int i;

	for (i=0; i<size; i++){
		if (grid[i][col]==sol)
			return false;
	}
	return true;

}

bool boxchecker(int sol, int startrow, int startcol, int grid[size][size]){
	int i,j;
	startrow = startrow - (startrow%3);
	startcol = startcol - (startcol%3);
	for (i=0; i<3; i++){
		for (j=0; j<3; j++){
			if (grid[i+startrow][j+startcol]==sol)
				return false;
		}
	}
	return true;

}

bool totalchecker(int sol, int row, int col, int grid[size][size]){
	if (colchecker(sol, col, grid) && rowchecker(sol, row, grid) && boxchecker(sol, row, col, grid)){
		return true;
	}else {return false;}

}

void printsolution(int grid[size][size]){
	int row, col;

	for (row=0; row<size; row++){
		for (col=0; col<size; col++){
			printf("%d ", grid[row][col]);
		}
		printf("\n");
	}
}

bool cellfinder(int *row, int *col, int grid[size][size]){
	for (*row=0; *row<size; (*row)++){
		for (*col=0; *col<size; (*col)++){
			if (grid[*row][*col] == 0)
				return true;
		}
	}
	return false;

}

bool solver(int grid[size][size]){
	int sol, row, col;

	if (cellfinder(&row,&col,grid)==false){
		return true;
	}
	if (row>=size && col>=size)
		return true;
	/*printf("%d\n", counter);
	counter++;*/
	for (sol=1; sol<=9; sol++){
		if (totalchecker(sol, row, col, grid)){
			grid[row][col] = sol;
			if (solver(grid)){
				return true;
			}
			grid[row][col] = 0;
		}

	}

	return false;
}

/* Has a small chance of solving sudoku, and world peace
   But only one at a time unfortunately*/

int main(int argc, char *argv[]){
	int grid[size][size];

	file_opener(argv[1], grid);
	solver(grid);
	printsolution(grid);

	return 0;
}
