


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

			double xGrow, yGrow;
getTransformedMotion(patt_trans, but, key, x, y,rX, xGrow, yGrow);

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
			//xOff += xNew; zOff += yNew;


		}
		else if (but == GLUT_MIDDLE_BUTTON){
if (min > 10||handles.empty()){
				yOff -= y;
			}
			else{
					scaleZ(y, size);

			}
			//yOff -= y;
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


	void initHandles(){

	handles.clear();
	handles.push_back(vertex(-size/2, -size/2, -size/2));
	handles.push_back(vertex(-size/2, -size/2, size/2));
	handles.push_back(vertex(size/2, -size/2, size/2));
	handles.push_back(vertex(size/2, -size/2, -size/2));

	handles.push_back(vertex(0, size/2, 0));
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




