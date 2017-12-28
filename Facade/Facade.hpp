#pragma once
/***************************************
���--����ṹ��ģʽ

��ͼ��
Ϊ��ϵͳ�е�һ��ӿ��ṩһ�µĽ���

�����ԣ�
1��Ϊһ��������ϵͳ�ṩһ���򵥽ӿڡ�
2����Ҫ����һ����νṹ����ϵͳʱ��ʹ�ø�ģʽ������ϵͳ��ÿ�����ڵ㡣

��ȱ�㣺
1���Կͻ�������ϵͳ�������˼����˿ͻ�����Ķ������Ŀ��ʹ����ϵͳʹ���������ӷ��㡣
2��ʵ������ϵͳ��ͻ�֮�������Ϲ�ϵ������ϵͳ�ڲ��Ĺ�����������ǽ���ϵġ�
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