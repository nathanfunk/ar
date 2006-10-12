#include "ptr_vector.h"

void loadTextures(char *textureFile);

int drawGroundGrid( int divisions, float x, float y, float height)
{
//	double        gl_para[16];
    int           i;
	float x0,x1,y0,y1;
	float deltaX, deltaY;

    glTranslatef(x/2.,-y/2.,0.);
    //draw the grid
    glColor3f(1,0,0);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f( -x, y, height );
	glVertex3f(  x, y, height );  
	glVertex3f(  x, -y, height );
	glVertex3f( -x, -y, height );
	glEnd();
	glLineWidth(1.0);
	
	//draw a grid of lines
	//X direction
	x0 = -x; x1 = -x;
	y0 = -y; y1 = y;
	deltaX = (2*x)/divisions;

	for(i=0;i<divisions;i++){
		x0 = x0 + deltaX;
		glBegin(GL_LINES);
		glVertex3f(x0,y0,height);
		glVertex3f(x0,y1,height);
		glEnd();
	}

	x0 = -x; x1 = x;
	deltaY = (2*y)/divisions;

	for(i=0;i<divisions;i++){
		y0 = y0 + deltaY;
		glBegin(GL_LINES);
		glVertex3f(x0,y0,height);
		glVertex3f(x1,y0,height);
		glEnd();
	}

	glLineWidth(0.5);

	
    //argDrawMode2D();
    return 0;
}

GLuint LoadGLTextureRepeat( const char *filename );	

//void loadTextures(char *textureFile);

class world{

public:
	world(){xOff = 0; yOff =0; zOff= 0;rX = 0; rY = 0; rZ = 0;
	sX = 1; sY = 1; sZ = 1;
	isSelected = 0;};
	world(char *scriptFile){
	//loadTextures("blah.txt");
		loadWorld(scriptFile);
		xOff = 0; yOff =0; zOff= 0; rX = 0; rY = 0; rZ = 0;
	sX = 1; sY = 1; sZ = 1;isSelected = 0;
	};

	~world(){ 
		for (int i = 0; i < (int) objectPtrs.size(); i++){
		delete objectPtrs[i];
	}
	
	};




	std::vector<object *> objectPtrs;
	stdx::ptr_vector<object> objects;
	//std::vector <myModel> modelVec;

	std::vector <GLuint> textureIndex;


	int getTransformedMotion( double patt_trans[3][4], int but, int key,int x, int y, double &xNew, double &yNew){
		double wa, wb, wc;
		double rotMat[3][3];
		getRotFromTrans(patt_trans, rotMat);
		arGetAngle(rotMat, &wa, &wb, &wc);

		//std::cout<<"Angles "<<180/3.14159*wa<<" "<<180/3.14159*wb<<" "<<180/3.14159*wc;
		//std::cout<<" Pos: "<<patt_trans[0][3]<<" "<<patt_trans[1][3]<<" "<<patt_trans[2][3]<<std::endl;

		//std::cout<<x<<" "<<y<<" "<<180/3.14159*wc;	
		xNew = 1*(x*cos(wc) - y * sin(wc));
		yNew = 1*(x*sin(wc) + y * cos(wc));
		//std::cout<<"new: "<<xNew<<" "<<yNew<<"sin(wc)"<<sin(wc)<<std::endl;	
	return 1;
	}


virtual void move(double patt_trans[3][4],int but, int key, int x, int y){
		
		double xNew, yNew;
			getTransformedMotion(patt_trans, but, key, x, y, xNew, yNew);



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
		//rZ += x; 
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		//rX-=y;
		}
		}


		else{


		if (but == GLUT_LEFT_BUTTON){
		xOff += xNew; yOff -= yNew;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 zOff -= y;
		}
		}

	}


void loadTextures(char *textureFile){


textureIndex.push_back(LoadGLTextureRepeat("steel01.bmp"));

	GLuint blah = LoadGLTextureRepeat("cement.bmp");
	std::cout<<"blah "<<blah<<std::endl;
textureIndex.push_back(blah);
std::cout<<"texindex at 1 "<<textureIndex[1]<<std::endl;

	//std::cout<<LoadGLTextureRepeat("steel01.bmp")<<std::endl;


/*std::ifstream fin(textureFile);
std::string line;
 while ( std::getline(fin,line) )
   {
	  
	  std::istringstream iss(line);
	  std::string type;	
	  iss>>type;
  if (type == "TEXTURE") {
		std::string filename;
		iss>>filename;
		std::cout<<filename<<std::endl;
		textureIndex.push_back(LoadGLTextureRepeat(filename.c_str()));
  }



 }
*/

}


void initMenu(){



}


void loadWorld(char *scriptFile){

	std::ifstream fin(scriptFile);
//	int type; 

	std::string line;

	
   while ( std::getline(fin,line) )
   {
	  
	  std::istringstream iss(line);
	  std::string type;	
	  iss>>type;
	  if (type == "MS3D") {
		std::string filename;
		float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ;
		iss>>filename>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ;
		std::cout<<filename<<xOff<<yOff<<zOff<<rX<<sX<<std::endl;
		objectPtrs.push_back(new myModel((int) objectPtrs.size(), (char *) filename.c_str(), xOff,yOff,zOff,rX,rY,rZ,sX,sY,sZ));
	  }
	  else if (type == "RECTANGLE"){
		  float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, x1, y1, x2, y2;
		  iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>x1>>y1>>x2>>y2;
			objectPtrs.push_back( new rectangle((int) objectPtrs.size(), 
			xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ, x1, y1, x2, y2));
	  }
 else if (type == "SPHERE"){
		  float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, radius;
		  iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>radius;
			objectPtrs.push_back( new sphere((int) objectPtrs.size(), 
			xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ, radius));
	  }
  else if (type == "CUBE"){
		  float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, size;
		  iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>size;
			objectPtrs.push_back( new cube((int) objectPtrs.size(), 
			xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ, size));
	  }
  else if (type == "PYRAMID"){
		  float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, size;
		  iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>size;
			objectPtrs.push_back( new pyramid((int) objectPtrs.size(), 
			xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ, size));
	  }

   else if (type == "CONE"){
		  float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, radius, height;
		  iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>radius>>height;
			objectPtrs.push_back( new cone((int) objectPtrs.size(), 
			xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ, radius, height));
	  }
    else if (type == "TRIANGLE"){
		  float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, x1, y1, x2, y2, x3, y3;
		  iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>x1>>y1>>x2>>y2>>x3>>y3;
			objectPtrs.push_back( new triangle((int) objectPtrs.size(), 
			xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ, x1, y1, x2, y2, x3, y3));
	  }
	 else if (type == "CYLINDER"){
		  float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, radius, height;
		  iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>radius>>height;
			objectPtrs.push_back( new cylinder((int) objectPtrs.size(), 
			xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ,radius, height));
	  }

else if (type == "PARTIALCYLINDER"){
		  float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, radius, height, startAngle, arcAngle;
		  iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>radius>>height>>startAngle>>arcAngle;
			objectPtrs.push_back( new  partialCylinder((int) objectPtrs.size(), 
			xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ,radius, height, startAngle, arcAngle));
	  }
else if (type == "FILLARC"){
		  float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, radius, startAngle, arcAngle;
		  iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>radius>>startAngle>>arcAngle;
			objectPtrs.push_back( new fillArc((int) objectPtrs.size(), 
			xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ,radius, startAngle, arcAngle));
	  }


   }



	}




void loadWorld(){

	objectPtrs.push_back(new myModel((int) objectPtrs.size(), "chair.ms3d", 50,0,-50,0,1));
	objectPtrs.push_back(new myModel((int) objectPtrs.size(), "lcdtv2.ms3d", 50,0,-50,0,1));

	//objects.push_back(new myModel((int) objectPtrs.size(), "chair.ms3d", 50,-10,-50,0,1));


	//objectPtrs.push_back(new rectangle(objectPtrs.size(), 0,0,100, 100, 90));

	}


void saveWorld(char *scriptFile){

	std::ofstream outfile(scriptFile);
	  if (outfile.is_open())
  {
	for (int i = 0; i< (int) objectPtrs.size(); i++){
	
		outfile << objectPtrs[i]->getDataString()<<std::endl;
	 }




    outfile.close();
  }


}


void exportSL(char *scriptFile){

	std::ofstream outfile(scriptFile);
	  if (outfile.is_open())
  {

	  


	for (int i = 0; i< (int) objectPtrs.size(); i++){
	outfile<< "<primitive name=\"Object\" description=\"\" key=\"Num_231670488\" version=\"1\"> "<<std::endl;
	  outfile<< "<states> "<< std::endl;
		  outfile<<"<physics params=\"\">FALSE</physics> "<< std::endl;
		  outfile<<"<temporary params=\"\">FALSE</temporary>"<<std::endl;
		  outfile << "<phantom params=\"\">FALSE</phantom> "<<std::endl;
		  outfile<< "</states>"<<std::endl;


		 outfile<<  "<properties>"<<std::endl;
 outfile<<"<levelofdetail val=\"9\">"<<std::endl;

		outfile << objectPtrs[i]->getSLDataString();

		outfile<<"<textures params=\"\">"<<std::endl;
outfile<<"</textures>"<<std::endl;
outfile<<"<scripts params=\"\">"<<std::endl;
outfile<<"</scripts>"<<std::endl;
outfile<<"</properties>"<<std::endl;
outfile<<"</primitive>"<<std::endl;

	 }





    outfile.close();
  }


}



void draw(){
glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glRotatef(rZ,0,0,1);
		glScalef(sX, sY, sZ);
//draw the floor
	glPushMatrix();

	


	glPushName(-100);

	//glTranslatef(0,0,-20);
	drawGroundGrid( 20, 100.0f, 100.0f, 0.0f);
	//glRotatef(90,1,0,0);
	//glTranslatef(-50,150,-100);
//drawGroundGrid( 10, 100.0f, 100.0f, 0.0f);
/*
	glTranslatef(0,0,-20);
	glRectf(-100,-100,100,100);
	glDisable( GL_LIGHTING);
*/
	glPopName();
	glPopMatrix();
	glEnable( GL_LIGHTING);

	glPushMatrix();
	glRotatef(90,1,0,0);

//draw the models
	for (int i = 0; i < (int) objects.size(); i++){
		//push i onto namestack
		//glPushName(i);
		objects[i].draw();
		//glPopName();

	}

	//draw the models
	for (int i = 0; i < (int) objectPtrs.size(); i++){
		//push i onto namestack
		glPushName(i);
		objectPtrs[i]->draw();
		glPopName();

	}
	glPopMatrix();

}

	float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ;
	int isSelected;


};