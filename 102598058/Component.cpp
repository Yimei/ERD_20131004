#include "Component.h"
#include <string>
using namespace std;
Component::Component(){
	_id = 0;
	_text = "";
	_type = "";
	_connectionsNum = 0;
}
void Component::setID(int id){
	_id = id;
}
void Component::setType(string type){
	_type = type;
}
void Component::setText(string name){
	_text = name;
}
void Component::setConnections(Component* component){
	_connectionsVector.push_back(component);
}
void Component::setConnectionsNum()
{
	_connectionsNum++;
}
int Component::getID(){
	return _id;
}
string Component::getText(){
	return _text;
}
string Component::getType(){
	return _type;
}
vector<Component*> Component::getConnections()
{
	return _connectionsVector;
}
int Component::getConnectionsNum(){
	return _connectionsNum;
}
void Component::connectTo(Component* component){
}
bool Component::canConnectTo(Component *component){
	return true;
}
Component::~Component(){
	
}
