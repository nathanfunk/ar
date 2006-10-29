

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


void setHandles(){
	initHandles(); //set the position of each corner handle
	highlightCorners(); //draw each handle and set the window coordinates
}

void initHandles(){

	handles.clear();
	handles.push_back(vertex(x1, y1, 0));
	handles.push_back(vertex(x2, y2, 0));
	handles.push_back(vertex(x3, y3, 0));
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



	winCoords.clear();
	for (unsigned i = 0; i < handles.size(); i++){
		GLdouble winX, winY, winZ;
		gluProject(handles[i].x, handles[i].y, handles[i].z,
					mMatrix, pMatrix, vPort,&winX, &winY, &winZ);
		winCoords.push_back(vertex((float) winX, (float) winY, (float) winZ));
	}
}



void highlightCorners(){
glPushMatrix();
glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sY, sZ);

		glDisable(GL_LIGHTING);
		glColor3f(0.85, 0.1, 0.1);

		for (unsigned i = 0; i < handles.size(); i++){
			glPushMatrix();
			glTranslatef(handles[i].x, handles[i].y, handles[i].z);
			glScalef(1/sX, 1/sY, 1/sZ);
			glutSolidCube(5);
			glPopMatrix();

		}
	setWinCoords(); //fill the wincoords vector with the wincoords of each handle
	glPopMatrix();

}






	void	draw(){
	if (isVisible == 1){
	if (isSelected == 1){
		highlight();
		setHandles();
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