#ifndef _Attribute_H_ 
#define _Attribute_H_
#include <string>
#include "Node.h"
#include "Connector.h"
using namespace std;
class Attribute:public Node{
public:
	Attribute();
	virtual ~Attribute();
	void connectTo(Component* component);
	bool canConnectTo(Component* component);
private:
	Connector* connector;
	Component* connectedEntity;
};
#endif