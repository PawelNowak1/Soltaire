#include "gameLogic.h"
#include "PegBoard.h"
#include "View.h"
#include <stdio.h>
#include <stdbool.h> // C99

#define maxSize 100
bool solution = false;

bool areCoordsInCorrectFormat(char toMove[], char toPlace[], int x, int y)
{

	if (strlen(toMove) != 2 || strlen(toPlace) != 2)
		return false;
	if (toMove[0] < 'A' || toMove[0] > 'A' + x || toPlace[0] < 'A' || toPlace[0] > 'A' + x)
		return false;
	if (toMove[1] < '1' || toMove[1] > '1' + y || toPlace[1] < '1' || toPlace[1] > '1' + y)
		return false;
	if (toMove[0] == toPlace[0] && toMove[1] == toPlace[1])
		return false;
	return true;

}

bool modifyBoardIfPossible(char toMove[], char toPlace[], struct Board *board)
{
	int coord1 = board->y*(toMove[1] - '1') + toMove[0] - 'A';
	int coord2 = board->y*(toPlace[1] - '1') + toPlace[0] - 'A';
	char offSquare = '0', peg = '1', avaiableSquare = '2';

	if (*(board->values + coord1) != peg || *(board->values + coord2) != avaiableSquare)
		return false;

	int possDifBetweenCoords[2] = { 2, 2 * board->y };

	if (coord1 - coord2 == possDifBetweenCoords[0] && *(board->values + coord1 - 1) == peg)
	{
		*(board->values + coord1 - 1) = avaiableSquare;
		*(board->values + coord1) = avaiableSquare;
		*(board->values + coord2) = peg;
		addMove(&(*board), coord1, coord2);
		return true;
	}
	if (coord1 - coord2 == -possDifBetweenCoords[0] && *(board->values + coord1 + 1) == peg)
	{
		*(board->values + coord1 + 1) = avaiableSquare;
		*(board->values + coord1) = avaiableSquare;
		*(board->values + coord2) = peg;
		addMove(&(*board), coord1, coord2);
		return true;
	}
	if (coord1 - coord2 == possDifBetweenCoords[1] && *(board->values + coord1 - board->y) == peg)
	{
		*(board->values + coord1 - board->y) = avaiableSquare;
		*(board->values + coord1) = avaiableSquare;
		*(board->values + coord2) = peg;
		addMove(&(*board), coord1, coord2);
		return true;
	}
	if (coord1 - coord2 == -possDifBetweenCoords[1] && *(board->values + coord1 + board->y) == peg)
	{
		*(board->values + coord1 + board->y) = avaiableSquare;
		*(board->values + coord1) = avaiableSquare;
		*(board->values + coord2) = peg;
		addMove(&(*board), coord1, coord2);
		return true;
	}

	return false;
}

int howMuchPegs(struct Board *board)
{
	int sum = 0;
	for (int i = 0; i < board->x; i++)
		for (int j = 0; j < board->y; j++)
			if (*(board->values + i*board->y + j) == '1')
			{
				sum++;
			}

	return sum;
}

void modifyCoord2(int dir, char coord1[], char *coord2)
{
	enum directions
	{
		up, right, down, left
	};
	int diffBetweenC1C2 = 2;
	coord2[2] = '\0';
	switch (dir)
	{
	case up:
		coord2[0] = coord1[0];
		coord2[1] = coord1[1] - diffBetweenC1C2; break;
	case right:
		coord2[0] = coord1[0] + diffBetweenC1C2;
		coord2[1] = coord1[1]; break;
	case down:
		coord2[0] = coord1[0];
		coord2[1] = coord1[1] + diffBetweenC1C2; break;
	case left:
		coord2[0] = coord1[0] - diffBetweenC1C2;
		coord2[1] = coord1[1]; break;
	}
}

void setSolution(bool x)
{
	solution = x;
}

void bot(struct Board *board)
{
	if (solution)
		return;

	if (howMuchPegs(&(*board)) == 1)
	{
		printf("\nZnaleziono rozwiazanie! Oto koncowa plansza: \n");
		displayBoard(&(*board));
		saveMoves(&(*board));
		solution = true;
	}
	char peg = '1';
	for (int i = 0; i < board->x; i++)
	{
		for (int j = 0; j < board->y; j++)
		{
			char coord1[3];
			coord1[0] = 'A' + j;
			coord1[1] = '1' + i;
			coord1[2] = '\0';
			if (*(board->values + board->y*(coord1[1] - '1') + coord1[0] - 'A') != peg)
				continue;
			for (int dir = 0; dir < 4; dir++)
			{
				char coord2[3];
				modifyCoord2(dir, coord1, coord2);

				if (areCoordsInCorrectFormat(coord1, coord2, board->x, board->y))
					if (modifyBoardIfPossible(coord1, coord2, &(*board)))
					{
						bot(&(*board));
						undoTheLastMove(&(*board));
					}
			}
		}
	}
}

void makeAMove(struct Board *board)
{

	char toMove[maxSize];
	char toPlace[maxSize];
	bool isInputCorrect = false;
	char undo[] = "cofnij";

	while (!isInputCorrect)
	{
		printf("\nPodaj wspolrzedne pionka ktory chcesz ruszyc (jezeli chcesz cofnac poprzedni ruch napisz \"cofnij\"): ");
		scanf("%s", toMove);

		if (strcmp(toMove, undo) == 0)
		{
			undoTheLastMove(&(*board));
			displayBoard(&(*board));
			continue;
		}

		printf("\nPodaj wspolrzedne pustego pola gdzie chesz pionek umiescic: ");
		scanf("%s", toPlace);


		if (!areCoordsInCorrectFormat(toMove, toPlace, board->x, board->y))
		{
			printf("\nPodano bledne wspolrzedne sprobuj jeszcze raz\n");
			continue;
		}
		if (!modifyBoardIfPossible(toMove, toPlace, &(*board)))
		{
			printf("\nDany ruch jest niemozliwy\n");
			continue;
		}
		else break;
	}
}

bool isAMoveLeft(struct Board *board)
{
	char offSquare = '0', peg = '1', avaiableSquare = '2';
	int possDifBetweenCoords[2] = { 2, 2 * board->y };
	for (int i = 0; i < board->x; i++)
	{
		for (int j = 0; j < board->y; j++)
		{
			if (*(board->values + i*board->y + j) == peg)
			{

				if (i*board->y + j + possDifBetweenCoords[0] < board->y * board->x && *(board->values + i*board->y + j + possDifBetweenCoords[0]) == avaiableSquare && *(board->values + i*board->y + j + possDifBetweenCoords[0] / 2) == peg)
					return true;
				if (i*board->y + j - possDifBetweenCoords[0] > 0 && *(board->values + i*board->y + j - possDifBetweenCoords[0]) == avaiableSquare && *(board->values + i*board->y + j - possDifBetweenCoords[0] / 2) == peg)
					return true;
				if (i*board->y + j + possDifBetweenCoords[1] < board->y * board->x && *(board->values + i*board->y + j + possDifBetweenCoords[1]) == avaiableSquare && *(board->values + i*board->y + j + possDifBetweenCoords[1] / 2) == peg)
					return true;
				if (i*board->y + j - possDifBetweenCoords[1] > 0 && *(board->values + i*board->y + j - possDifBetweenCoords[1]) == avaiableSquare && *(board->values + i*board->y + j - possDifBetweenCoords[1] / 2) == peg)
					return true;

			}

		}
	}
	return false;
}
bool isGameOver(struct Board *board)
{
	char peg = '1';
	if (!isAMoveLeft(&(*board)))
	{
		printf("\nBrak dostepnych ruchow zostalo %d pionkow \n", howMuchPegs(&(*board)));
		displayBoard(&(*board));
		return true;
	}
	return false;
}