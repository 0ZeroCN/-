#pragma once
/***************************************
工厂方法--类创建型模式

意图：
定义一个用于创建对象的接口，让子类决定实例化哪一个类。使一个类的实例化延迟到其子类。

适用性：
1、当一个类希望由它的子类来指定它所创建的对象的时候。

优缺点：
1、为创建一个特定的产品对象，不得不创建工厂方法类的子类
2、使用模板以避免创建子类
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

