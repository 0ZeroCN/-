#pragma once
/***************************************
访问者--对象行为型模式

意图：
表示一个作用于某对象结构中的各元素的操作。

适用性：
1、需要对一个对象结构中的对象进行很多不同的并且不相关的操作，而你想避免让这些操作“污染”这些对象的类。
2、定义对象结构的类很少改变，但经常需要在此结构上定义新的操作。

优缺点：
1、易于增加新的操作
2、集中相关的操作而分离无关的操作
3、难以增加新的对象，visitor要添加一个新的抽象操作
4、破坏封装
***************************************/
class Watt{};
class Currency{};
class EquipmentVisitor;

class Equipment
{
public:
	virtual ~Equipment(){}

	const char* Name(){ return _name; }

	virtual Watt Power(){}
	virtual Currency NetPrice(){}
	virtual Currency DiscountPrice(){}

	virtual void Accept(EquipmentVisitor&){}

protected:
	Equipment(const char*){};

private:
	const char* _name;
};

class FloppyDisk : public Equipment
{
public:
	virtual void Accept(EquipmentVisitor& visitor){
		visitor.VisitFloppyDisk(this);
	}
};
class Card{};
class Chassis{};
class Bus{};
class EquipmentVisitor
{
public:
	virtual ~EquipmentVisitor(){}

	virtual void VisitFloppyDisk(FloppyDisk*){}
	virtual void VisitCard(Card*){}
	virtual void VisitChassis(Chassis*){}
	virtual void VisitBus(Bus*){}

protected:
	EquipmentVisitor(){}
};

class PricingVisitor : public EquipmentVisitor
{
public:
	PricingVisitor(){}

	Currency& GetTotalPrice(){
		return _total;
	}

	virtual void VisitFloppyDisk(FloppyDisk*){
		//add price
	}
	virtual void VisitCard(Card*){
		//add price
	}
	virtual void VisitChassis(Chassis*){
		//add price
	}
	virtual void VisitBus(Bus*){
		//add price
	}

private:
	Currency _total;
};

class Inventory{};
class InventoryVisitor : public EquipmentVisitor
{
public:
	InventoryVisitor(){}

	Inventory& GetInventory(){
		return _inventory;
	}

	virtual void VisitFloppyDisk(FloppyDisk*){
		//do Inventory
	}
	virtual void VisitCard(Card*){
		//do Inventory
	}
	virtual void VisitChassis(Chassis*){
		//do Inventory
	}
	virtual void VisitBus(Bus*){
		//do Inventory
	}

private:
	Inventory _inventory;
};