// Prototype.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Prototype.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	MazePrototypeFactory simpleMazeFactory(new Maze, new Wall, new Room, new Door(0));
	MazeGame game;
	game.CreateMaze(simpleMazeFactory);
	return 0;
}

