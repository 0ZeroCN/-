#pragma once
/***************************************
适配器--类、对象结构型模式

意图：
将一个类的接口转换成客户希望的另外一个接口。使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。

适用性：
1、你想使用一个已经存在的类，而它的接口不符合你的需求。
***************************************/

#define Coord int
class Point
{
public:
	Point(int x, int y){
		x_ = x;
		y_ = y;
	}

private:
	int x_;
	int y_;
};

class Manipulator
{

};

class Shape
{
public:
	Shape(){}
	virtual void BoundingBox(Point& bottomLeft, Point& topRight) const {}
	virtual Manipulator* CreateManipulator(){ return new Manipulator; }
};

class TextView
{
public:
	TextView(){}
	void GetOrigin(Coord& x, Coord& y) const {}
	void GetExtent(Coord& width, Coord& height) const {}
	virtual bool IsEmpty(){ return true; }
};

class TextManipulator : public Manipulator
{
public:
	TextManipulator(Shape *sh){}
};

/*******************************************
类适配器

优缺点：
1、当要匹配一个类和所有它的子类时，该适配器不能胜任
2、可以重定义要适配对象的部分行为，不需要额外的指针
*******************************************/
class ClassTextShape : public Shape, private TextView
{
public:
	ClassTextShape(){}

	virtual void BoundingBox(Point& bottomLeft, Point& topRight) const {
		Coord bottom, left, width, height;
		GetOrigin(bottom, left);
		GetExtent(width, height);
		bottomLeft = Point(bottom, left);
		topRight = Point(bottom + height, left + width);
	}

	bool IsEmpty() { return TextView::IsEmpty(); }

	Manipulator *CreateManipulator(){
		return new TextManipulator(this);
	}
};

/*******************************************
对象适配器

优缺点：
1、能匹配一个类和所有它的子类时
2、不能重定义要适配对象的部分行为，需要额外的指针
*******************************************/
class ObjectTextShape : public Shape
{
public:
	ObjectTextShape(TextView *t){ t_ = t; }

	void BoundingBox(Point& bottomLeft, Point& topRight) const{
		Coord bottom, left, width, height;
		t_->GetOrigin(bottom, left);
		t_->GetExtent(width, height);
		bottomLeft = Point(bottom, left);
		topRight = Point(bottom + height, left + width);
	}

	bool IsEmpty() { return t_->IsEmpty(); }

	Manipulator *CreateManipulator() {
		return new TextManipulator(this);
	}

private:
	TextView *t_;
};