#include <string>
#include <iostream>
#include "Relationship.h"
#define E "E"
#define TWO 2
using namespace std;
Relationship::Relationship():Node(){
	for (int i = 0; i < connectedEntity.size();i++)
	{
		connectedEntity[i] = NULL;
	}
}
void Relationship::connectTo(Component* component){
}
bool Relationship::canConnectTo(Component* component){
	
	if (component->getType()!= E)
	{
		return false;
	}
	else if(connectedEntity.size() == TWO)
	{
		return false;
	}
	else  
	{
		setConnections(component);
		return true;
	}
}
void Relationship::setConnections(Component* component)
{
	connectedEntity.push_back(component);
}
vector<Component*> Relationship::getConnections()
{
	return connectedEntity;
}
Relationship::~Relationship(){

}