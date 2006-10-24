/*
The code in this file is was adapted to Windows Forms from an MFC
tutorial at 
http://www.codeguru.com/cpp/g-m/opengl/openfaq/article.php/c10975/
*/
#include "OGLControl.h"

using namespace ms3dglut;

OGLControl::OGLControl(void)
{
	m_fPosX = 0.0f;    // X position of model in camera view
	m_fPosY = 0.0f;    // Y position of model in camera view
	m_fZoom = 10.0f;   // Zoom on model in camera view
	m_fRotX = 0.0f;    // Rotation on model in camera view
	m_fRotY = 0.0f;    // Rotation on model in camera view

	this->BackColor = Drawing::Color::Black;
	this->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
	this->SetStyle(ControlStyles::DoubleBuffer, false);
	this->SetStyle(ControlStyles::Opaque, true);
	this->SetStyle(ControlStyles::ResizeRedraw, true);
	this->SetStyle(ControlStyles::UserPaint, true);
}

void OGLControl::oglCreate(System::Drawing::Rectangle rect, Form ^parent)
{
	m_oldWindow = rect;
	m_originalRect = rect;
}

void OGLControl::oglInitialize()
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

	// Basic Setup:
	//
	// Set color to use when clearing the background.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	// Turn on backface culling
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// set up model view matrix
	updateModelView();

	// Send draw request
	OnDraw();
}

void OGLControl::oglDrawScene()
{
   // Wireframe Mode
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glBegin(GL_QUADS);
      // Top Side
      glVertex3f( 1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);

      // Bottom Side
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);

      // Front Side
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);

      // Back Side
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      // Left Side
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);

      // Right Side
      glVertex3f( 1.0f,  1.0f,  1.0f);
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
   glEnd();
}

void OGLControl::OnPaint(PaintEventArgs ^e)
{
	// this is supposed to do to nothing so that the timer-based drawing takes over
	//ValidateRect(Null)
	//Form::OnPaint(e);
	//e->Graphics->FillRectangle(SystemBrushes::Highlight, 10, 10, 30, 30);
}


void OGLControl::OnCreateControl()
{
	oglInitialize();
	// Set up timer
	timer = gcnew System::Windows::Forms::Timer();
	timer->Tick += gcnew EventHandler(this, &OGLControl::OnTick);
	timer->Interval = 1;
	timer->Start();
}

void OGLControl::OnMouseMove(MouseEventArgs ^e)
{
	int diffX = (int)(e->X - m_fLastX);
	int diffY = (int)(e->Y - m_fLastY);
	m_fLastX  = (float)e->X;
	m_fLastY  = (float)e->Y;
	// Left mouse button
	if (e->Button == Windows::Forms::MouseButtons::Left)
	{
		m_fRotX += (float)0.5f * diffY;

		if ((m_fRotX > 360.0f) || (m_fRotX < -360.0f))
		{
			m_fRotX = 0.0f;
		}

		m_fRotY += (float)0.5f * diffX;

		if ((m_fRotY > 360.0f) || (m_fRotY < -360.0f))
		{
			m_fRotY = 0.0f;
		}
	}

	// Right mouse button
	else if (e->Button == Windows::Forms::MouseButtons::Right)
	{
		m_fZoom -= (float)0.1f * diffY;
	}

	// Middle mouse button
	else if (e->Button == Windows::Forms::MouseButtons::Middle)
	{
		m_fPosX += (float)0.05f * diffX;
		m_fPosY -= (float)0.05f * diffY;
	}

	OnDraw();

	//CWnd::OnMouseMove(nFlags, point);
	UserControl::OnMouseMove(e);
}

void OGLControl::OnDraw()
{
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.0f);
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);
}

void OGLControl::updateModelView()
{
	// Map the OpenGL coordinates.
	glViewport(0, 0, Width, Height);

	// Projection view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set our current view perspective
	gluPerspective(35.0f, (float)Width / (float)Height, 0.01f, 300.0f);
	// Model view
	glMatrixMode(GL_MODELVIEW);
}

void OGLControl::OnSizeChanged(System::EventArgs ^e)
{
	UserControl::OnSizeChanged(e);
	
	if (0 >= Width || 0 >= Height) return;

	updateModelView();
}

/* Event handler for timer ticks */
void OGLControl::OnTick(Object ^sender, EventArgs ^e)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw OpenGL scene
	oglDrawScene();

	// Swap buffers
	if (!SwapBuffers(hdc))
	{
		System::Diagnostics::Debug::WriteLine("SwapBuffers failed: " + GetLastError());
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
