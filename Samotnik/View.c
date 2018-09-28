#include "View.h"
#include "PegBoard.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void displayBoard(struct Board *board)
{
	printf("----------- SAMOTNIK ----------\n");
	printf("\t  ");
	char offSquare = '0', peg = '1', avaiableSquare = '2';
	char horizontalCoords = 'A';
	for (int i = 0; i < board->x; i++)
		printf("%c ", horizontalCoords + i);

	for (int i = 0; i < board->x; i++)
	{
		printf("\n\t%d", i + 1);
		for (int j = 0; j < board->y; j++)
		{
			if (*(board->values + i*board->y + j) == offSquare)
				printf("  ");
			else if (*(board->values + i*board->y + j) == peg)
				printf(" X");
			else if (*(board->values + i*board->y + j) == avaiableSquare)
				printf(" O");
		}
	}
}

bool botEnabled()
{
	enum choice
	{
		play = 1, bot
	};
	printf("\nChcesz zagrac recznie czy pozwolic botowi zrobic to za ciebie?");
	printf("\n1. Chce zagrac recznie");
	printf("\n2. Niech bot znajdzie rozwiazanie za mnie\n");
	int x;
	scanf("%d", &x);
	if (x == bot)
	{
		printf("\nZnajdowanie rozwiazania...\n");
		return true;
	}
	printf("\nNajpierw wprowadz wspolrzedne pionka podajac litere kolumny i numer wiersza\na nastepnie wspolrzedne pustego pola\n");
	return false;
}

char *getLevel()
{
	enum choice
	{
		standart = 1, square, european, asymmetric, german, diamond
	};

	switch (getLevelMenu())
	{
	case standart:
		return "standart.txt";
	case square:
		return "square.txt";
	case european:
		return "european.txt";
	case asymmetric:
		return "asymmetric.txt";
	case german:
		return "german.txt";
	case diamond:
		return "diamond.txt";
	}
}


int getLevelMenu()
{
	int choice = 0;
	printf("\nSamotnik\nCelem gry jest zostawienie na planszy jak najmniejszej liczby pionkow.\nIdealnym rozwiazaniem jest pozostawienie jednego pionka\nPionka bije sie przeskakujac go w pionie lub w poziomie.\nNie mozna poruszac sie na ukos oraz nie mozna bic kilku pionkow w jednym ruchu.");
	printf("\nX - pionek");
	printf("\nO - puste pole");
	printf("\n\nWybierz w jaka wersje chcesz zagrac:");
	printf("\n1. Standardowa wersja");
	printf("\n2. Kwadratowa wersja");
	printf("\n3. Europejska wersja");
	printf("\n4. Asemetryczna wersja");
	printf("\n5. Niemiecka wersja");
	printf("\n6. Diamentowa wersja\n");
	scanf("%d", &choice);
	return choice;
}
