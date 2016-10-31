
#include "BaseObject.h"


class PortalObject : public BaseObject
{
public:
	PortalObject(int type, int index);
	~PortalObject(){}

	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);

	glm::ivec2 getSize() { return glm::ivec2(OBJECT_SIZE_X, BIG_OBJECT_SIZE_Y); } 

	int getType(){return type;}
	int getIndex(){return index;}

private:
	bool type;
	int index;
};

