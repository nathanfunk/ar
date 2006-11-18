#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <gl/glaux.h>
//#include "bmp.h"

AUX_RGBImageRec *myAuxDIBImageLoad(const char *Filename);
AUX_RGBImageRec *LoadBMP(const char *Filename);
GLuint LoadGLTexture( const char *filename );
GLuint LoadGLTextureRepeat( const char *filename );

#endif