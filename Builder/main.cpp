// Builder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Builder.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	StandardMazeBuilder builder;
	builder.BuildMaze();
	MazeGame game;
	game.CreateMaze(builder);

	system("pause");
	return 0;
}

