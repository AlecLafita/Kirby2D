
#include "BaseObject.h"


class PortalObject : public BaseObject
{
public:
	PortalObject(int type);
	~PortalObject(){}

	void init(ShaderProgram &shaderProgram, Scene* scene);
	void update(int deltaTime);

	glm::ivec2 getSize() { return glm::ivec2(BIG_OBJECT_SIZE_X, BIG_OBJECT_SIZE_Y); } 

	int getType(){return type;}

private:
	bool type;
};

