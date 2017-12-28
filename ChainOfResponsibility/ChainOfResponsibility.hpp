#pragma once
/***************************************
职责链--对象行为型模式

意图：
使多个对象都有机会处理请求，从而避免请求的发送者和接受者之间的耦合关系。
将这些对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。

适用性：
1、有多个对象可以处理一个请求，哪个对象处理该请求运行时刻自动确定。
2、可处理一个请求的对象集合应被动态指定。

优缺点：
1、对唯一实例的受控访问
2、比类操作更灵活
***************************************/
typedef int Topic;
const Topic NO_HELP_TOPIC = -1;

class HelpHandler
{
public:
	HelpHandler(HelpHandler* h, Topic t = NO_HELP_TOPIC):_successor(h), _topic(t){}
	virtual bool HasHelp(){
		return _topic != NO_HELP_TOPIC;
	}
	virtual void SetHandle(HelpHandler* h, Topic t){
		_successor = h;
		_topic = t;
	}
	virtual void HandleHelp(){
		if (_successor != 0)
		{
			_successor->HandleHelp();
		}
	}

private:
	HelpHandler* _successor;
	Topic _topic;
};

class Widget : public HelpHandler
{
public:
	Widget(Widget* w, Topic t = NO_HELP_TOPIC)
		: HelpHandler(w, t)
	{
		_parent = w;
	}

private:
	Widget* _parent;
};

class Button : public Widget
{
public:
	Button(Widget* d, Topic t = NO_HELP_TOPIC)
	: Widget(d, t)
	{}

	virtual void HandleHelp(){
		if (HasHelp())
		{
			//handle
		}
		else
		{
			HelpHandler::HandleHelp();
		}
	}
};

class Dialog : public Widget
{
public:
	Dialog(HelpHandler* h, Topic t = NO_HELP_TOPIC)
	: Widget(0)
	{
		SetHandle(h, t);
	}

	virtual void HandleHelp(){
		if (HasHelp())
		{
			//handle
		}
		else
		{
			HelpHandler::HandleHelp();
		}
	}
};

class Application : public HelpHandler
{
public:
	Application(Topic t)
		: HelpHandler(0, t)
	{}

	virtual void HandleHelp(){
		//
	}
};