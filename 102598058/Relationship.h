#ifndef _Relationship_H_ 
#define _Relationship_H_
#include <string>
#include <vector>
#include "Node.h"
using namespace std;
class Relationship:public Node{
public:
	Relationship();
	virtual ~Relationship();
	void connectTo(Component* component);
	bool canConnectTo(Component* component);
	
private:
	vector<Component*> connectedEntity;
};
#endif