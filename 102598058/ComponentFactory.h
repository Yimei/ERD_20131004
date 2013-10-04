#ifndef _ComponentFactory_H_ 
#define _ComponentFactory_H_
#include <string>
#include "Component.h"
using namespace std;
class ComponentFactory{
public: 
	ComponentFactory();
	virtual ~ComponentFactory();
	Component* createComponent(string type);
};
#endif