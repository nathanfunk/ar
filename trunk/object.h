/*
ARMOUSEHOUSE Augmented Reality Mouse House
Created by Farooq Ahmad Sept. 2006
Object class - base class for shape primitives in shapeClasses.h
and milkshape model class in myModel.h
*/


#include <string>

//#define PI		3.141592654
#define PI_2	PI * 2
#ifndef RADIANS
#define RADIANS(x) ((x)/180.0*3.14159265358979323)
#endif // RADIANS



/* Shape primitives for ARMouseHouse
Farooq Ahmad 2006
*/



static void startLighting(GLfloat (&mat_ambient)[4]);
static void startLighting2(void);


void getRotFromTrans(double patt_trans[3][4], double (&rotMat)[3][3]){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			rotMat[i][j]  = patt_trans[i][j];
		}
	}
}

class object{
public:
	object(){
	xOff = 0; yOff = 0; zOff = 0;
	rX = 0; rY = 0; rZ = 0;
	sX = 1; sY = 1; sZ = 1;

	isVisible = 1; isSelected = 0;
	setColors(0.2, 0.3, 0.5, 1);
	quadratic =  gluNewQuadric();
	texture = 0;
	};
	
	object(float _xOff, float _yOff, float _zOff, float _rX, float _rY, float _rZ, 
		float _sX, float _sY, float _sZ){
		xOff = _xOff; yOff = _yOff;  zOff = _zOff; 
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ= _sZ;
		texture = 0;

	}


	virtual object * clone(){return new object(*this);};

	int getTransformedMotion( double patt_trans[3][4], int but, int key,int x, int y, double &xNew, double &yNew){
		double wa, wb, wc;
		double rotMat[3][3];
		getRotFromTrans(patt_trans, rotMat);
		arGetAngle(rotMat, &wa, &wb, &wc);

		//std::cout<<"Angles "<<180/3.14159*wa<<" "<<180/3.14159*wb<<" "<<180/3.14159*wc;
		//std::cout<<" Pos: "<<patt_trans[0][3]<<" "<<patt_trans[1][3]<<" "<<patt_trans[2][3]<<std::endl;

		//std::cout<<x<<" "<<y<<" "<<180/3.14159*wc;	
		xNew = 1*(x*cos(wc) - y * sin(wc));
		yNew = 1*(x*sin(wc) + y * cos(wc));
		//std::cout<<"new: "<<xNew<<" "<<yNew<<"sin(wc)"<<sin(wc)<<std::endl;	
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

	virtual void draw() {};

	virtual std::string getDataString(){ 
		//std::string 
		return std::string("OBJECT ") + "DERIVED CLASS DATA UNDEFINED";
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
	
	int name;
	int isSelected; int isVisible;
	//float xo, yo, x1, y1,  x2, y2, z,r;
	float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ; //x1, y1, x2, y2;
	GLfloat   mat_ambient[4];   //  = {0.2, 0.3, 0.5, 1.0};
	GLUquadricObj *quadratic;

	//float m_shininess;
	GLuint texture;
	std::string textureFilename;



};