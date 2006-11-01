
class multiShape:public object{
public:
	multiShape(){};
	multiShape(std::vector<object *> _shapePtrs
	, float _x, float _y,  float _z, float _rX, float _rY, float _rZ, float _sX, float _sY, float _sZ){
		xOff = _x; yOff = _y;  zOff = _z; 
		rX = _rX; rY = _rY; rZ = _rZ;
		sX = _sX; sY = _sY; sZ = _sZ;
		//shapePtrs = _shapePtrs;
		//copy(_shapePtrs.begin(), _shapePtrs.end(), shapePtrs.begin());
		copy(_shapePtrs.begin(), _shapePtrs.end(), std::back_insert_iterator<std::vector<object *> >(shapePtrs));
	};

object* clone()   { return new multiShape(*this); }

std::vector<object *> ungroup(){
	
 for (std::vector<object *>::iterator it = shapePtrs.begin(); it!=shapePtrs.end();) {
	 (*it)->transform(xOff, yOff, zOff, rX, rY, rZ, sX, sY, sZ);
	 ++it;
 }
	return shapePtrs;
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
		rX += x; 
		////rY-=y; //yOff += y;
		}
		else if (but == GLUT_RIGHT_BUTTON){
		rX += x;
		}
		else if (but == GLUT_MIDDLE_BUTTON){
		rX+=x;
		}
		}


		else{


		if (but == GLUT_LEFT_BUTTON){
		
			xOff += xNew; zOff += yNew;



		}
		else if (but == GLUT_MIDDLE_BUTTON){
		 yOff -= y;
		}
		}

	}





	virtual void	draw(){


		glPushMatrix();		
		glTranslatef(xOff,yOff,zOff);
		glRotatef(rX,0,1,0);
		glRotatef(rY,1,0,0);
		glScalef(sX, sY, sZ);



		for (int i = 0; i < (int) shapePtrs.size(); i++){
			if (shapePtrs[i]->drawMode == NORMAL||shapePtrs[i]->drawMode == WIREFRAME){
			//push i onto namestack
			glPushName(i);
				shapePtrs[i]->drawTopLevel(5,5,5);
			glPopName();
			}

		}
		for (int i = 0; i < (int) shapePtrs.size(); i++){
			if (shapePtrs[i]->drawMode == TRANSPARENT){
			//push i onto namestack
			glPushName(i);
			shapePtrs[i]->drawTopLevel(5,5,5);
			glPopName();
			}


		}

		glPopMatrix();
	}


	

	std::vector<object *> shapePtrs;
	
	
};


