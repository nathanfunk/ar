#pragma once

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "world.h"
#include "Controller.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;




namespace ms3dglut {

ref class OGLControl : public UserControl
{
private:
	System::Windows::Forms::Timer	^m_timer;
//	CWnd    *hWnd;
	HDC     m_hdc;
	HGLRC   m_hrc;
	HFONT   m_font;
	int     m_nPixelFormat;
	Graphics ^m_g;
	Controller	*m_controller;
public:
	OGLControl(void);
	virtual void OnPaint(PaintEventArgs ^e) override;
	virtual void OnCreateControl() override;
	virtual void OnSizeChanged(EventArgs ^e) override;
	virtual void OnMouseDown(MouseEventArgs ^e) override;
	virtual void OnMouseUp(MouseEventArgs ^e) override;
	virtual void OnMouseMove(MouseEventArgs ^e) override;
	virtual void OnKeyDown(KeyEventArgs ^e) override;
	void OnTick(Object ^sender, EventArgs ^e);
	void setController(Controller *controller) {m_controller = controller;}
	void resizeViewport() {if (m_controller) m_controller->reshapeCB(Width, Height);}
	virtual ~OGLControl(void);
private:
	int getGLUTButton(System::Windows::Forms::MouseButtons b);
	int getModifierKeys();
	void drawBranding();
};

}