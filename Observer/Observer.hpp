#pragma once
/***************************************
观察者--对象行为型模式

意图：
定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。

适用性：
1、当一个对象的改变需要同时改变其他对象，而不知道具体有多少对象有待改变。
2、当一个对象必须通知其他对象，而它又不能假定其它对象是谁。

优缺点：
1、目标和观察者间的抽象耦合
2、一个观察者并不知道其它观察者的存在，可能意外更新
***************************************/
template <class Item>
class List
{
public:
	void Append(cosnt Item&){}
	void Remove(osnt Item&){}
};
class Subject;

class Observer
{
public:
	virtual ~Observer(){}
	virtual void Update(Subject* theChangedSubject) = 0;

protected:
	Observer(){}
};

class Subject
{
public:
	virtual ~Subject(){}
	virtual void Attach(Observer* ob){
		_observers->Append(ob);
	}
	virtual void Detach(Observer* ob){
		_observers->Remove(ob);
	}
	virtual void Notify(){
		//inform observers
	}
protected:
	Subject();
private:
	List<Observer*> *_observers;
};

class ClockTimer : public Subject
{
public:
	ClockTimer(){}

	virtual int GetHour(){}
	virtual int GetMinute(){}
	virtual int GetSecond(){}

	void Tick(){
		Notify();
	}
};

class Widget{};

class DigitalClock : public Widget, public Observer
{
public:
	DigitalClock(ClockTimer* s){
		_subject = s;
		_subject->Attach(this);
	}
	virtual ~DigitalClock(){
		_subject->Detach(this);
	}

	virtual void Update(Subject* theChangedSubject){
		if (theChangedSubject == _subject)
		{
			Draw();
		}
	}
	virtual void Draw(){
		int hour = _subject->GetHour();
		int minute = _subject->GetMinute();
	}

private:
	ClockTimer* _subject;
};

class AnalogClock : public Widget, public Observer
{
public:
	AnalogClock(ClockTimer*){}
	virtual void Update(Subject* theChangedSubject){}
	virtual void Draw(){}
};

