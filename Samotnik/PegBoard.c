#include "PegBoard.h"
#include "View.h"
#include <stdio.h>
#define maxSize 2000
#define maxPeg 100
#define oneLine 8

void addMove(struct Board *board, int coord1, int coord2)
{
	struct Moves *current = (struct Moves*) malloc(sizeof(struct Moves));
	current->coord1 = coord1;
	current->coord2 = coord2;
	current->next = board->lastMove;
	board->lastMove = current;
}

void undoTheLastMove(struct Board *board)
{
	if (board->lastMove == NULL)
		return;
	char offSquare = '0', peg = '1', avaiableSquare = '2';
	int coord1 = board->lastMove->coord1;
	int coord2 = board->lastMove->coord2;
	*(board->values + coord1) = peg;
	*(board->values + coord2) = avaiableSquare;
	*(board->values + (coord1 + coord2) / 2) = peg;
	struct Moves* toRemove = board->lastMove;
	board->lastMove = board->lastMove->next;
	free(toRemove);
}

void deleteMoves(struct Board *board)
{
	while (board->lastMove != NULL)
	{
		struct Moves *current = board->lastMove;
		board->lastMove = board->lastMove->next;
		free(current);
	}
}

void saveMoves(struct Board *board)
{
	printf("\nCzy chcesz zapisac wykonane ruchy do pliku?");
	printf("\n1. Tak");
	printf("\n2. Nie\n");
	int choice = 0;
	scanf("%d", &choice);

	if (choice != 1)
		return;

	FILE * outFile;
	char buffer[maxSize];
	char name[maxSize];
	printf("\nWpisz nazwe wyjsciowego pliku\n");
	scanf("%s", name);
	outFile = fopen(name, "w");

	if (outFile == NULL) perror("Error opening file");
	else
	{
		char moves[maxPeg][oneLine];
		int i = 0;
		struct Moves *current = board->lastMove;
		while (current != NULL)
		{
			moves[i][0] = current->coord1 % board->x + 'A';
			moves[i][1] = current->coord1 / board->y + '1';
			moves[i][2] = ' ';
			moves[i][3] = '-';
			moves[i][4] = ' ';
			moves[i][5] = current->coord2 % board->x + 'A';
			moves[i][6] = current->coord2 / board->y + '1';
			moves[i][7] = '\0';
			current = current->next;
			i++;
		}
		for (int j = i - 1; j >= 0; j--)
		{
			fprintf(outFile, "%s\n", moves[j]);
		}
	}
	fclose(outFile);
}