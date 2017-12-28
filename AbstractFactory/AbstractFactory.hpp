#pragma once
/***************************************
���󹤳�--���󴴽���ģʽ

��ͼ��
�ṩһ������һϵ����ػ��໥��������Ľӿڣ�������ָ�����Ǿ�����ࡣ

�����ԣ�
1��һ��ϵͳҪ�ɶ��ϵ�в�Ʒ�е�һ��������
2��һ��ϵͳҪ���������Ĳ�Ʒ�Ĵ�������Ϻͱ�ʾ

��ȱ�㣺
1�������˾�����࣬�ͻ�ͨ�����󹤳��ͳ����Ʒ�������ʵ��
2��һ�����幤����Ӧһϵ�о����Ʒ�����ڽ�����Ʒϵ��
3�������ڲ�Ʒ��һ����
4������֧��������Ĳ�Ʒ�����漰�����󹤳�������������ĸı�
***************************************/

#include "stdafx.h"
#include "../MapSite/MapSite.hpp"

class MazeFactory
{
public:
	MazeFactory(){
		printf("MazeFactory\n");
	}

	virtual Maze *MakeMaze() const { return new Maze; }
	virtual Wall *MakeWall() const { return new Wall; }
	virtual Room *MakeRoom(int n) const { return new Room(n); }
	virtual Door *MakeDoor(Room *r1, Room *r2) const { return new Door(r1, r2); }
};

class EnchantedMazeFactory : public MazeFactory
{
public:
	EnchantedMazeFactory(){
		printf("EnchantedMazeFactory\n");
	}

	virtual Maze *MakeMaze() const { return new Maze; }
	virtual Wall *MakeWall() const { return new Wall; }
	virtual Room *MakeRoom(int n) const { return new EnchantedRoom(n); }
	virtual Door *MakeDoor(Room *r1, Room *r2) const { return new DoorNeedingSpell(r1, r2); }
};

class MazeGame
{
public:
	Maze *CreateMaze(MazeFactory &factory){
		Maze *aMaze = factory.MakeMaze();

		Room *r1 = factory.MakeRoom(1);
		Room *r2 = factory.MakeRoom(2);
		Door *theDoor = factory.MakeDoor(r1, r2);

		r1->SetSide(North, factory.MakeWall());
		r1->SetSide(East, theDoor);
		r1->SetSide(South, factory.MakeWall());
		r1->SetSide(West, factory.MakeWall());

		r2->SetSide(North, factory.MakeWall());
		r2->SetSide(East, factory.MakeWall());
		r2->SetSide(South, factory.MakeWall());
		r2->SetSide(West, theDoor);

		aMaze->AddRoom(r1);
		aMaze->AddRoom(r2);

		return aMaze;
	}
};