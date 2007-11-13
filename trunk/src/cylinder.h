
class cylinder:public object{
public:
	cylinder(){ 
	//quadratic =  gluNewQuadric();
	};

	cylinder(int _name, float _rad, float _height)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; rad = _rad; height = _height; rX = 0; sX = 1; sY = 1; sZ= 1; isVisible = 1; rY = 0;
		//quadratic =  gluNewQuadric();
		XYSize = rad;
		ZSize = height;
				tMatrix.loadIdentity();
				rotMat.loadIdentity();
		
	}
	cylinder(int _name, 
		float _xOff, float _yOff, float _zOff,
		float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
		float _rad, float _height)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; 
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ= _sZ;
		rad = _rad; height = _height; isVisible = 1;
		//quadratic =  gluNewQuadric();

		XYSize = rad;
		ZSize = height;

		tMatrix.loadIdentity();
		tMatrix.translate(_xOff, _yOff, _zOff);
		rotMat.loadIdentity();
	}

	object* clone()   { return new cylinder(*this); }

	std::string getDataString(){
		std::ostringstream data;
		data<<"CYLINDER "<<xOff()<<" "<<yOff()<<" "<<zOff()<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<rad<<" "<<height;	
		return data.str(); 
	}

	virtual std::string getSLDataString(){
		std::ostringstream data;
		data<<"<type val=\"1\"> "<<std::endl;
		data<<"<position x=\""<<xOff()/100<<"\" y=\""<<yOff()/100<<"\" z=\""<<zOff()/100<<"\">"<<std::endl;
		data<<"<rotation x=\""<<PI/180*(rX-90)<<"\" y=\""<<PI/180*rY<<"\" z=\""<<PI/180*rZ<<"\">"<<std::endl;
		data<<"<size x=\""<<rad*sX/100<<"\" y=\""<<rad*sY/100<<"\" z=\""<<height*sZ/100<<"\">"<<std::endl;
		return data.str(); 
	}


/*
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
*/


	void initHandles(){

		handles.clear();
		handles.push_back(vertex(0, 0, -rad));
		handles.push_back(vertex(0, 0, rad));
		handles.push_back(vertex(rad, 0, 0));
		handles.push_back(vertex(-rad, 0, 0));

		handles.push_back(vertex(0, height, -rad));
		handles.push_back(vertex(0, height, rad));
		handles.push_back(vertex(rad, height, 0));
		handles.push_back(vertex(-rad, height, 0));
	}


	/*
	Draws a cylinder with its axis along the y-axis
	*/
	void draw() {
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);

		gluDisk(quadratic, 0, rad, 15, 15);
		gluCylinder(quadratic, rad, rad,  height, 15, 15);
		glPushMatrix();
			glTranslatef(0,0,height);
			gluDisk(quadratic, 0, rad, 15, 15);
		glPopMatrix();

		glPopMatrix();
	}

	float rad, height;
};