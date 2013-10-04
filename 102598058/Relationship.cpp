#include <string>
#include <iostream>
#include "Relationship.h"
using namespace std;

Relationship::Relationship():Node(){

}
void Relationship::connectTo(Component* component){
	this->setConnections(component);
}
bool Relationship::canConnectTo(Component* component){
	
	if (component->getType()!="E")
	{
		return false;
	}
	else if(_connectionsVector.size()==2)
	{
		return false;
	}
	else  
	{
		hadConnected(component);
	}
}
bool Relationship::hadConnected(Component* component)
{
	for (int i = 0; i < _connectionsVector.size();i++)
	{
		if (_connectionsVector[i]->getID() == component->getID())
		{
			cout << "The node '" << this->getID() << "' has already been connected to component '" << component->getID() << "'." << endl;
			return false;
		}
	}
	_connectionsVector.push_back(component);
	return true;
}
Relationship::~Relationship(){

}