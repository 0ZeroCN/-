#pragma once
/***************************************
备忘录--对象行为型模式

意图：
在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可以将该对象恢复到原先保存的状态。

适用性：
1、必须保存一个对象在某一个时刻的（部分）状态，这样以后需要时它才能恢复到先前的状态。
2、如果一个用接口来让其他对象直接得到这些状态，将会暴露对象的实现细节并破坏对象的封装性。

优缺点：
1、保持封装性，避免暴露内部信息
2、使用备忘录的代价可能很高，可能涉及数据的大量拷贝
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


