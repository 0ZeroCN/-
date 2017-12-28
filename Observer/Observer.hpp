#pragma once
/***************************************
�۲���--������Ϊ��ģʽ

��ͼ��
���������һ��һ�Զ��������ϵ����һ�������״̬�����ı�ʱ���������������Ķ��󶼵õ�֪ͨ�����Զ����¡�

�����ԣ�
1����һ������ĸı���Ҫͬʱ�ı��������󣬶���֪�������ж��ٶ����д��ı䡣
2����һ���������֪ͨ�������󣬶����ֲ��ܼٶ�����������˭��

��ȱ�㣺
1��Ŀ��͹۲��߼�ĳ������
2��һ���۲��߲���֪�������۲��ߵĴ��ڣ������������
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

