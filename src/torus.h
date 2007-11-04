

class torus:public object{
public:
	torus(){ 
	
	};
	torus(int _name, float _x, float _y,  float _z, float _radius, float _tubeRad)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name;
		sX = 5;sY = 2; sZ= 2; isVisible = 1; rX = 0; rY = 0;
			minI = 0;
		XYSize = _radius;
		ZSize = _radius;

		Radius = _radius;
		TubeRadius = _tubeRad;
		TorusDL = 0;
initDisplayList();

tMatrix.loadIdentity();
		tMatrix.translate(_x, _y, _z);

	}
	torus(int _name, float _x, float _y,  float _z, 
		float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
		float _radius, float _tubeRad)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; 
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ = _sZ;
		minI = 0;
	 isVisible = 1; 

		XYSize = _radius;
		ZSize = _radius;
TorusDL = 0;

	Radius = _radius;
		TubeRadius = _tubeRad;
		initDisplayList();

		tMatrix.loadIdentity();
		tMatrix.translate(_x, _y, _z);
	}


object* clone()   { 
	
	//std::cout<<"CLONE PreValues "<<pxOff<<" "<<pyOff<<" "<<pzOff<<std::endl;
	std::cout<<"CLONE xValues "<<xOff()<<" "<<yOff()<<" "<<zOff()<<std::endl;
	return new torus(*this); }


std::string getDataString(){
		std::ostringstream data;
		data<<"TORUS "<<xOff()<<" "<<yOff()<<" "<<zOff()<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<Radius;	
		return data.str(); 
	}

	virtual std::string getSLDataString(){
		std::ostringstream data;
		data<<"<type val=\"0\"> "<<std::endl;
		data<<"<position x=\""<<xOff()/100<<"\" y=\""<<yOff()/100<<"\" z=\""<<zOff()/100<<"\">"<<std::endl;
		data<<"<rotation x=\""<<PI/180*(rX-90)<<"\" y=\""<<PI/180*rY<<"\" z=\""<<PI/180*rZ<<"\" s =\"1.0\""<<">"<<std::endl;
		data<<"<size x=\""<<Radius*sX/100<<"\" y=\""<<Radius*sY/100<<"\" z=\""<<Radius*sZ/100<<"\">"<<std::endl;
		return data.str(); 
	}




/*

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
				scaleXY(xGrow, yGrow, Radius);
			}
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 
			
			if (min > 10||handles.empty()){
				yOff -= y;
			}
			else{
					scaleZ(y, Radius);

			}



		}
		}

	}

*/


void initDisplayList(){

//void initDisplayList(){
//procedure CreateTorus(TubeRadius, Radius : GLfloat; Sides, Rings : Integer);

//void draw(){

//Radius = 5; 
//float	TubeRadius = 2.5;
//float TubeRadius = 2;

	int Sides = 20;
	int rings = 20;
int i, j;
float theta, phi, theta1, cosTheta, sinTheta, cosTheta1, sinTheta1, ringDelta, sideDelta, cosPhi, sinPhi, dist;

  sideDelta = 2.0 * PI / Sides;
  ringDelta = 2.0 * PI / rings;
  theta = 0.0;
  cosTheta = 1.0;
  sinTheta = 0.0;

  TorusDL =glGenLists(1);
  glNewList(TorusDL, GL_COMPILE);

  //std::cout<<"TORUS ";

  for (i = rings - 1; i >= 0; i--) {
      theta1 = theta + ringDelta;
      cosTheta1 = cos(theta1);
      sinTheta1 = sin(theta1);
      glBegin(GL_QUAD_STRIP);
        phi = 0.0;
  //std::cout<<"loop 1"<<std::endl;
	  for (j = Sides; j >= 0; j--){
          phi = phi + sideDelta;
          cosPhi = cos(phi);
          sinPhi = sin(phi);
          dist = Radius + (TubeRadius * cosPhi);

          glNormal3f(cosTheta1 * cosPhi, -sinTheta1 * cosPhi, sinPhi);
          glVertex3f(cosTheta1 * dist, -sinTheta1 * dist, TubeRadius * sinPhi);

          glNormal3f(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi);
          glVertex3f(cosTheta * dist, -sinTheta * dist, TubeRadius * sinPhi);
		//  std::cout<<"loop 2"<<std::endl;
	  }
      glEnd();
      theta = theta1;
      cosTheta = cosTheta1;
      sinTheta = sinTheta1;
  }
 glEndList();
}


void initHandles(){

	handles.clear();
	handles.push_back(vertex(-Radius, -Radius, -Radius));
	handles.push_back(vertex(Radius, -Radius, -Radius));
	handles.push_back(vertex(Radius, -Radius, Radius));
	handles.push_back(vertex(-Radius, -Radius, Radius));

	handles.push_back(vertex(-Radius, Radius, -Radius));
	handles.push_back(vertex(Radius, Radius, -Radius));
	handles.push_back(vertex(Radius, Radius, Radius));
	handles.push_back(vertex(-Radius, Radius, Radius));
}



	void	draw(){

		   glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0, 1.0);

		glCallList(TorusDL);

glDisable(GL_POLYGON_OFFSET_FILL);

   glDisable(GL_LIGHTING);

glColor3f (1.0, 1.0, 1.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glCallList (TorusDL);
   
   
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   glEnable(GL_LIGHTING);

		/*int numc = 20;
		int numt = 20;

		int i, j, k;
   double s, t, x, y, z, twopi;

   twopi = 2 * PI;
   for (i = 0; i < numc; i++) {
      glBegin(GL_QUAD_STRIP);
      for (j = 0; j <= numt; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % numc + 0.5;
            t = j % numt;

            x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
            z = .1 * sin(s * twopi / numc);
            glVertex3f(size*x, size*y, size*z);
         }
      }
      glEnd();
   }*/




	}


	float Radius,  TubeRadius;
	int TorusDL;
//	int minI;
//	float  min;
};


