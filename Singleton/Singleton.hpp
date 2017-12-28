#pragma once
/***************************************
����--���󴴽���ģʽ

��ͼ��
��֤һ�������һ��ʵ�������ṩһ����������ȫ�ַ��ʵ㡣

�����ԣ�
1������ֻ����һ��ʵ�����ҿͻ����Դ�һ��������֪�ķ��ʵ������ʱ��
2�������Ψһʵ��Ӧ����ͨ�����໯����չ�ģ����ҿͻ�Ӧ��������Ĵ������ʹ��һ����չ��ʵ��ʱ��

��ȱ�㣺
1����Ψһʵ�����ܿط���
2��������������
***************************************/

class MazeFactory
{
public:
	static MazeFactory *Instance(){
		if (_instance == 0)
		{
			_instance = new MazeFactory;
		}

		return _instance;
	}

protected:
	MazeFactory();

private:
	static MazeFactory *_instance;
};

MazeFactory *MazeFactory::_instance = 0;