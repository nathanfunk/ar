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
#define VIEW_DISTANCE_MIN		100.0			// Objects closer to the camera than this will not be displayed.
#define VIEW_DISTANCE_MAX		5000.0		// Objects further away from the camera than this will not be displayed.

namespace ms3dglut {

class ARMouseHouse {
private:
	int		video_w, video_h;		// size of the video stream
	int		vpOffsetX, vpOffsetY;	// the offset of the viewport
	int		thresh;
	int		ar_count;				// counter for determining FPS
	int		fps;					// last calculated FPS value

	ARUint8					*ARTImage;		// current image
	char					*cparam_name;
	ARParam					 cparam;		// camera parameters
	ARGL_CONTEXT_SETTINGS_REF arglSettings;

	char	*patt_name;
	double	patt_width;
	double	patt_center[2];
	double	patt_trans[3][4];

	int		patt_id;
	int		patt_found;

	int		lastButton;
	int		specialKey;

	World	*world;
	bool	useGLUTGUI;
	bool	drawVideo;
	int		gotImage;

public:
	ARMouseHouse(bool useGLUTGUI);
	~ARMouseHouse();
	bool idleCB();
	void reshapeCB( int width , int height );
	void arrowKeysCB( int a_keys, int x, int y );
	void initMenu();
	void menuCB(int item);
	void colorMenuCB(int item);
	void textureMenuCB(int item);
	void fileMenuCB(int item);
	void displayCB(void);
	void motionCB(int x, int y);
	void mouseCB(int button, int state, int x, int y);
	void mouseCBwithModifier(int button, int state, int x, int y, int modifier);
	int getFPS();
	void keyboardCB( unsigned char key, int x, int y);
	void InitGL ( GLvoid );
	int  ar_init( void );
	void ar_cleanup(void);
	World *getWorld() {return world;}
	void LoadWorld();
	void setTexture(std::string modelName);
	void addObject(int objectType);
	void addObject(std::string modelName);
	void setColors(float r, float g, float b);
	void cycleTransparency();
	void setDrawVideo(bool value);
	void newWorld();
	bool newWorld(string fileName);

private:
	void ar_draw( void );
	int selection(int key, int mouse_x, int mouse_y);
	int selectionRect(int key);
	int GetOGLPos(int x, int y, float pos[]);
	int initDrag(int button, int x, int y);
	void drawSelectionRect();
	int endDrag(int button, int x, int y);
	int keyMapping(unsigned char key);

};

}
#endif