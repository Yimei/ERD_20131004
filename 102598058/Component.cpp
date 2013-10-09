#include "Component.h"
#include <string>
using namespace std;
Component::Component(){
	_id = 0;
	_text = "";
	_type = "";
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
int Component::getID(){
	return _id;
}
string Component::getText(){
	return _text;
}
string Component::getType(){
	return _type;
}
void Component::connectTo(Component* component)
{
}
bool Component::canConnectTo(Component *component){
	return true;
}
Component::~Component()
{
}
