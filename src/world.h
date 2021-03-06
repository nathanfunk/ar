#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
#include "object.h"
#include "IObserver.h"

#include "Texture.h"

//Texture * LoadTGA(char *);
GLuint LoadTGA(char *);

using namespace std;

namespace ms3dglut {

class World : public IObserver {
private:
	string fileName;
	bool isDirtyFlag; // true if world has been edited since last save
	bool drawGrid;

public:
	vector<object *> objectPtrs;
	//stdx::ptr_vector<object> objects;
	//std::vector <myModel> modelVec;
	vector <GLuint> textureIndex;

	Texture texture[2];

	vector<Texture *> texturePtrs;

	float xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ;
	int isSelected;

	World();
	World(const string &scriptFile);
	~World();
	int drawGroundGrid( int divisions, float x, float y, float height);
	int getTransformedMotion( double patt_trans[3][4], int but, int key,int x, int y, double &xNew, double &yNew);
	virtual void move(double patt_trans[3][4],int but, int key, int x, int y);
	void loadTextures(char *textureFile);
	void initMenu();
	//void loadWorld();
	void World::setTexture(const string &modelName);
	bool loadWorld(const string &scriptFile);
	void saveWorld();
	void saveWorld(const string &scriptFile);
	void exportSL(const string &scriptFile);
	void draw();
	void addObject(object *o);
	void addObject(int objectType);
	void addObject(const string& modelName);
	object *createObject(int objectType);
	object *createObject(const string &modelName);
	int getNumberOfObjects() {return (int)objectPtrs.size();}
	object *getObject(int i) {return objectPtrs[i];}
	string getFileName() {return fileName;}
	bool isDirty() {return isDirtyFlag;}
	bool hasFileName() {return !fileName.empty();}
	void update(const ISubject &subject);
	void removeSelected();
	void setDrawGrid(bool value) {drawGrid = value;}
};
}
#endif