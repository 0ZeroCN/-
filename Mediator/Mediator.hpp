#pragma once
/***************************************
�н���--������Ϊ��ģʽ

��ͼ��
��һ���н��������װһϵ�еĶ��󽻻����н���ʹ��������Ҫ��ʽ���໥���ã��Ӷ�ʹ�������ɢ�����ҿ��Զ����ظı�����֮��Ľ�����

�����ԣ�
1��һ������Զ������õ��Ǹ��ӵķ�ʽ����ͨ�š�
2��һ���������������ܶ������ֱ������Щ����ͨ�ţ��������Ը��øö���
3���붨��һ���ֲ��ڶ�����е���Ϊ�����ֲ�������̫������ࡣ

��ȱ�㣺
1���������������
2����һ��������
3�����Ƽ��л�
4�����˶���Э��
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

