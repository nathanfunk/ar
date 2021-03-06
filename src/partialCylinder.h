


class partialCylinder:public object{
public:
	partialCylinder(){ 
	
	};
	partialCylinder(int _name, float _x, float _y,  float _rad,float _height, float _startAngle, float _arcAngle, float _r)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; 
		radius= _rad; height = _height;
		startAngle = PI/180*_startAngle; arcAngle = PI/180*_arcAngle;
		rX = 0; sX = 1; sY = 1; sZ= 1; isVisible = 1; rY = _r;
		rZ = 0;


		XYSize = _rad;
		ZSize = _height;

		tMatrix.loadIdentity();
		tMatrix.translate(_x, _y, 0);
		rotMat.loadIdentity();


	}
	partialCylinder(int _name, float _xOff, float _yOff,float _zOff,  
		float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
		float _rad,float _height, float _startAngle, float _arcAngle)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; 
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ= _sZ;
		radius= _rad; height = _height;
		startAngle = PI/180*_startAngle; arcAngle = PI/180*_arcAngle;
		isVisible = 1; 

		XYSize = _rad;
		ZSize = _height;

		tMatrix.loadIdentity();
		tMatrix.translate(_xOff, _yOff, _zOff);
		rotMat.loadIdentity();

	}



	partialCylinder* clone()   { std::cout<<"partialCylinder clone"<<std::endl; return new partialCylinder(*this); }

	std::string getDataString(){
		std::ostringstream data;
		data<<"PARTIALCYLINDER "<<xOff()<<" "<<yOff()<<" "<<zOff()<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<radius<<" "<<height<<" "<<startAngle<<" "<<arcAngle;	
		//data<<"PARTIALCYLINDER "<<getGlobalDataString<<"LOCAL "<<radius<<" "<<height<<" "<<startAngle<<" "<<arcAngle;	
		return data.str(); 
	}

	virtual std::string getSLDataString(){
		std::ostringstream data;
		data<<"<type val=\"6\"> "<<std::endl;
		data<<"<position x=\""<<xOff()/100<<"\" y=\""<<yOff()/100<<"\" z=\""<<zOff()/100<<"\">"<<std::endl;
		data<<"<rotation x=\""<<PI/180*(rX-90)<<"\" y=\""<<PI/180*rY<<"\" z=\""<<PI/180*rZ<<"\">"<<std::endl;
		data<<"<size x=\""<<radius*sX/100<<"\" y=\""<<radius*sY/100<<"\" z=\""<<height*sZ/100<<"\">"<<std::endl;
		return data.str(); 
	}


	void draw(){	
		int n = 20;
		int stack;
		int stacks = 20;
		int slices = 20;

		GLdouble dangle,dradius,dheight;
		GLdouble normCo, normZ;

		float baseR = radius;
		float topR = radius;

		dangle  = 360.0/slices;
		dradius = (baseR-topR)/stacks;
		dheight = height/stacks;

		normZ = cos(atan(height/abs(topR-baseR)));
		normCo = sqrt(1-normZ*normZ);


		float pheta;
		float angle_increment =  PI_2 / slices;

		if (texture != 0) {
			//std::cout<<"enabling texture "<<std::endl;	
			glEnable( GL_TEXTURE_2D );	
			glBindTexture( GL_TEXTURE_2D, texture);
		}

		float xTexInc = 1.0 / stacks;
		float yTexInc = 1.0 / slices;


		//std::cout<<"DRAW "<<std::endl;

		for(stack=0; stack < stacks; ++stack) {
			glBegin(GL_QUAD_STRIP);
			/*for(slice=0; slice<=slices; ++slice) {
			glNormal3d(normCo*sin(RADIANS(dangle*slice)),normCo*cos(RADIANS(dangle*slice)),normZ);
			glVertex3f( (topR + stack   *dradius)*sin(RADIANS(dangle*slice)),
			(topR + stack   *dradius)*cos(RADIANS(dangle*slice)),
			height- stack   *dheight);
			glVertex3f( (topR +(stack+1)*dradius)*sin(RADIANS(dangle*slice)),
			(topR +(stack+1)*dradius)*cos(RADIANS(dangle*slice)),
			height-(stack+1)*dheight);
			}
			*/

			int sliceNum = 0;

			for (pheta = startAngle;
				pheta < startAngle + arcAngle + 0.001;
				pheta += angle_increment)
			{
				//x = width/2 * cos (pheta);
				//y = height/2 * sin (pheta);
				//glVertex2f (x, y);
				float x = topR * cos(pheta);
				float y = topR * sin(pheta);

				glNormal3f(cos(pheta), sin(pheta), 0.0);

				glVertex3f(x, y,  stack*dheight);
				glTexCoord2f((stack-1)*xTexInc, sliceNum*yTexInc);
				glVertex3f(x, y, (stack+1)*dheight);
				glTexCoord2f(stack*xTexInc, sliceNum*yTexInc);

				// std::cout<<"["<<x<<" "<<y<<" "<<stack   *dheight<<"] ";
				//std::cout<<"["<<stack*xTexInc<<" "<<sliceNum*yTexInc<<"] "<<"["<<(stack+1)*xTexInc<<" "<<sliceNum*yTexInc<<"] "<<std::endl;
				sliceNum++;
				//std::cout<<" slice "<<sliceNum<<"Ytex "<<sliceNum*yTexInc;
			}


			//std::cout<<" stack "<<stack<<"xTEx "<<stack*xTexInc<<std::endl;
			glEnd();

		}
	}

	float radius, height, startAngle, arcAngle;
};

