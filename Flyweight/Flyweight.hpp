#pragma once
/***************************************
��Ԫ--����ṹ��ģʽ

��ͼ��
���ù�������Ч��֧�ִ���ϸ���ȵĶ���

�����ԣ�
1��һ��Ӧ�ó���ʹ���˴����Ķ���
2����ȫ����ʹ�ô����Ķ�����ɺܴ�Ĵ洢������
3������Ĵ����״̬���ɱ�Ϊ�ⲿ״̬��

��ȱ�㣺
1�������FlyweightԽ�࣬�洢��ԼҲ��Խ�ࡣ
***************************************/
class BTree{};
class Window{};
class GlyphContext
{
public:
	GlyphContext(){}
	virtual ~GlyphContext(){}

	virtual void Next(int step = 1){}
	virtual void Insert(int quantity = 1);

	virtual Font* GetFont(){}
	virtual void SetFont(Font*, int span = 1){}

private:
	int _index;
	BTree* _fonts;
};
class Font{};

class Glyph
{
public:
	virtual ~Glyph(){}

	virtual void Draw(Window*, GlyphContext&){}

	virtual void SetFont(Font*, GlyphContext&){}
	virtual Font *GetFont(GlyphContext&){}

	virtual void First(GlyphContext&){}
	virtual void Next(GlyphContext&){}
	virtual bool IsDone(GlyphContext&){}
	virtual Glyph* Current(GlyphContext&){}

	virtual void Insert(Glyph*, GlyphContext&){}
	virtual void Remove(GlyphContext&){}

protected:
	Glyph(){}
};

class Character : public Glyph
{
public:
	Character(char){}

	virtual void Draw(Window*, GlyphContext&){}

private:
	char _charcode;
};

const int NCHARCODES = 128;
class Row{};
class Column{};
class GlyphFactory
{
public:
	GlyphFactory(){
		for (int i = 0; i < NCHARCODES; ++i)
		{
			_character[i] = 0;
		}
	}

	virtual ~GlyphFactory(){}

	virtual Character* CreateCharacter(char c){
		if (!_character[c])
		{
			_character[c] = new Character(c);
		}

		return _character[c];
	}
	virtual Row* CreateRow(){ return new Row; }
	virtual Column* CreateColumn(){ return new Column; }

private:
	Character *_character[NCHARCODES];
};