#ifndef MYMODEL_H
#define MYMODEL_H

#include "shapeClasses.h"


/* Wrapper around Portalib milkshape model loader 
Farooq Ahmad 2006
*/



class myModel:public object{
public:
	myModel(){		
		pModel = new MilkshapeModel();
		xOff = 0; yOff = 0; zOff = 0; rX = 0; rY=0; sX = 1;sY = 1; sZ = 1;  //offsets, rotation,scale

		timeStep = 0; actionStep = 0; isSelected = 0; isVisible = 1; velocity = 10; rotVel = 10;

		std::vector<float> initial; 
		initial.push_back(xOff);initial.push_back(yOff);initial.push_back(zOff);
		initial.push_back(rX);initial.push_back(sX);initial.push_back(0); //timestep
		script.push_back(initial);

		}
	myModel(int _name, char *modelFile, float x, float y, float z, float r, float s){
		name = _name;  
		modelFileName = modelFile;
		pModel = new MilkshapeModel();
		init(modelFile);
		xOff = x; yOff = y; zOff = z; rX = r; rY=0;sX = s; sY = s; sZ = s;
		timeStep = 0; actionStep = 0; isSelected = 0; isVisible = 1;velocity = 10;rotVel = 10;


		std::vector<float> initial; 
		initial.push_back(xOff);initial.push_back(yOff);initial.push_back(zOff);
		initial.push_back(rX);initial.push_back(sX);initial.push_back(0); //timestep
		script.push_back(initial);
		//initial[3] = 15; initial[5] = 20; script.push_back(initial);
		//initial[3] = 30;initial[5] = 2;script.push_back(initial);


	}


myModel(int _name, char *modelFile, float _xOff, float _yOff, float _zOff, 
		float _rX,float _rY,float _rZ, float _sX, float _sY, float _sZ){
		name = _name;  
		modelFileName = modelFile;
		pModel = new MilkshapeModel();

		init(modelFile); 
		xOff = _xOff; yOff = _yOff; zOff = _zOff; rX = _rX; rY=_rY; rZ = _rZ; sX = _sX; sY = _sY; sZ = _sZ;
		timeStep = 0; actionStep = 0; isSelected = 0; isVisible = 1;velocity = 10;rotVel = 10;


		std::vector<float> initial; 
		initial.push_back(xOff);initial.push_back(yOff);initial.push_back(zOff);
		initial.push_back(rX);initial.push_back(sX);initial.push_back(0); //timestep
		script.push_back(initial);
		//initial[3] = 15; initial[5] = 20; script.push_back(initial);
		//initial[3] = 30;initial[5] = 2;script.push_back(initial);


	}



	myModel(int _name, char *modelFile, char *scriptFile, float x, float y, float z, float r, float s){
		name = _name;

		modelFileName = modelFile;
		scriptFileName = scriptFile;
		//std::ostringstream m; m << modelFile; modelFileName = m.str();
		//std::ostringstream f; f << scriptFile; scriptFileName = f.str();


		pModel = new MilkshapeModel();
		init(modelFile);
		xOff = x; yOff = y; zOff = z; rX = r; rY=0;sX = s; sY = s; sZ = s;
		timeStep = 0; actionStep = 0; isSelected = 0; isVisible = 1;velocity = 10;rotVel = 10;
		loadScript(scriptFile);	

		///setGoal(-100,-100, 180, 1, 1);


	}
	object* clone()   { return new myModel(*this); }

	
	std::string getDataString(){
		std::ostringstream data;
		data<<"MS3D "<<modelFileName<<" "<<xOff<<" "<<yOff<<" "<<zOff<<" "<<rX<<" "<<rY<<" "<<rZ<<" "<<sX<<" "<<sY<<" "<<sZ;	
		return data.str(); 
	}



	int loadScript(char *scriptFile){
		//open the script file, load the script vector	
		float Num;
		std::vector<float> scriptLine;

		std::ifstream inFile(scriptFile, std::ios::in);	
		if (inFile.fail())
		{std::cout << "Could not open readfile.txt" << std::endl;exit(1);	}

		inFile >> Num;
		scriptLine.push_back(Num);
		while (! inFile.fail())
		{
			inFile >> Num;
			std::cout<<Num<<" ";

			scriptLine.push_back(Num);
			if (scriptLine.size() >= 6){ 
				script.push_back(scriptLine);
				scriptLine.clear();
				std::cout<<std::endl;
			}
		}
		inFile.close();

			return 0;
	};

	int init(char *modelFile){
		if ( pModel->loadModelData( modelFile ) == false )		// Loads The Model And Checks For Errors
		{
			MessageBox( NULL, "Couldn't load the model", "Error", MB_OK | MB_ICONERROR );
			return 0;													// If Model Didn't Load Quit
		}

		//pModel->reloadTextures();

		return 1;
	}

	void reload(){
	pModel->reloadTextures();
	}

	float distance(float x1, float y1,  float x2, float y2){
		return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	}

	void setGoal(float xGoal, float zGoal, float rGoal, float pDelta, float rDelta){
		//plan a path, put in into the motion script
		std::vector<float> pos; 
		pos.push_back(xOff);pos.push_back(yOff);pos.push_back(zOff);
		pos.push_back(rX);pos.push_back(sX);pos.push_back(0);

		
		//first turn to face the goal
		float dir = (180/PI)*atan2(zGoal - pos[2], xGoal - pos[0]);
		float rDist = dir - pos[3]; float rDistLast;
		float rStep = rDist/abs(rDist)*rotVel;
		std::cout<<"rCurr : "<<pos[3]<<"rstep"<<rStep<<" goal: "<<dir<<std::endl;
		while (abs(rDist) > rDelta){
			pos[3] += rStep;
			rDistLast = rDist;
			rDist = pos[3] - dir;
			if (abs(rDist) > abs(rDistLast)) break;
			////std::cout<<"Adding "<<pos[3]<<" dist: "<<rDist<<std::endl;
			script.push_back(pos);
		}

		float dist = distance(pos[0], pos[2], xGoal, zGoal); float distLast;
		float xStep = (xGoal - pos[0])/dist * velocity;
		float zStep = (zGoal - pos[2])/dist * velocity;
		std::cout<<"goal: "<<xGoal<<" "<<zGoal<<" curr: "<<pos[0]<<" "<<pos[2]<<" dist: "<<dist<<" step: "<<xStep<<" "<<zStep<<std::endl;
		while (dist> pDelta)
		{
			pos[0] += xStep;
			pos[2] += zStep;
			distLast = dist;
			dist = distance(pos[0], pos[2], xGoal, zGoal);
			if (dist > distLast) break;
			////std::cout<<"Adding "<<pos[0]<<" "<<pos[2]<<" dist: "<<dist<<std::endl;
			script.push_back(pos);
		}
		
		//turn in the goal direction
		 dir = rGoal;
		 rDist = dir - pos[3];
		 rStep = rDist/abs(rDist)*rotVel;
		std::cout<<"rCurr : "<<pos[3]<<"rstep"<<rStep<<" goal: "<<dir<<std::endl;
		while (abs(rDist) > rDelta){
			pos[3] += rStep;
			rDistLast = rDist;
			rDist = pos[3] - dir;
			if (abs(rDist) > abs(rDistLast)) break;
			////std::cout<<"Adding "<<pos[3]<<" dist: "<<rDist<<std::endl;
			script.push_back(pos);
		}


	}

	//void select(){ isSelected = 1;};
	//void deselect(){ isSelected= 0;};
	///int isSelect(){return isSelected;};


	void setPosition(float x, float y, float z, float r, float s){
		xOff = x;
		yOff = y;
		zOff = z;
		rX = r;
		sX = s; sY = s; sZ = s;//sOff = s;
	}

	void advanceScript(){

		//if (script.size()<=1) return;

		
		if (timeStep++ > (int) script[actionStep][5]) { actionStep ++; timeStep = 0;}
		if (actionStep >= (int) script.size()){ actionStep = 0; timeStep = 0; };

		//std::cout<<"MOVING TO "<< script[actionStep][0]<<" "
			//<<script[actionStep][1]<<" "<<script[actionStep][2]<<std::endl;

		setPosition( script[actionStep][0], script[actionStep][1], script[actionStep][2],
				script[actionStep][3], script[actionStep][4]);

	}

	int actionStep;
	int timeStep;
	std::vector <std::vector <float> > script; //x,y,z  timedelayAfter ///x, y, z, rx, ry, rz, anBegin, anEnd;








	void draw(){

	//advanceScript();

	
	if (isVisible == 1){

if (isSelected == 1){
	highlight();
	}


//glPushName(name);

	glPushMatrix();		
   glTranslatef(xOff,yOff,zOff);

	//glTranslatef(xOff,zOff,yOff);
	glRotatef(rX,0,1,0);
	glRotatef(rY, 1, 0, 0);
	


	glScalef(sX, sY, sZ);
	//pModel->reloadTextures();
startLighting2();

	glEnable( GL_TEXTURE_2D );	
	pModel->draw();
	glDisable(GL_TEXTURE_2D );	
	glPopMatrix();
//glPopName();

	}
	
	}

	int name;
	Model *pModel;
	//float xOff, yOff, zOff, rX, sOff;
	
	//int isSelected; 
	int isVisible;

	float xGoal, yGoal, zGoal, rGoal, sGoal, deltaGoal, velocity, rotVel;
	std::string modelFileName, scriptFileName;

};

#endif