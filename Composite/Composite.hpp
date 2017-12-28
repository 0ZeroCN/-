#pragma once
#include <vector>
using namespace std;
/***************************************
���--����ṹ��ģʽ

��ͼ��
��������ϳ����νṹ�Ա�ʾ������-���塱�Ĳ�νṹ��ʹ���û��Ե����������϶����ʹ�þ���һ���ԡ�

�����ԣ�
1�������ʾ����Ĳ���-�����νṹ��
2����ϣ���û�������϶����뵥������Ĳ�ͬ���û���ͳһ��ʹ����Ͻṹ�е����ж���

��ȱ�㣺
1��ʹ�õݹ���ϣ��û���������ͼԪ������
2����󻯳������ӿ�
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