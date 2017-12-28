#pragma once
#include <list>
/***************************************
命令--对象行为型模式

意图：
将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化。
对请求排队或记录请求日志，以及支持可撤销的操作。

适用性：
1、在不同的时刻指定、排列和执行请求。
2、支持取消操作。
3、支持修改日志。

优缺点：
1、增加新的Command很容易，因为无需改变已有的类
2、支持取消和重做
***************************************/
class Command
{
public:
	virtual ~Command(){}
	
	virtual void Execute() = 0;

protected:
	Command(){}
};

class Document
{
public:
	Document(const char* name){
		_name = name;
	}
	
	void Open(){}
	void Paste(){}

private:
	const char* _name;
};

class Application
{
public:
	void Add(Document*){}
};

class OpenCommand : public Command
{
public:
	OpenCommand(Application* a){
		_application = a;
	}

	virtual void Execute(){}
protected:
	virtual const char* AskUser(){
		const char* name = AskUser();
		if (name != 0)
		{
			Document* document = new Document(name);
			_application->Add(document);
			document->Open();
		}
	}
private:
	Application* _application;
	char* _response;
};

class PasteCommand : public Command
{
public:
	PasteCommand(Document* doc){
		_document = doc;
	}

	virtual void Execute(){
		_document->Paste();
	}

private:
	Document* _document;
};

class MacroCommand : public Command
{
public:
	MacroCommand(){}
	virtual ~MacroCommand(){}

	virtual void Add(Command* cmd){
		_cmds->push_back(cmd);
	}
	virtual void Remove(Command* cmd){
		_cmds->remove(cmd);
	}

	virtual void Execute(){
		//execute all cmds
	}

private:
	std::list<Command*>* _cmds;
};

