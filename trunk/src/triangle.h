

class triangle:public object{
public:
	triangle(){ 
	
	};
	triangle(int _name, float _x1, float _y1,  float _x2,float _y2, float _x3, float _y3, float _r)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; x1 = _x1; y1 = _y1;  x2 = _x2; y2 = _y2; 
		x3 = _x3; y3 = _y3;
		rX = 0; sX = 1; sY = 1; sZ= 1; isVisible = 1; rY = _r;
		xOff = 0; yOff = 0; zOff = 0; rZ = 0;

		XYSize = 1;
		ZSize = 1;

		tMatrix.loadIdentity();
		

	}
	triangle(int _name, float _xOff, float _yOff, float _zOff, float _x1, float _y1,  float _x2,float _y2, float _x3, float _y3, float _r)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; x1 = _x1; y1 = _y1;  x2 = _x2; y2 = _y2; 
		x3 = _x3; y3 = _y3;
		rX = 0; sX = 1; sY = 1; sZ= 1; isVisible = 1; rY = _r;
		xOff = _xOff; yOff = _yOff; zOff = _zOff; rZ = 0;

				XYSize = 1;
		ZSize = 1;
		tMatrix.loadIdentity();
		tMatrix.translate(_xOff, _yOff, _zOff);
	}
	triangle(int _name, float _xOff, float _yOff, float _zOff, 
		
		float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ,
		float _x1, float _y1,  float _x2,float _y2, float _x3, float _y3)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; x1 = _x1; y1 = _y1;  x2 = _x2; y2 = _y2; x3 = _x3; y3 = _y3;
			rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ= _sZ;
		
		isVisible = 1; 
		xOff = _xOff; yOff = _yOff; zOff = _zOff; 

		XYSize = 1;
		ZSize = 1;
tMatrix.loadIdentity();
		tMatrix.translate(_xOff, _yOff, _zOff);
	}





	triangle* clone()   { std::cout<<"triangle clone"<<std::endl; return new triangle(*this); }
std::string getDataString(){
		std::ostringstream data;
		data<<"TRIANGLE "<<xOff<<" "<<yOff<<" "<<zOff<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<x3<<" "<<y3;	
		return data.str(); 
	}



void initHandles(){

	handles.clear();
	handles.push_back(vertex(x1, y1, 0));
	handles.push_back(vertex(x2, y2, 0));
	handles.push_back(vertex(x3, y3, 0));
}




	void	draw(){

		glBegin(GL_TRIANGLES);		// Drawing Using Triangles
		   glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( x3, y3, 0.0f);		// Top
			glTexCoord2f( 1.0f, 0.0f );
		glVertex3f(x1,y1, 0.0f);		// Bottom Left
		 glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( x2,y2, 0.0f);		// Bottom Right
		 glEnd();			

	}
	float x1, y1,  x2, y2, x3, y3, rZ;
};