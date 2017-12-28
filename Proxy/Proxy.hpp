#pragma once
#include <iostream>
using namespace std;
/***************************************
����--����ṹ��ģʽ

��ͼ��
Ϊ���������ṩһ�ִ����Կ��ƶ��������ķ��ʡ�

�����ԣ�
1��Զ�̴���Ϊһ�������ڲ�ͬ�ĵ�ַ�ռ��ṩ�ֲ�����
2������������Ҫ��������
3������������ƶ�ԭʼ����ķ��ʡ�
4������ָ��ȡ���򵥵�ָ�룬���ڷ��ʶ���ʱִ��һЩ���Ӳ�����

��ȱ�㣺
1�����Խ�������Ż�������Ҫ�󴴽�����
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