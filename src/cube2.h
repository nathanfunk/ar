

class cube2:public object{
public:
	cube2(){ 
	
	};
	cube2(int _name, float _x, float _y,  float _z, float _size)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; xOff = _x; yOff = _y;  zOff = _z; sX = 5;sY = 2; sZ= 2; size = _size; isVisible = 1; rX = 0; rY = 0;
			minI = 0;
		XYSize = size;
		ZSize = size;


	}
	cube2(int _name, float _x, float _y,  float _z, 
		float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
		float _size)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; 
		xOff = _x; yOff = _y;  zOff = _z; 
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ = _sZ;
		minI = 0;
		size = _size; isVisible = 1; 

		XYSize = size;
		ZSize = size;
	}


object* clone()   { 
	
	std::cout<<"CLONE PreValues "<<pxOff<<" "<<pyOff<<" "<<pzOff<<std::endl;
	std::cout<<"CLONE xValues "<<xOff<<" "<<yOff<<" "<<zOff<<std::endl;
	return new cube2(*this); }


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
		rX += x;   ////rY -= y;
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
		if (min > 10 || handles.empty()){
			xOff += xNew; zOff += yNew;
			}
			else{
				scaleXY(xGrow, yGrow, size);
			}
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 
			
			if (min > 10||handles.empty()){
				yOff -= y;
			}
			else{
					scaleZ(y, size);

			}



		}
		}

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


void initHandles(){

	handles.clear();
	handles.push_back(vertex(-size/2, -size/2, -size/2));
	handles.push_back(vertex(size/2, -size/2, -size/2));
	handles.push_back(vertex(size/2, -size/2, size/2));
	handles.push_back(vertex(-size/2, -size/2, size/2));

	handles.push_back(vertex(-size/2, size/2, -size/2));
	handles.push_back(vertex(size/2, size/2, -size/2));
	handles.push_back(vertex(size/2, size/2, size/2));
	handles.push_back(vertex(-size/2, size/2, size/2));
}



	void	draw(){



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

	}
	float size;
//	int minI;
//	float  min;
};
