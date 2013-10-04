#include <string>
#include "ComponentFactory.h"

#include "Connector.h"
#include "Attribute.h"
#include "Entity.h"
#include "Relationship.h"

using namespace std;
ComponentFactory::ComponentFactory(){
}
Component* ComponentFactory::createComponent(string type){
	if(type  == "A")
	{
		return new Attribute();
	}
	else if(type == "E")
	{
		return new Entity();
	}
	else if(type == "R")
	{
		return new Relationship();
	}
	else if(type == "C")
	{
		return new Connector();
	}
	else
	{
		return NULL;
	}
}
ComponentFactory::~ComponentFactory(){

}