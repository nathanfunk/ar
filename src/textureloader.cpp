#include <fstream>
#include <iostream>
#include <gl/glaux.h>
//#include "bmp.h"

/**
 * Added by Nathan. Probably actually in bmp.h. Remove this when
 * bmp.h is added to the directory.
 */
AUX_RGBImageRec *myAuxDIBImageLoad(const char *Filename)
{
	return NULL;
}

AUX_RGBImageRec *LoadBMP(const char *Filename)						// Loads A Bitmap Image
{
	FILE *File=NULL;												// File Handle

std::cout<<"file: "<<Filename<<std::endl;

	if (!Filename)													// Make Sure A Filename Was Given
	{
		return NULL;												// If Not Return NULL
	}

	fopen_s(&File, Filename,"r");									// Check To See If The File Exists


	

	if (File)														// Does The File Exist?
	{
		fclose(File);												// Close The Handle
		return myAuxDIBImageLoad(Filename);							// Load The Bitmap And Return A Pointer
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
