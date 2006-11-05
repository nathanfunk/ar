/*
ARMOUSEHOUSE Augmented Reality Mouse House
Created by Farooq Ahmad Sept. 2006
3D shape primitives - Derived Classes from object class in object.h

*/

#ifndef SHAPECLASSES_H
#define SHAPECLASSES_H

extern int lastX;
extern int lastY; 

#include "object.h"
#include "sphere.h"
#include "cube2.h"
#include "room.h"
#include "wall.h"
//#include "wall2.h"
#include "rectangle.h"
#include "cone.h"
#include "triangle.h"
#include "pyramid.h"
#include "cylinder.h"
#include "torus.h"
#include "partialCylinder.h"
#include "line.h"
#include "fillArc.h"
#include "multiShape.h"





/*
class partialSphere:public object{
public:
	partialCylinder(){ 
	
	};
	partialCylinder(int _name, float _x, float _y,  float _rad,float _height, float _startAngle1, float _arcAngle1, 
		float _startAngle2, float _arcAngle2, float _r)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; xOff = _x; yOff = _y;  radius= _rad; height = _height;
		startAngle2 = PI/180*_startAngle1; arcAngle1 = PI/180*_arcAngle1;
		startAngle2 = PI/180*_startAngle2; arcAngle2 = PI/180*_arcAngle2;
		rX = 0; sX = 1; sY = 1; sZ= 1; isVisible = 1; rY = _r;
		xOff = 0; yOff = 0; zOff = 0; r3 = 0;
	}

	partialSphere* clone()   { std::cout<<"partialSphere clone"<<std::endl; return new partialSphere(*this); }


virtual void move(double patt_trans[3][4],int but, int key, int x, int y){
		
		double xNew, yNew;
			getTransformedMotion(patt_trans, but, key, x, y, xNew, yNew);



		if (key == GLUT_ACTIVE_ALT){
		if (but == GLUT_LEFT_BUTTON){
		sX += (float)x / 25; sZ -= (float)y / 25; //yOff += y;
		}

		else if (but == GLUT_MIDDLE_BUTTON){
		 //sX -= (float)y / 25; sZ -= (float)y / 25; 
			sY += (float) y/ 15;
			arcAngle -= (float)x / 15;
		}
		}
	else if (key == GLUT_ACTIVE_CTRL){
		if (but == GLUT_LEFT_BUTTON){
		rX += x; rY-=y; //yOff += y;
		}

		else if (but == GLUT_MIDDLE_BUTTON){
		rY-=y;r3+=x;
		}
		}


		else{


		if (but == GLUT_LEFT_BUTTON){
		xOff += xNew; zOff += yNew;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 yOff -= y;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 rX += x; rY+= y;//sOff += y;
		}
		}

	}



	void	draw(){
	if (isVisible == 1){
	if (isSelected == 1){
		highlight();
	}
	//glPushName(name);

	int n = 100;

	glPushMatrix();		
		glTranslatef(xOff,yOff ,zOff);
		//move to center
		
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
glRotatef(r3,0,0,1);


		glScalef(sX, sZ, sY);
		startLighting(mat_ambient);
		

int stack,slice;
int stacks = 50;
int slices = 50;

  GLdouble dangle,dradius,dheight;
  GLdouble normCo, normZ;

	float baseR = radius;
	float topR = radius;

  dangle  = 360.0/slices;
  dradius = (baseR-topR)/stacks;
  dheight = 360.0/stacks;

  normZ = cos(atan(height/abs(topR-baseR)));
  normCo = sqrt(1-normZ*normZ);
	
  
  float pheta;
	float angle_increment =  PI_2 / slices;

  for(stack=0; stack<stacks ; ++stack) {
    glBegin(GL_QUAD_STRIP); {
    

for (pheta = startAngle1; pheta - (startAngle1 + arcAngle1)
                          < 0.001; pheta += angle_increment)
    {

for (zeta = startAngle2; zeta - (startAngle2 + arcAngle2)
                          < 0.001; zeta += angle_increment)
    {

        //x = width/2 * cos (pheta);
        //y = height/2 * sin (pheta);
        //glVertex2f (x, y);
		float y1 = topR * cos(pheta);
		float x1 = topR * sin(pheta);
		
		float y2 = topR * cos(zeta);
		float x2 = topR * sin(zeta);

		glVertex3f(y1,x1, height- stack   *dheight);
		glVertex3f(y1,x1, height-(stack+1)*dheight);

}



	}

	}
	
	glEnd();
  }



	glDisable ( GL_LIGHTING ) ;
	glPopMatrix();
	//glPopName();
	}
	}
	float radius, height, startAngle, arcAngle, r3;
};
*/


#endif