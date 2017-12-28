#pragma once
/***************************************
享元--对象结构型模式

意图：
运用共享技术有效地支持大量细粒度的对象。

适用性：
1、一个应用程序使用了大量的对象。
2、完全由于使用大量的对象，造成很大的存储开销。
3、对象的大多数状态都可变为外部状态。

优缺点：
1、共享的Flyweight越多，存储节约也就越多。
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