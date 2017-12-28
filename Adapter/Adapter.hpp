#pragma once
/***************************************
������--�ࡢ����ṹ��ģʽ

��ͼ��
��һ����Ľӿ�ת���ɿͻ�ϣ��������һ���ӿڡ�ʹ��ԭ�����ڽӿڲ����ݶ�����һ��������Щ�����һ������

�����ԣ�
1������ʹ��һ���Ѿ����ڵ��࣬�����Ľӿڲ������������
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
��������

��ȱ�㣺
1����Ҫƥ��һ�����������������ʱ��������������ʤ��
2�������ض���Ҫ�������Ĳ�����Ϊ������Ҫ�����ָ��
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
����������

��ȱ�㣺
1����ƥ��һ�����������������ʱ
2�������ض���Ҫ�������Ĳ�����Ϊ����Ҫ�����ָ��
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