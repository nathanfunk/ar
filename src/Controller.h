/*
Created by Farooq Ahmad Sept. 2006
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H

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

class Tools {
public:
	static const int MOVE = 0;
	static const int ROTATE = 1;
	static const int SCALE = 2;
};

class Controller {
private:
	int		video_w, video_h;		// size of the video stream
	int		vpOffsetX, vpOffsetY;	// the offset of the viewport
	int		thresh;
	int		ar_count;				// counter for determining FPS
	int		fps;					// last calculated FPS value
	bool	nothingSelected;		// flag whether any object is selected
	bool	selectionBoxMode;		// true if currently dragging a selection box around objects

	ARUint8					*ARTImage;		// current image
	ARParam					 cparam;		// camera parameters
	ARGL_CONTEXT_SETTINGS_REF arglSettings;

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
	int		currentTool;
	int		gotImage;

public:
	Controller(bool useGLUTGUI);
	~Controller();
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
	int getMarkerStatus();
	void keyboardCB( unsigned char key, int x, int y);
	void InitGL(GLvoid);
	int  ar_init(const string &exeDir);
	void ar_cleanup(void);
	World *getWorld() {return world;}
	void LoadWorld();
	void setTexture(const string &modelName);
	void addObject(int objectType);
	void addObject(const string &modelName);
	void setColors(float r, float g, float b);
	void cycleTransparency();
	void setDrawVideo(bool value);
	void setRotateMode(bool value);
	void newWorld();
	bool newWorld(const string &fileName);
	void setCurrentTool(int tool) {currentTool = tool;}
	int getCurrentTool() {return currentTool;}
	void group();
	void ungroup();
	void selectAll();

private:
	string buildConfigString(bool showDialog, bool setRes, int resX, int resY);
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