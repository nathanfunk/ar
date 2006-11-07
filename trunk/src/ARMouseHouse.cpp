/*
ARMOUSEHOUSE Augmented Reality Mouse House
Created by Farooq Ahmad Sept. 2006
*/

//#define GLUT_GUI_MODE
#define _CRTDBG_MAP_ALLOC	// include for mapping allocation for detecting memory leaks

#include <stdlib.h>
#include <crtdbg.h>			// include for detecting memory leaks

#include <math.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class GLUquadric {};// avoids "warning LNK4248: unresolved typeref token (01000030) for 'GLUquadric'; image may not run"
struct _ARGL_CONTEXT_SETTINGS {}; // avoids "warning LNK4248: unresolved typeref token (01000031) for '_ARGL_CONTEXT_SETTINGS'; image may not run"

#include <gl/glut.h>   // The GL Utility Toolkit (Glut) Header
#include <gl/glaux.h>
//#include <GL/glui.h>

#include <AR/gsub_lite.h>
#include <AR/video.h>
#include <AR/param.h>
#include <AR/ar.h>

#include "Timer.h"
#include "MilkshapeModel.h"
#include "glbmp.h"
#include "myModel.h"
#include "world.h"
#include "MainWindow.h" // uses System::... causes ambiguities for myModel calling MessageBox
#include "ARMouseHouse.h"
//--------------------------------------------------------------------------------------

using namespace std;
using namespace ms3dglut;

//--------------------------------------------------------------------------------------

int lastX;
int lastY; 

int x1Rect;
int y1Rect;
int x2Rect;
int y2Rect;
int selectRectDefined;
int nothingSelected;

ARMouseHouse *controller;

//--------------------------------------------------------------------------------------

void idleCB() {controller->idleCB();}
void reshapeCB( int width , int height ) {controller->reshapeCB(width, height);}
void arrowKeysCB( int a_keys, int x, int y ) {controller->arrowKeysCB(a_keys, x, y);}
void menuCB(int item) {controller->menuCB(item);}
void colorMenuCB(int item) {controller->colorMenuCB(item);}
void textureMenuCB(int item) {controller->colorMenuCB(item);}
void fileMenuCB(int item) {controller->fileMenuCB(item);}
void displayCB(void) {controller->displayCB();}
void motionCB(int x, int y) {controller->motionCB(x, y);}
void mouseCB(int button, int state, int x, int y) {controller->mouseCB(button, state, x, y);}
void keyboardCB( unsigned char key, int x, int y) {controller->keyboardCB(key, x, y);}



AUX_RGBImageRec *LoadBMP(const char *Filename)						// Loads A Bitmap Image
{
	FILE *File=NULL;												// File Handle

	if (!Filename)													// Make Sure A Filename Was Given
	{
		return NULL;												// If Not Return NULL
	}

	fopen_s(&File, Filename,"r");									// Check To See If The File Exists

	if (File)														// Does The File Exist?
	{
		fclose(File);												// Close The Handle
		return auxDIBImageLoad(Filename);							// Load The Bitmap And Return A Pointer
	}

	return NULL;													// If Load Failed Return NULL
}

GLuint LoadGLTexture( const char *filename )						// Load Bitmaps And Convert To Textures
{
	AUX_RGBImageRec *pImage;										// Create Storage Space For The Texture
	GLuint texture = 0;												// Texture ID

	pImage = LoadBMP( filename );									// Loads The Bitmap Specified By filename

/* //glbmp style
glbmp_t bitmap;
	int err = glbmp_LoadBitmap(filename, GLBMP_ANY_SIZE, &bitmap);
  if(err <= 0)
   {
      fprintf(stderr, "Error loading bitmap file: %s Error %d\n", filename, err);
      exit(1);
   }

		glGenTextures(1, &texture);									// Create The Texture
		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, bitmap.width, bitmap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap.rgb_data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


	glbmp_FreeBitmap(&bitmap);
	return texture;
*/

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if ( pImage != NULL && pImage->data != NULL )					// If Texture Image Exists
	{
		glGenTextures(1, &texture);									// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pImage->sizeX, pImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		free(pImage->data);											// Free The Texture Image Memory
		free(pImage);												// Free The Image Structure
	}

	return texture;													// Return The Status
}


GLuint LoadGLTextureRepeat( const char *filename )						// Load Bitmaps And Convert To Textures
{
	AUX_RGBImageRec *pImage;										// Create Storage Space For The Texture
	GLuint texture = 0;												// Texture ID

	pImage = LoadBMP( filename );									// Loads The Bitmap Specified By filename


	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if ( pImage != NULL && pImage->data != NULL )					// If Texture Image Exists
	{
		glGenTextures(1, &texture);									// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pImage->sizeX, pImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE) 



		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		free(pImage->data);											// Free The Texture Image Memory
		free(pImage);												// Free The Image Structure
	}
	else std::cout<<"Could not load texture"<<std::endl;

	std::cout<<"texture is "<<texture<<std::endl;
	return texture;													// Return The Status
}




//--------------------------------------------------------------------------------------
#ifdef GLUT_GUI_MODE

int main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
{
	// enable automatic memory leak detection report on exit
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	controller = new ARMouseHouse(true);
	glutInit(&argc, argv);
	controller->InitGL();
	controller->ar_init();
	controller->initMenu();

	//GLUT callbacks
	glutMotionFunc(motionCB);
	glutSpecialFunc(arrowKeysCB);
	glutKeyboardFunc(keyboardCB);
	glutMouseFunc(mouseCB);
	glutDisplayFunc(displayCB);
	glutReshapeFunc(reshapeCB);
	glutIdleFunc(idleCB);

	arVideoCapStart();

//		argMainLoop( ar_mouseEvent, ar_keyEvent, ar_mainLoop ); //gsub.h dependent
	glutMainLoop();

	char ch = getchar();
	delete controller;
	return 0;
}

#else //-------------------------------------------------------------------------------------
[STAThreadAttribute]
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// enable automatic memory leak detection report on exit
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew ms3dglut::MainWindow());

	return 0;
}
#endif


//--------------------------------------------------------------------------------------
#pragma unmanaged


ARMouseHouse::ARMouseHouse(bool useGLUTGUI) {
	this->useGLUTGUI = useGLUTGUI;
	thresh = 100;
	ar_count = 0;
	cparam_name	= "Data/camera_para.dat";
	ARTImage		= NULL; // current image
	arglSettings	= NULL;
	patt_name		= "Data/patt.triangle";
	patt_width		= 80.0;
	patt_center[0]	= 0.0;
	patt_center[1] = 0.0;
	patt_found		= false;
	world = new World();
	world->loadWorld("myworld.txt");
	world->loadTextures("blah.txt");
	drawVideo = true;
}

ARMouseHouse::~ARMouseHouse() {
	ar_cleanup();
	if (world) delete world;
}

void ARMouseHouse::ar_cleanup(void)
{
	if (arglSettings) {
		arglCleanup(arglSettings);
	}
    arVideoCapStop();
    arVideoClose();
//    argCleanup(); //gsub.h dependent
}


void ARMouseHouse::InitGL ( GLvoid )     // Create Some Everyday Functions
{	
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable ( GL_COLOR_MATERIAL );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glInitNames(); //init the name stack for selection

	// initialize lighting
    GLfloat   light_position[]  = {0.0, 0.0, -1.0, 0.0};
    GLfloat   ambi[]            = {0.2, 0.2, 0.2, 1.0};
    GLfloat   diffuse[]			= {1.0, 1.0, 1.0, 1.0};
    GLfloat   spec[]			= {1.0, 1.0, 1.0, 1.0};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambi);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

//	GLfloat   mat_ambient[]     = {1.0, 1.0, 1.0, 1.0};
//    GLfloat   mat_flash[]       = {1.0, 1.0, 1.0, 1.0};
//    GLfloat   mat_flash_shiny[] = {50.0};
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_flash);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_flash_shiny);	
//	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
}


void ARMouseHouse::ar_draw( void )
{
	double    p[16];
	double    m[16];

	// Projection transformation.
	arglCameraFrustum(&cparam, VIEW_DISTANCE_MIN, VIEW_DISTANCE_MAX, p);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(p);
	glMatrixMode(GL_MODELVIEW);
	// Viewing transformation.
	glLoadIdentity();

	glClearDepth( 1.0 );
	glClear(GL_DEPTH_BUFFER_BIT);

	/* load the camera transformation matrix */
	arglCameraView(patt_trans, m, VIEW_SCALEFACTOR); //gsub_lite.h - TODO: check scale factor
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(m);

	// Display the world
	world->draw();

	if (nothingSelected)
		drawSelectionRect();
}

void ARMouseHouse::displayCB(void)
{
	if (useGLUTGUI) {
		// Select correct buffer for this context.
		glDrawBuffer(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers for new frame.
	} else {
		// OGLControl takes care of setting the right buffer
	}

	// draw the video image
	if (drawVideo) {
		arglDispImage(ARTImage, &cparam, 1.0, arglSettings);
	}

    arVideoCapNext();
	ARTImage = NULL; // Image data is no longer valid after calling arVideoCapNext().

	// draw the world if the pattern has been found
	if (patt_found) {
		ar_draw();
	}

	// swap buffers if using GLUT (OGLControl does this itself)
	if (useGLUTGUI) {
		glutSwapBuffers();
	}
}

/**
Idle callback. Is called before the GUI goes into idle state.

Returns true if window needs to be redrawn, false otherwise
*/
bool ARMouseHouse::idleCB()
{
	static int ms_prev;
	int ms;
	float s_elapsed;
    ARUint8         *dataPtr;
    ARMarkerInfo    *marker_info;
    int             marker_num;
    int             j, k;

	// Find out how long since Idle() last ran.
	ms = glutGet(GLUT_ELAPSED_TIME);
	s_elapsed = (float)(ms - ms_prev) * 0.001;
	if (s_elapsed < 0.01f) {
		return false; // Don't update more often than 100 Hz.
	}
	ms_prev = ms;

    // try to grab a new frame
	// return if none is available
	if ((dataPtr = (ARUint8 *)arVideoGetImage()) == NULL) {
		return false;
	}
	ARTImage = dataPtr;	// Save the fetched image.
	patt_found = FALSE;	// Invalidate any previous detected markers.

	if( ar_count == 0 ) arUtilTimerReset();
    ar_count++;

    // detect the markers in the video frame
    if( arDetectMarker(dataPtr, thresh, &marker_info, &marker_num) < 0 ) {
		printf("arDetectMarker failed! Exiting. Press any key to continue.");
		getchar();
        ar_cleanup();
        exit(0);
	}
	// Check through the marker_info array for highest confidence
	// visible marker matching our preferred pattern.
	k = -1;
	for (j = 0; j < marker_num; j++) {
		if (marker_info[j].id == patt_id) {
			if (k == -1) k = j; // First marker detected.
			else if(marker_info[j].cf > marker_info[k].cf) k = j; // Higher confidence marker detected.
		}
	}

	if (k != -1) {
		// Get the transformation between the marker and the real camera into patt_trans.
		arGetTransMatCont(&(marker_info[k]), patt_trans, patt_center, patt_width, patt_trans);
		
		patt_found = TRUE;
	}

	if (useGLUTGUI) {
		// Tell GLUT the display has changed.
		glutPostRedisplay();
	}
	return true;
}


void ARMouseHouse::reshapeCB( int width , int height )   // Create The Reshape Function (the viewport)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;													// Making Height Equal One
	}

	glViewport(0,0,width,height);									// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);									// Select The Projection Matrix
	glLoadIdentity();												// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(15.0f,(GLfloat)width/(GLfloat)height,VIEW_DISTANCE_MIN,VIEW_DISTANCE_MAX);	// View Depth of 1000

	glMatrixMode(GL_MODELVIEW);										// Select The Modelview Matrix
	glLoadIdentity();												// Reset The Modelview Matrix
}



void ARMouseHouse::arrowKeysCB( int a_keys, int x, int y )  // Create Special Function (required for arrow keys)
{

	std::cout<< "Arrow key : "<<a_keys<<std::endl;

	switch ( a_keys ) {
	case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
		//glutFullScreen ( ); // Go Into Full Screen Mode
		//glutReshapeWindow ( 352, 288 );





		break;
	case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
		//glutReshapeWindow ( 320, 240 ); // Go Into A 500 By 500 Window



		break;
	default:
		break;
	}
}






void ARMouseHouse::ar_init( void )
{
    ARParam  wparam;
    /* open the video path */
	//if( arVideoOpen( vconf ) < 0 ){
	if( arVideoOpen("Data\\WDM_camera_flipV.xml") < 0 ){
        printf("arVideoOpen failed!! Press any key to exit...\n");
		_getch();
		exit(0);
	}

    /* find the size of the window */
    if( arVideoInqSize(&xsize, &ysize) < 0 ) exit(0);
    printf("Image size (x,y) = (%d,%d)\n", xsize, ysize);

    /* set the initial camera parameters */
    if( arParamLoad(cparam_name, 1, &wparam) < 0 ) {
        printf("Camera parameter load error!! Press any key to exit...\n");
		_getch();
        exit(0);
    }

    arParamChangeSize( &wparam, xsize, ysize, &cparam );
    arInitCparam( &cparam );
    printf("*** Camera Parameter ***\n");
    arParamDisp( &cparam );

    if( (patt_id=arLoadPatt(patt_name)) < 0 ) {
        printf("Pattern load error!! Press any key to exit...\n");
		_getch();
        exit(0);
    }

    /* open the graphics window */
//    argInit( &cparam, 1.0, 0, 0, 0, 0 ); //gsub.h dependent
	// ----------------------------------------------------------------------------
	// Library setup.
	//

	// Set up GL context(s) for OpenGL to draw into.
	if (useGLUTGUI) {
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutInitWindowSize(cparam.xsize, cparam.ysize);
		glutCreateWindow("AR Window");
	}

	// Setup argl library for current context.
	if ((arglSettings = arglSetupForCurrentContext()) == NULL) {
		fprintf(stderr, "main(): arglSetupForCurrentContext() returned error.\n");
		exit(-1);
	}
	glEnable(GL_DEPTH_TEST);
	arUtilTimerReset();

	// ----------------------------------------------------------------------------
}


/* cleanup function called when program exits */
/* Allow picking with the mouse
 picking code from http://www.hitlabnz.org/forum/archive/index.php/t-55.html
 */
int ARMouseHouse::selection(int key, int mouse_x, int mouse_y) { 
	GLuint   buffer[512];	// Set Up A Selection Buffer 
	GLint   hits;	  // The Number Of Objects That We Selected 
	double   gl_para[16];
	// The Size Of The Viewport. [0] Is , [1] Is , [2] Is , [3] Is  
	GLint   viewport[4]; 
	GLdouble projMatrix[16];

	int selected = -1;

	glSelectBuffer(512, buffer);   // Tell OpenGL To Use Our Array For Selection 
	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer. 

	glRenderMode(GL_SELECT);  

	glInitNames();   // Initializes The Name Stack 
	///glPushName(-1);   // Push 0 (At Least One Entry) Onto The Stack 

	//argDrawMode3D(); //gsub.h dependent
	//argDraw3dCamera( 0, 0 ); //gsub.h dependent
	arglCameraFrustum(&cparam, VIEW_DISTANCE_MIN, VIEW_DISTANCE_MAX, projMatrix);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport); 

	glPushMatrix();	    // Push The Projection Matrix 
	glLoadIdentity();	   // Resets The Matrix 


	std::cout<<"Pick Matrix: "<<mouse_x<<" "<<viewport[3]-mouse_y<<std::endl;

	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is. 
	gluPickMatrix((GLdouble) mouse_x, (GLdouble) (viewport[3]-mouse_y), 5, 5, viewport); 

	//multiply the pick matrix by the projection matrix
	glMultMatrixd(projMatrix);

	//now draw everything as in ar_draw
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	/* load the camera transformation matrix */
	//argConvGlpara(patt_trans, gl_para); //gsub.h dependent
	arglCameraView(patt_trans, gl_para, VIEW_SCALEFACTOR);
	glLoadMatrixd( (GLdouble *) gl_para );


	//print out gl_para
	std::cout<<gl_para[8]<<" "<<gl_para[9]<<" "<<gl_para[10]<<std::endl;

	glMatrixMode(GL_MODELVIEW);
	//glTranslatef( 0.0, 0.0, 25.0 );

	//draw the world
	world->draw();

	glPopMatrix();

	//stop Picking, what did we click?

	glMatrixMode(GL_PROJECTION);   // Select The Projection Matrix 
	glPopMatrix();	   // Pop The Projection Matrix 
	glMatrixMode(GL_MODELVIEW);   // Select The Modelview Matrix 
	glFlush();
	hits=glRenderMode(GL_RENDER);   // Switch To Render Mode, Find Out How Many 
	// Objects Were Drawn Where The Mouse Was 

	if (hits > 0) {	       // If There Were More Than 0 Hits 
		int   choose = buffer[3];   // Make Our Selection The First Object 
		int depth = buffer[1];	   // Store How Far Away It Is 

		printf("hits: %d %d\n", hits, choose); 

		for (int loop = 1; loop < hits; loop++)	    // Loop Through All The Detected Hits 
		{ 
			// If This Object Is Closer To Us Than The One We Have Selected 
			if (buffer[loop*4+1] < GLuint(depth)) 
			{ 
				choose = buffer[loop*4+3];   // Select The Closer Object 
				depth = buffer[loop*4+1];	 // Store How Far Away It Is 
				printf("object, depth: %d %d\n", choose, depth); 
			}	   
		} 
		selected = choose; 
		printf("closest: %d\n", selected); 


		if ((selected >= 0) && ((unsigned)selected < world->getNumberOfObjects())) {
			world->isSelected = 0;
			if (key != GLUT_ACTIVE_SHIFT){
				for (size_t i = 0; i < world->getNumberOfObjects(); i++){
					//world->objectPtrs[i]->deselect();
					///world->objectPtrs[i]->isSelected = 0;
					world->objectPtrs[i]->isSelected = 0;
				}

			}
			// world->objectPtrs[selected]->select();
			world->objectPtrs[selected]->isSelected = 1;

		}
		else if (selected == -100){
			for (size_t i = 0; i < world->getNumberOfObjects(); i++){
				//world->objectPtrs[i]->deselect();
				///world->objectPtrs[i]->isSelected = 0;
				world->objectPtrs[i]->isSelected = 0;
			}
			world->isSelected = 1;
		}


	} else { 
		selected = -1; 
		printf("no hits!\n"); 
	}	 

	return selected;

} 





int ARMouseHouse::selectionRect(int key) { 
	GLuint   buffer[512];	// Set Up A Selection Buffer 
	GLint   hits;	  // The Number Of Objects That We Selected 
	double   gl_para[16];
	// The Size Of The Viewport. [0] Is , [1] Is , [2] Is , [3] Is  
	GLint   viewport[4]; 
	GLdouble projMatrix[16];


	selectRectDefined = 1;

	int selected = -1;

	glSelectBuffer(512, buffer);   // Tell OpenGL To Use Our Array For Selection 
	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer. 

	glRenderMode(GL_SELECT);  

	glInitNames();   // Initializes The Name Stack 
	///glPushName(-1);   // Push 0 (At Least One Entry) Onto The Stack 

	//argDrawMode3D(); //gsub.h dependent
	//argDraw3dCamera( 0, 0 ); //gsub.h dependent
	arglCameraFrustum(&cparam, VIEW_DISTANCE_MIN, VIEW_DISTANCE_MAX, projMatrix);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport); 

	glPushMatrix();	    // Push The Projection Matrix 
	glLoadIdentity();	   // Resets The Matrix 


	float winX1 = (float)x1Rect;
	float winY1 = (float)viewport[3] - (float)y1Rect;
	float winX2 = (float)x2Rect;
	float winY2 = (float)viewport[3] - (float)y2Rect;

	GLdouble width = abs(winX2 - winX1);
	GLdouble height = abs(winY2 - winY1);
	GLdouble centerX = (winX1 + winX2 )/2;
	GLdouble centerY = (winY1 + winY2 )/2;

 // glOrtho(0.0,   // left
    //       1.0,   // right
     //      0.0,   // bottom
      //     1.0,   // top
      //     1.0,  // near
       //    -1.0);  // far

	std::cout<<"Rect Pick Matrix: "<<winX1<<" "<<winY1<<" "<<winX2 - winX1<<" "<<winY2 - winY1<<std::endl;

	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is. 
	//gluPickMatrix((GLdouble) winX1, (GLdouble) winY1, (GLdouble) winX2 - winX1, (GLdouble) winY2 - winY1, viewport); 
gluPickMatrix(centerX, centerY, width, height, viewport); 



	//multiply the pick matrix by the projection matrix
	glMultMatrixd(projMatrix);

	//now draw everything as in ar_draw
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	/* load the camera transformation matrix */
	//argConvGlpara(patt_trans, gl_para); //gsub.h dependent
	arglCameraView(patt_trans, gl_para, VIEW_SCALEFACTOR);
	glLoadMatrixd( (GLdouble *) gl_para );


	//print out gl_para
	std::cout<<gl_para[8]<<" "<<gl_para[9]<<" "<<gl_para[10]<<std::endl;

	glMatrixMode(GL_MODELVIEW);
	//glTranslatef( 0.0, 0.0, 25.0 );

	//draw the world
	world->draw();

	glPopMatrix();

	//stop Picking, what did we click?

	glMatrixMode(GL_PROJECTION);   // Select The Projection Matrix 
	glPopMatrix();	   // Pop The Projection Matrix 
	glMatrixMode(GL_MODELVIEW);   // Select The Modelview Matrix 
	glFlush();
	hits=glRenderMode(GL_RENDER);   // Switch To Render Mode, Find Out How Many 
	// Objects Were Drawn Where The Mouse Was 

	if (hits > 0) {	       // If There Were More Than 0 Hits 
		int   choose = buffer[3];   // Make Our Selection The First Object 
		int depth = buffer[1];	   // Store How Far Away It Is 

		printf("hits: %d %d\n", hits, choose); 
		if (choose >= 0 && choose < (int) world->getNumberOfObjects())
			world->objectPtrs[choose]->isSelected = 1;
		for (int loop = 1; loop < hits; loop++)	    // Loop Through All The Detected Hits 
		{ 
			// If This Object Is Closer To Us Than The One We Have Selected 
			//if (buffer[loop*4+1] < GLuint(depth)) 
			//{ 
				choose = buffer[loop*4+3];   // Select The Closer Object 
				depth = buffer[loop*4+1];	 // Store How Far Away It Is 
				printf("object, depth: %d %d\n", choose, depth); 
			if (choose >= 0 && choose < (int) world->getNumberOfObjects())
				world->objectPtrs[choose]->isSelected = 1;

			//}	   
		} 
		selected = choose; 
		printf("closest: %d\n", selected); 


		if ((selected >= 0) && (selected < (int) world->getNumberOfObjects())) {
			world->isSelected = 0;
		//	if (key != GLUT_ACTIVE_SHIFT){
		//		for (size_t i = 0; i < world->getNumberOfObjects(); i++){
					//world->objectPtrs[i]->deselect();
					///world->objectPtrs[i]->isSelected = 0;
		//			world->objectPtrs[i]->isSelected = 0;
		//		}

			//}
			// world->objectPtrs[selected]->select();
			//world->objectPtrs[selected]->isSelected = 1;

		}
		else if (selected == -100){
			for (int i = 0; i < (int) world->getNumberOfObjects(); i++){
				//world->objectPtrs[i]->deselect();
				///world->objectPtrs[i]->isSelected = 0;
				world->objectPtrs[i]->isSelected = 0;
			}
			world->isSelected = 1;
		}


	} else { 
		selected = -1; 
		selectRectDefined = 0;
		printf("no hits!\n"); 
	}	 

	return selected;

} 




void ARMouseHouse::menuCB(int item)
{
     switch (item) {

      case 1:
		  world->addObject(new myModel((int) world->objectPtrs.size(), "chair.ms3d", 50,0,-50,0,1));
            break;
      case 2:
			world->addObject(new myModel((int) world->objectPtrs.size(), "lcdtv2.ms3d", 50,0,-50,0,1));
			break;
    case 3:
			world->addObject(new myModel((int) world->objectPtrs.size(), "bed2.ms3d", 50,0,-50,0,1));
			break;
  case 4:
			world->addObject(new myModel((int) world->objectPtrs.size(), "toilet3.ms3d", 50,0,-50,0,1));
			break;//was toilet3.ms3d
 case 5:
			world->addObject(new myModel((int) world->objectPtrs.size(), "sink.ms3d", 50,0,-50,0,10));
			break;//was sink
case 6:
			world->addObject(new myModel((int) world->objectPtrs.size(), "sheep2.ms3d", 50,0,-50,0,1));
			break;

case 7:
			world->addObject(new myModel((int) world->objectPtrs.size(), "fart.ms3d", 50,0,-50,0,1));
			break;
case 8:
			world->addObject(new myModel((int) world->objectPtrs.size(), "sofa2.ms3d", 50,0,-50,0,2));
			break;
case 9:
			world->addObject(new myModel((int) world->objectPtrs.size(), "stairs2.ms3d", 50,0,-50,0,100));
			break;
case 10:
			world->addObject(new myModel((int) world->objectPtrs.size(), "tab3.ms3d", 50,0,-50,0,1));
			break;
case 11:
			world->addObject(new myModel((int) world->objectPtrs.size(), "shelf.ms3d", 50,0,-50,0,1));
			break;
case 12:
			world->addObject(new myModel((int) world->objectPtrs.size(), "wooddoor.ms3d", 50,0,-50,0,1));
			break;
case 13:
			world->addObject(new myModel((int) world->objectPtrs.size(), "window4.ms3d", 50,0,-50,0,10));
			break;


	  default:
			break;

	 }
};

void ARMouseHouse::setColors(float r, float g, float b) {
	for (size_t i = 0; i < world->getNumberOfObjects(); i++){
		if (world->objectPtrs[i]->isSelected) {
			world->objectPtrs[i]->setColors(r, g, b);
		}
	}
}


void ARMouseHouse::colorMenuCB(int item)
{

     switch (item) {
      case 1:
		 	for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			world->objectPtrs[i]->setColors(0.8,0.3,0.3,1);
			}	
			}
            break;
      case 2:
		for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			world->objectPtrs[i]->setColors(0.2,0.3,0.5,1);
			}
			}
			break;
       case 3:
		for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			world->objectPtrs[i]->setColors(0.2,0.8,0.8,1);
			}
			}
			break;
	  default:
			break;

	 }
};




void ARMouseHouse::textureMenuCB(int item)
{
/*
	std::cout<<"item "<<item<<"texindex size "<<world->textureIndex.size()<<std::endl;
if ((item > 0) && (item <= world->textureIndex.size())){
	for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){			
				world->objectPtrs[i]->setTexture(world->textureIndex[item-1]);
			}
		}
}
*/
	     switch (item) {
      case 0:
		 		for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			world->objectPtrs[i]->setTexture((GLuint) 0);
			}
			}
			break;
      case 1:
		for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			world->objectPtrs[i]->setTexture(LoadGLTextureRepeat("steel01.bmp"));
			}
			}
			break;
	case 2:
		for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			world->objectPtrs[i]->setTexture(LoadGLTextureRepeat("b1.bmp"));
			}
			}
			break;
	case 3:
		for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			world->objectPtrs[i]->setTexture(LoadGLTextureRepeat("b19.bmp"));
			}
			}
			break;
	case 4:
		for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			world->objectPtrs[i]->setTexture(LoadGLTextureRepeat("b7.bmp"));
			}
			}
			break;
      case 5:
		for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			world->objectPtrs[i]->setTexture(LoadGLTextureRepeat("panel_01.bmp"));
			}	
			}
            break;
     case 6:
		for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			world->objectPtrs[i]->setTexture(LoadGLTextureRepeat("grass.bmp"));
			}	
			}
            break;
			     case 7:
		for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			world->objectPtrs[i]->setTexture(LoadGLTextureRepeat("cement.bmp"));
			}	
			}
            break;
			     case 8:
		for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			world->objectPtrs[i]->setTexture(LoadGLTextureRepeat("road1.bmp"));
			}	
			}
            break;



	  default:
			break;

	 }
	 
};




void ARMouseHouse::fileMenuCB(int item)
{

     switch (item) {
      case 1:
		 	world->saveWorld("myworld.txt");
            break;
      case 2:
		 	world->exportSL("SLFile.txt");
            break;
	  default:
			break;

	 }
};




int ARMouseHouse::GetOGLPos(int x, int y, float pos[])
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	pos[0] = posX; pos[1] = posY; posZ = pos[2];

	return 1;
}



int ARMouseHouse::endDrag(int button, int x, int y){
	std::cout<<"end drag"<<std::endl;

	selectionRect(specialKey);

	return 0;
}

int ARMouseHouse::initDrag(int button, int x, int y){
	lastX = x;
	lastY = y;
	lastButton = button;

	float pos[3];
	GetOGLPos(x, y, pos);
	std::cout<<"Drag Started at : ["<<x<<" "<<y<<" ]"<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<std::endl;


	nothingSelected = 1;




	for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			//std::cout<<"Object "<<i<<" selected:"<<" moving "<<xMove<<" "<<yMove<<std::endl;
			world->objectPtrs[i]->initSelection(lastButton, specialKey, x,y);
			 nothingSelected = 0;
		}

	}

	if (nothingSelected){
			x1Rect = x;
			y1Rect = y;
			x2Rect = x;
			y2Rect = y;

	}


	return 1;
}



/*mouse motion callback - for dragging */
void ARMouseHouse::motionCB(int x, int y)
{
	//if an object is being dragged, move the object

		if ((x == lastX) && (y == lastY)) return;

	int xMove = x - lastX; int yMove = y - lastY;
	lastX = x; lastY = y;

	double wa, wb, wc;
		double rotMat[3][3];
		object::getRotFromTrans(patt_trans, rotMat);
		arGetAngle(rotMat, &wa, &wb, &wc);

		std::cout<<"Angles "<<180/3.14159*wa<<" "<<180/3.14159*wb<<" "<<180/3.14159*wc<<std::endl;
		//std::cout<<" Pos: "<<patt_trans[0][3]<<" "<<patt_trans[1][3]<<" "<<patt_trans[2][3]<<std::endl;

		int nothingSelected = 1;

		if (world->isSelected == 1){
			world->move(patt_trans, lastButton, specialKey, xMove, yMove);
			nothingSelected = 0;
		}

	for (int i =0; i < (int) world->objectPtrs.size(); i++){
		if (world->objectPtrs[i]->isSelected == 1){
			std::cout<<"Object "<<i<<" selected:"<<" moving "<<xMove<<" "<<yMove<<std::endl;
			world->objectPtrs[i]->move(patt_trans, lastButton, specialKey, xMove, yMove);
			nothingSelected = 0;
		}
		
	}

			x2Rect = x;
			y2Rect = y;

	



}

void ARMouseHouse::drawSelectionRect(){

	GLint viewport[4];
			glGetIntegerv( GL_VIEWPORT, viewport );

	float winX1 = (float)x1Rect;
	float winY1 = (float)viewport[3] - (float)y1Rect;
	float winX2 = (float)x2Rect;
	float winY2 = (float)viewport[3] - (float)y2Rect;

			
			glMatrixMode (GL_PROJECTION); glPushMatrix (); glLoadIdentity ();
	// Viewing transformation.
   glOrtho(0.0,   // left
           1.0,   // right
           0.0,   // bottom
           1.0,   // top
           1.0,  // near
           -1.0);  // far
glMatrixMode (GL_MODELVIEW); glPushMatrix (); glLoadIdentity ();
			//std::cout<<"Selection RECt: "<<winX1/viewport[2]<<" "<<winY1/viewport[3]
			//<<" "<<winX2/viewport[2]<<" "<<winY2/viewport[3]<<std::endl;

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glRectf(winX1/viewport[2], winY1/viewport[3],winX2/viewport[2], winY2/viewport[3]);
	  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//  glBegin(GL_POLYGON);
    //  glVertex2d(0.25, 0.25);
     // glVertex2d(0.75, 0.25);
     // glVertex2d(0.75, 0.75);
     // glVertex2d(0.25, 0.75);
   //glEnd();
			glMatrixMode (GL_MODELVIEW);
			glPopMatrix();

			glMatrixMode (GL_PROJECTION);
				glPopMatrix();

				 
}



void ARMouseHouse::initMenu(){

	int submenu1, submenu2, submenu3, submenu4, mainMenu;

	submenu1 = glutCreateMenu(::menuCB);
	glutAddMenuEntry("Chair", 1);
	glutAddMenuEntry("TV", 2);
	glutAddMenuEntry("Bed", 3);
	glutAddMenuEntry("Toilet", 4);
	glutAddMenuEntry("Sink", 5);
	glutAddMenuEntry("Sheep", 6);
	glutAddMenuEntry("Desk", 7);
	glutAddMenuEntry("Sofa", 8);
	glutAddMenuEntry("Stairs", 9);
	glutAddMenuEntry("Kitchen Table", 10);
	glutAddMenuEntry("Shelf", 11);
	glutAddMenuEntry("Door", 12);
	glutAddMenuEntry("Window", 13);

	submenu2 = glutCreateMenu(::colorMenuCB);
	glutAddMenuEntry("Red", 1);//
	glutAddMenuEntry("Blue", 2);//
	glutAddMenuEntry("Green", 3);//


	submenu3 = glutCreateMenu(::fileMenuCB);
	glutAddMenuEntry("Save", 1);//
	glutAddMenuEntry("Export to SL", 2);//
	//glutAddMenuEntry("Green", 3);//

	submenu4 = glutCreateMenu(::textureMenuCB);
	glutAddMenuEntry("None", 0);//
	glutAddMenuEntry("Steel", 1);//
	glutAddMenuEntry("Checkers", 2);//
	glutAddMenuEntry("Red Checkers",3);//
	glutAddMenuEntry("Beige Marble", 4);//
	glutAddMenuEntry("Wood", 5);//
	glutAddMenuEntry("Grass", 6);//
	glutAddMenuEntry("Cement", 7);//
	glutAddMenuEntry("Road", 8);//

	mainMenu = glutCreateMenu(::menuCB);
	glutAddSubMenu("File", submenu3);
	glutAddSubMenu("Models", submenu1);
	glutAddSubMenu("Colors", submenu2);//
	glutAddSubMenu("Texture", submenu4);//


	glutAttachMenu(GLUT_RIGHT_BUTTON);

}


void ARMouseHouse::mouseCB(int button, int state, int x, int y) {
	if (useGLUTGUI) {
		mouseCBwithModifier(button, state, x, y, glutGetModifiers());
	}
}

void ARMouseHouse::mouseCBwithModifier(int button, int state, int x, int y, int modifier) {
	specialKey = modifier;
	if (state == GLUT_DOWN){
		//if (selectRectDefined == 0){
		for (int i =0; i < (int) world->objectPtrs.size(); i++){
			world->objectPtrs[i]->isSelected = 0;
		}
		world->isSelected = 0;	
		//}

		std::cout << "Clicked " << x << " " << y << endl;
		selection(modifier, x, y);
		initDrag(button, x, y);
	}

	if (state == GLUT_UP){
		if (nothingSelected)
			endDrag(button, x,y);
	}
}

int ARMouseHouse::keyMapping(unsigned char key) {
	switch (key) {
		case 'r': return ObjectTypes::RECTANGLE;
		case 'e': return ObjectTypes::TRIANGLE;
		case 'a': return ObjectTypes::FILLARC;
		case 'p': return ObjectTypes::PARTIALCYLINDER;
		case 's': return ObjectTypes::SPHERE;
		case 'b': return ObjectTypes::CUBE;
		case 't': return ObjectTypes::CYLINDER;
		case 'c': return ObjectTypes::CONE;
		case 'o': return ObjectTypes::PYRAMID;
		case 'l': return ObjectTypes::LINE;
		case 'w': return ObjectTypes::WALL;
		case 'h': return ObjectTypes::TORUS;
		default: return -1;
	}
}
void ARMouseHouse::addObject(int objectType) {
	world->addObject(objectType);
}

void ARMouseHouse::cycleTransparency() {
	std::cout<<"transparent"<<std::endl;

	int i = 0;
	for (std::vector<object *>::iterator it = world->objectPtrs.begin(); it!=world->objectPtrs.end();) {
		if ( (*it)->isSelected  == 1)
		{

			if ((*it)->drawMode == NORMAL)
				(*it)->drawMode = WIREFRAME;
			else
				if ((*it)->drawMode == WIREFRAME)
					(*it)->drawMode = TRANSPARENT;
				else
					(*it)->drawMode = NORMAL;


			it++;
		}
		else ++it;
	}
}
void ARMouseHouse::setDrawVideo(bool value)
{
	drawVideo = value;
}

void ARMouseHouse::keyboardCB(unsigned char key_in, int x, int y)
{
	unsigned char key = tolower(key_in); // convert to lower case (for non-GLUT interface)
	int nObjects = (int) world->objectPtrs.size();

	/* quit if the ESC key is pressed */
	if( key == 0x1b ) {
		printf("*** %f (frame/sec)\n", (double)ar_count/arUtilTimer());
		if (useGLUTGUI) {
			ar_cleanup();
			exit(0);
		}
	}


	std::cout<<"Key: "<<key<<std::endl;


	// handle most object types
	int objectType = keyMapping(key);
	if (objectType > 0)	addObject(objectType);

	if( key == 'm' ) {
		std::cout<<"new mouse"<<std::endl;
		world->addObject(new myModel(nObjects, "mouse2.ms3d", 0,0,0,0,1.5));	
	}


	if( key == 'd' ) {
		std::cout<<"copy"<<std::endl;

		int i = 0;
		for (std::vector<object *>::iterator it = world->objectPtrs.begin(); it!=world->objectPtrs.end();) {
			if ( (*it)->isSelected  == 1)
			{
				std::cout<<"copying "<<i<<std::endl;
				it = world->objectPtrs.insert(world->objectPtrs.end(), ((*it)->clone()) );
				it++;
			}
			else ++it;
		}
	}


	if( key == 'g' ) {
		std::cout<<"group"<<std::endl;

		std::vector<object *> newGroup;

		//ungroup all grouped objects that are selected
		int i = 0;
		for (std::vector<object *>::iterator it = world->objectPtrs.begin(); it!=world->objectPtrs.end();) {
			if ( (*it)->isSelected  == 1)
			{
				std::cout<<"ungrouping "<<i<<std::endl;
				std::vector<object *> group = (*it)->ungroup();
				if (!group.empty()){
					//std::back_insert_iterator<std::vector<object *> >(world->objectPtrs)
					copy(group.begin(), group.end(), std::back_insert_iterator<std::vector<object *> >(world->objectPtrs));
					it = world->objectPtrs.erase(it++);
				}
				else ++it;
			}
			else ++it;
		}

		i = 0;
		for (std::vector<object *>::iterator it = world->objectPtrs.begin(); it!=world->objectPtrs.end();) {
			if ( (*it)->isSelected  == 1)
			{
				std::cout<<"Adding to group "<<i<<std::endl;
				newGroup.push_back((*it)->clone());
				//++it;
				it = world->objectPtrs.erase(it++);
			}
			else ++it;
		}


		//multiShape * myMulti = new multiShape(newGroup);
		world->addObject(new multiShape(newGroup, 0,0,0,0,0,0,1,1,1));
	}

	if( key == 'u' ) {
		std::cout<<"ungroup"<<std::endl;
		//if any of the selected objects is a multiShape
		//take the objects from the shapePtrs vector and put into the world vector
		//then destroy the multishape

		int i = 0;
		for (std::vector<object *>::iterator it = world->objectPtrs.begin(); it!=world->objectPtrs.end();) {
			if ( (*it)->isSelected  == 1)
			{
				std::cout<<"ungrouping "<<i<<std::endl;
				std::vector<object *> group = (*it)->ungroup();
				if (!group.empty()){

					//std::back_insert_iterator<std::vector<object *> >(world->objectPtrs)
					copy(group.begin(), group.end(), std::back_insert_iterator<std::vector<object *> >(world->objectPtrs));
					it = world->objectPtrs.erase(it++);
				}
				else ++it;
			}
			else ++it;
		}
	}

	// backspace (8) or delete (46) (seems like GLUT doesn't send 46 through this callback)
	if( key == 8 || key == 46) {
		std::cout<<"deleting"<<std::endl;
		//for (int i = 0; i< world->objectPtrs.size(); i++){

		int i = 0;
		for (std::vector<object *>::iterator it = world->objectPtrs.begin(); it!=world->objectPtrs.end();) {
			if ( (*it)->isSelected  == 1)
			{
				std::cout<<"deleting "<<i<<std::endl;
				it = world->objectPtrs.erase(it++);

			}
			else ++it;

		}

	}

	if( key == 'i' ) { cycleTransparency();}


	/*
	if (key == 'i'||key == 'j'||key == 'k'||key == 'l'){
		int xMove = 0;
		int yMove = 0;
		if (key == 'i') yMove = 5;
		if (key == 'k') yMove = -5;
		if (key == 'j') xMove = 5;
		if (key == 'l') xMove = -5;


		for (std::vector<object *>::iterator it = world->objectPtrs.begin(); it!=world->objectPtrs.end();) {
			if ( (*it)->isSelected  == 1)
			{
				(*it)->move(xMove, yMove);
				it++;
			}
			else ++it;
		}

	}
	*/
}

/**
 * Creates a new world. Just like that.
 */
void ARMouseHouse::newWorld() {
	if (world) delete world;
	world = new World();
}

/**
 * Creates a new world from a file. Just like that.
 *
 * Returns true if successful, false otherwise.
 */
bool ARMouseHouse::newWorld(string fileName) {
	if (world) delete world;
	world = new World();
	// TODO: add code for checking if unsuccessful
	return world->loadWorld(fileName);
}
