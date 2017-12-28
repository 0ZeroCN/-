#pragma once
#include "../MapSite/MapSite.hpp"
/***************************************
原型--对象创建型模式

意图：
用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。

适用性：
1、为了避免创建一个与产品类层次平行的工厂类层次时。
2、当这个唯一实例应该是通过子类化可扩展的，并且客户应该无需更改代码就能使用一个扩展的实例时。

优缺点：
1、每个子类都必须实现clone操作
2、通过对象复合定义新的行为，无需编程即可定义新的类
***************************************/

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

class MazePrototypeFactory : public MazeFactory
{
public:
	MazePrototypeFactory(Maze *m, Wall *w, Room *r, Door *d){
		_prototypeMaze = m;
		_prototypeWall = w;
		_prototypeRoom = r;
		_prototypeDoor = d;
	}

	virtual Maze *MakeMaze() const { return new Maze; }
	virtual Wall *MakeWall() const { return _prototypeWall->Clone(); }
	virtual Room *MakeRoom(int n) const { return new Room(n); }
	virtual Door *MakeDoor(Room *r1, Room *r2) const { 
		Door *door = _prototypeDoor->Clone();
		door->Initialize(r1, r2);
		return door;
	}

private:
	Maze *_prototypeMaze;
	Room *_prototypeRoom;
	Wall *_prototypeWall;
	Door *_prototypeDoor;
};

class MazeGame
{
public:
	Maze *CreateMaze(MazePrototypeFactory &factory){
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