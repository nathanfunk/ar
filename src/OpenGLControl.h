#pragma once

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

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
	System::Drawing::Rectangle   m_rect;
	System::Drawing::Rectangle   m_oldWindow;
	System::Drawing::Rectangle   m_originalRect;
	float	m_fPosX, m_fPosY;    // position of model in camera view
	float	m_fZoom;			// Zoom on model in camera view
	float	m_fRotX, m_fRotY;    // Rotation on model in camera view
	float	m_fLastX, m_fLastY;
	Graphics ^g;
private:
	void oglInitialize();
public:
	OGLControl(void);
	void oglCreate(System::Drawing::Rectangle rect, Form ^parent);
	void oglDrawScene();
	virtual void OnPaint(PaintEventArgs ^e) override;
	virtual void OnCreateControl() override;
	virtual void OnSizeChanged(EventArgs ^e) override;
	virtual void OnMouseMove(MouseEventArgs ^e) override;
	void updateModelView();
	void OnDraw();
	void OnTick(Object ^sender, EventArgs ^e);

	virtual ~OGLControl(void);
};

}