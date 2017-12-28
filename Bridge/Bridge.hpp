#pragma once
/***************************************
桥接--对象结构型模式

意图：
将抽象部分与它的实现部分分离，使它们都可以独立地变化。

适用性：
1、你不希望在抽象和它的实现部分之间有一个固定的绑定关系。
2、在程序运行时刻实现部分应可以被选择或者切换。
3、类的抽象以及它的实现都应该可以通生成子类的方法加以扩充。

优缺点：
1、分离接口及其实现部分
2、提高可扩展性
3、实现细节对客户透明
***************************************/
#define Coord int
class Point
{
public:
	Coord x(){ return x_; }
	Coord y(){ return y_; }

private:
	Coord x_;
	Coord y_;
};

class Window;
class View
{
public:
	View(){}

	void DrawOn(Window *w){}
};

class WindowImp
{
public:
	virtual void DeviceBitmap(const char*, Coord, Coord) = 0;
	virtual void DeviceRect(Coord x1, Coord y1, Coord x2, Coord y2) = 0;
};

class Window
{
public:
	Window(View* contents){}

	virtual void DrawContents(){}

	virtual void DrawRect(Point& p1, Point& p2){
		WindowImp *imp = GetWindowImp();
		imp->DeviceRect(p1.x(), p1.y(), p2.x(), p2.y());
	}

protected:
	WindowImp* GetWindowImp(){}
	View* GetView(){}

private:
	WindowImp *_imp;
	View *_contents;
};

class ApplicationWindow : public Window
{
public:
	virtual void DrawContents(){
		GetView()->DrawOn(this);
	}
};

class IconWindow : public Window
{
public:
	virtual void DrawContents(){
		WindowImp* imp = GetWindowImp();
		if (imp != 0)
		{
			imp->DeviceBitmap(_bitmapName, 0, 0);
		}
	}

private:
	const char* _bitmapName;
};

class XWindowImp : public WindowImp
{
public:
	XWindowImp(){}

	virtual void DeviceRect(Coord, Coord, Coord, Coord){}
};

class PMWindowImp : public WindowImp
{
public:
	PMWindowImp(){}
	virtual void DeviceRect(Coord, Coord, Coord, Coord){}
};