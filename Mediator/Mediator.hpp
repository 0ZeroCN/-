#pragma once
/***************************************
中介者--对象行为型模式

意图：
用一个中介对象来封装一系列的对象交互。中介者使各对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。

适用性：
1、一组对象以定义良好但是复杂的方式进行通信。
2、一个对象引用其他很多对象并且直接与这些对象通信，导致难以复用该对象。
3、想定制一个分布在多个类中的行为，而又不想生成太多的子类。

优缺点：
1、减少子类的生成
2、将一组对象解耦
3、控制集中化
4、简化了对象协议
***************************************/
class MouseEvent;
class Widget;

class DialogDirector
{
public:
	virtual ~DialogDirector(){}

	virtual void ShowDialog(){}
	virtual void WidgetChanged(Widget*) = 0;

};

class Widget
{
public:
	Widget(DialogDirector*){}
	virtual void Changed(){
		_director->WidgetChanged(this);
	}

	virtual void HandleMouse(MouseEvent& event){}

private:
	DialogDirector* _director;
};

template <class Item>
class List{};

class ListBox : public Widget
{
public:
	ListBox(DialogDirector* d) : Widget(d){}

	virtual const char* GetSelection(){}
	virtual void SetList(List<char*>* listItems){}
	virtual void HandleMouse(MouseEvent& event){}
};

class EntryField : public Widget
{
public:
	EntryField(DialogDirector* d) : Widget(d){}

	virtual void SetText(const char* text){}
	virtual void HandleMouse(MouseEvent& event){
		Changed();
	}
};

class Button : public Widget
{
public:
	Button(DialogDirector* d) : Widget(d){}
};

class FontDialogDirector : public DialogDirector
{
public:
	FontDialogDirector(){}
	virtual ~FontDialogDirector(){}
	virtual void WidgetChanged(Widget* theChangedWidget){
		if (theChangedWidget == _fontlist)
		{
			_fontName->SetText(_fontlist->GetSelection());
		}
		else if (theChangedWidget == _ok)
		{
			//apply font change and dismiss dialog
		}
		else if (theChangedWidget == _cancel)
		{
			//dismiss dialog
		}
	}

protected:
	virtual void CreateWidgets(){
		_ok = new Button(this);
		_cancel = new Button(this);
		_fontlist = new ListBox(this);
		_fontName = new EntryField(this);
	}

private:
	Button* _ok;
	Button* _cancel;
	ListBox* _fontlist;
	EntryField* _fontName;
};

