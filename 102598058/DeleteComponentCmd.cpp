#include "DeleteComponentCmd.h"

DeleteComponentCmd::DeleteComponentCmd(ERModel* model,int id):Command()
{
	ID = id;
	eRModel = model;
	componentCopy = NULL;
	for (int i = 0; i < connectionCopy.size();i++)
	{
		connectionCopy.push_back(NULL);
	}
}
DeleteComponentCmd::~DeleteComponentCmd(){

}
void DeleteComponentCmd::execute()
{
	if (eRModel->getComponentsVector()[eRModel->getIndexOfComponentID(ID)]->getType()=="C")
	{
		componentCopy = eRModel->componentsClone("C",eRModel->getIndexOfComponentID(ID));
		connectionCopy.push_back(componentCopy);
		connectionCopy.push_back(eRModel->connectionsClone(eRModel->getConnectionsVector()[eRModel->getIndexOfConnectionsID(ID)+1]->getType(),eRModel->getIndexOfConnectionsID(ID)+1));
		connectionCopy.push_back(eRModel->connectionsClone(eRModel->getConnectionsVector()[eRModel->getIndexOfConnectionsID(ID)+1+1]->getType(),eRModel->getIndexOfConnectionsID(ID)+1+1));
		
	}
	else
	{
		componentCopy = eRModel->componentsClone(eRModel->getComponentsVector()[eRModel->getIndexOfComponentID(ID)]->getType(),eRModel->getIndexOfComponentID(ID));
		for (int i = 0; i < eRModel->getComponentsVector()[eRModel->getIndexOfComponentID(ID)]->getConnections().size();i++)
		{
			connectionCopy.push_back(eRModel->componentsClone(eRModel->getComponentsVector()[eRModel->getIndexOfComponentID(ID)]->getConnections()[i]->getType(),eRModel->getIndexOfComponentID(eRModel->getComponentsVector()[eRModel->getIndexOfComponentID(ID)]->getConnections()[i]->getID())));
		}
		
	}

	eRModel->deleteComponent(ID);
	
}
void DeleteComponentCmd::unexecute()
{

}
