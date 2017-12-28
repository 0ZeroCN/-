#pragma once
/***************************************
�Ž�--����ṹ��ģʽ

��ͼ��
�����󲿷�������ʵ�ֲ��ַ��룬ʹ���Ƕ����Զ����ر仯��

�����ԣ�
1���㲻ϣ���ڳ��������ʵ�ֲ���֮����һ���̶��İ󶨹�ϵ��
2���ڳ�������ʱ��ʵ�ֲ���Ӧ���Ա�ѡ������л���
3����ĳ����Լ�����ʵ�ֶ�Ӧ�ÿ���ͨ��������ķ����������䡣

��ȱ�㣺
1������ӿڼ���ʵ�ֲ���
2����߿���չ��
3��ʵ��ϸ�ڶԿͻ�͸��
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