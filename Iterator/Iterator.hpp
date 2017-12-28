#pragma once
/***************************************
迭代器--对象行为型模式

意图：
提供一种方法顺序访问一个聚合对象中各个元素，而又不需暴露该对象的内部表示。

适用性：
1、访问一个聚合对象的内容而无需暴露它的内部表示。
2、支持对聚合对象的多种遍历。
3、为遍历不同的聚合结构提供一个统一地接口

优缺点：
1、支持以不同的方式遍历一个聚合。
2、迭代器简化了聚合的接口。
3、在一个聚合上可以有多个遍历
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