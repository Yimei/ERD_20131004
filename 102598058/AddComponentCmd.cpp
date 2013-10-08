#include "AddComponentCmd.h"

AddComponentCmd::AddComponentCmd(ERModel* model, string type):Command()
{
	eRModel = model;
	componentType = type;
	componentCopy =NULL;
}
AddComponentCmd::~AddComponentCmd(){

}
void AddComponentCmd::execute()
{
	if(componentCopy==NULL)
	{
		eRModel->addNode(componentType);
		componentCopy = eRModel->clone(componentType);
	}
	else
	{
		eRModel->setComponentsVector(componentCopy);
	}
}
void AddComponentCmd::unexecute()
{
	eRModel->deleteComponent(componentCopy->getID());
	//eRModel->deleteLastComponent();
}
