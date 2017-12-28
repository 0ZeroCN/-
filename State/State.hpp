#pragma once
/***************************************
状态--对象行为型模式

意图：
允许一个对象在其内部状态改变时改变它的行为。对象看起来似乎修改了它的类。

适用性：
1、一个对象的行为取决于它的状态，并且它必须在运行时刻根据状态改变它的行为。
2、一个操作中含有庞大的多分支的条件语句，且这些分支依赖于该对象的状态。

优缺点：
1、将与特定状态相关的行为局部化，并且将不同状态的行为分割开。
2、使得状态转换显示化。
***************************************/

class TCPOctetStream;
class TCPState;
class TCPClosed;

class TCPConnection
{
public:
	TCPConnection(){
		_state = TCPClosed::Instance();
	}

	void ActiveOpen(){
		_state->ActiveOpen(this);
	}
	void PassiveOpen(){
		_state->PassiveOpen(this);
	}
	void Close(){
		_state->Close(this);
	}
	void Send(){
		_state->Send(this);
	}
	void Acknowledge(){
		_state->Acknowledge(this);
	}
	void Synchronize(){
		_state->Synchronize(this);
	}

	void ProcessOctet(TCPOctetStream*){}

private:
	friend class TCPState;
	void ChangeState(TCPState* s){
		_state = s;
	}

private:
	TCPState* _state;
};

class TCPState
{
public:
	virtual void Transmit(TCPConnection*, TCPOctetStream*){}
	virtual void ActiveOpen(TCPConnection*){}
	virtual void PassiveOpen(TCPConnection*){}
	virtual void Close(TCPConnection*){}
	virtual void Send(TCPConnection*){}
	virtual void Acknowledge(TCPConnection*){}
	virtual void Synchronize(TCPConnection*){}

protected:
	void ChangeState(TCPConnection* t, TCPState* s){
		t->ChangeState(s);
	}
};

class TCPEstablished : public TCPState
{
public:
	static TCPState* Instance(){}

	virtual void Transmit(TCPConnection* t , TCPOctetStream* o){
		t->ProcessOctet(o);
	}
	virtual void Close(TCPConnection* t){
		ChangeState(t, TCPListen::Instance());
	}
};

class TCPListen : public TCPState
{
public:
	static TCPState* Instance(){}

	virtual void Send(TCPConnection* t){
		ChangeState(t, TCPEstablished::Instance());
	}
};

class TCPClosed : public TCPState
{
public:
	static TCPState* Instance(){}

	virtual void ActiveOpen(TCPConnection* t){
		ChangeState(t, TCPEstablished::Instance());
	}
	virtual void PassiveOpen(TCPConnection* t){
		ChangeState(t, TCPListen::Instance());
	}
};