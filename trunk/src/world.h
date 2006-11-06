#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
#include "object.h"
using namespace std;

namespace ms3dglut {

class World {
private:
	string fileName;
	bool isDirtyFlag; // true if world has been edited since last save

public:
	vector<object *> objectPtrs;
	//stdx::ptr_vector<object> objects;
	//std::vector <myModel> modelVec;
	vector <GLuint> textureIndex;

	float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ;
	int isSelected;

	World();
	World(string scriptFile);
	~World();
	int drawGroundGrid( int divisions, float x, float y, float height);
	int getTransformedMotion( double patt_trans[3][4], int but, int key,int x, int y, double &xNew, double &yNew);
	virtual void move(double patt_trans[3][4],int but, int key, int x, int y);
	void loadTextures(char *textureFile);
	void initMenu();
	//void loadWorld();
	bool loadWorld(string scriptFile);
	void saveWorld();
	void saveWorld(string scriptFile);
	void exportSL(string scriptFile);
	void draw();
	void addObject(object *o);
	void addObject(int objectType);
	object *createObject(int objectType);
	size_t getNumberOfObjects() {return objectPtrs.size();}
	string getFileName() {return fileName;}
	bool isDirty() {return isDirtyFlag;}
	bool hasFileName() {return !fileName.empty();}
};
}
#endif