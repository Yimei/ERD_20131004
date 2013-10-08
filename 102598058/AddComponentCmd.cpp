#include "AddComponentCmd.h"

AddComponentCmd::AddComponentCmd(ERModel* model, string type):Command()
{
	eRModel = model;
	componentType = type;
}
AddComponentCmd::~AddComponentCmd(){

}
void AddComponentCmd::execute()
{
	eRModel->addNode(componentType);
}
void AddComponentCmd::unexecute()
{
	//eRModel->deleteLastComponent();
}
