




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

		XYSize = radius;
		ZSize = 0;

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

		XYSize = radius;
		ZSize = 0;

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
	
	int n = 50;
	float pheta, angle_increment;
    float x1, y1, x2, y2;

    if (n <= 0)
        n = 1;

    angle_increment = PI_2 / n;
	int stacks = 20;
	float radIncrement = radius/stacks;

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

	}
	float radius, startAngle, arcAngle, thickness;
};



