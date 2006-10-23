

class cube:public object{
public:
	cube(){ 
	
	};
	cube(int _name, float _x, float _y,  float _z, float _size)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; xOff = _x; yOff = _y;  zOff = _z; sX = 5;sY = 2; sZ= 2; size = _size; isVisible = 1; rX = 0; rY = 0;
	}
	cube(int _name, float _x, float _y,  float _z, 
		float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
		float _size)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; 
		xOff = _x; yOff = _y;  zOff = _z; 
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ = _sZ;


	


		size = _size; isVisible = 1; 
	}


object* clone()   { 
	
	std::cout<<"CLONE PreValues "<<pxOff<<" "<<pyOff<<" "<<pzOff<<std::endl;
	std::cout<<"CLONE xValues "<<xOff<<" "<<yOff<<" "<<zOff<<std::endl;
	return new cube(*this); }


std::string getDataString(){
		std::ostringstream data;
		data<<"CUBE "<<xOff<<" "<<yOff<<" "<<zOff<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<size;	
		return data.str(); 
	}

	virtual std::string getSLDataString(){
		std::ostringstream data;
		data<<"<type val=\"0\"> "<<std::endl;
		data<<"<position x=\""<<xOff/100<<"\" y=\""<<yOff/100<<"\" z=\""<<zOff/100<<"\">"<<std::endl;
		data<<"<rotation x=\""<<PI/180*(rX-90)<<"\" y=\""<<PI/180*rY<<"\" z=\""<<PI/180*rZ<<"\" s =\"1.0\""<<">"<<std::endl;
		data<<"<size x=\""<<size*sX/100<<"\" y=\""<<size*sY/100<<"\" z=\""<<size*sZ/100<<"\">"<<std::endl;
		return data.str(); 
	}


virtual void move(double patt_trans[3][4],int but, int key, int x, int y){
		
		double xNew, yNew;
			getTransformedMotion(patt_trans, but, key, x, y, xNew, yNew);

			double xGrow, yGrow;
getTransformedMotion(patt_trans, but, key, x, y,rX, xGrow, yGrow);

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
		if (min > 10){
			xOff += xNew; zOff += yNew;
			}

			else{

			//after scaling, center of cube must be moved so that only one corner is dragged
			//determine xOff and yOff changes by finding the x and y differences (in object coordinates)
			//of the new larger/smaller shape, and convert back to world coordinates
			//(rotation matrix with r = -rotation of object
			float rzRad = RADIANS(rX);
			std::cout<<"rX : "<<rX<<std::endl;
			float xScaleInc = xGrow / 20;
			float yScaleInc = yGrow / 20;
			float xOffInc = xScaleInc*size/2*cos(-rzRad) - yScaleInc*size/2*sin(-rzRad);
			float yOffInc = xScaleInc*size/2*sin(-rzRad) + yScaleInc*size/2*cos(-rzRad);
		
		if (min == d1||min == d5){	
			sX -= xScaleInc; xOff += xOffInc; 
			sZ-= yScaleInc; zOff+= yOffInc;
		}
		else if (min == d2|| min == d6){
			sX += xScaleInc; xOff += xOffInc; 
			sZ -= yScaleInc; zOff+= yOffInc;
		}
		else if (min == d3||min == d7){ 
			sX += xScaleInc; xOff += xOffInc; 
			sZ+= yScaleInc; zOff+= yOffInc;
		}
		else if (min == d4||min == d8){
			sX -= xScaleInc; xOff += xOffInc; 
			sZ+= yScaleInc; zOff+= yOffInc; 
		}
		}
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 
			
			if (min > 10){
				yOff -= y;
			}
			else{

					float yScaleInc = - (float)y / 25;
					float yOffInc = yScaleInc*size/2;
	//sY += yScaleInc;

				if (min == d1||min == d2||min == d3||min == d4){	
					sY -= yScaleInc;
					yOff += yOffInc;
				}
				else if (min == d5||min == d6||min == d7||min == d8){
					sY += yScaleInc;
					yOff += yOffInc;
				}
			}



		}
		}

	}


void initSelection(int but, int key, int x, int y){

	GLint vPort[4];
	glGetIntegerv( GL_VIEWPORT, vPort );
	GLfloat mouseX = (float) lastX;
	GLfloat mouseY = (float)vPort[3] - (float) lastY;

	d1 = distance ( (float) mouseX, (float) mouseY, (float) winX1, (float) winY1);
	min = d1;

	d2 = distance ( (float) mouseX, (float) mouseY, (float) winX2, (float) winY2);
	if (d2 < min ) min = d2;
	 d3 = distance ( (float) mouseX, (float) mouseY, (float) winX3, (float) winY3);
	if (d3 < min ) min = d3;
	d4 = distance ( (float) mouseX, (float) mouseY, (float) winX4, (float) winY4);
	if (d4 < min ) min = d4;

	d5 = distance ( (float) mouseX, (float) mouseY, (float) winX5, (float) winY5);
	if (d5 < min ) min = d5;

		d6 = distance ( (float) mouseX, (float) mouseY, (float) winX6, (float) winY6);
	if (d6 < min ) min = d6;
		d7 = distance ( (float) mouseX, (float) mouseY, (float) winX7, (float) winY7);
	if (d7 < min ) min = d7;
		d8 = distance ( (float) mouseX, (float) mouseY, (float) winX8, (float) winY8);
	if (d8 < min ) min = d8;


	std::cout<<" Point 1 projected to "<<winX1<<" "<<winY1<<" "<<std::endl;
	std::cout<<" dist from "<<lastX<<" "<<lastY<<": "<<d1<<std::endl;
	std::cout<<" Point 2 projected to "<<winX2<<" "<<winY2<<" "<<std::endl;
	std::cout<<" dist from "<<lastX<<" "<<lastY<<": "<<d2<<std::endl;
	std::cout<<" Point 3 projected to "<<winX3<<" "<<winY3<<" "<<std::endl;
	std::cout<<" dist from "<<lastX<<" "<<lastY<<": "<<d3<<std::endl;
	std::cout<<" Point 4 projected to "<<winX4<<" "<<winY4<<" "<<std::endl;
	std::cout<<" dist from "<<lastX<<" "<<lastY<<": "<<d4<<std::endl;

	std::cout<<" Point 5 projected to "<<winX5<<" "<<winY5<<" "<<std::endl;
	std::cout<<" dist from "<<lastX<<" "<<lastY<<": "<<d5<<std::endl;
	std::cout<<" Point 6 projected to "<<winX6<<" "<<winY6<<" "<<std::endl;
	std::cout<<" dist from "<<lastX<<" "<<lastY<<": "<<d6<<std::endl;

	std::cout<<" Point 7 projected to "<<winX7<<" "<<winY7<<" "<<std::endl;
	std::cout<<" dist from "<<lastX<<" "<<lastY<<": "<<d7<<std::endl;
	std::cout<<" Point 8 projected to "<<winX8<<" "<<winY8<<" "<<std::endl;
	std::cout<<" dist from "<<lastX<<" "<<lastY<<": "<<d8<<std::endl;


	std::cout<<" closest is "<<min<<std::endl;

	std::cout<<"Current pos: "<<getDataString();


}



void drawRect(){

	
	glBegin( GL_POLYGON );
//first face   
//drawSquare(size);
glVertex3f( -size/2, -size/2, 0.0f );
   glTexCoord2f( 0.0f, 0.0f );
   glVertex3f(  size/2, -size/2, 0.0f );
   glTexCoord2f( 1.0f, 0.0f );
   glVertex3f(  size/2,  size/2, 0.0f );
   glTexCoord2f( 1.0f, 1.0f );
   glVertex3f( -size/2,  size/2, 0.0f );
   glTexCoord2f( 0.0f, 1.0f );
  glEnd();

}

void highlightCorners(){
glPushMatrix();
glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sY, sZ);

		glDisable(GL_LIGHTING);
		glColor3f(0.85, 0.1, 0.1);
glPushMatrix();
glTranslatef(-size/2, -size/2, -size/2);
glScalef(1/sX, 1/sY, 1/sZ);
glutSolidCube(5);
glPopMatrix();

glPushMatrix();
glTranslatef(-size/2, -size/2, size/2);
glScalef(1/sX, 1/sY, 1/sZ);
glutSolidCube(5);
glPopMatrix();


glPushMatrix();
glTranslatef(-size/2, size/2, -size/2);
glScalef(1/sX, 1/sY, 1/sZ);
glutSolidCube(5);
glPopMatrix();

glPushMatrix();
glTranslatef(-size/2, size/2, size/2);
glScalef(1/sX, 1/sY, 1/sZ);
glutSolidCube(5);
glPopMatrix();

glPushMatrix();
glTranslatef(size/2, -size/2, -size/2);
glScalef(1/sX, 1/sY, 1/sZ);
glutSolidCube(5);
glPopMatrix();

glPushMatrix();
glTranslatef(size/2, -size/2, size/2);
glScalef(1/sX, 1/sY, 1/sZ);
glutSolidCube(5);
glPopMatrix();

glPushMatrix();
glTranslatef(size/2, size/2, -size/2);
glScalef(1/sX, 1/sY, 1/sZ);
glutSolidCube(5);
glPopMatrix();

glPushMatrix();
glTranslatef(size/2, size/2, size/2);
glScalef(1/sX, 1/sY, 1/sZ);
glutSolidCube(5);
glPopMatrix();





glPopMatrix();
}



void setWinCoords(){
	GLint vPort[4];
	GLdouble mMatrix[16];
	GLdouble pMatrix[16];
	//GLdouble winX, winY, winZ;
	GLdouble  winZ;
	glGetDoublev( GL_MODELVIEW_MATRIX, mMatrix);
	glGetDoublev( GL_PROJECTION_MATRIX, pMatrix);
	glGetIntegerv( GL_VIEWPORT, vPort );
	//std::cout<<"Closest vertex is "<<

	GLfloat mouseX = (float) lastX;
	GLfloat mouseY = (float)vPort[3] - (float) lastY;


	gluProject(-size/2,-size/2,-size/2, mMatrix, pMatrix, vPort,&winX1, &winY1, &winZ1);
gluProject(-size/2,-size/2,size/2, mMatrix, pMatrix, vPort,&winX4, &winY4, &winZ4);
gluProject(-size/2,size/2,-size/2, mMatrix, pMatrix, vPort,&winX5, &winY5, &winZ5);
gluProject(-size/2,size/2,size/2, mMatrix, pMatrix, vPort,&winX8, &winY8, &winZ8);

gluProject(size/2,-size/2,-size/2, mMatrix, pMatrix, vPort,&winX2, &winY2, &winZ2);
gluProject(size/2,-size/2,size/2, mMatrix, pMatrix, vPort,&winX3, &winY3, &winZ3);
gluProject(size/2,size/2,-size/2, mMatrix, pMatrix, vPort,&winX6, &winY6, &winZ6);
gluProject(size/2,size/2,size/2, mMatrix, pMatrix, vPort,&winX7, &winY7, &winZ7);




}



	void	draw(){
	if (isVisible == 1){
	if (isSelected == 1){
		highlight();
		highlightCorners();
	}
	//glPushName(name);
	glPushMatrix();		
		glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sY, sZ);


//glMultMatrixf(objTrans);


setWinCoords();
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
drawRect();
glPopMatrix();
//second face
glPushMatrix();
glRotatef(90,1,0,0);
glTranslatef(0, 0, -size/2);
drawRect();
glPopMatrix();
 //thirdface
glPushMatrix();
glTranslatef(0.0f, 0.0, -size/2);
drawRect();
glPopMatrix();
   //fourth face
glPushMatrix();
glRotatef(90,1,0,0);
glTranslatef(0, 0, size/2);
drawRect();
glPopMatrix();
//fifth face
   glPushMatrix();
glRotatef(90,0,1,0);
glTranslatef(0, 0, size/2);
drawRect();
glPopMatrix();
 //sixth face
   glPushMatrix();
glRotatef(90,0,1,0);
glTranslatef(0, 0, -size/2);
drawRect();
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

		float d1, d2, d3, d4,d5, d6, d7, d8, min;
	GLdouble winX1, winY1, winZ1,
		winX2, winY2, winZ2,
		winX3, winY3, winZ3,
		winX4, winY4, winZ4,
		winX5, winY5, winZ5,
		winX6, winY6, winZ6,
		winX7, winY7, winZ7,
		winX8, winY8, winZ8;


};
