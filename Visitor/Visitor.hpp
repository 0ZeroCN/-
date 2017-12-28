#pragma once
/***************************************
������--������Ϊ��ģʽ

��ͼ��
��ʾһ��������ĳ����ṹ�еĸ�Ԫ�صĲ�����

�����ԣ�
1����Ҫ��һ������ṹ�еĶ�����кܶ಻ͬ�Ĳ��Ҳ���صĲ������������������Щ��������Ⱦ����Щ������ࡣ
2���������ṹ������ٸı䣬��������Ҫ�ڴ˽ṹ�϶����µĲ�����

��ȱ�㣺
1�����������µĲ���
2��������صĲ����������޹صĲ���
3�����������µĶ���visitorҪ���һ���µĳ������
4���ƻ���װ
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