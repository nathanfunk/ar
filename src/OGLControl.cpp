/*
The code in this file is was adapted to Windows Forms from an MFC
tutorial at 
http://www.codeguru.com/cpp/g-m/opengl/openfaq/article.php/c10975/
*/
#define TRIAL_VERSION

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
	// Leaving this empty so nothing happens when a paint event occurs
	// All painting happens on Tick events

	// drawing in here and using Invalidate() at the end works, but seems to
	// cause other controls to not redraw as frequently
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
	//m_hdc = GetDC()->m_hDC;
	//TODO: this seems very iffy
	m_g = CreateGraphics();
	m_hdc = (HDC)(m_g->GetHdc().ToInt64()); // need to use delete?
	//System::Diagnostics::Debug::WriteLine("HDC: " + m_hdc);

	// Pixel format.
	m_nPixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	if (!SetPixelFormat(m_hdc, m_nPixelFormat, &pfd)) {
		Diagnostics::Debug::WriteLine("Failed to set pixel format");
	}

	// Create the OpenGL Rendering Context.
	m_hrc = wglCreateContext(m_hdc);
	if (!wglMakeCurrent(m_hdc, m_hrc))
	{
		Diagnostics::Debug::WriteLine("Failed to active device context");
	}

	// branding related
	{
		// Select a font for rendering the branding
		m_font = CreateFont(80, 0, 0, 0,
						FW_NORMAL, FALSE, FALSE, FALSE,
						ANSI_CHARSET, OUT_DEFAULT_PRECIS,
						CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
						DEFAULT_PITCH | FF_ROMAN,
						"Arial");

		SelectObject(m_hdc, m_font);

		// create bitmaps for the device context font's first 256 glyphs 
		wglUseFontBitmaps(m_hdc, 0, 256, 1000); 
		 
		// set up for a string-drawing display list call 
		glListBase(1000); 
	}

	// Set up timer
	m_timer = gcnew System::Windows::Forms::Timer();
	m_timer->Tick += gcnew EventHandler(this, &OGLControl::OnTick);
	// Want to set tick frequency high enough to not limit the frame rate
	// but low enough to not cause many unnecessary messages to be sent
	m_timer->Interval = 1000/20; // 20Hz
	m_timer->Start();
}

/**
 * Gets the GLUT button id from the Windows Forms id
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
	m_controller->mouseCBwithModifier(getGLUTButton(e->Button), GLUT_DOWN, e->X, e->Y, getModifierKeys());
	UserControl::OnMouseDown(e);
}

void OGLControl::OnMouseUp(MouseEventArgs ^e)
{
	m_controller->mouseCBwithModifier(getGLUTButton(e->Button), GLUT_UP, e->X, e->Y, getModifierKeys());
	UserControl::OnMouseDown(e);
}

void OGLControl::OnMouseMove(MouseEventArgs ^e)
{
	// motion callback function should only be called if a mouse button is pressed
	if (e->Button != ::MouseButtons::None) {
		m_controller->motionCB(e->X, e->Y);
	}
	UserControl::OnMouseMove(e);
}

int OGLControl::getModifierKeys()
{
	int value = 0;
	if ((Control::ModifierKeys & Keys::Shift) == Keys::Shift) 
		value += GLUT_ACTIVE_SHIFT;
	if ((Control::ModifierKeys & Keys::Alt) == Keys::Alt)
		value += GLUT_ACTIVE_ALT;
	if ((Control::ModifierKeys & Keys::Control) == Keys::Control)
		value += GLUT_ACTIVE_CTRL;
	
	return value;
}

void OGLControl::OnKeyDown(KeyEventArgs ^e)
{
	m_controller->keyboardCB(e->KeyValue, 0, 0);
}


void OGLControl::OnSizeChanged(System::EventArgs ^e)
{
	UserControl::OnSizeChanged(e);
	resizeViewport();
}

/**
 * Event handler for timer ticks. Tries to get a new image from the camera
 * and then redisplay the image if necessary.
 */
void OGLControl::OnTick(Object ^sender, EventArgs ^e)
{
	if (m_controller->idleCB()) {
		// a new picture is available from the camera
		// so draw it and the model (if marker is detected)

		glDrawBuffer(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw OpenGL scene
		m_controller->displayCB();

#ifdef TRIAL_VERSION
		// Draw branding
		drawBranding();
#endif
		// Swap buffers
		if (!SwapBuffers(m_hdc))
		{
			System::Diagnostics::Debug::WriteLine("SwapBuffers failed: " + GetLastError());
		}
	}
}


void OGLControl::drawBranding()
{
	// set color
	glDisable(GL_LIGHTING);

	glMatrixMode (GL_PROJECTION);
	glPushMatrix ();
		glLoadIdentity ();
		// Viewing transformation.
		glOrtho(0.0,   // left
				Width,   // right
				0.0,   // bottom
				Height,   // top
				1.0,  // near
				-1.0);  // far
		glMatrixMode (GL_MODELVIEW);
		glPushMatrix ();
			glLoadIdentity ();

			glColor3f(0.9F, 0.9F, 0.9F); 
			// move bottom left, southwest of the red triangle 
			glRasterPos2f(30.0F, 30.0F); 
			 			 
			// draw a string using font display lists 
			glCallLists(9, GL_UNSIGNED_BYTE, "ooqua.com"); 

			// get all those commands to execute 
			glFlush(); 
			
			glMatrixMode (GL_MODELVIEW);
		glPopMatrix();

	glMatrixMode (GL_PROJECTION);
	glPopMatrix();		 
	glEnable(GL_LIGHTING);

}


OGLControl::~OGLControl()
{
	System::Diagnostics::Debug::WriteLine("Inside OGLControl destructor");

	// branding related
	{
		// delete the font
		DeleteObject(m_font);			 
		// delete our 256 glyph display lists 
		glDeleteLists(1000, 256);
	}

	wglMakeCurrent(NULL, NULL);
	if (m_hrc) {
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	} else {
		System::Diagnostics::Debug::WriteLine("hrc is already deleted");
	}
	if (m_hdc) {
		m_g->ReleaseHdc((IntPtr)m_hdc);
		m_hdc = NULL;
	} else {
		System::Diagnostics::Debug::WriteLine("hdc is already released");
	}
	if (m_g) {
		delete m_g;
	} else {
		System::Diagnostics::Debug::WriteLine("g is already deleted");
	}
}
