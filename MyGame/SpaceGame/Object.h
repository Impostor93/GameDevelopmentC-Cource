#include "Position.h"
class GameObject
{
public:
	GameObject(Position position);
	~GameObject();

	Position getPosition();
	void setPosition(Position position);

	void virtual Visualise() = 0;
	void virtual Destroy();

protected:
	Position _position;
};
