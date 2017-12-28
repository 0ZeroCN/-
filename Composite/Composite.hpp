#pragma once
#include <vector>
using namespace std;
/***************************************
组合--对象结构型模式

意图：
将对象组合成树形结构以表示“部分-整体”的层次结构。使得用户对单个对象和组合对象的使用具有一致性。

适用性：
1、你想表示对象的部分-整体层次结构。
2、你希望用户忽略组合对象与单个对象的不同，用户将统一地使用组合结构中的所有对象。

优缺点：
1、使用递归组合，用户不必区分图元和容器
2、最大化抽象基类接口
***************************************/
class Watt{};
class Currency{};

class Equipment
{
public:
	virtual ~Equipment(){}

	const char* Name(){ return _name; }

	virtual Watt Power(){}
	virtual Currency NetPrice(){}
	virtual Currency DiscountPrice(){}

	virtual void Add(Equipment*){}
	virtual void Remove(Equipment*){}
	virtual vector<Equipment> GetEquipments(){}

protected:
	Equipment(const char*){};

private:
	const char* _name;
};

class FloppyDisk : public Equipment
{
public:
	FloppyDisk(const char* name):Equipment(name)
	{}
	virtual ~FloppyDisk(){}

	virtual Watt Power(){}
	virtual Currency NetPrice(){}
	virtual Currency DiscountPrice(){}
};

class CompositeEquipment : public Equipment
{
public:
	CompositeEquipment(const char* name) :Equipment(name)
	{}
	virtual ~CompositeEquipment(){}

	virtual Watt Power(){}
	virtual Currency NetPrice(){}
	virtual Currency DiscountPrice(){}

	virtual void Add(Equipment*){}
	virtual void Remove(Equipment*){}
	virtual vector<Equipment> GetEquipments(){}
};