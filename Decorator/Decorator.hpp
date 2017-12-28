#pragma once
/***************************************
装饰--对象结构型模式

意图：
动态地给一个对象添加一些额外的职责

适用性：
1、在不影响其他对象的情况下，以动态、透明的方式给单个对象添加职责。
2、处理那些可以撤销的职责
3、当不能采用生成子类的方法扩充时。

优缺点：
1、比静态继承更灵活
2、避免在层次结构高层的类有太多的特征，提供一种“即用即付”的方法来添加职责
3、会产生很多看上去类似的小对象
***************************************/

class VisualComponent
{
public:
	VisualComponent(){}

	virtual void Draw(){}
	virtual void Resize(){}
};

class Decorator : public VisualComponent
{
public:
	Decorator(VisualComponent*){}

	virtual void Draw(){ _component->Draw(); }
	virtual void Resize(){ _component->Resize(); }

private:
	VisualComponent* _component;
};

class BorderDecorator : public Decorator
{
public:
	BorderDecorator(VisualComponent* vc, int borderWidth) : Decorator(vc), _width(borderWidth)
	{}

	virtual void Draw(){ 
		Decorator::Draw();
		DrawBorder(_width);
	}
	
private:
	void DrawBorder(int){}

private:
	int _width;
};