
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
		else if (but == GLUT_MIDDLE_BUTTON){
		rY-=y;
		}
		}
		//	}

		else{
		if (but == GLUT_LEFT_BUTTON){
		//xOff += xNew; zOff += yNew;
		
		if (min > 10 || handles.empty()){
			xOff += xNew; zOff += yNew;
			}
			else{
				scaleXY(xGrow, yGrow, rad);
			}
		
		
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 yOff -= y;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 rX += x; rY+= y;//sOff += y;
		}
		}

	}





void highlightCorners(){


		glDisable(GL_LIGHTING);
		glColor3f(0.85, 0.1, 0.1);

glPushMatrix();		
		glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sZ, sY);


		glPushMatrix();
		glScalef(1/sX, 1/sZ, 1/sY);
		glutSolidCube(5);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(0,0,height);
		glScalef(1/sX, 1/sZ, 1/sY);
		glutSolidCube(5);
		glPopMatrix();



glPopMatrix();



}


void initHandles(){

	handles.clear();
	handles.push_back(vertex(-rad, -rad, 0));
	handles.push_back(vertex(-rad, rad, 0));
	handles.push_back(vertex(rad, rad, 0));
	handles.push_back(vertex(rad, -rad, 0));

	handles.push_back(vertex(0, 0, height));
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
		glScalef(sX, sY, sZ);
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