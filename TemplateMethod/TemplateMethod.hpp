#pragma once
/***************************************
ģ�巽��--����Ϊ��ģʽ

��ͼ��
����һ�������е��㷨�ĹǼܣ�����һЩ�����ӳٵ����ࡣʹ�����಻�ı�һ���㷨�Ľṹ�����ض�����㷨��ĳЩ�ض����衣

�����ԣ�
1��һ����ʵ��һ���㷨�Ĳ���Ĳ��֣������ɱ����Ϊ����������ʵ�֡�
2���������й�������ΪӦ����ȡ���������е�һ�������������Ա�������ظ���

��ȱ�㣺

***************************************/

class View
{
public:
	void SetFocus(){}
	void ResetFocus(){}
	virtual void DoDisplay() = 0;

	void Display(){
		SetFocus();
		DoDisplay();
		ResetFocus();
	}
};

class MyView : public View
{
public:
	virtual void DoDisplay(){}
};