#ifndef OBJECT_H
#define OBJECT_H


#define NORMAL 0
#define WIREFRAME 1

/*
ARMOUSEHOUSE Augmented Reality Mouse House
Created by Farooq Ahmad Sept. 2006
Object class - base class for shape primitives in shapeClasses.h
and milkshape model class in myModel.h
*/


#include <string>

#ifndef PI
#	define PI	3.1415926535897932384626433832795
#endif
#define PI_2	PI * 2
#ifndef RADIANS
#define RADIANS(x) ((x)/180.0*3.14159265358979323)
#endif // RADIANS



/* Shape primitives for ARMouseHouse
Farooq Ahmad 2006
*/



void startLighting(GLfloat (&mat_ambient)[4]);
void startLighting2(void);



class vertex{
public:
	vertex(float _x, float _y, float _z){
		x = _x; y = _y; z = _z;
	};

	float x, y, z;
};




class object{
public:
	object(){
	xOff = 0; yOff = 0; zOff = 0;
	rX = 0; rY = 0; rZ = 0;
	sX = 1; sY = 1; sZ = 1;

std::cout<<"Object constructor 1"<<std::endl;
pxOff = 0; pyOff = 0; pzOff = 0;
prX = 0; prY =0; prZ = 0;
psX = 1; psY = 1; psZ = 1;


	isVisible = 1; isSelected = 0;
	setColors(0.2, 0.3, 0.5, 1);
	quadratic =  gluNewQuadric();
	texture = 0;

	minI = 0;
	drawMode = NORMAL;

	};
	
	object(float _xOff, float _yOff, float _zOff, float _rX, float _rY, float _rZ, 
		float _sX, float _sY, float _sZ){
		xOff = _xOff; yOff = _yOff;  zOff = _zOff; 
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ= _sZ;


		std::cout<<"Object constructor 2"<<std::endl;
pxOff = 0; pyOff = 0; pzOff = 0;
prX = 0; prY =0; prZ = 0;
psX = 1; psY = 1; psZ = 1;


		texture = 0;
	minI = 0;

	drawMode = NORMAL;
	}

	object(GLfloat _objTrans[16]){
		//objTrans = _objTrans;

		std::memcpy(&objTrans, &_objTrans, sizeof(objTrans));
	}




	virtual object * clone(){
		
		std::cout<<" OBJECT CLONE "<<std::endl;
		return new object(*this);};


	static void getRotFromTrans(double patt_trans[3][4], double (&rotMat)[3][3]){
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				rotMat[i][j]  = patt_trans[i][j];
			}
		}
	}
	int getTransformedMotion( double patt_trans[3][4], int but, int key,int x, int y, double &xNew, double &yNew){
		double wa, wb, wc;
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



	virtual std::vector<object *> ungroup(){std::vector<object *> emptyVec; return emptyVec;};


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



	void setColors(GLfloat c1, GLfloat c2, GLfloat c3, GLfloat c4){
		mat_ambient[0] = c1;  mat_ambient[1] = c2; mat_ambient[2] = c3; mat_ambient[3] = c4;
	}

	void setTexture(GLuint _texture){
		if (_texture == 0){
			texture = 0;
			return;
		}

		texture = _texture;
		//glBindTexture( GL_TEXTURE_2D, texture );
	
	}

	void drawTopLevel(float snapPos, float snapRot, float snapScale){

		glPushMatrix();		
		glTranslatef(pxOff,pyOff,pzOff);
		glRotatef(prX,0,1,0);
		glRotatef(prY,1,0,0);
		glScalef(psX, psY, psZ);

		draw();

		//if (snap_to_grid == 1)
		snap(snapPos, snapRot, snapScale);
		glPopMatrix();
	}


	virtual void snap(float snapPos, float snapRot, float snapScale){
		//if (snapPos >0){
		//xOff = (int) (xOff / snapPos) * snapPos;
		//yOff = (int) (yOff / snapPos) * snapPos;
		//zOff = (int) (zOff / snapPos) * snapPos;
		//}


	}


	virtual void draw() {
	
		for (int i = 0; i < vertices.size(); i++){
			


		}
	
	
	
	};

	virtual std::string getDataString(){ 
		//std::string 
		return std::string("OBJECT ") + "DERIVED CLASS DATA UNDEFINED";
	}
	virtual std::string getSLDataString(){
		std::ostringstream data;
		data<<"<type val=\"0\"> "<<std::endl;
		data<<"<position x=\""<<xOff/100<<"\" y=\""<<yOff/100<<"\" z=\""<<zOff/100<<">"<<std::endl;
		data<<"<rotation x=\""<<PI/180*(rX-90)<<"\" y=\""<<PI/180*rY<<"\" z=\""<<PI/180*rZ<<">"<<std::endl;
		data<<"<size x=\""<<sX<<"\" y=\""<<sY<<"\" z=\""<<sZ<<">"<<std::endl;
		return data.str(); 
	}


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


	


	virtual void highlight(){
	glPushMatrix();		
		glTranslatef(xOff,0,zOff);
	
		glPushMatrix();
		//glTranslatef(0,60,0);

			glDisable ( GL_LIGHTING ) ;
			//startLighting2();
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
	

			glEnable ( GL_LIGHTING ) ;
		glPopMatrix();
	
	glPopMatrix();


	}


	//virtual void initSelection(int but, int key, int x, int y){};

	virtual void initSelection(int but, int key, int x, int y){

	GLint vPort[4];
	glGetIntegerv( GL_VIEWPORT, vPort );
	GLfloat mouseX = (float) lastX;
	GLfloat mouseY = (float)vPort[3] - (float) lastY;


	min = 999999;

	if (winCoords.empty()) {
		std::cout<<"winCoords empty "<<std::endl;	
		return;
	}

	min = distance((float) mouseX, (float) mouseY, 
			(float) winCoords[0].x, (float) winCoords[0].y);
	minI = 0;

	for (int i = 1; i < winCoords.size(); i++){
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
		glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sY, sZ);

		glDisable(GL_LIGHTING);
		glColor3f(0.85, 0.1, 0.1);


		for (int i = 0; i < handles.size(); i++){
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
	GLdouble  winZ;

glPushMatrix();
glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sY, sZ);


	glGetDoublev( GL_MODELVIEW_MATRIX, mMatrix);
	glGetDoublev( GL_PROJECTION_MATRIX, pMatrix);
	glGetIntegerv( GL_VIEWPORT, vPort );
	//std::cout<<"Closest vertex is "<<

	GLfloat mouseX = (float) lastX;
	GLfloat mouseY = (float)vPort[3] - (float) lastY;



	winCoords.clear();
	for (int i = 0; i < handles.size(); i++){
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
			std::cout<<"rX : "<<rX<<std::endl;

			float xScaleInc = xGrow/20;float yScaleInc = yGrow / 20;
			float xOffInc = xScaleInc*oSize/2*cos(-rzRad) - yScaleInc*oSize/2*sin(-rzRad);
			float yOffInc = xScaleInc*oSize/2*sin(-rzRad) + yScaleInc*oSize/2*cos(-rzRad);

			if (handles[minI].x < 0) xScaleInc *=-1;
			if (handles[minI].z < 0) yScaleInc *=-1;
			sX += xScaleInc; sZ+= yScaleInc;
			xOff+= xOffInc; zOff += yOffInc;
	}

	void scaleZ(float y, float oSize){
				float yScaleInc = - (float)y / 25;
				float yOffInc = yScaleInc*oSize/2;
				if (handles[minI].y < 0) yScaleInc *=-1;
				sY += yScaleInc;
				yOff += yOffInc;
	}



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


	virtual void move(double patt_trans[3][4], int but, int key, int x, int y){
		//int specialKey = glutGetModifiers();
		double xNew, yNew;
			getTransformedMotion(patt_trans, but, key, x, y, xNew, yNew);


			//if (key ==(GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT)){
		if (key == GLUT_ACTIVE_ALT){
		if (but == GLUT_LEFT_BUTTON){
		sX += (float)x / 25; sZ -= (float)y / 25; //yOff += y;
		}
		else if (but == GLUT_RIGHT_BUTTON){
		 sY -= (float)y / 25;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 //sX -= (float)y / 25; sZ -= (float)y / 25;
			sY -= (float)y / 25;
		}
		}
	 else if (key == GLUT_ACTIVE_CTRL){
		if (but == GLUT_LEFT_BUTTON){
		rX += x; 
		////rY+=y; //yOff += y;
		}
		else if (but == GLUT_RIGHT_BUTTON){
		rY += x;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		rX+=x;
		}
		}
		//	}

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


		//used by shapes to find closest corner to mouse click
	float distance(float x1, float y1, float x2, float y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	}


	int name;
	int isSelected; int isVisible;
	//float xo, yo, x1, y1,  x2, y2, z,r;

GLfloat  objTrans[16];

	float pxOff, pyOff, pzOff, prX, prY, prZ, psX, psY, psZ; 

	float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ; //x1, y1, x2, y2;
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

};

#endif