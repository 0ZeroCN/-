#pragma once
/***************************************
生成器--对象创建型模式

意图：
将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以构建不同的表示。

适用性：
1、当构造过程必须允许被构造的对象有不同的表示时

优缺点：
1、生成方法故意不声明为纯虚成员函数，而是定义为空方法，使客户只定义感兴趣的操作
2、定义一个新的生成器，用来改变产品内部的表示
***************************************/
#include "stdafx.h"
#include "../MapSite/MapSite.hpp"

class MazeBuilder
{
public:
	virtual void BuildMaze(){}
	virtual void BuildRoom(int n){}
	virtual void BuildDoor(int roomFrom, int roomTo){}
	
	virtual Maze *GetMaze(){ return 0; }
};

class StandardMazeBuilder : public MazeBuilder
{
public:
	StandardMazeBuilder(){ _currentMaze = 0; }

	virtual void BuildMaze(){ _currentMaze = new Maze; }
	virtual void BuildRoom(int n){
		if (!_currentMaze->RoomNo(n))
		{
			Room *room = new Room(n);
			_currentMaze->AddRoom(room);

			room->SetSide(North, new Wall);
			room->SetSide(East, new Wall);
			room->SetSide(South, new Wall);
			room->SetSide(West, new Wall);
		}
	}
	virtual void BuildDoor(int roomFrom, int roomTo){
		Room *r1 = _currentMaze->RoomNo(roomFrom);
		Room *r2 = _currentMaze->RoomNo(roomTo);
		Door *d = new Door(r1, r2);

		r1->SetSide(CommonWall(r1, r2), d);
		r2->SetSide(CommonWall(r1, r2), d);
	}

	virtual Maze *GetMaze(){ return _currentMaze; }

private:
	Direction CommonWall(Room *r1, Room *r2){ return East; }
	Maze *_currentMaze;
};

class CountingMazeBuilder : public MazeBuilder
{
public:
	CountingMazeBuilder(){ _rooms = _doors = 0; }
	virtual void BuildMaze(){}
	virtual void BuildRoom(int n){ _rooms++; }
	virtual void BuildDoor(int roomFrom, int roomTo){ _doors++; }
	virtual void AddWall(int n, Direction d){}

	void GetCounts(int& rooms, int &doors) const{
		rooms = _rooms;
		doors = _doors;
	}

private:
	int _doors;
	int _rooms;
};

class MazeGame
{
public:
	Maze *CreateMaze(MazeBuilder &builder){
		builder.BuildRoom(1);
		builder.BuildRoom(2);
		builder.BuildDoor(1, 2);
		return builder.GetMaze();
	}
};