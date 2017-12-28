#pragma once
/***************************************
����--������Ϊ��ģʽ

��ͼ��
����һϵ�е��㷨��������һ������װ����������ʹ���ǿ��໥�滻����ģʽʹ���㷨�ɶ�����ʹ�����Ŀͻ����仯��

�����ԣ�
1���ṩ��һ���ö����Ϊ�е�һ����Ϊ������һ����ķ�����
2����Ҫʹ��һ���㷨�Ĳ�ͬ���塣

��ȱ�㣺
1������һϵ�пɹ����õ��㷨����Ϊ������̳еķ�����
2������һЩ������䡣
3���ͻ������˽ⲻͬ�Ĳ���
4�������˶������Ŀ
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

