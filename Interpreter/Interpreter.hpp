#pragma once
#include <string>
/***************************************
解释器--类行为型模式

意图：
给定一个语言，定义它的文法的一种表示，并定义一个解释器，这个解释器使用该表示来解释语言中的句子。

适用性：
1、当有一个语言需要解释执行，并且你可将该语言中的句子表示为一个抽象语法树时，可使用解释器模式。

优缺点：
1、通过继承，易于改变和扩展文法
2、易于文法实现，定义抽象语法树中各个节点的类的实现大体类似
3、复杂的文法难以维护
4、增加了新的解释表达式的方法
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
