#pragma once
#include "../MapSite/MapSite.hpp"
/***************************************
ԭ��--���󴴽���ģʽ

��ͼ��
��ԭ��ʵ��ָ��������������࣬����ͨ��������Щԭ�ʹ����µĶ���

�����ԣ�
1��Ϊ�˱��ⴴ��һ�����Ʒ����ƽ�еĹ�������ʱ��
2�������Ψһʵ��Ӧ����ͨ�����໯����չ�ģ����ҿͻ�Ӧ��������Ĵ������ʹ��һ����չ��ʵ��ʱ��

��ȱ�㣺
1��ÿ�����඼����ʵ��clone����
2��ͨ�����󸴺϶����µ���Ϊ�������̼��ɶ����µ���
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