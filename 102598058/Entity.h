#ifndef _Entity_H_ 
#define _Entity_H_
#include <vector>
#include <string>
#include "Node.h"
using namespace std;
class Entity:public Node{
public:
	Entity();
	virtual ~Entity();
	bool hadConnected(Component* component);
	void connectTo(Component* component);
	bool canConnectTo(Component* component);
private:
	vector<Component*> _connectionsVector;
};
#endif