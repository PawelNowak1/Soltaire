#include "initGame.h"
#include "PegBoard.h"
#include <stdio.h>
#include <stdlib.h>
#define maxSizeOfBoard 1000

void initDimensions(char buffer[], struct Board *board)
{
	char *token;
	char *search = ",";
	token = strtok(buffer, search);
	board->x = atoi(token);

	token = strtok(NULL, search);
	board->y = atoi(token);
}

struct Board initBoard(char name[])
{
	FILE * inFile;
	char buffer[maxSizeOfBoard];
	inFile = fopen(name, "r");

	if (inFile == NULL) perror("Error opening file");
	else
	{
		struct Board board;
		board.lastMove = NULL;
		fgets(buffer, maxSizeOfBoard, inFile);
		initDimensions(buffer, &board);
		board.values = (char *)malloc((board.x) * (board.y) * sizeof(char));

		for (int i = 0; i < board.x; i++)
		{
			fgets(buffer, maxSizeOfBoard, inFile);
			for (int j = 0; j < board.y; j++)
				*(board.values + i*board.y + j) = buffer[j];
		}

		fclose(inFile);
		return board;
	}

}