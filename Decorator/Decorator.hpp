#pragma once
/***************************************
װ��--����ṹ��ģʽ

��ͼ��
��̬�ظ�һ���������һЩ�����ְ��

�����ԣ�
1���ڲ�Ӱ���������������£��Զ�̬��͸���ķ�ʽ�������������ְ��
2��������Щ���Գ�����ְ��
3�������ܲ�����������ķ�������ʱ��

��ȱ�㣺
1���Ⱦ�̬�̳и����
2�������ڲ�νṹ�߲������̫����������ṩһ�֡����ü������ķ��������ְ��
3��������ܶ࿴��ȥ���Ƶ�С����
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