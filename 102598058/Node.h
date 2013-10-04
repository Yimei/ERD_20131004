#ifndef _Node_H_ 
#define _Node_H_
#include <string>
#include "Component.h"
using namespace std;
class Node:public Component
{
public:
	Node();
	virtual ~Node();
	virtual void connectTo(Component* component)=0;
	virtual bool canConnectTo(Component* component)=0; 
private:
	string type;
};
#endif