#pragma once
/***************************************
��������--�ഴ����ģʽ

��ͼ��
����һ�����ڴ�������Ľӿڣ����������ʵ������һ���ࡣʹһ�����ʵ�����ӳٵ������ࡣ

�����ԣ�
1����һ����ϣ��������������ָ�����������Ķ����ʱ��

��ȱ�㣺
1��Ϊ����һ���ض��Ĳ�Ʒ���󣬲��ò��������������������
2��ʹ��ģ���Ա��ⴴ������
***************************************/

#include "FactoryMethod.hpp"
#include "../MapSite/MapSite.hpp"

class MazeGame
{
public:
	Maze *CreateMaze(){
		Maze *aMaze = MakeMaze();

		Room *r1 = MakeRoom(1);
		Room *r2 = MakeRoom(2);

		Room *r1 = MakeRoom(1);
		Room *r2 = MakeRoom(2);
		Door *theDoor = MakeDoor(r1, r2);

		r1->SetSide(North, MakeWall());
		r1->SetSide(East, theDoor);
		r1->SetSide(South, MakeWall());
		r1->SetSide(West, MakeWall());

		r2->SetSide(North, MakeWall());
		r2->SetSide(East, MakeWall());
		r2->SetSide(South, MakeWall());
		r2->SetSide(West, theDoor);

		aMaze->AddRoom(r1);
		aMaze->AddRoom(r2);

		return aMaze;
	}

	virtual Maze *MakeMaze() const { return new Maze; }
	virtual Wall *MakeWall() const { return new Wall; }
	virtual Room *MakeRoom(int n) const { return new Room(n); }
	virtual Door *MakeDoor(Room *r1, Room *r2) const { return new Door(r1, r2); }
};

class BombedMazeGame : public MazeGame
{
public:
	BombedMazeGame();

	virtual Wall *MakeWall() const { return new BombedWall; }
	virtual Room *MakeRoom(int n) const { return new RoomWithABomb(n); }
	virtual Door *MakeDoor(Room *r1, Room *r2) const { return new DoorNeedingSpell(r1, r2); }
};

