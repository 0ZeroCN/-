// AbstractFactory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AbstractFactory.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	MazeFactory factory;
//	EnchantedMazeFactory factory;
	MazeGame game;
	game.CreateMaze(factory);

	system("pause");
	return 0;
}

