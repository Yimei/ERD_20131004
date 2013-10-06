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
		if(component->getType() == "A")
		{
			setConnections(component);
		}
		return true;
	}
}
void Entity::setConnections(Component* component)
{
	this->attributesVector.push_back(component);
}
Entity::~Entity(){

}