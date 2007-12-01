#ifndef MULTISHAPE_H
#define MULTISHAPE_H

class multiShape:public object{
public:
	multiShape(){};	
	multiShape(std::vector<object *> _shapePtrs,
		float _x, float _y,  float _z, 
		float _rX, float _rY, float _rZ,
		float _sX, float _sY, float _sZ){

		tMatrix.loadIdentity();
		tMatrix.translate(_x, _y, _z);		

		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ = _sZ;
		//shapePtrs = _shapePtrs;
		//copy(_shapePtrs.begin(), _shapePtrs.end(), shapePtrs.begin());
		copy(_shapePtrs.begin(), _shapePtrs.end(), std::back_insert_iterator<std::vector<object *> >(shapePtrs));
		
		for (int i = 0 ; i < (int) shapePtrs.size(); i++) {
			shapePtrs[i]->isSelected = 0;
		}

		centroid.x = 0; centroid.y = 0; centroid.z = 0;
		calcCentroid();
	};

	/*
	Destructor. Free up memory for all group members
	*/
	~multiShape() {
		ostringstream o;
		OutputDebugStr("multiShape destructor\n");
		for (int i = 0; i < (int) shapePtrs.size(); i++) {
			o.str("");
			o << "Deleting object " << i << " from multiShape: " << shapePtrs[i]->getDataString() << endl;
			OutputDebugStr(o.str().c_str());
			delete shapePtrs[i];
		}
	}

	object* clone()   { return new multiShape(*this); }

	std::vector<object *> getObjects() {
		return shapePtrs;
	}

	void calcCentroid(){
		
		float x, y, z;
		x = 0; y = 0; z = 0;
		if (shapePtrs.size() == 0) return;

		for (int i = 0 ; i < (int) shapePtrs.size(); i++){
			x+= shapePtrs[i]->tMatrix.m_matrix[12];
			y+= shapePtrs[i]->tMatrix.m_matrix[13];
			z+= shapePtrs[i]->tMatrix.m_matrix[14];
		}

		centroid.x = x/ shapePtrs.size();
		centroid.y = y/ shapePtrs.size();
		centroid.z = z/ shapePtrs.size();

		std::cout<<"Centroid: "<<centroid.x<<" "<<centroid.y<<" "<<centroid.z<<std::endl;
	}


	virtual void move(double patt_trans[3][4],int but, int key, int x, int y)
	{	
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
		else if (key == GLUT_ACTIVE_CTRL)
		{
			if (but == GLUT_LEFT_BUTTON)
			{
				//rX += x; 
				//rotate each object about the centroid
				for (int i = 0 ; i < (int) shapePtrs.size(); i++)
				{
					shapePtrs[i]->rotate(x, centroid.x, centroid.y, centroid.z, 0, 1, 0);
					//x+= shapePtrs[i]->xOff;
					//y+= shapePtrs[i]->yOff;
					//z+= shapePtrs[i]->zOff;
				}
				calcCentroid();
				////rY-=y; //yOff += y;
			}

			else if (but == GLUT_MIDDLE_BUTTON)
			{
				rX+=x;
			}
		}
		else
		{

			if (but == GLUT_LEFT_BUTTON){

				//xOff += xNew; zOff += yNew;
				for (int i = 0 ; i < (int) shapePtrs.size(); i++){
					shapePtrs[i]->tMatrix.translate(xNew, 0, yNew);
				}
				calcCentroid();
			}
			else if (but == GLUT_MIDDLE_BUTTON){
				//yOff -= y;
				for (int i = 0 ; i < (int) shapePtrs.size(); i++){
					shapePtrs[i]->tMatrix.translate(0, -y, 0);
				}

			}
		}

		notifyObservers();
	}

	/*
	Applies the transformations and draws each object within the multiShape using
	its drawTopLevel method
	*/
	virtual void drawTopLevel(float snapPos, float snapRot, float snapScale) {
		glPushMatrix();

		applyTransform();

		for (int i = 0; i < (int) shapePtrs.size(); i++)
		{		
			shapePtrs[i]->drawTopLevel(snapPos, snapRot, snapScale);
		}

		glPopMatrix();
	}

	/*
	Draws the multiShape with all transformations of the individual objects as well as
	the group transformation applied.
	*/
	virtual void drawTransformed()
	{
		glPushMatrix();
		applyTransform();

		// draw each object in the multishape
		for (int i = 0; i < (int) shapePtrs.size(); i++)
		{		
			shapePtrs[i]->drawTransformed();
		}

		glPopMatrix();
	}

	/*
	Applies the transformations associated with the object by loading the transformation
	matrix and scaling by sX, sY, sZ
	*/
	virtual void applyTransform()
	{
		// move the entire group
		glMultMatrixf(tMatrix.getMatrix());
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sY, sZ);
	}

	/*
	Highlights the group.
	*/
	virtual void highlight() {
		glPushMatrix();
		applyTransform();
		// draw each object in the multishape
		for (int i = 0; i < (int) shapePtrs.size(); i++)
		{		
			shapePtrs[i]->highlight();
		}
		glPopMatrix();
	}

	/*
	Removes all items from the group without freeing their memory. This is necessary for the
	ungrouping functionality. Objects are moved to the world and need to be detached from
	the multiShape so their memory is not freed when the multiShape is deleted.
	*/
	void detachObjects() {
		shapePtrs.clear();
	}
	
	// The objects that are part of the group
	std::vector<object *> shapePtrs;

	// The centroid vertex of the group
	vertex centroid;
	
};


#endif