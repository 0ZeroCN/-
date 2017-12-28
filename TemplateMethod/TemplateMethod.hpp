#pragma once
/***************************************
模板方法--类行为型模式

意图：
定义一个操作中的算法的骨架，而将一些步骤延迟到子类。使得子类不改变一个算法的结构即可重定义该算法的某些特定步骤。

适用性：
1、一次性实现一个算法的不变的部分，并将可变的行为留给子类来实现。
2、各子类中公共的行为应被提取出来并集中到一个公共父类中以避免代码重复。

优缺点：

***************************************/

class View
{
public:
	void SetFocus(){}
	void ResetFocus(){}
	virtual void DoDisplay() = 0;

	void Display(){
		SetFocus();
		DoDisplay();
		ResetFocus();
	}
};

class MyView : public View
{
public:
	virtual void DoDisplay(){}
};