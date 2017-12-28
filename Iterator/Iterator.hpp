#pragma once
/***************************************
������--������Ϊ��ģʽ

��ͼ��
�ṩһ�ַ���˳�����һ���ۺ϶����и���Ԫ�أ����ֲ��豩¶�ö�����ڲ���ʾ��

�����ԣ�
1������һ���ۺ϶�������ݶ����豩¶�����ڲ���ʾ��
2��֧�ֶԾۺ϶���Ķ��ֱ�����
3��Ϊ������ͬ�ľۺϽṹ�ṩһ��ͳһ�ؽӿ�

��ȱ�㣺
1��֧���Բ�ͬ�ķ�ʽ����һ���ۺϡ�
2�����������˾ۺϵĽӿڡ�
3����һ���ۺ��Ͽ����ж������
***************************************/
template <class Item>
class List
{
public:
	List(long size = 1024){}

	long Count() const{}
	Item& Get(long index) const{}
};

template <class Item>
class Iterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual Item CurrentItem() const = 0;

protected:
	Iterator(){}
};

template <class Item>
class ListIterator : public Iterator<Item>
{
public:
	ListIterator(const List<Item>* aList):_list(aList), _current(0){}
	virtual void First(){
		_current = 0;
	}
	virtual void Next(){
		_current++;
	}
	virtual bool IsDone(){
		return _current >= _list->Count();
	}
	virtual Item CurrentItem() const{
		if (IsDone())
		{

		}
		return _list->Get(_current);
	}

private:
	const List<Item>* _list;
	long _current;
};