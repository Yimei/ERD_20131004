#include <string>
#include <iostream>
#include "Entity.h"
using namespace std;
Entity::Entity():Node(){
}
void Entity::connectTo(Component* component){
	//this->setConnections(component);
}
bool Entity::canConnectTo(Component* component){
	if (component->getType() == "E")//¬Orelationship ©Î attribute
	{
		return false;
	}
	else 
	{
		
			setConnections(component);
		
		return true;
	}
}
void Entity::setConnections(Component* component)
{
	this->connectedNodesVector.push_back(component);
}
vector<Component*> Entity::getConnections()
{
	return connectedNodesVector;
}
Entity::~Entity(){

}