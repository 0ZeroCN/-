#pragma once
/***************************************
ְ����--������Ϊ��ģʽ

��ͼ��
ʹ��������л��ᴦ�����󣬴Ӷ���������ķ����ߺͽ�����֮�����Ϲ�ϵ��
����Щ��������һ���������������������ݸ�����ֱ����һ����������Ϊֹ��

�����ԣ�
1���ж��������Դ���һ�������ĸ����������������ʱ���Զ�ȷ����
2���ɴ���һ������Ķ��󼯺�Ӧ����ָ̬����

��ȱ�㣺
1����Ψһʵ�����ܿط���
2��������������
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