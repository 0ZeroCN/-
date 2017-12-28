#pragma once
#include <string>
/***************************************
������--����Ϊ��ģʽ

��ͼ��
����һ�����ԣ����������ķ���һ�ֱ�ʾ��������һ�������������������ʹ�øñ�ʾ�����������еľ��ӡ�

�����ԣ�
1������һ��������Ҫ����ִ�У�������ɽ��������еľ��ӱ�ʾΪһ�������﷨��ʱ����ʹ�ý�����ģʽ��

��ȱ�㣺
1��ͨ���̳У����ڸı����չ�ķ�
2�������ķ�ʵ�֣���������﷨���и����ڵ�����ʵ�ִ�������
3�����ӵ��ķ�����ά��
4���������µĽ��ͱ��ʽ�ķ���
***************************************/
class VariableExp;
class Context
{
public:
	bool Lookup(const char*) const{}
	void Assign(VariableExp*, bool){}
};

class BooleanExp
{
public:
	BooleanExp(){}
	virtual ~BooleanExp(){}

	virtual bool Evaluate(Context&) = 0;
	virtual BooleanExp* Replace(const char*, BooleanExp&) = 0;
	virtual BooleanExp* Copy() const = 0;
};

class VariableExp : public BooleanExp
{
public:
	VariableExp(const char* name){
		_name = strdup(name);
	}
	virtual ~VariableExp(){}

	virtual bool Evaluate(Context& aContext){
		return aContext.Lookup(_name);
	}
	virtual BooleanExp* Replace(const char* name, BooleanExp& exp){
		if (strcmp(name, _name) == 0)
		{
			return exp.Copy();
		}
		else
		{
			return new VariableExp(_name);
		}
	}
	virtual BooleanExp* Copy() const{
		return new VariableExp(_name);
	}

private:
	char* _name;
};

class AndExp : public BooleanExp
{
public:
	AndExp(BooleanExp* op1, BooleanExp* op2){
		_operand1 = op1;
		_operand2 = op2;
	}
	virtual ~AndExp(){}

	virtual bool Evaluate(Context& aContext){
		return _operand1->Evaluate(aContext) && _operand1->Evaluate(aContext);
	}
	virtual BooleanExp* Replace(const char* name, BooleanExp& exp){
		return new AndExp(_operand1->Replace(name, exp), _operand2->Replace(name, exp));
	}
	virtual BooleanExp* Copy() const{
		new AndExp(_operand1->Copy(), _operand2->Copy());
	}

private:
	BooleanExp* _operand1;
	BooleanExp* _operand2;
};

class OrExp : public BooleanExp
{

};

class NotExp : public BooleanExp
{

};
//(true and x) or (y and (not x))
BooleanExp* expression;
Context constext;
VariableExp* x = new VariableExp("x");
VariableExp* y = new VariableExp("y");
