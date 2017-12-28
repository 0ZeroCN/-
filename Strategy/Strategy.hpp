#pragma once
/***************************************
策略--对象行为型模式

意图：
定义一系列的算法，把它们一个个封装起来，并且使它们可相互替换。本模式使得算法可独立于使用它的客户而变化。

适用性：
1、提供了一种用多个行为中的一个行为来配置一个类的方法。
2、需要使用一个算法的不同变体。

优缺点：
1、定义一系列可供重用的算法或行为，替代继承的方法。
2、消除一些条件语句。
3、客户必须了解不同的策略
4、增加了对象的数目
***************************************/
class Compoitor;
class Component;
class Coord{};
class Composition
{
public:
	Composition(Compoitor*){}
	void Repair(){
		Coord* natural;
		Coord* stretchability;
		Coord* shrinkability;
		int componentCount;
		int* breaks;
		//prepare the arrays with the desired component sizes

		int breakCount;
		breakCount = _compositor->Compose(natural, stretchability, shrinkability, componentCount, _lineWidth, breaks);
			
	}

private:
	Compositor* _compositor;
	Component* _component;
	int _componentCount;
	int _lineWidth;
	int* _lineBreaks;
	int _lineCount;
};

class Compositor
{
public:
	virtual int Compose(Coord natural[], Coord stretch[], Coord shrink[],
		int componentCount, int lineWidth, int breaks[]) = 0;

protected:
	Compositor(){}
};

class SimpleCompositor : public Compositor
{
public:
	SimpleCompositor(){}

	virtual int Compose(Coord natural[], Coord stretch[], Coord shrink[],
		int componentCount, int lineWidth, int breaks[]){}
};

class TexCompositor : public Compositor
{
public:
	TexCompositor(){}

	virtual int Compose(Coord natural[], Coord stretch[], Coord shrink[],
		int componentCount, int lineWidth, int breaks[]){}
};

class ArrayCompositor : public Compositor
{
public:
	ArrayCompositor(){}

	virtual int Compose(Coord natural[], Coord stretch[], Coord shrink[],
		int componentCount, int lineWidth, int breaks[]){}
};

