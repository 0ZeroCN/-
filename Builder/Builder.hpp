#pragma once
/***************************************
������--���󴴽���ģʽ

��ͼ��
��һ�����Ӷ���Ĺ��������ı�ʾ���룬ʹ��ͬ���Ĺ������̿��Թ�����ͬ�ı�ʾ��

�����ԣ�
1����������̱�����������Ķ����в�ͬ�ı�ʾʱ

��ȱ�㣺
1�����ɷ������ⲻ����Ϊ�����Ա���������Ƕ���Ϊ�շ�����ʹ�ͻ�ֻ�������Ȥ�Ĳ���
2������һ���µ��������������ı��Ʒ�ڲ��ı�ʾ
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