#pragma once
#include <vector>
using namespace std;

enum Direction
{
	North,
	South,
	East,
	West
};

class MapSite
{
public:
	virtual void Enter() = 0;
};

class Room : public MapSite
{
public:
	Room(){};
	~Room(){
		printf("delete room %d\n", _roomNumber);
	}

	Room(int roomNo){ 
		_roomNumber = roomNo;
		printf("Room\n");
	}

	MapSite * GetSide(Direction d) const{
		return _sides[d];
	}
	void SetSide(Direction d, MapSite* pSide){
		_sides[d] = pSide;
	}
	int GetRoomNo(){ return _roomNumber; }

	virtual void Enter(){}

private:
	MapSite * _sides[4];
	int _roomNumber;
};

class EnchantedRoom : public Room
{
public:
	EnchantedRoom(int roomNo) : Room(roomNo){
		printf("EnchantedRoom\n");
	}
};

class RoomWithABomb : public Room
{
public:
	RoomWithABomb(int n) : Room(n)
	{}
};

class Wall : public MapSite
{
public:
	Wall(){
		printf("Wall\n");
	}
	Wall(const Wall &other){}
	~Wall(){};

	virtual Wall *Clone() const { return new Wall(*this); }
	virtual void Enter(){}
};

class BombedWall : public Wall
{
public:
	BombedWall(){}
	BombedWall(const BombedWall &other) : Wall(other){
		_bomb = other._bomb;
	}
	virtual Wall *Clone() const { return new BombedWall(*this); }
	bool HasBomb(){ return _bomb; }

private:
	bool _bomb;
};

class Door : public MapSite
{
public:
	Door(){}
	Door(const Door &d){
		_room1 = d._room1;
		_room2 = d._room2;
	}
	Door(Room *r1 = 0, Room *r2 = 0) : _isOpen(false){
		_room1 = r1;
		_room2 = r2;
		printf("Door\n");
	}
	~Door(){}

	virtual void Initialize(Room *r1, Room *r2){
		_room1 = r1;
		_room2 = r2;
	}

	virtual Door *Clone() const{
		return new Door(*this);
	}

	virtual void Enter(){ _isOpen = true; }
	Room *OtherSideFrom(Room *r){
		if (r == _room1)
		{
			return _room2;
		}
		else if (r == _room2)
		{
			return _room1;
		}
		else
		{
			return NULL;
		}
	}

private:
	Room *_room1;
	Room *_room2;
	bool _isOpen;
};

class DoorNeedingSpell : public Door
{
public:
	DoorNeedingSpell(Room *r1, Room *r2) : Door(r1, r2){
		printf("DoorNeedingSpell\n");
	}
};

class Maze
{
public:
	Maze(){
		printf("Maze\n");
	}
	~Maze(){
		printf("delete Maze\n");
	}

	void AddRoom(Room *r){
		_rooms.push_back(r);
	}

	Room *RoomNo(int num) {
		if (_rooms.empty())
		{
			return NULL;
		}

		vector<Room *>::iterator it = _rooms.begin();
		for (; it != _rooms.end(); ++it)
		{
			if (num == (*it)->GetRoomNo())
			{
				return (*it);
			}
		}

		return NULL;
	}

private:
	vector<Room *> _rooms;
};

