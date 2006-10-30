
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
	
glBegin(GL_LINES);
glVertex2f(x1,y1);
glVertex2f(x2,y2);
glEnd();

	}
	float x1,y1,x2,y2;
};

