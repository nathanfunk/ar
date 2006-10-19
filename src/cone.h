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
