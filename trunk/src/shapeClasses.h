/*
ARMOUSEHOUSE Augmented Reality Mouse House
Created by Farooq Ahmad Sept. 2006
3D shape primitives - Derived Classes from object class in object.h

*/
int lastX; int lastY; 

#include "object.h"
#include "sphere.h"
#include "cube.h"
#include "rectangle.h"

class multiShape:public object{
public:
	multiShape(){};
	multiShape(std::vector<object *> _shapePtrs
	, float _x, float _y,  float _z, float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ){
		xOff = _x; yOff = _y;  zOff = _z; 
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ = _sZ;
		//shapePtrs = _shapePtrs;
		//copy(_shapePtrs.begin(), _shapePtrs.end(), shapePtrs.begin());
		copy(_shapePtrs.begin(), _shapePtrs.end(), std::back_insert_iterator<std::vector<object *> >(shapePtrs));
	};

object* clone()   { return new multiShape(*this); }

std::vector<object *> ungroup(){
	
 for (std::vector<object *>::iterator it = shapePtrs.begin(); it!=shapePtrs.end();) {
	 (*it)->transform(xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ);
	 ++it;
 }
	return shapePtrs;
}

virtual void move(double patt_trans[3][4],int but, int key, int x, int y){
		
		double xNew, yNew;
			getTransformedMotion(patt_trans, but, key, x, y, xNew, yNew);



		if (key == GLUT_ACTIVE_ALT){
		if (but == GLUT_LEFT_BUTTON){
		sX += (float)x / 25; 
		 sY -= (float)y / 25;
		////sZ -= (float)y / 25; 
		}
	
		else if (but == GLUT_MIDDLE_BUTTON){
		 sZ -= (float)y / 25; 
		 ///sY -= (float)y / 25;
		}
		}
	else if (key == GLUT_ACTIVE_CTRL){
		if (but == GLUT_LEFT_BUTTON){
		rX += x; 
		////rY-=y; //yOff += y;
		}
		else if (but == GLUT_RIGHT_BUTTON){
		rX += x;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		rX+=x;
		}
		}


		else{


		if (but == GLUT_LEFT_BUTTON){
		
			xOff += xNew; zOff += yNew;



		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 yOff -= y;
		}
		}

	}


	virtual void	draw(){


		glPushMatrix();		
		glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sY, sZ);


		for (int i = 0; i < shapePtrs.size(); i++){
				shapePtrs[i]->drawTopLevel();			
		}

		glPopMatrix();
	}


	

	std::vector<object *> shapePtrs;
	
	
};








class pyramid:public object{
public:
	pyramid(){ 
	
	};
	pyramid(int _name, float _x, float _y,  float _z, float _size)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; xOff = _x; yOff = _y;  zOff = _z; sX = 5;sY = 5; sZ= 5; size = _size; isVisible = 1; rX = 0; rY = 0;
	}
	pyramid(int _name, float _x, float _y,  float _z, 
		float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
		float _size)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; xOff = _x; yOff = _y;  zOff = _z; 
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ = _sZ; 
		size = _size; isVisible = 1; 
	}


object* clone()   { return new pyramid(*this); }


std::string getDataString(){
		std::ostringstream data;
		data<<"PYRAMID "<<xOff<<" "<<yOff<<" "<<zOff<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<size;	
		return data.str(); 
	}

	virtual std::string getSLDataString(){
		std::ostringstream data;
		data<<"<type val=\"2\"> "<<std::endl;
		data<<"<position x=\""<<xOff/100<<"\" y=\""<<yOff/100<<"\" z=\""<<zOff/100<<"\">"<<std::endl;
		data<<"<rotation x=\""<<PI/180*(rX-90)<<"\" y=\""<<PI/180*rY<<"\" z=\""<<PI/180*rZ<<"\">"<<std::endl;
		data<<"<size x=\""<<size*sX/100<<"\" y=\""<<size*sY/100<<"\" z=\""<<size*sZ/100<<"\">"<<std::endl;
		return data.str(); 
	}


virtual void move(double patt_trans[3][4],int but, int key, int x, int y){
		
		double xNew, yNew;
			getTransformedMotion(patt_trans, but, key, x, y, xNew, yNew);

if (key & GLUT_ACTIVE_CTRL &&
			key & GLUT_ACTIVE_ALT){
				std::cout<<"ctrl and alt held"<<std::endl;
			}

		if (key == GLUT_ACTIVE_ALT){
		if (but == GLUT_LEFT_BUTTON){
		sX += (float)x / 25; 
		 //sY -= (float)y / 25;
		sZ -= (float)y / 25; 
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 ///sZ -= (float)y / 25; 
		 sY -= (float)y / 25;
		}
		}
	else if (key == GLUT_ACTIVE_CTRL){
		if (but == GLUT_LEFT_BUTTON){
		rX += x; 
		////rY-=y; //yOff += y;
		}
		else if (but == GLUT_RIGHT_BUTTON){
		rX += x;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		rX+=x;
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

void drawTri(){

	glBegin(GL_TRIANGLES);		// Drawing Using Triangles
		   glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( -size/2, -size/2, 0.0f);		// bottom left
			glTexCoord2f( 1.0f, 0.0f );
		glVertex3f(size/2,-size/2, 0.0f);		// Bottom right
		 glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( 0,size/2, -size/2);		//top
		 glEnd();			

}



	void	draw(){
	if (isVisible == 1){
	if (isSelected == 1){
		highlight();
	}
	//glPushName(name);
	glPushMatrix();		
		glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sY, sZ);
startLighting(mat_ambient);

if (texture != 0) {
	//std::cout<<"enabling texture "<<std::endl;	
	glEnable( GL_TEXTURE_2D );	
	glBindTexture( GL_TEXTURE_2D, texture);

}


//glColor3f(0.85, 0.1, 0.1);
//first face
glPushMatrix();
glTranslatef(0.0f, 0.0, size/2);
drawTri();
glPopMatrix();
//second face

glPushMatrix();
glRotatef(90,0,1,0);
glTranslatef(0, 0, size/2);
drawTri();
glPopMatrix();

//thirdface
glPushMatrix();
glRotatef(180,0,1,0);
glTranslatef(0, 0.0, size/2);
drawTri();
glPopMatrix();

   //fourth face
glPushMatrix();
glRotatef(-90,0,1,0);
glTranslatef(0, 0, size/2);
drawTri();
glPopMatrix();




///glColor3f(0.85, 0.1, 0.1);
///		glutSolidCube(size);
	glDisable ( GL_LIGHTING ) ;

	glPopMatrix();

glDisable( GL_TEXTURE_2D );	


	//glPopName();
	}
	}
	float size;
};





class cone:public object{
public:
	cone(){ 
	
	};
	cone(int _name, float _x, float _y,  float _z, float _rad, float _height)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; xOff = _x; yOff = _y;  zOff = _z; sX = 1;sY = 1; sZ= 1; rad= _rad; height = _height; isVisible = 1; rX = 0; rY = 0;rZ = 0;
			
	}
cone(int _name, float _x, float _y,  float _z,
	 	float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
	 float _rad, float _height)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; xOff = _x; yOff = _y;  zOff = _z; 
	rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ = _sZ; 
	rad= _rad; height = _height; isVisible = 1;
			
	}



object* clone()   { return new cone(*this); }
std::string getDataString(){
		std::ostringstream data;
		data<<"CONE "<<xOff<<" "<<yOff<<" "<<zOff<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<rad<<" "<<height;	
		return data.str(); 
	}



virtual void move(double patt_trans[3][4],int but, int key, int x, int y){
		
		double xNew, yNew;
			getTransformedMotion(patt_trans, but, key, x, y, xNew, yNew);



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
		rX += x; rY+=y; //yOff += y;
		}
		else if (but == GLUT_RIGHT_BUTTON){
		rX += x;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		rX+=x;
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
	glPushMatrix();		
		glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sZ, sY);
startLighting(mat_ambient);

glColor3f(0.85, 0.1, 0.1);
		glutSolidCone(rad, height, 5, 15);
	glDisable ( GL_LIGHTING ) ;

	glPopMatrix();
	//glPopName();
	}
	}
	float rad, height;
};



class triangle:public object{
public:
	triangle(){ 
	
	};
	triangle(int _name, float _x1, float _y1,  float _x2,float _y2, float _x3, float _y3, float _r)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; x1 = _x1; y1 = _y1;  x2 = _x2; y2 = _y2; 
		x3 = _x3; y3 = _y3;
		rX = 0; sX = 1; sY = 1; sZ= 1; isVisible = 1; rY = _r;
		xOff = 0; yOff = 0; zOff = 0; rZ = 0;
	}
	triangle(int _name, float _xOff, float _yOff, float _zOff, float _x1, float _y1,  float _x2,float _y2, float _x3, float _y3, float _r)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; x1 = _x1; y1 = _y1;  x2 = _x2; y2 = _y2; 
		x3 = _x3; y3 = _y3;
		rX = 0; sX = 1; sY = 1; sZ= 1; isVisible = 1; rY = _r;
		xOff = _xOff; yOff = _yOff; zOff = _zOff; rZ = 0;
	}
	triangle(int _name, float _xOff, float _yOff, float _zOff, 
		
		float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
		float _x1, float _y1,  float _x2,float _y2, float _x3, float _y3)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; x1 = _x1; y1 = _y1;  x2 = _x2; y2 = _y2; x3 = _x3; y3 = _y3;
			rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ= _sZ;
		
		isVisible = 1; 
		xOff = _xOff; yOff = _yOff; zOff = _zOff; 
	}





	triangle* clone()   { std::cout<<"triangle clone"<<std::endl; return new triangle(*this); }
std::string getDataString(){
		std::ostringstream data;
		data<<"TRIANGLE "<<xOff<<" "<<yOff<<" "<<zOff<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<x3<<" "<<y3;	
		return data.str(); 
	}



 void move(double patt_trans[3][4], int but, int key, int x, int y){
		//int specialKey = glutGetModifiers();
		double xNew, yNew;
			getTransformedMotion(patt_trans, but, key, x, y, xNew, yNew);


			


		if (key == GLUT_ACTIVE_ALT){
		if (but == GLUT_LEFT_BUTTON){
		sX += (float)x / 25; sZ -= (float)y / 25; //yOff += y;
		}
		else if (but == GLUT_RIGHT_BUTTON){
		 sY -= (float)y / 25;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 //sX -= (float)y / 25; sZ -= (float)y / 25;
			//sY -= (float)y / 25;
			x3 += (float) x ;
			y3 -= (float) y ;
		}
		}
	else if (key == GLUT_ACTIVE_CTRL){
		if (but == GLUT_LEFT_BUTTON){
		rX += x; rY+=y; //yOff += y;
		}
		else if (but == GLUT_RIGHT_BUTTON){
		rY += x;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		rZ+=x;
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
	glPushMatrix();		
		glTranslatef(xOff,yOff,zOff);
		
		
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
glRotatef(rZ,0,0,1);

		glScalef(sX, sZ, 1);
		startLighting(mat_ambient);
if (texture != 0) {
	//std::cout<<"enabling texture "<<std::endl;	
	glEnable( GL_TEXTURE_2D );	
	glBindTexture( GL_TEXTURE_2D, texture);

}



		glBegin(GL_TRIANGLES);		// Drawing Using Triangles
		   glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( x3, y3, 0.0f);		// Top
			glTexCoord2f( 1.0f, 0.0f );
		glVertex3f(x1,y1, 0.0f);		// Bottom Left
		 glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( x2,y2, 0.0f);		// Bottom Right
		 glEnd();			

	glDisable ( GL_LIGHTING ) ;
	glPopMatrix();
	//glPopName();

		glDisable( GL_TEXTURE_2D );	
	}
	}
	float x1, y1,  x2, y2, x3, y3, rZ;
};

class fillArc:public object{
public:
	fillArc(){ 
	
	};
	fillArc(int _name, float _x, float _y,  float _rad, float _startAngle, float _arcAngle, float _r)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; xOff = _x; yOff = _y;  radius = _rad;
		startAngle = PI/180*_startAngle; arcAngle = PI/180*_arcAngle;
		rX = 0; sX = 1; sY = 1; sZ= 1; isVisible = 1; rY = _r;
		zOff = 0;
	}

fillArc(int _name, float _xOff, float _yOff,  float _zOff, 
		float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
		float _rad, float _startAngle, float _arcAngle)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; xOff = _xOff; yOff = _yOff;  zOff  = _zOff; 
		
		radius = _rad;
		startAngle = PI/180*_startAngle; arcAngle = PI/180*_arcAngle;
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ= _sZ;
		
		isVisible = 1;

	}


	fillArc* clone()   { std::cout<<"fillarc clone"<<std::endl; return new fillArc(*this); }
std::string getDataString(){
		std::ostringstream data;
		data<<"FILLARC "<<xOff<<" "<<yOff<<" "<<zOff<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<radius<<" "<<startAngle<<" "<<arcAngle;	
		return data.str(); 
	}

virtual void move(double patt_trans[3][4],int but, int key, int x, int y){
		
		double xNew, yNew;
			getTransformedMotion(patt_trans, but, key, x, y, xNew, yNew);



		if (key == GLUT_ACTIVE_ALT){
		if (but == GLUT_LEFT_BUTTON){
		sX += (float)x / 25; sZ -= (float)y / 25; //yOff += y;
		}

		else if (but == GLUT_MIDDLE_BUTTON){
		 //sX -= (float)y / 25; sZ -= (float)y / 25; 
		 arcAngle -= (float)y / 5;
		 thickness += (float) x /5;
		}
		}
	else if (key == GLUT_ACTIVE_CTRL){
		if (but == GLUT_LEFT_BUTTON){
		rX += x; rY-=y; //yOff += y;
		}
		else if (but == GLUT_RIGHT_BUTTON){
		rX += x;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		rX+=x;
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

	int n = 50;

	glPushMatrix();		
		glTranslatef(xOff,yOff ,zOff);
		//move to center
		
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);

		glScalef(sX, sZ, 1);
		startLighting(mat_ambient);
		
////
	float pheta, angle_increment;
    float x1, y1, x2, y2;

    if (n <= 0)
        n = 1;

    angle_increment = PI_2 / n;

    //  specify the center
    //glVertex2f (0.0f, 0.0f);
/*
    glPushMatrix ();

    //  center the oval at x_center, y_center


    //  fill the oval using triangle fan
    glBegin (GL_TRIANGLE_FAN);

    glVertex2f (0.0f, 0.0f);

    for (pheta = startAngle; pheta - (startAngle + arcAngle)
                          < 0.001; pheta += angle_increment)
    {
        x = radius * cos (pheta);
        y = radius * sin (pheta);

        glVertex2f (x, y);
    }

    glEnd ();

    glPopMatrix ();
	/////
*/

	glPushMatrix();
	int stacks = 20;
	float radIncrement = radius/stacks;
	


   // glVertex2f (0.0f, 0.0f);


for (int stack = 0; stack <stacks ; stack++){

	glBegin (GL_QUAD_STRIP);
    for (pheta = startAngle; pheta - (startAngle + arcAngle)
                          < 0.001; pheta += angle_increment)
    {
        x1 = stack*radIncrement * cos (pheta);
        y1 = stack*radIncrement * sin (pheta);

        x2 = (stack+1)*radIncrement * cos (pheta);
        y2 = (stack+1)*radIncrement * sin (pheta);
        glVertex2f (x1, y1);
		glVertex2f (x2, y2);

    }
	 glEnd ();
}

   

    glPopMatrix ();





	glDisable ( GL_LIGHTING ) ;
	glPopMatrix();
	//glPopName();
	}
	}
	float radius, startAngle, arcAngle, thickness;
};


class cylinder:public object{
public:
	cylinder(){ 
	quadratic =  gluNewQuadric();
	};
	cylinder(int _name, float _rad, float _height)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; rad = _rad; height = _height; rX = 0; sX = 1; sY = 1; sZ= 1; isVisible = 1; rY = 0;
		quadratic =  gluNewQuadric();

	}
	cylinder(int _name, 
		float _xOff, float _yOff, float _zOff,
		float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
		float _rad, float _height)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; 
		xOff = _xOff; yOff = _yOff; zOff = _zOff;
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ= _sZ;
		rad = _rad; height = _height; isVisible = 1;
		quadratic =  gluNewQuadric();

	}




	object* clone()   { return new cylinder(*this); }

	std::string getDataString(){
		std::ostringstream data;
		data<<"CYLINDER "<<xOff<<" "<<yOff<<" "<<zOff<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<rad<<" "<<height;	
		return data.str(); 
	}
	virtual std::string getSLDataString(){
		std::ostringstream data;
		data<<"<type val=\"1\"> "<<std::endl;
		data<<"<position x=\""<<xOff/100<<"\" y=\""<<yOff/100<<"\" z=\""<<zOff/100<<"\">"<<std::endl;
		data<<"<rotation x=\""<<PI/180*(rX-90)<<"\" y=\""<<PI/180*rY<<"\" z=\""<<PI/180*rZ<<"\">"<<std::endl;
		data<<"<size x=\""<<rad*sX/100<<"\" y=\""<<rad*sY/100<<"\" z=\""<<height*sZ/100<<"\">"<<std::endl;
		return data.str(); 
	}


	void	draw(){
	if (isVisible == 1){
	if (isSelected == 1){
		highlight();
	}
	//glPushName(name);
	glPushMatrix();		
		glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sZ, sY);
	startLighting(mat_ambient);
		//quadratic =  gluNewQuadric();		
		gluDisk(quadratic, 0, rad, 15, 15);
		gluCylinder(quadratic, rad, rad,  height, 15, 15);

		glTranslatef(0,0,height);
		gluDisk(quadratic, 0, rad, 15, 15);

	glDisable ( GL_LIGHTING ) ;

	glPopMatrix();
	//glPopName();
	}
	}
	float rad, height; GLUquadricObj *quadratic;
};




class partialCylinder:public object{
public:
	partialCylinder(){ 
	
	};
	partialCylinder(int _name, float _x, float _y,  float _rad,float _height, float _startAngle, float _arcAngle, float _r)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; xOff = _x; yOff = _y;  radius= _rad; height = _height;
		startAngle = PI/180*_startAngle; arcAngle = PI/180*_arcAngle;
		rX = 0; sX = 1; sY = 1; sZ= 1; isVisible = 1; rY = _r;
		zOff = 0; rZ = 0;
	}
	partialCylinder(int _name, float _xOff, float _yOff,float _zOff,  
		float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
		float _rad,float _height, float _startAngle, float _arcAngle)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; 
		xOff = _xOff; yOff = _yOff;  zOff = _zOff;
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ= _sZ;
		radius= _rad; height = _height;
		startAngle = PI/180*_startAngle; arcAngle = PI/180*_arcAngle;
		isVisible = 1; 
	}



	partialCylinder* clone()   { std::cout<<"partialCylinder clone"<<std::endl; return new partialCylinder(*this); }

std::string getDataString(){
		std::ostringstream data;
		data<<"PARTIALCYLINDER "<<xOff<<" "<<yOff<<" "<<zOff<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<radius<<" "<<height<<" "<<startAngle<<" "<<arcAngle;	
		//data<<"PARTIALCYLINDER "<<getGlobalDataString<<"LOCAL "<<radius<<" "<<height<<" "<<startAngle<<" "<<arcAngle;	
		return data.str(); 
	}
	virtual std::string getSLDataString(){
		std::ostringstream data;
		data<<"<type val=\"6\"> "<<std::endl;
		data<<"<position x=\""<<xOff/100<<"\" y=\""<<yOff/100<<"\" z=\""<<zOff/100<<"\">"<<std::endl;
		data<<"<rotation x=\""<<PI/180*(rX-90)<<"\" y=\""<<PI/180*rY<<"\" z=\""<<PI/180*rZ<<"\">"<<std::endl;
		data<<"<size x=\""<<radius*sX/100<<"\" y=\""<<radius*sY/100<<"\" z=\""<<height*sZ/100<<"\">"<<std::endl;
		return data.str(); 
	}



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
		rY-=y;rZ+=x;
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


	startLighting(mat_ambient);
	glPushMatrix();		
		glTranslatef(xOff,yOff ,zOff);
		//move to center
		
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
glRotatef(rZ,0,0,1);


		glScalef(sX, sZ, sY);
		
		

int stack;
int stacks = 100;
int slices = 100;

  GLdouble dangle,dradius,dheight;
  GLdouble normCo, normZ;

	float baseR = radius;
	float topR = radius;

  dangle  = 360.0/slices;
  dradius = (baseR-topR)/stacks;
  dheight = height/stacks;

  normZ = cos(atan(height/abs(topR-baseR)));
  normCo = sqrt(1-normZ*normZ);
	
  
  float pheta;
	float angle_increment =  PI_2 / slices;

if (texture != 0) {
	//std::cout<<"enabling texture "<<std::endl;	
	glEnable( GL_TEXTURE_2D );	
	glBindTexture( GL_TEXTURE_2D, texture);

}

float xTexInc = 1.0 / stacks;
float yTexInc = 1.0 / slices;


//std::cout<<"DRAW "<<std::endl;

  for(stack=0; stack<stacks ; ++stack) {
    glBegin(GL_QUAD_STRIP); {
      /*for(slice=0; slice<=slices; ++slice) {
        glNormal3d(normCo*sin(RADIANS(dangle*slice)),normCo*cos(RADIANS(dangle*slice)),normZ);
        glVertex3f( (topR + stack   *dradius)*sin(RADIANS(dangle*slice)),
                    (topR + stack   *dradius)*cos(RADIANS(dangle*slice)),
                    height- stack   *dheight);
        glVertex3f( (topR +(stack+1)*dradius)*sin(RADIANS(dangle*slice)),
                    (topR +(stack+1)*dradius)*cos(RADIANS(dangle*slice)),
                    height-(stack+1)*dheight);
	  }
	*/

int sliceNum = 0;



for (pheta = startAngle; pheta - (startAngle + arcAngle)
                          < 0.001; pheta += angle_increment)
    {
        //x = width/2 * cos (pheta);
        //y = height/2 * sin (pheta);
        //glVertex2f (x, y);
		float x = topR * cos(pheta);
		float y = topR * sin(pheta);
		

		

		glVertex3f(x,y,  stack   *dheight);
		 glTexCoord2f(  (stack-1)*xTexInc, sliceNum*yTexInc);
		glVertex3f(x,y, (stack+1)*dheight);
		 glTexCoord2f(   stack*xTexInc , sliceNum*yTexInc);
	
		// std::cout<<"["<<x<<" "<<y<<" "<<stack   *dheight<<"] ";
		//std::cout<<"["<<stack*xTexInc<<" "<<sliceNum*yTexInc<<"] "<<"["<<(stack+1)*xTexInc<<" "<<sliceNum*yTexInc<<"] "<<std::endl;
	sliceNum++;
		//std::cout<<" slice "<<sliceNum<<"Ytex "<<sliceNum*yTexInc;

	}


//std::cout<<" stack "<<stack<<"xTEx "<<stack*xTexInc<<std::endl;

	}
	
	glEnd();

  
  }




	glDisable ( GL_LIGHTING ) ;
	glPopMatrix();
	glDisable( GL_TEXTURE_2D );	
	//glPopName();
	}
	}
	float radius, height, startAngle, arcAngle;
};



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



class line:public object{
public:
	line(){ 
	
	};
	line(int _name, float _x1,float _y1, float _x2, float _y2 )//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name;x1 = _x1; x2 = _x2; y1 = _y1; y2 = _y2; rX = 0; sX = 1; sY = 1; sZ= 1; isVisible = 1; rY = 0;
	}

	object* clone()   { return new line(*this); }
	void move(double patt_trans[3][4],int but, int key, int x, int y){
		//int specialKey = glutGetModifiers();
		if (key == GLUT_ACTIVE_ALT){
		if (but == GLUT_LEFT_BUTTON){
		sX += (float)x / 25; sZ -= (float)y / 25; //yOff += y;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 sY += (float)y /5;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 sX -= (float)y / 25; sZ -= (float)y / 25; sY -= (float)y / 25;
		}
		}
		else if (key == GLUT_ACTIVE_CTRL){
		if (but == GLUT_LEFT_BUTTON){
		rX += x; rY+=y; //yOff += y;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		rY+=y;
		}
		}


		else{
		if (but == GLUT_LEFT_BUTTON){
		xOff += x; zOff += y;
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
	glPushMatrix();		
		glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sZ, sY);
	startLighting(mat_ambient);
glBegin(GL_LINES);
glVertex2f(x1,y1);
glVertex2f(x2,y2);
glEnd();


	glDisable ( GL_LIGHTING ) ;

	glPopMatrix();
	//glPopName();
	}
	}
	float x1,y1,x2,y2;
};

