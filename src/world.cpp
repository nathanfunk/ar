#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <gl/glut.h>   // The GL Utility Toolkit (Glut) Header

#include <AR/gsub_lite.h>

#include "ptr_vector.h"
#include "shapeClasses.h"
#include "myModel.h"
#include "world.h"


#pragma unmanaged

using namespace std;
using namespace ms3dglut;

void loadTextures(char *textureFile);

GLuint LoadGLTextureRepeat( const char *filename );	

//void loadTextures(char *textureFile);

World::World() {
	xOff = 0; yOff =0; zOff= 0;rX = 0; rY = 0; rZ = 0;
	sX = 1; sY = 1; sZ = 1;
	isSelected = 0;
	isDirtyFlag = false;
}
/*
Got rid of this because loading from a file can potentially fail.
Would need to notify caller that it has failed, which is not possible
through a constructor. So instead, first construct, then call
loadWorld().
World::World(string scriptFile) {
	//loadTextures("blah.txt");
	loadWorld(scriptFile);
	xOff = 0; yOff =0; zOff= 0; rX = 0; rY = 0; rZ = 0;
	sX = 1; sY = 1; sZ = 1;isSelected = 0;
	isDirtyFlag = false;
}*/

World::~World(){ 
	for (int i = 0; i < (int) getNumberOfObjects(); i++){
		delete getObject(i);
	}

}

int World::drawGroundGrid( int divisions, float x, float y, float height)
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

int World::getTransformedMotion( double patt_trans[3][4], int but, int key,int x, int y, double &xNew, double &yNew){
	double wa, wb, wc;
	double rotMat[3][3];
	object::getRotFromTrans(patt_trans, rotMat);
	arGetAngle(rotMat, &wa, &wb, &wc);

	//cout<<"Angles "<<180/3.14159*wa<<" "<<180/3.14159*wb<<" "<<180/3.14159*wc;
	//cout<<" Pos: "<<patt_trans[0][3]<<" "<<patt_trans[1][3]<<" "<<patt_trans[2][3]<<endl;

	//cout<<x<<" "<<y<<" "<<180/3.14159*wc;	
	xNew = 1*(x*cos(wc) - y * sin(wc));
	yNew = 1*(x*sin(wc) + y * cos(wc));
	//cout<<"new: "<<xNew<<" "<<yNew<<"sin(wc)"<<sin(wc)<<endl;	
	return 1;
}


/**
 * Moves the entire world.
 */
void World::move(double patt_trans[3][4],int but, int key, int x, int y){
	double xNew, yNew;

	// world is being modified, so set dirty flag
	isDirtyFlag = true;

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
	else {
		if (but == GLUT_LEFT_BUTTON){
			xOff += xNew; yOff -= yNew;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
			zOff -= y;
		}
	}

}


void World::loadTextures(char *textureFile){

	textureIndex.push_back(LoadGLTextureRepeat("steel01.bmp"));

	GLuint blah = LoadGLTextureRepeat("cement.bmp");
	cout<<"blah "<<blah<<endl;
	textureIndex.push_back(blah);
	cout<<"texindex at 1 "<<textureIndex[1]<<endl;

	//cout<<LoadGLTextureRepeat("steel01.bmp")<<endl;


	/*ifstream fin(textureFile);
	string line;
	while ( getline(fin,line) )
	{

	istringstream iss(line);
	string type;	
	iss>>type;
	if (type == "TEXTURE") {
	string filename;
	iss>>filename;
	cout<<filename<<endl;
	textureIndex.push_back(LoadGLTextureRepeat(filename.c_str()));
	}
	}
	*/

}


void World::initMenu(){
}



/**
 * Loads a world from a file.
 *
 * Reads the file line by line and then sets the fileName member to the name of the file.
 * Returns true if load was sucessful, false otherwise.
 */
bool World::loadWorld(string scriptFile){
	ifstream fin(scriptFile.c_str());
	string line;

	while ( getline(fin,line) )
	{

		istringstream iss(line);
		string type;	
		iss>>type;
		if (type == "MS3D") {
			string filename;
			float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ;
			iss>>filename>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ;
			cout<<filename<<xOff<<yOff<<zOff<<rX<<sX<<endl;
			objectPtrs.push_back(new myModel((int) getNumberOfObjects(), (char *) filename.c_str(), xOff,yOff,zOff,rX,rY,rZ,sX,sY,sZ));
		}
		else if (type == "RECTANGLE"){
			float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, x1, y1, x2, y2;
			iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>x1>>y1>>x2>>y2;
			objectPtrs.push_back( new rectangle((int) getNumberOfObjects(), 
				xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ, x1, y1, x2, y2));
		}
		else if (type == "SPHERE"){
			float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, radius;
			iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>radius;
			objectPtrs.push_back( new sphere((int) getNumberOfObjects(), 
				xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ, radius));
		}
		else if (type == "CUBE"){
			float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, size;
			iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>size;
			objectPtrs.push_back( new cube2((int) getNumberOfObjects(), 
				xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ, size));
		}
		else if (type == "PYRAMID"){
			float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, size;
			iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>size;
			objectPtrs.push_back( new pyramid((int) getNumberOfObjects(), 
				xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ, size));
		}

		else if (type == "CONE"){
			float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, radius, height;
			iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>radius>>height;
			objectPtrs.push_back( new cone((int) getNumberOfObjects(), 
				xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ, radius, height));
		}
		else if (type == "TRIANGLE"){
			float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, x1, y1, x2, y2, x3, y3;
			iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>x1>>y1>>x2>>y2>>x3>>y3;
			objectPtrs.push_back( new triangle((int) getNumberOfObjects(), 
				xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ, x1, y1, x2, y2, x3, y3));
		}
		else if (type == "CYLINDER"){
			float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, radius, height;
			iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>radius>>height;
			objectPtrs.push_back( new cylinder((int) getNumberOfObjects(), 
				xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ,radius, height));
		}

		else if (type == "PARTIALCYLINDER"){
			float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, radius, height, startAngle, arcAngle;
			iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>radius>>height>>startAngle>>arcAngle;
			objectPtrs.push_back( new  partialCylinder((int) getNumberOfObjects(), 
				xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ,radius, height, startAngle, arcAngle));
		}
		else if (type == "FILLARC"){
			float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ, radius, startAngle, arcAngle;
			iss>>xOff>>yOff>>zOff>>rX>>rY>>rZ>>sX>>sY>>sZ>>radius>>startAngle>>arcAngle;
			objectPtrs.push_back( new fillArc((int) getNumberOfObjects(), 
				xOff,yOff,zOff, rX, rY, rZ, sX, sY, sZ,radius, startAngle, arcAngle));
		} else {
			return false;
		}
	}

	// set file name
	fileName = scriptFile;
	// file is not dirty after being opened
	isDirtyFlag = false;
	return true;
}

//void World::loadWorld(){
//
//	objectPtrs.push_back(new myModel((int) getNumberOfObjects(), "chair.ms3d", 50,0,-50,0,1));
//	objectPtrs.push_back(new myModel((int) getNumberOfObjects(), "lcdtv2.ms3d", 50,0,-50,0,1));
//
//	//objects.push_back(new myModel((int) getNumberOfObjects(), "chair.ms3d", 50,-10,-50,0,1));
//	//objectPtrs.push_back(new rectangle(getNumberOfObjects(), 0,0,100, 100, 90));
//}

/**
 * Saves the world under the current file name if one exists.
 */
void World::saveWorld() {
	if (!fileName.empty()) {
		saveWorld(fileName);
	}
}

/**
 * Saves the world under a specific file name.
 */
void World::saveWorld(string scriptFile){
	ofstream outfile(scriptFile.c_str());

	if (outfile.is_open())
	{
		for (int i = 0; i< (int) getNumberOfObjects(); i++){

			outfile << getObject(i)->getDataString()<<endl;
		}
		outfile.close();
	}

	// set file name
	fileName = scriptFile;
	// file is no longer dirty
	isDirtyFlag = false;
}


void World::exportSL(string scriptFile){

	ofstream outfile(scriptFile.c_str());
	if (outfile.is_open())
	{
		for (int i = 0; i< (int) getNumberOfObjects(); i++){
			outfile<< "<primitive name=\"Object\" description=\"\" key=\"Num_231670488\" version=\"1\"> "<<endl;
			outfile<< "<states> "<< endl;
			outfile<<"<physics params=\"\">FALSE</physics> "<< endl;
			outfile<<"<temporary params=\"\">FALSE</temporary>"<<endl;
			outfile << "<phantom params=\"\">FALSE</phantom> "<<endl;
			outfile<< "</states>"<<endl;

			outfile<<  "<properties>"<<endl;
			outfile<<"<levelofdetail val=\"9\">"<<endl;

			outfile << getObject(i)->getSLDataString();

			outfile<<"<textures params=\"\">"<<endl;
			outfile<<"</textures>"<<endl;
			outfile<<"<scripts params=\"\">"<<endl;
			outfile<<"</scripts>"<<endl;
			outfile<<"</properties>"<<endl;
			outfile<<"</primitive>"<<endl;

		}

		outfile.close();
	}

}



void World::draw(){
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
	for (int i = 0; i < (int) getNumberOfObjects(); i++){
		if (getObject(i)->drawMode == NORMAL||getObject(i)->drawMode == WIREFRAME||getObject(i)->drawMode == OUTLINE){
			//push i onto namestack
			glPushName(i);
			getObject(i)->drawTopLevel(5,5,5);
			glPopName();
		}

	}

	for (int i = 0; i < (int) getNumberOfObjects(); i++){
		if (getObject(i)->drawMode == TRANSPARENT){
			//push i onto namestack
			glPushName(i);
			getObject(i)->drawTopLevel(5,5,5);
			glPopName();
		}
	}

	glPopMatrix();
}

/**
Adds an object to the world
*/
void World::addObject(object *o) {
	// set dirty flag
	isDirtyFlag = true;

	// observe the object
	o->attachObserver(*this);

	// add the object
	objectPtrs.push_back(o);
}

/**
 * Adds and object of specified type
 */
void World::addObject(int objectType) {
	// set dirty flag
	isDirtyFlag = true;

	// add the object
	addObject(createObject(objectType));
}

/**
 * Adds an object from a model
 */
void World::addObject(std::string modelName) {
	// set dirty flag
	isDirtyFlag = true;

	// add the object
	addObject(createObject(modelName));
}



/**
 * Creates an object of specified type
 */
object *World::createObject(int objectType) {
	int nObjects = (int)getNumberOfObjects();
	object *o;

	switch (objectType) {
		case ObjectTypes::RECTANGLE:
			o = new rectangle(nObjects, -10,-10,50, 50, 90);
			break;
		case ObjectTypes::TRIANGLE:
			o = new triangle(nObjects, -50,50,-50, -50,-50,50, -50, 0,50, 45);
			break;
		case ObjectTypes::FILLARC:
			o = new fillArc(nObjects, -50,-50,100, 100, 50, 90);
			break;
		case ObjectTypes::PARTIALCYLINDER:
			o = new partialCylinder(nObjects, -50,-50,100, 100, 0,180, 0);
			break;
		case ObjectTypes::SPHERE:
			o = new sphere(nObjects, 0,0,30,30);
			break;
		case ObjectTypes::CUBE:
			o = new cube2(nObjects, 0,30,60,30);
			 //PlaySound("squish.wav", NULL, SND_FILENAME | SND_SYNC);
			break;
		case ObjectTypes::TORUS:
			o = new torus(nObjects, 0,30,60,10, 5);
			break;
		case ObjectTypes::WALL:
			o = new wall(nObjects, 0,30,60,30);
			break;
		case ObjectTypes::CYLINDER:
			o = new cylinder(nObjects, 10, 10);
			break;
		case ObjectTypes::CONE:
			o = new cone(nObjects, 0,0,0, 10, 30);
			break;
		case ObjectTypes::PYRAMID:
			o = new pyramid(nObjects, 0,30,60, 30);
			break;
		case ObjectTypes::LINE:
			o = new line(nObjects, 0, 0, 30, 30);
			break;

/*

		case ObjectTypes::STOVE:
			o = new rectangle(nObjects, -10,-10,50, 50, 90);
			break;
		case ObjectTypes::TRIANGLE:
			o = new triangle(nObjects, -50,50,-50, -50,-50,50, -50, 0,50, 45);
			break;
*/













	}

	return o;
}



object *World::createObject(std::string modelName) {
	int nObjects = (int)getNumberOfObjects();
	object *o;

	
	//std::string fullPath("models/");

//fullPath.append(modelName);
//fullPath.append(".ms3d");

o = new myModel(nObjects, (char *) modelName.c_str(), 0,0,0,0,1.5);
//o = new pyramid(nObjects, 0,30,60, 30);
	return o;
}

void World::update(const ISubject &subject) {
	isDirtyFlag = true;
}