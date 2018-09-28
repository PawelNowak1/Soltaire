#pragma once

struct Moves
{
	struct Moves* next;
	int coord1;
	int coord2;
};

struct Board
{
	int x, y;
	char *values;
	struct Moves* lastMove;
};

void addMove(struct Board *board, int coord1, int coord2);
void undoTheLastMove(struct Board *board);
void deleteMoves(struct Board *board);
void saveMoves(struct Board *board);
