#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char** initializeMatrix(char **matrix, int row, int column){
	int i;
	matrix = (char **)malloc(sizeof(char*) * row);
	for(i = 0; i<row; ++i){
		matrix[i] = (char *)malloc(sizeof(char) * column);
	}
	return matrix;
}

int** initializeBoard(int **board, int row, int column){
	int i;
	board = (int **)malloc(sizeof(int*) * row);
	for(i = 0; i<row; ++i){
		board[i] = (int *)malloc(sizeof(int) * column);
	}
	return board;
}

void matrixToBoard(char **matrix, int **board, int row, int column, int *startX, int *startY){
	int i,j;
	for(i = 0; i < row; ++i){
		for(j = 0; j < column; ++j){
			if(matrix[i][j] == '+' || matrix[i][j] == '|' || matrix[i][j] == '-')
				board[i][j] = 0;
			else if(matrix[i][j] == 'b' || matrix[i][j] == 'c' || matrix[i][j] == 'O'){
				board[i][j] = matrix[i][j];
				if(matrix[i][j] == 'b'){
					*startX = i;
					*startY = j;
				}
			}		
			else
				board[i][j] = 1;
		}
	}
}

void readFile(char *fileName, char **matrix, int row, int column){
	FILE *file;
	int i, j;
	char character;
	if( (file = fopen(fileName, "r")) != NULL){
		
		for(i=0; i<row; ++i){
			fgets(matrix[i], column + 1, file);
			fscanf(file, "%c", &character);
		}
	}
	else
		printf("Dosya Acilamadi!");
}

void delay(){
	int i,j;
	for(i = 0; i<1000000; ++i){
		for(j = 0; j<200; ++j){
			
		}
	}
}

void displayBoard(char **matrix, int **control, int row, int column, int score){
	int i,j;
	int static round = 0;
	system("cls");
	printf("Score: %d\n\n",score);
	for(i = 0; i<row; ++i){
		for(j = 0; j<column; ++j){
			if(control[i][j] == 0 || matrix[i][j] == 'b' || matrix[i][j] == 'c' || i % 2 == 0 || j % 2 == 0)
				printf("%c",matrix[i][j]);
			else
				printf("*");
		}
		printf("\n");
	}
	printf("\n");
}

void randomApples(char **matrix, int row, int column, int numberOfApples){
	int i, x, y;
	for(i = 0; i<numberOfApples; ++i){
		do{
			x = rand() % row;
			y = rand() % column;
		}while(x % 2 == 0 || y % 2 == 0 || matrix[x][y] == 'b' || matrix[x][y] == 'c');
		matrix[x][y] = 'O';
	}
}

int dfs(int x, int y, int **board, int **control, char **matrix, int row, int column, int *score){
	int dx[4] = {-1, 0, +1, 0};
	int dy[4] = {0, -1, 0, +1};
	int i;
	int finish;
	int count;
	
	if(board[x][y] == 'O'){
		matrix[x][y] = ' ';
		printf("An Apple Found! +10 Points!\n");
		(*score) += 10;
		printf("Press Any Key\n");
		getch();
	}
		
	
	if(x < 0 || x == row)
		return 0;
	if(y < 0 || y == column)
		return 0;
			
	if(board[x][y] == 99){           //Cikis
		return 1;
	}
		
	if(board[x][y] == 0){
		return 0;
	}
	
	if(x % 2 == 1 && y % 2 == 1)
		displayBoard(matrix, control, row, column, *score);
	delay();
	
	finish = 0;
	i = 0;
	count = 0;
	while(i<4 && finish == 0){
		if(board[x + dx[i] ][y + dy[i]] != 0 && control[ x + dx[i] ][ y + dy[i] ] == 0){
			control[ x + dx[i] ][ y + dy[i] ] = 1;
			finish = dfs(x + dx[i], y + dy[i], board, control, matrix, row, column, score);
			if(finish == 0){
				control[ x + dx[i] ][ y + dy[i] ] = 0;
			}
				
		}
		if(board[x + dx[i] ][y + dy[i]] == 0)
			count++;
		i++;
	}
	if(finish == 1)
		return 1;
	else{
		if(count == 3){
			printf("Hit the Wall! -5 Points\n");
			*score -= 5;
			printf("Press Any Key\n");
			getch();
		}			
		return 0;
	}		
}


int main(){
	
	char **matrix;
	int **board;
	int **control;
	char fileName[20] = {"maze.txt"};
	int finish;
	int score;
	int row, column, startX, startY;
	int i, j;
	int dx[4] = {-1, 0, +1, 0};
	int dy[4] = {0, -1, 0, +1};
	
	srand(time(NULL));
	
	printf("Number Of Rows: ");
	scanf("%d",&row);
	
	printf("Number Of Columns: ");
	scanf("%d",&column);
	
	matrix = initializeMatrix(matrix, row, column);
	readFile(fileName, matrix, row, column);
	
	control = (int **)calloc(row, sizeof(int *));
	for(i=0; i<row; ++i){
		control[i] = (int *)calloc(column, sizeof(int));
	} 
	board = initializeBoard(board, row, column);
	randomApples(matrix, row, column, 5);
	matrixToBoard(matrix, board, row, column, &startX, &startY);
	
	displayBoard(matrix, control, row, column, 0);
	printf("Press Any Key To Start\n");
	getch();		
	finish = 0;
	i = 0;
	score = 0;
	control[startX][startY] = 1;
	while(i<4 && finish == 0){
		if(board[startX + dx[i] ][startY + dy[i]] != 0){
			control[ startX + dx[i] ][ startY + dy[i] ] = 1;
			finish = dfs(startX + dx[i], startY + dy[i], board, control, matrix, row, column, &score);
			if(finish == 0)
				control[ startX + dx[i] ][ startY + dy[i] ] = 0;
		}		
		i++;
	}
	displayBoard(matrix, control, row, column, score);
	delay();
	if(finish == 1)
		printf("Cikisa Ulasildi!\nPuaniniz: %d",score);
	else
		printf("Cikis Bulunamadi!");
	return 0;	
}
