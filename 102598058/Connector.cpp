#include <string>
#include "Connector.h"
using namespace std;

Connector::Connector():Component(){
	_nodeOneConnectionId=0;
	_nodeTwoConnectionId=0;
}
void Connector::connectTo(Component* component){
	this->setConnections(component);
}
bool Connector::canConnectTo(Component* component){
	return false;
}
int Connector::getNodeOneConnectionId()
{
	return _nodeOneConnectionId;
}
int Connector::getNodeTwoConnectionId()
{
	return _nodeTwoConnectionId;
}
Connector::~Connector(){

}