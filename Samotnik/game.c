#include "game.h"
#include "initGame.h"
#include "PegBoard.h"
#include <stdbool.h>

bool mainLoop(struct Board *board)
{
	displayBoard(&(*board));
	makeAMove(&(*board));
	return !isGameOver(&(*board));
}

void playGame()
{
	struct Board board = initBoard(getLevel());

	if (botEnabled())
	{
		setSolution(false);
		bot(&board);
	}
	else
	{
		bool running = true;
		while (running)
		{
			running = mainLoop(&board);
		}
		saveMoves(&board);
	}

	deleteMoves(&board);
	free(board.values);
	playGame();
}