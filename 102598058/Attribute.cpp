#include <string>
#include <iostream>
#include "Attribute.h"
using namespace std;
Attribute::Attribute():Node(){	
	connectedEntity = NULL;
}
void Attribute::connectTo(Component* component){
	//this->setConnections(component);
}
bool Attribute::canConnectTo(Component* component){
	if ((component->getType() != "E") )//���|������connector���D
	{
		return false;
	}
	else if(connectedEntity!=NULL)
	{
		return false;
	}
	else
	{
		connectedEntity = component;
	}
}
Attribute::~Attribute(){
	delete connectedEntity;
}