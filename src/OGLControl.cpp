/*
The code in this file is was adapted to Windows Forms from an MFC
tutorial at 
http://www.codeguru.com/cpp/g-m/opengl/openfaq/article.php/c10975/
*/
#include "OGLControl.h"

using namespace ms3dglut;

OGLControl::OGLControl(void)
{
	this->BackColor = Drawing::Color::Black;
	this->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
	this->SetStyle(ControlStyles::DoubleBuffer, false);
	this->SetStyle(ControlStyles::Opaque, true);
	this->SetStyle(ControlStyles::ResizeRedraw, true);
	this->SetStyle(ControlStyles::UserPaint, true);
}


void OGLControl::OnPaint(PaintEventArgs ^e)
{
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw OpenGL scene
	controller->displayCB();

	// Swap buffers
	if (!SwapBuffers(hdc))
	{
		System::Diagnostics::Debug::WriteLine("SwapBuffers failed: " + GetLastError());
	}
}


void OGLControl::OnCreateControl()
{
	// Initial Setup:
	//
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,    // bit depth
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16,    // z-buffer depth
		0, 0, 0, 0, 0, 0, 0,
	};

	// Get device context only once.
	//hdc = GetDC()->m_hDC;
	//TODO: this seems very iffy
	g = CreateGraphics();
	hdc = (HDC)(g->GetHdc().ToInt64()); // need to use delete?
	//System::Diagnostics::Debug::WriteLine("HDC: " + hdc);

	// Pixel format.
	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	if (!SetPixelFormat(hdc, m_nPixelFormat, &pfd)) {
		Diagnostics::Debug::WriteLine("Failed to set pixel format");
	}

	// Create the OpenGL Rendering Context.
	hrc = wglCreateContext(hdc);
	if (!wglMakeCurrent(hdc, hrc))
	{
		Diagnostics::Debug::WriteLine("Failed to active device context");
	}

	// Set up timer
	timer = gcnew System::Windows::Forms::Timer();
	timer->Tick += gcnew EventHandler(this, &OGLControl::OnTick);
	timer->Interval = 1000/30; //30Hz
	timer->Start();
}

/**
Gets the GLUT button id from the Windows Forms id
*/
int OGLControl::getGLUTButton(System::Windows::Forms::MouseButtons b) {
	if (b == ::MouseButtons::Left) {
		return GLUT_LEFT_BUTTON;
	} else if (b == ::MouseButtons::Middle) {
		return GLUT_MIDDLE_BUTTON;
	} else {
		return GLUT_RIGHT_BUTTON;
	}
}

void OGLControl::OnMouseDown(MouseEventArgs ^e)
{
	controller->mouseCB(getGLUTButton(e->Button), GLUT_DOWN, e->X, e->Y);
	UserControl::OnMouseDown(e);
}

void OGLControl::OnMouseUp(MouseEventArgs ^e)
{
	controller->mouseCB(getGLUTButton(e->Button), GLUT_UP, e->X, e->Y);
	UserControl::OnMouseDown(e);
}

void OGLControl::OnMouseMove(MouseEventArgs ^e)
{
	// motion callback function should only be called if a mouse button is pressed
	if (e->Button != ::MouseButtons::None) {
		controller->motionCB(e->X, e->Y);
	}
	UserControl::OnMouseMove(e);
}

void OGLControl::OnKeyDown(KeyEventArgs ^e)
{
	controller->keyboardCB(e->KeyValue, 0, 0);
}


void OGLControl::OnSizeChanged(System::EventArgs ^e)
{
	UserControl::OnSizeChanged(e);
	
	if (0 >= Width || 0 >= Height) return;

	glViewport(0,0,Width,Height);							// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);							// Select The Projection Matrix
	glLoadIdentity();										// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(15.0f,(GLfloat)Width/(GLfloat)Height,1.0f,1000.0f);	// View Depth of 1000

	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();										// Reset The Modelview Matrix

}

/** Event handler for timer ticks
*/
void OGLControl::OnTick(Object ^sender, EventArgs ^e)
{
	if (controller->idleCB()) {
		// new video frame is available
		Invalidate();
	}
}


OGLControl::~OGLControl()
{
	System::Diagnostics::Debug::WriteLine("Inside OGLControl destructor");
	wglMakeCurrent(NULL, NULL);
	if (hrc) {
		wglDeleteContext(hrc);
		hrc = NULL;
	} else {
		System::Diagnostics::Debug::WriteLine("hrc is already deleted");
	}
	if (hdc) {
		g->ReleaseHdc((IntPtr)hdc);
		hdc = NULL;
	} else {
		System::Diagnostics::Debug::WriteLine("hdc is already released");
	}
	if (g) {
		delete g;
	} else {
		System::Diagnostics::Debug::WriteLine("g is already deleted");
	}
}
