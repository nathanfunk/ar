#ifndef SCENE_H
#define SCENE_H

//scene.txt:
//object1name x y z rx ry rz scale ms3dfile

#include <String>


class Object{
public:
	Object(String _Name, float x, float y, float z, char *fileName);
	String Name;
	int pos[3]; //position and rotation in scene
	int rot[3];
	int scale;
	int radius; //radius of bounding sphere
	int Check_collision(Object);

	virtual void Draw();
	virtual void Animate(int frame1, int frame2);

protected:
	loadObject(char *fileName);

}

Object::Object(String _Name, char *fileName){
	Name = _Name;
}

class scene{
	public: 
		scene(char *scenefile);
		update(); //update the state of each object

	protected:	
		vector<Objects> Objects;
}
//the scene graph -hah


#endif // ndef SCENE_H