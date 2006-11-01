/*
ARMOUSEHOUSE Augmented Reality Mouse House
Created by Farooq Ahmad Sept. 2006
*/

#ifndef ARMOUSEHOUSE_H
#define ARMOUSEHOUSE_H

#include <gl/glut.h>   // The GL Utility Toolkit (Glut) Header

#include <AR/gsub_lite.h>
#include <AR/video.h>
#include <AR/param.h>
#include <AR/ar.h>

#include "Timer.h"
#include "MilkshapeModel.h"
#include "glbmp.h"
#include "myModel.h"
#include "world.h"

//ARToolkit stuff
/*#ifdef _WIN32
char		*vconf = "Data\\WDM_camera_flipV.xml";
#else
char		*vconf = "";
#endif*/

#define VIEW_SCALEFACTOR		1.0			// 1.0 ARToolKit unit becomes 0.025 of my OpenGL units.
#define VIEW_DISTANCE_MIN		0.1			// Objects closer to the camera than this will not be displayed.
#define VIEW_DISTANCE_MAX		10000.0		// Objects further away from the camera than this will not be displayed.

namespace ms3dglut {

class ARMouseHouse {
private:
	int		xsize, ysize;
	int		thresh;
	int		ar_count;

	ARUint8					*gARTImage; // current image
	char					*gCparam_name;
	ARParam					 gCparam;				// camera parameters
	ARGL_CONTEXT_SETTINGS_REF gArglSettings;

	char	*gPatt_name;
	double	gPatt_width;
	double	gPatt_center[2];
	double	gPatt_trans[3][4];

	int		gPatt_id;
	int		gPatt_found;

	int		lastButton;
	int		specialKey;

	World	world;
	bool	useGLUTGUI;
public:
	ARMouseHouse(bool useGLUTGUI);
	~ARMouseHouse();
	bool idleCB();
	void reshapeCB( int width , int height );
	void arrowKeysCB( int a_keys, int x, int y );
	//void initMenu();
	//void menuCB(int item);
	//void colorMenuCB(int item);
	//void textureMenuCB(int item);
	//void fileMenuCB(int item);
	void displayCB(void);
	void motionCB(int x, int y);
	void mouseCB(int button, int state, int x, int y);
	void keyboardCB( unsigned char key, int x, int y);
	void InitGL ( GLvoid );
	void ar_init( void );
	void ar_cleanup(void);
	World *getWorld() {return &world;}
private:
	void ar_draw( void );
	int selection(int key, int mouse_x, int mouse_y);
	int ARMouseHouse::selectionRect(int key);
	int GetOGLPos(int x, int y, float pos[]);
	int initDrag(int button, int x, int y);
	void drawSelectionRect();
	int endDrag(int button, int x, int y);
	int keyMapping(unsigned char key);
};

}
#endif