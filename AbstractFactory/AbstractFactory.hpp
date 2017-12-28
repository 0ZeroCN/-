#pragma once
/***************************************
抽象工厂--对象创建型模式

意图：
提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。

适用性：
1、一个系统要由多个系列产品中的一个来配置
2、一个系统要独立于它的产品的创建、组合和表示

优缺点：
1、分离了具体的类，客户通过抽象工厂和抽象产品的类操纵实例
2、一个具体工厂对应一系列具体产品，易于交换产品系列
3、有利于产品的一致性
4、难以支持新种类的产品，需涉及到抽象工厂及其所有子类的改变
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