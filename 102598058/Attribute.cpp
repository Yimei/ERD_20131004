#include <string>
#include <iostream>
#include "Attribute.h"
using namespace std;
Attribute::Attribute():Node(){	
}
void Attribute::connectTo(Component* component){
	this->setConnections(component);
}
bool Attribute::canConnectTo(Component* component){
	
	if (component->getType() == this->getType())
	{
		return false;
	}
	if ((component->getType()=="E") && (this->getConnectionsNum()==0))//不會有重複connector問題
	{
		component->setConnectionsNum();
		this->setConnectionsNum();
		return true;
	}
	else
	{
		return false;
	}
}
Attribute::~Attribute(){

}