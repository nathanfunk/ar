#ifndef SPHERE_H
#define SPHERE_H

class sphere:public object{
public:
	sphere(){ 
	
	};
	sphere(int _name, float _x, float _y,  float _z, float _rad)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; xOff = _x; yOff = _y;  zOff = _z;sX = 1; sY = 1; sZ =1; radius = _rad; isVisible = 1; rY = 0; rX = 0;
			XYSize = radius;
		ZSize = radius;

	}
	sphere(int _name, float _x, float _y,  float _z, float _rX, float _rY, float _rZ, 
		float _sX, float _sY, float _sZ, float _rad)//:
		//object(_name, _x1, _y1, _x2, _y2, _r)
	{
		name = _name; xOff = _x; yOff = _y;  zOff = _z;
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ = _sZ; 
		radius = _rad; isVisible = 1; 

				XYSize = radius;
		ZSize = radius;
	}

	
	object* clone()  { return new sphere(*this); }

	std::string getDataString(){
		std::ostringstream data;
		data<<"SPHERE "<<xOff<<" "<<yOff<<" "<<zOff<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ<<" "<<radius;	
		return data.str(); 
	}
	virtual std::string getSLDataString(){
		std::ostringstream data;
		data<<"<type val=\"3\"> "<<std::endl;
		data<<"<position x=\""<<xOff/100<<"\" y=\""<<yOff/100<<"\" z=\""<<zOff/100<<"\">"<<std::endl;
		data<<"<rotation x=\""<<PI/180*(rX-90)<<"\" y=\""<<PI/180*rY<<"\" z=\""<<PI/180*rZ<<"\">"<<std::endl;
		data<<"<size x=\""<<radius*sX/100<<"\" y=\""<<radius*sY/100<<"\" z=\""<<radius*sZ/100<<"\">"<<std::endl;
		return data.str(); 
	}



	void	draw(){
	if (isVisible == 1){
	
		glutSolidSphere(radius, 10, 10);

	}
	}
	float radius;
};

#endif