#pragma once

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "world.h"
#include "ARMouseHouse.h"

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
	System::Windows::Forms::Timer	^timer;
//	CWnd    *hWnd;
	HDC     hdc;
	HGLRC   hrc;
	int     m_nPixelFormat;
	Graphics ^g;
	ARMouseHouse	*controller;
public:
	OGLControl(void);
	virtual void OnPaint(PaintEventArgs ^e) override;
	virtual void OnCreateControl() override;
	virtual void OnSizeChanged(EventArgs ^e) override;
	virtual void OnMouseMove(MouseEventArgs ^e) override;
	void OnDraw();
	void OnTick(Object ^sender, EventArgs ^e);
	void setController(ARMouseHouse *controller) {this->controller = controller;}
	virtual ~OGLControl(void);
};

}