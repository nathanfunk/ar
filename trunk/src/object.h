#ifndef OBJECT_H
#define OBJECT_H


#define NORMAL 0
#define TRANSPARENT 1
#define WIREFRAME 2
#define OUTLINE 3
/*
ARMOUSEHOUSE Augmented Reality Mouse House
Created by Farooq Ahmad Sept. 2006
Object class - base class for shape primitives in shapeClasses.h
and milkshape model class in myModel.h
*/

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <AR/ar.h>
#include <GL/glut.h>

#include "ISubject.h"
#include "Matrix.h"

#ifndef PI
#	define PI	3.1415926535897932384626433832795
#endif
#define PI_2	PI * 2
#ifndef RADIANS
#define RADIANS(x) ((x)/180.0*3.14159265358979323)
#endif // RADIANS

extern int lastX, lastY;

/* Shape primitives for ARMouseHouse
Farooq Ahmad 2006
*/


class vertex{
public:

	vertex(){x = 0; y = 0; z = 0;}
	vertex(float _x, float _y, float _z){
		x = _x; y = _y; z = _z;
	};

	float x, y, z;
};

class ObjectTypes {
public:
	static const int MS3D		= 0;
	static const int TRIANGLE	= 1;
	static const int RECTANGLE	= 2;
	static const int SPHERE		= 3;
	static const int CUBE		= 4;
	static const int PYRAMID	= 5;
	static const int CONE		= 6;
	static const int CYLINDER	= 7;
	static const int PARTIALCYLINDER = 8;
	static const int FILLARC	= 9;
	static const int LINE		= 10;
	static const int WALL		= 11;
	static const int TORUS		= 12;
};



class object : public ISubject {
public:
	object(){
//		xOff = 0; yOff = 0; zOff = 0;
		rX = 0; rY = 0; rZ = 0;
		sX = 1; sY = 1; sZ = 1;

		std::cout<<"Object constructor 1"<<std::endl;
		//pxOff = 0; pyOff = 0; pzOff = 0;
		//prX = 0; prY =0; prZ = 0;
		//psX = 1; psY = 1; psZ = 1;


		isVisible = 1; isSelected = 0;
		setColors(1.0, 1.0, 1.0, 1.0); //default colour is white
		quadratic =  gluNewQuadric();
		texture = 0;

		minI = 0;
		drawMode = NORMAL;
		tMatrix.loadIdentity();
		rotMat.loadIdentity();
		scaleMat.loadIdentity();

	};

	object(float _xOff, float _yOff, float _zOff, float _rX, float _rY, float _rZ, 
		float _sX, float _sY, float _sZ){
		//xOff = _xOff; yOff = _yOff;  zOff = _zOff; 
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ= _sZ;


		std::cout<<"Object constructor 2"<<std::endl;
		quadratic =  gluNewQuadric();

		texture = 0;
		minI = 0;

		drawMode = NORMAL;
		tMatrix.loadIdentity();
		tMatrix.translate(_xOff, _yOff, _zOff);

		rotate(_rX,1,0,0);
		rotate(_rY,0,1,0);
		rotate(_rZ,0,0,1);

		scaleMat.loadIdentity();
		//scale(_sX,_sY, _sZ);
	}

	object(GLfloat _objTrans[16]){
		//objTrans = _objTrans;

		std::memcpy(&objTrans, &_objTrans, sizeof(objTrans));
	}

	object(PL3D::Matrix _tMatrix){
		//objTrans = _objTrans;

		std::memcpy(&tMatrix, &_tMatrix, sizeof(objTrans));
	}

	virtual object::~object() {
		OutputDebugStr("Inside object destructor\n");
		gluDeleteQuadric(quadratic);
	}


	virtual object * clone(){

		std::cout<<" OBJECT CLONE "<<std::endl;
		return new object(*this);
	};

	float xOff() {
		const float *matrix = tMatrix.getMatrix();
		return matrix[12];
	}
	float yOff() {
		const float *matrix = tMatrix.getMatrix();
		return matrix[13];
	}
	float zOff() {
		const float *matrix = tMatrix.getMatrix();
		return matrix[14];
	}

	static void getRotFromTrans(double patt_trans[3][4], double (&rotMat)[3][3]){
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				rotMat[i][j]  = patt_trans[i][j];
			}
		}
	}

	int getTransformedMotion( double patt_trans[3][4], int but, int key,int x, int y, double &xNew, double &yNew){
		//		double wa, wb, wc;
		double rotMat[3][3];

		double mouseMat[3];

		getRotFromTrans(patt_trans, rotMat);
		//arGetAngle(rotMat, &wa, &wb, &wc);
		arGetAngle(rotMat, &mouseMat[0], &mouseMat[1], &mouseMat[2]);


		//std::cout<<"Angles "<<180/3.14159*wa<<" "<<180/3.14159*wb<<" "<<180/3.14159*wc;
		//std::cout<<" Pos: "<<patt_trans[0][3]<<" "<<patt_trans[1][3]<<" "<<patt_trans[2][3]<<std::endl;

		//std::cout<<x<<" "<<y<<" "<<180/3.14159*wc;	
		xNew = (x*cos(mouseMat[2]) - y * sin(mouseMat[2]));
		yNew = (x*sin(mouseMat[2]) + y * cos(mouseMat[2]));

		//std::cout<<"new: "<<xNew<<" "<<yNew<<"sin(wc)"<<sin(wc)<<std::endl;	
		return 1;
	}


	int getTransformedMotion( double patt_trans[3][4], int but, int key,int x, int y, float _rX, float _rY, 
		float _rZ, double &xNew, double &yNew){

			double wa, wb, wc;
			double rotMat[3][3];
			getRotFromTrans(patt_trans, rotMat);
			arGetAngle(rotMat, &wa, &wb, &wc);

			float rxRad = RADIANS(_rX);
			float ryRad = RADIANS(_rY);
			float rzRad = RADIANS(_rZ);


			//std::cout<<"Angles "<<180/3.14159*wa<<" "<<180/3.14159*wb<<" "<<180/3.14159*wc;
			//std::cout<<" Pos: "<<patt_trans[0][3]<<" "<<patt_trans[1][3]<<" "<<patt_trans[2][3]<<std::endl;

			//std::cout<<x<<" "<<y<<" "<<180/3.14159*wc;	
			xNew = (x*cos(wc) - y * sin(wc))*cos(wb);
			yNew = (x*sin(wc) + y * cos(wc));
			//std::cout<<"new: "<<xNew<<" "<<yNew<<"sin(wc)"<<sin(wc)<<std::endl;	
			return 1;
	}


/*
	virtual std::vector<vertex> boundingBox(){
		std::vector<vertex> bbox;
		float xOff = tMatrix.

		bbox.push_back(vertex(xOff - abs(sX*XYSize), yOff - abs(sY*XYSize), zOff - abs(sZ*ZSize)));
		bbox.push_back(vertex(xOff + abs(sX*XYSize), yOff + abs(sY*XYSize), zOff - abs(sZ*ZSize)));

		//bbox.push_back(vertex(sX*XYSize, sY*XYSize, sZ*ZSize));
		//bbox.push_back(vertex(-sX*XYSize, -sY*XYSize, -sZ*ZSize));
		return bbox;
	};*/


	int getTransformedMotion( double patt_trans[3][4], int but, int key,int x, int y, 
		float _rZ, double &xNew, double &yNew){
			double wa, wb, wc;
			double rotMat[3][3];
			getRotFromTrans(patt_trans, rotMat);
			arGetAngle(rotMat, &wa, &wb, &wc);

			float rzRad = RADIANS(_rZ);


			std::cout<<"Total angle :"<<180/PI*wc<< " + "<<_rZ<< " = "<<180/PI*wc + _rZ;
			//std::cout<<"Angles "<<180/3.14159*wa<<" "<<180/3.14159*wb<<" "<<180/3.14159*wc;
			//std::cout<<" Pos: "<<patt_trans[0][3]<<" "<<patt_trans[1][3]<<" "<<patt_trans[2][3]<<std::endl;

			//std::cout<<x<<" "<<y<<" "<<180/3.14159*wc;	
			xNew = 1*(x*cos(wc+rzRad) - y * sin(wc+rzRad));
			yNew = 1*(x*sin(wc+rzRad) + y * cos(wc+rzRad));
			std::cout<<"new: "<<xNew<<" "<<yNew<<"sin(wc)"<<sin(wc)<<std::endl;	
			return 1;
	}


	/**
	Sets the color of the object, while preserving the alpha value.
	*/
	void setColors(GLfloat c1, GLfloat c2, GLfloat c3){

		std::cout<<"Setting colors "<<std::endl;
		mat_ambient[0] = c1;  mat_ambient[1] = c2; mat_ambient[2] = c3;
		notifyObservers();
	}

	void setColors(GLfloat c1, GLfloat c2, GLfloat c3, GLfloat c4){
		mat_ambient[0] = c1;  mat_ambient[1] = c2; mat_ambient[2] = c3; mat_ambient[3] = c4;
		notifyObservers();
	}

	void setTexture(GLuint _texture){
		if (_texture == 0){
			texture = 0;
			return;
		}

		texture = _texture;
		//glBindTexture( GL_TEXTURE_2D, texture );

		notifyObservers();
	}

	void drawTopLevel(float snapPos, float snapRot, float snapScale){

		glPushMatrix();		

		glEnable(GL_DEPTH_TEST);
		if (drawMode == TRANSPARENT){
			glEnable (GL_BLEND); 
			glColor4f(0.85, 0.1, 0.1, 0.4f);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE);
		}

		if (drawMode == WIREFRAME){
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		if (isSelected == 1){
			highlight();

		}
		//startLighting(mat_ambient);

		if (texture != 0) {	
			glEnable( GL_TEXTURE_2D );	
			glBindTexture( GL_TEXTURE_2D, texture);
		} else {
			glColor4f(mat_ambient[0], 
				mat_ambient[1], 
				mat_ambient[2], 
				mat_ambient[3]);

			// set material properties
			GLfloat   ambient[]     = {0.2, 0.2, 0.2, 1.0};
			GLfloat   diffuse[]     = {0.8, 0.8, 0.8, 1.0};
			GLfloat   specular[]    = {0.0, 0.0, 0.0, 1.0};

			glMaterialfv( GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv( GL_FRONT, GL_SPECULAR, specular);
			glMaterialf( GL_FRONT, GL_SHININESS, 0.0);
		}

		glPushMatrix();
		glMultMatrixf(tMatrix.getMatrix());

		// apply scaling
		glScalef(sX, sY, sZ);

		// call normal draw
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 1.0);
		draw();
		glDisable(GL_POLYGON_OFFSET_FILL);

		// draw outline if selected
		if (isSelected == 1||drawMode == OUTLINE){
			//draw wireframe
			glDisable(GL_LIGHTING);
			glColor3f (1.0, 1.0, 1.0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			draw();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_LIGHTING);
		}


		glPopMatrix();

		glDisable(GL_BLEND);
		//glDisable ( GL_LIGHTING ) ;
		glDisable( GL_TEXTURE_2D );	
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//if (snap_to_grid == 1)
		snap(snapPos, snapRot, snapScale);
		glPopMatrix();
	}


		virtual void snap(float snapPos, float snapRot, float snapScale){
			/*if (snapPos >0){
			xOff = (int) (xOff / snapPos) * snapPos;
			yOff = (int) (yOff / snapPos) * snapPos;
			zOff = (int) (zOff / snapPos) * snapPos;
			}
				if (snapScale >0){
			sX= (int) (sX/ snapScale) * snapScale;
			sY = (int) (sY / snapScale) * snapScale;
			sZ = (int) (sZ / snapScale) * snapScale;
			}
			*/
		}


		virtual void draw() { };

		virtual std::string getDataString(){ 
			//std::string 
			return std::string("OBJECT ") + "DERIVED CLASS DATA UNDEFINED";
		}

/*		object no longer uses xOff, yOff, zOff
		virtual std::string getSLDataString(){
			std::ostringstream data;
			data<<"<type val=\"0\"> "<<std::endl;
			data<<"<position x=\""<<xOff/100<<"\" y=\""<<yOff/100<<"\" z=\""<<zOff/100<<">"<<std::endl;
			data<<"<rotation x=\""<<PI/180*(rX-90)<<"\" y=\""<<PI/180*rY<<"\" z=\""<<PI/180*rZ<<">"<<std::endl;
			data<<"<size x=\""<<sX<<"\" y=\""<<sY<<"\" z=\""<<sZ<<">"<<std::endl;
			return data.str(); 
		}
*/
/*
		std::string getGlobalDataString(){
			std::ostringstream data;
			data<<"TRANSFORM "<<xOff<<" "<<yOff<<" "<<zOff<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ;	
			data<<"TEXTURE ";
			if(texture !=0) { data<<"NONE";} 
			else {data<<texture;}
			data<<" COLOR ";
			data<<mat_ambient[0]<<" "<<mat_ambient[1]<<" "<<mat_ambient[2]<<" "<<mat_ambient[3];
			return data.str(); 
		}
*/





		virtual void highlight(){
			glDisable(GL_LIGHTING);
			// draw handles for object
			setHandles();

			glPushMatrix();		
			//glTranslatef(xOff,0,zOff);
			glMultMatrixf(tMatrix.getMatrix());
			glPushMatrix();
			//glTranslatef(0,60,0);

			glColor3f(0.8, 0.3, 0.3);
			//glutSolidSphere(3,5,5);

			glPushMatrix();
			glRotatef(-90,1,0,0);
			//gluDisk(quadratic, 0, rad, 15, 15);
			gluCylinder(quadratic, 0.5, 0.5,  500, 15, 15);
			glPopMatrix();

			glRotatef(rX,0,1,0);
			glRotatef(rY,1,0,0);
			glScalef(2,0.5,2);
			//glutWireCube(5);
			glutSolidCube(5);

			glPopMatrix();
			glPopMatrix();
			glEnable(GL_LIGHTING);
		}


		//virtual void initSelection(int but, int key, int x, int y){};

		/**
		 * Initializes selection of an object. This method is called when
		 * a mouse down event is recieved in the controller.
		 */
		virtual void initSelection(int but, int key, int x, int y){

			GLint vPort[4];
			glGetIntegerv( GL_VIEWPORT, vPort ); // sets vPort to (x, y, w, h)

			// convert to openGL coordinates (origin at lower left)
			GLfloat mouseX = (float) lastX;
			GLfloat mouseY = (float)vPort[3] - (float) lastY;

			// check if window coordinates of handles are set
			if (winCoords.empty()) {
				std::cout<<"winCoords empty "<<std::endl;	
				return;
			}

			// get distance to first handle and assume it is closest 
			// to the click point
			min = distance((float) mouseX, (float) mouseY, 
				(float) winCoords[0].x, (float) winCoords[0].y);
			minI = 0;

			// check other handles to find the one closest to the mouse click point
			for (int i = 1; i < (int) winCoords.size(); i++){
				float dist = distance((float) mouseX, (float) mouseY, 
					(float) winCoords[i].x, (float) winCoords[i].y);
				if (dist < min){
					minI = i;		
					min = dist;
				}
			}
			
			std::cout<<"min is "<<min<<" best point is "<<minI<<std::endl;
			std::cout<<"Current pos: "<<getDataString();
		}


		void setHandles(){
			initHandles();
			if (handles.empty()) {return;}
			//set the position of each corner handle
			highlightCorners(); //draw each handle and set the window coordinates
			setWinCoords();
		}




		virtual void initHandles(){};

		void highlightCorners(){
			glPushMatrix();
//			glTranslatef(xOff,yOff,zOff);
			glMultMatrixf(tMatrix.getMatrix());
			//glRotatef(rX,0,1,0);
			//glRotatef(rY,1,0,0);
			glScalef(sX, sY, sZ);

			glColor3f(0.85, 0.1, 0.1);


			for (int i = 0; i < (int) handles.size(); i++){
				glPushMatrix();
				glTranslatef(handles[i].x, handles[i].y, handles[i].z);
				glScalef(1/sX, 1/sY, 1/sZ);
				glutSolidCube(5);
				glPopMatrix();

			}
			glPopMatrix();

		}

		void setWinCoords(){
			GLint vPort[4];
			GLdouble mMatrix[16];
			GLdouble pMatrix[16];
			//GLdouble winX, winY, winZ;
			//	GLdouble  winZ;

			glPushMatrix();
			glMultMatrixf(tMatrix.getMatrix());
			//glTranslatef(xOff,yOff,zOff);
			//glRotatef(rX,0,1,0);
			//glRotatef(rY,1,0,0);
			glScalef(sX, sY, sZ);


			glGetDoublev( GL_MODELVIEW_MATRIX, mMatrix);
			glGetDoublev( GL_PROJECTION_MATRIX, pMatrix);
			glGetIntegerv( GL_VIEWPORT, vPort );
			//std::cout<<"Closest vertex is "<<

			GLfloat mouseX = (float) lastX;
			GLfloat mouseY = (float)vPort[3] - (float) lastY;



			winCoords.clear();
			for (int i = 0; i < (int) handles.size(); i++){
				GLdouble winX, winY, winZ;
				gluProject(handles[i].x, handles[i].y, handles[i].z,
					mMatrix, pMatrix, vPort,&winX, &winY, &winZ);
				winCoords.push_back(vertex((float) winX, (float) winY, (float) winZ));
			}

			glPopMatrix();


		};


		void scaleXY(float xGrow, float yGrow, float oSize){
			//after scaling, center of cube must be moved so that only one corner is dragged
			//determine xOff and yOff changes by finding the x and y differences (in object coordinates)
			//of the new larger/smaller shape, and convert back to world coordinates
			//(rotation matrix with r = -rotation of object
			float rzRad = RADIANS(rX);
			std::cout<<"rX : "<<rX<<"oSize "<<oSize<<std::endl;

			float xScaleInc = xGrow/20;float yScaleInc = yGrow / 20;
			float xOffInc = xScaleInc*oSize/2*cos(-rzRad) - yScaleInc*oSize/2*sin(-rzRad);
			float yOffInc = xScaleInc*oSize/2*sin(-rzRad) + yScaleInc*oSize/2*cos(-rzRad);

			if (handles[minI].x < 0) xScaleInc *=-1;
			if (handles[minI].z < 0) yScaleInc *=-1;
			sX += xScaleInc; sZ+= yScaleInc;
			//xOff+= xOffInc; zOff += yOffInc;
			tMatrix.translate(xOffInc, 0, yOffInc);

			notifyObservers();
		}


		void scaleX(float xGrow, float oSize){
			//after scaling, center of cube must be moved so that only one corner is dragged
			//determine xOff and yOff changes by finding the x and y differences (in object coordinates)
			//of the new larger/smaller shape, and convert back to world coordinates
			//(rotation matrix with r = -rotation of object
			float rzRad = RADIANS(rX);
			std::cout<<"rX : "<<rX<<std::endl;

			float xScaleInc = xGrow/20;
			float xOffInc = xScaleInc*oSize/2*cos(-rzRad) ;
			float yOffInc = xScaleInc*oSize/2*sin(-rzRad) ;

			if (handles[minI].x < 0) xScaleInc *=-1;
			sX += xScaleInc; 
			//xOff+= xOffInc; zOff += yOffInc;
			//move(xOffInc, 0, yOffInc);
			tMatrix.translate(xOffInc, 0, yOffInc);

			notifyObservers();
		}



		void scaleZ(float y, float oSize){
			float yScaleInc = - (float)y / 25;
			float yOffInc = yScaleInc*oSize/2;
			if (handles[minI].y < 0) yScaleInc *=-1;
			sY += yScaleInc;
			//yOff += yOffInc;
			//move(0, yOffInc, 0);
			tMatrix.translate(0, yOffInc, 0);

			notifyObservers();
		}


/*
		virtual void transform(float _x, float _y, float _z, float _rX, float _rY, float _rZ,
			float _sX, float _sY, float _sZ){

				std::cout<<"transforming object"<<std::endl;
				pxOff += _x;
				pyOff += _y;
				pzOff += _z;
				prX += _rX;
				prY += _rY;
				prZ += _rZ;
				psX *= _sX;
				psY *= _sY;
				psZ *= _sZ;
		}
*/


		//virtual void move(float x, float y, float z){
			//xOff += x;
			//yOff += y;
			//zOff += z;

			//tMatrix.translate(x, y, z);
		//}

		//rotate rX degrees around x axis, rY degrees around y axis..etc
		void rotate(float _rX, float _rY, float _rZ){
			//set the rotation matrix
			rotMat.setRotationDegrees(_rX, _rY,_rZ);
			//multiply by tmatrix.
			///tMatrix.postMultiply(rotMat);
			rotMat.postMultiply(tMatrix);
			tMatrix.set(rotMat.getMatrix());

			notifyObservers();
		}

		void scale(float _sX, float _sY, float _sZ){
			scaleMat.loadIdentity();
			scaleMat.setScale(_sX, _sY, _sZ);
			scaleMat.postMultiply(tMatrix);
			tMatrix.set(scaleMat.getMatrix());

			notifyObservers();
		}




	
		//rotate theta degrees around axis defined by (x,y,z) at point(xOff,yOff,zOff)
		void rotate(float theta, float x, float y, float z){
			
			rX+=theta;
			rotMat.loadIdentity();
			//rotMat.setRotationDegrees(theta,x,y,z);
			rotMat.setRotationDegrees(theta, tMatrix.m_matrix[12], tMatrix.m_matrix[13], 
				tMatrix.m_matrix[14], x, y, z);

			rotMat.postMultiply(tMatrix);
			tMatrix.set(rotMat.getMatrix());
			//tMatrix.postMultiply(rotMat);

			notifyObservers();
		}


				//rotate theta degrees around axis defined by (x,y,z) at point(a,b,c)
		void rotate(float theta, float a, float b, float c, float x, float y, float z){
			
			std::cout<<"Rotate around "<<a<<" "<<b<<" "<<c<<std::endl;
			rX+=theta;
			rotMat.loadIdentity();
			//rotMat.setRotationDegrees(theta,x,y,z);
			rotMat.setRotationDegrees(theta, a, b, 
				c, x, y, z);

			rotMat.postMultiply(tMatrix);
			tMatrix.set(rotMat.getMatrix());
			//tMatrix.postMultiply(rotMat);

			notifyObservers();
		}

		




		virtual void move(double patt_trans[3][4], int but, int key, int x, int y){
			//int specialKey = glutGetModifiers();
			double xNew, yNew;
			getTransformedMotion(patt_trans, but, key, x, y, xNew, yNew);

			double xGrow, yGrow;
			getTransformedMotion(patt_trans, but, key, x, y,rX, xGrow, yGrow);



			//if (key ==(GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT)){
			if (key == GLUT_ACTIVE_ALT){
				if (but == GLUT_LEFT_BUTTON){
					sX += (float)x / 25; sZ -= (float)y / 25; //yOff += y;
				}
				else if (but == GLUT_MIDDLE_BUTTON){
					//sX -= (float)y / 25; sZ -= (float)y / 25;
					sY -= (float)y / 25;
				}
			}
			else if (key == GLUT_ACTIVE_CTRL){
				if (but == GLUT_LEFT_BUTTON){
					//rX += x; 

					std::cout<<"ROTATING"<<std::endl;
					rotate(x, 0, 1, 0);
					//rotate(0, x, 0);

					////rY+=y; //yOff += y;
				}
				else if (but == GLUT_MIDDLE_BUTTON){
					//rX+=x;
					////rotate(x,0,y);
					rotate(x,1,0,0);
					rotate(y,0,0,1);
				}
			}
			//	}

			else{
				if (but == GLUT_LEFT_BUTTON){

					if (min > 10 || handles.empty()){
						//xOff += xNew; zOff += yNew;
						//move(xNew, 0, yNew);
						tMatrix.translate(xNew, 0, yNew);

					}
					else{
						std::cout<<"--------------SCALING------------------"<<std::endl;
						scaleXY(xGrow, yGrow, XYSize);
					}



				}
				else if (but == GLUT_MIDDLE_BUTTON){
					if (min > 10||handles.empty()){
						//yOff -= y;
						//move(0, -y, 0);
					tMatrix.translate(0, -y, 0);

					}
					else{
						scaleZ(y, ZSize);

					}
				}
			}
			notifyObservers();
		}


		//used by shapes to find closest corner to mouse click
		float distance(float x1, float y1, float x2, float y2){
			return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		}


		int name;
		int isSelected; int isVisible;
		GLfloat  objTrans[16];

		//float xOff, yOff, zOff;	// offset
		float rX, rY, rZ;
		float sX, sY, sZ; //x1, y1, x2, y2;
		GLfloat   mat_ambient[4];   //  = {0.2, 0.3, 0.5, 1.0};
		GLUquadricObj *quadratic;

		//float m_shininess;
		GLuint texture;
		std::string textureFilename;

		std::vector<vertex> vertices;  //all vertices used for drawing (rel to object center)
		std::vector<vertex> handles;  //handles for resizing, stretching etc. (rel to object center)
		std::vector<vertex> winCoords; //window coordinates of each handles
		int shapeType; //GL_QUAD_STRIP, GL_TRIANGLE_FAN, GL_QUAD, etc.

		int drawMode;
		int minI; 
		float min;

		float XYSize, ZSize;
		PL3D::Matrix tMatrix; 

		PL3D::Matrix rotMat;

		PL3D::Matrix scaleMat;

};

#endif