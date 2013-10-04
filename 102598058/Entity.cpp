#include <string>
#include <iostream>
#include "Entity.h"
using namespace std;
Entity::Entity():Node(){
}
void Entity::connectTo(Component* component){
	this->setConnections(component);
}
bool Entity::canConnectTo(Component* component){
	if (component->getType() == "E")//�Orelationship �� attribute
	{
		return false;
	}
	else //����s�P�@��A or R
	{
		hadConnected(component);
	}
}
bool Entity::hadConnected(Component* component)
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
Entity::~Entity(){

}