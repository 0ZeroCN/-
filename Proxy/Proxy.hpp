#pragma once
#include <iostream>
using namespace std;
/***************************************
代理--对象结构型模式

意图：
为其他对象提供一种代理以控制对这个对象的访问。

适用性：
1、远程代理为一个对象在不同的地址空间提供局部代表。
2、虚代理根据需要创建对象。
3、保护代理控制对原始对象的访问。
4、智能指引取代简单的指针，它在访问对象时执行一些附加操作。

优缺点：
1、可以进行最大优化，根据要求创建对象。
***************************************/
class Point{};
class Event{};

class Graphic
{
public:
	virtual ~Graphic(){}
	
	virtual void Draw(const Point& at) = 0;
	virtual void HandleMouse(Event& event) = 0;

	virtual const Point& GetExtent() = 0;
	
	virtual void Load(istream& from) = 0;
	virtual void Save(ostream& to) = 0;

protected:
	Graphic(){}
};

class Image : public Graphic
{
public:
	Image(const char* file){}
	virtual ~Image();

	virtual void Draw(const Point& at){}
	virtual void HandleMouse(Event& event){}

	virtual const Point& GetExtent(){}

	virtual void Load(istream& from){}
	virtual void Save(ostream& to){}
};

class ImageProxy : public Graphic
{
public:
	ImageProxy(const char* imageFile){
		_fileName = strdup(imageFile);
		_extent = Point();
		_image = 0;
	}
	virtual ~ImageProxy(){}

	virtual void Draw(const Point& at){
		GetImage()->Draw(at);
	}
	virtual void HandleMouse(Event& event){
		GetImage()->HandleMouse(event);
	}

	virtual const Point& GetExtent(){}

	virtual void Load(istream& from){}
	virtual void Save(ostream& to){}

protected:
	Image* GetImage()
	{
		if (_image == 0)
		{
			_image = new Image(_fileName);
		}
		return _image;
	}

protected:
	Image* _image;
	Point _extent;
	char* _fileName;
};