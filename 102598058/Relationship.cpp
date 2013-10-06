#include <string>
#include <iostream>
#include "Relationship.h"
using namespace std;

Relationship::Relationship():Node(){
	for (int i = 0; i < connectedEntity.size();i++)
	{
		connectedEntity[i] = NULL;
	}
}
void Relationship::connectTo(Component* component){
	//this->setConnections(component);
}
bool Relationship::canConnectTo(Component* component){
	
	if (component->getType()!="E")
	{
		return false;
	}
	else if(connectedEntity.size() == 2)
	{
		return false;
	}
	else  
	{
		connectedEntity.push_back(component);
		return true;
	}
}
Relationship::~Relationship(){

}