#include "ConnectComponentsCmd.h"
ConnectComponentsCmd::ConnectComponentsCmd(ERModel* model,string type):Command()
{
	componentCopy = NULL;
	componentType = type;
	eRModel = model;
	for (int i = 0; i < connectionsCopy.size();i++)
	{
		connectionsCopy[i] = NULL;
	}
}
ConnectComponentsCmd::~ConnectComponentsCmd(){

}
void ConnectComponentsCmd::execute()
{
	if(componentCopy==NULL)
	{
		eRModel->connectTwoNode();
		componentCopy = eRModel->clone("C");
		connectionsCopy.push_back(componentCopy);
		connectionsCopy.push_back(eRModel->connectionsClone(eRModel->getConnectionsVector()[eRModel->getConnectionsVector().size()-1-1]->getType(),eRModel->getConnectionsVector().size()-1-1));
		connectionsCopy.push_back(eRModel->connectionsClone(eRModel->getConnectionsVector()[eRModel->getConnectionsVector().size()-1]->getType(),eRModel->getConnectionsVector().size()-1));
	}
	else
	{
		eRModel->setComponentsVector(componentCopy);
		for (int i = 0; i < connectionsCopy.size();i++)
		{
			eRModel->setConnectionsVector(connectionsCopy[i]);
		}
	}
}
void ConnectComponentsCmd::unexecute()
{
	eRModel->deleteComponent(componentCopy->getID());
}
