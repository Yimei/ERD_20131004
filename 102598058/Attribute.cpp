#include <string>
#include <iostream>
#include "Attribute.h"
using namespace std;
Attribute::Attribute():Node()
{	
	for (int i = 0; i < connectedEntity.size();i++)
		connectedEntity.push_back(NULL);
}
void Attribute::connectTo(Component* component){
	//this->setConnections(component);
}
bool Attribute::canConnectTo(Component* component){
	if ((component->getType() != "E") )//不會有重複connector問題
	{
		return false;
	}
	else if(connectedEntity.size() >0)
	{
		return false;
	}
	else
	{
		connectedEntity.push_back(component);
	}
}
vector<Component*> Attribute::getConnections()
{
	return connectedEntity;
}
Attribute::~Attribute(){
	//delete connectedEntity;
}