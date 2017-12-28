#pragma once
#include <list>
/***************************************
����--������Ϊ��ģʽ

��ͼ��
��һ�������װΪһ�����󣬴Ӷ�ʹ����ò�ͬ������Կͻ����в�������
�������Ŷӻ��¼������־���Լ�֧�ֿɳ����Ĳ�����

�����ԣ�
1���ڲ�ͬ��ʱ��ָ�������к�ִ������
2��֧��ȡ��������
3��֧���޸���־��

��ȱ�㣺
1�������µ�Command�����ף���Ϊ����ı����е���
2��֧��ȡ��������
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

