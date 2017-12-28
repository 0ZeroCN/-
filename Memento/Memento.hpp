#pragma once
/***************************************
����¼--������Ϊ��ģʽ

��ͼ��
�ڲ��ƻ���װ�Ե�ǰ���£�����һ��������ڲ�״̬�����ڸö���֮�Ᵽ�����״̬�������Ժ�Ϳ��Խ��ö���ָ���ԭ�ȱ����״̬��

�����ԣ�
1�����뱣��һ��������ĳһ��ʱ�̵ģ����֣�״̬�������Ժ���Ҫʱ�����ָܻ�����ǰ��״̬��
2�����һ���ýӿ�������������ֱ�ӵõ���Щ״̬�����ᱩ¶�����ʵ��ϸ�ڲ��ƻ�����ķ�װ�ԡ�

��ȱ�㣺
1�����ַ�װ�ԣ����Ⱪ¶�ڲ���Ϣ
2��ʹ�ñ���¼�Ĵ��ۿ��ܸܺߣ������漰���ݵĴ�������
***************************************/
class Point{};

class Graphic
{
public:
	void Move(Point){}
};

class ConstraintSolverMemento
{
public:
	virtual ~ConstraintSolverMemento();

private:
	friend class ConstraintSolver;
	ConstraintSolverMemento(){}
};

class MoveCommand
{
public:
	MoveCommand(Graphic* target, const Point& delta){}
	void Execute(){
		ConstraintSolver* solver = ConstraintSolver::Instance();
		_state = solver->CreateMemento();
		_target->Move(_delta);
		solver->Solve();
	}
	void Unexecute(){
		ConstraintSolver* solver = ConstraintSolver::Instance();
		_target->Move(_delta);
		solver->SetMemento(_state);
		solver->Solve();
	}

private:
	ConstraintSolverMemento* _state;
	Point _delta;
	Graphic* _target;
};

class ConstraintSolver
{
public:
	static ConstraintSolver* Instance(){}

	void Solve(){}
	void AddConstraint(Graphic* startConnection, Graphic* endConnection){}
	void RemoveConstraint(Graphic* startConnection, Graphic* endConnection){}
	ConstraintSolverMemento* CreateMemento(){}
	void SetMemento(ConstraintSolverMemento*){}

private:
	//nontrivial state and operations for enforcing
};


