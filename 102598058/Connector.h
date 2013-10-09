#ifndef _Connector_H_ 
#define _Connector_H_
#include <string>
#include "Component.h"
using namespace std;
class Connector:public Component{
public:
	Connector();
	virtual ~Connector();
	int getNodeOneConnectionId();
	int getNodeTwoConnectionId();
	void connectTo(Component* component);
	bool canConnectTo(Component* component);
	vector<Component*> getConnections();
	int _nodeOneConnectionId;
	int _nodeTwoConnectionId;
private:
	string type;
	vector<Component*> connectedComponent;
};
#endif