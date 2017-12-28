#pragma once
/***************************************
单件--对象创建型模式

意图：
保证一个类仅有一个实例，并提供一个访问它的全局访问点。

适用性：
1、当类只能有一个实例而且客户可以从一个众所周知的访问点访问它时。
2、当这个唯一实例应该是通过子类化可扩展的，并且客户应该无需更改代码就能使用一个扩展的实例时。

优缺点：
1、对唯一实例的受控访问
2、比类操作更灵活
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