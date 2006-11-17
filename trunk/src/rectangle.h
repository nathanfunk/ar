

class rectangle:public object{
public:
	rectangle(){ 
	
	};
	rectangle(int _name, float _x1, float _y1,  float _x2,float _y2,float _r)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; x1 = _x1; y1 = _y1;  x2 = _x2; y2 = _y2; rX = 0; sX = 1; sY = 1; sZ= 1; isVisible = 1; rY = _r;
		xOff = 0; yOff = 0; zOff = 0;
		tMatrix.loadIdentity();
	}
	rectangle(int _name, float _xOff, float _yOff, float _zOff, 
		float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
		float _x1, float _y1,  float _x2,float _y2)//:
		//object(_xOff, _yOff,_zOff, _rX, _rY, _rZ, _sX, _sY, _sZ)
	{
		name = _name; x1 = _x1; y1 = _y1;  x2 = _x2; y2 = _y2; 
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ= _sZ; isVisible = 1; 
		xOff = _xOff; yOff = _yOff; zOff = _zOff;

		tMatrix.loadIdentity();
		tMatrix.translate(_xOff, _yOff, _zOff);
	}




	rectangle* clone()   { std::cout<<"rect clone"<<std::endl; return new rectangle(*this); }

std::string getDataString(){
		std::ostringstream data;
		data<<"RECTANGLE "<<xOff<<" "<<yOff<<" "<<zOff<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2;	
		return data.str(); 
	}

	virtual std::string getSLDataString(){
		std::ostringstream data;
		data<<"<type val=\"0\"> "<<std::endl;
		data<<"<position x=\""<<xOff/100<<"\" y=\""<<yOff/100<<"\" z=\""<<zOff/100<<"\">"<<std::endl;
		data<<"<rotation x=\""<<PI/180*(rX-90)<<"\" y=\""<<PI/180*rY<<"\" z=\""<<PI/180*rZ<<"\">"<<std::endl;
		data<<"<size x=\""<<(x2-x1)*sX/100<<"\" y=\""<<(y2-y1)*sY/100<<"\" z=\""<<0.0001<<"\">"<<std::endl;
		return data.str(); 
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

	std::cout<<" Point 1 projected to "<<winX1<<" "<<winY1<<" "<<std::endl;
	std::cout<<" dist from "<<lastX<<" "<<lastY<<": "<<d1<<std::endl;
	std::cout<<" Point 2 projected to "<<winX2<<" "<<winY2<<" "<<std::endl;
	std::cout<<" dist from "<<lastX<<" "<<lastY<<": "<<d2<<std::endl;
	std::cout<<" Point 3 projected to "<<winX3<<" "<<winY3<<" "<<std::endl;
	std::cout<<" dist from "<<lastX<<" "<<lastY<<": "<<d3<<std::endl;
	std::cout<<" Point 4 projected to "<<winX4<<" "<<winY4<<" "<<std::endl;
	std::cout<<" dist from "<<lastX<<" "<<lastY<<": "<<d4<<std::endl;

	std::cout<<" closest is "<<min<<std::endl;


}

float distance(float x1, float y1, float x2, float y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
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


	gluProject(x1,y1,0, mMatrix, pMatrix, vPort,&winX1, &winY1, &winZ);
	gluProject(x1,y2,0, mMatrix, pMatrix, vPort,&winX2, &winY2, &winZ);
	gluProject(x2,y2,0, mMatrix, pMatrix, vPort,&winX3, &winY3, &winZ);
	gluProject(x2,y1,0, mMatrix, pMatrix, vPort,&winX4, &winY4, &winZ);

}


	virtual void move(double patt_trans[3][4], int but, int key, int x, int y){
		//int specialKey = glutGetModifiers();
		double xNew, yNew;

		double xGrow, yGrow;
			getTransformedMotion(patt_trans, but, key, x, y, xNew, yNew);

			std::cout<<"rect rz: "<<rZ<<std::endl;
		getTransformedMotion(patt_trans, but, key, x, y,rX, xGrow, yGrow);

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
		
			if (min > 10){
			xOff += xNew; zOff += yNew;
			}

			else{

		if (min == d1){x1 += xGrow; y1+= yGrow;}
		else if (min == d2){x1+=xGrow/2; y2+=yGrow/2; }
		else if (min == d3){x2+=xGrow/2; y2+=yGrow/2; }
		else if (min == d4){x2+=xGrow/2; y1+=yGrow/2; }
			}



		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 yOff -= y;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 rX += x; rY+= y;//sOff += y;
		}
		}

		notifyObservers();
	}

	void	draw(){
glBegin( GL_POLYGON );
glVertex3f( x1, y1, 0.0f );
   glTexCoord2f( 0.0f, 0.0f );
   glVertex3f(  x1, y2, 0.0f );
   glTexCoord2f( 1.0f, 0.0f );
   glVertex3f(  x2,  y2, 0.0f );
   glTexCoord2f( 1.0f, 1.0f );
   glVertex3f( x2,  y1, 0.0f );
   glTexCoord2f( 0.0f, 1.0f );
  glEnd();
	}
	float x1, y1,  x2, y2;

		float d1, d2, d3, d4, min;
	GLdouble winX1, winY1, winX2, winY2, winX3, winY3, winX4, winY4;


};