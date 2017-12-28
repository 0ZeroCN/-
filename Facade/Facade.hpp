#pragma once
/***************************************
外观--对象结构型模式

意图：
为子系统中的一组接口提供一致的界面

适用性：
1、为一个复杂子系统提供一个简单接口。
2、需要构建一个层次结构的子系统时，使用该模式定义子系统中每层的入口点。

优缺点：
1、对客户屏蔽子系统组件，因此减少了客户处理的对象的数目并使得子系统使用起来更加方便。
2、实现了子系统与客户之间的松耦合关系，而子系统内部的功能组件往往是紧耦合的。
***************************************/

class istream{};

class Token{};

class CodeGenerator
{
public:
	CodeGenerator(istream&){}

protected:
	istream _output;
};

class ProgramNode
{
public:
	virtual void GetSourcePosition(int& line, int& index){}

	virtual void Add(ProgramNode*){}
	virtual void Remove(ProgramNode*){}

	virtual void Traverse(CodeGenerator&);
	
protected:
	ProgramNode(){}
};

class Scanner
{
public:
	Scanner(istream&){}
	virtual ~Scanner(){}

	virtual Token& Scan(){}

private:
	istream _inputStream;
};

class ProgramNodeBuilder
{
public:
	ProgramNodeBuilder(){}

	virtual ProgramNode* NewVariable(const char *variableName) const {}
	virtual ProgramNode* NewAssignment(ProgramNode* variable, ProgramNode* expression) const {}
	virtual ProgramNode* NewReturnStatement(ProgramNode* value) const {}
	virtual ProgramNode*NewCondition(ProgramNode* condition, ProgramNode* truePart, ProgramNode*falsePart) const {}

	ProgramNode* GetRootNode(){}

private:
	ProgramNode* _node;
};

class Parser
{
public:
	Parser(){}
	virtual ~Parser(){}

	virtual void Parse(Scanner&, ProgramNodeBuilder&){}
};

class Compiler
{
public:
	Compiler(){}

	virtual void Compile(istream& input, istream& output)
	{
		Scanner scanner(input);
		ProgramNodeBuilder builder;
		Parser parser;

		parser.Parse(scanner, builder);
		CodeGenerator generator(output);
		ProgramNode* parseTree = builder.GetRootNode();
		parseTree->Traverse(generator);

	}
};