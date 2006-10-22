/*
ARMOUSEHOUSE Augmented Reality Mouse House
Created by Farooq Ahmad Sept. 2006
*/

#ifndef ARMOUSEHOUSE_H
#define ARMOUSEHOUSE_H


//ARToolkit stuff
#ifdef _WIN32
char		*vconf = "Data\\WDM_camera_flipV.xml";
#else
char		*vconf = "";
#endif

#define VIEW_SCALEFACTOR		1.0			// 1.0 ARToolKit unit becomes 0.025 of my OpenGL units.
#define VIEW_DISTANCE_MIN		0.1			// Objects closer to the camera than this will not be displayed.
#define VIEW_DISTANCE_MAX		10000.0		// Objects further away from the camera than this will not be displayed.

int			xsize, ysize;
int			thresh = 100;
int			ar_count = 0;

static ARUint8					*gARTImage		= NULL; // current image
char							*gCparam_name	= "Data/camera_para.dat";
ARParam							 gCparam;				// camera parameters
static ARGL_CONTEXT_SETTINGS_REF gArglSettings	= NULL;

char	*gPatt_name		= "Data/patt.triangle";
double	gPatt_width		= 80.0;
double	gPatt_center[2]	= {0.0, 0.0};
double	gPatt_trans[3][4];
int		gPatt_id;
int		gPatt_found		= false;

int		lastButton;
int		specialKey;

/*
#pragma comment( lib, "opengl32.lib" )	// Search For OpenGL32.lib While Linking ( NEW )
#pragma comment( lib, "glu32.lib" )		// Search For GLu32.lib While Linking    ( NEW )
#pragma comment( lib, "glaux.lib" )		// Search For GLaux.lib While Linking    ( NEW )
*/
using namespace std;
World w1("myworld.txt");
//World w1;


AUX_RGBImageRec *LoadBMP(const char *Filename);
GLuint LoadGLTexture( const char *filename );
GLuint LoadGLTextureRepeat( const char *filename );
static void ar_cleanup(void);
void InitGL ( GLvoid );
void display ( void );
static void ar_draw( void );
static void displayCB(void);
void idleCB();
void reshapeCB( int width , int height );
void arrowKeysCB( int a_keys, int x, int y );
static void ar_init( void );
/* cleanup function called when program exits */
static void startLighting(GLfloat (&mat_ambient)[4]);
static void startLighting2(void);
/* Allow picking with the mouse
 picking code from http://www.hitlabnz.org/forum/archive/index.php/t-55.html
 */
int selection(int key, int mouse_x, int mouse_y);
void menuCB(int item);
void colorMenuCB(int item);
void textureMenuCB(int item);
void fileMenuCB(int item);
int GetOGLPos(int x, int y, float pos[]);
int initDrag(int button, int x, int y);
/*mouse motion callback - for dragging */
static void motionCB(int x, int y);
static void initMenu();
static void mouseCB(int button, int state, int x, int y);
static void keyboardCB( unsigned char key, int x, int y);
int main ( int argc, char** argv );

#endif