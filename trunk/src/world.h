#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "object.h"
using namespace std;

namespace ms3dglut {

class World {
public:
	vector<object *> objectPtrs;
	//stdx::ptr_vector<object> objects;
	//std::vector <myModel> modelVec;
	vector <GLuint> textureIndex;

	float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ;
	int isSelected;

	World();
	World(char *scriptFile);
	~World();
	int drawGroundGrid( int divisions, float x, float y, float height);
	int getTransformedMotion( double patt_trans[3][4], int but, int key,int x, int y, double &xNew, double &yNew);
	virtual void move(double patt_trans[3][4],int but, int key, int x, int y);
	void loadTextures(char *textureFile);
	void initMenu();
	void loadWorld(char *scriptFile);
	void loadWorld();
	void saveWorld(char *scriptFile);
	void exportSL(char *scriptFile);
	void draw();
	void addObject(object *o);
	void addObject(int objectType);
	object *createObject(int objectType);
	size_t getNumberOfObjects();
};
}
#endif