#include <stdio.h>
#include <stdlib.h>

#define N 9

void print(int arr[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%d ",arr[i][j]);
		printf("\n");
	}
}

int isSafe(int grid[N][N], int row,
					int col, int num)
{
	
	for (int x = 0; x <= 8; x++)
		if (grid[row][x] == num)
			return 0;


	for (int x = 0; x <= 8; x++)
		if (grid[x][col] == num)
			return 0;

	int startRow = row - row % 3,
				startCol = col - col % 3;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (grid[i + startRow][j +
						startCol] == num)
				return 0;

	return 1;
}

int solveSudoku(int grid[N][N], int row, int col)
{
	
	if (row == N - 1 && col == N)
		return 1;

	if (col == N)
	{
		row++;
		col = 0;
	}
	if (grid[row][col] > 0)
		return solveSudoku(grid, row, col + 1);

	for (int num = 1; num <= N; num++)
	{
		if (isSafe(grid, row, col, num)==1)
		{
			grid[row][col] = num;
			if (solveSudoku(grid, row, col + 1)==1)
				return 1;
		}
		grid[row][col] = 0;
	}
	return 0;
}

int main()
{
	FILE* ptr;
	char ch;
	int arr[N][N];
	ptr = fopen("sudoku.txt", "r");

	if (NULL == ptr) {
		printf("file can't be opened \n");
	}
	int i = 0;
	int j = 0;
	do {
		ch = fgetc(ptr);
		if (ch == '\n'){
			i++;
			j = 0;
		}
		if (ch != '\n' && ch != ' ' && !(ch-'0' < 0) && (ch - '0') <= 9) {
			arr[i][j] = ch - '0';
			j++;
		}
	} while (ch != EOF);
	fclose(ptr);
	if (solveSudoku(arr, 0, 0)==1)
		print(arr);
	else
		printf("No solution exists");

	return 0;
}
