#include "DeleteComponentCmd.h"
DeleteComponentCmd::DeleteComponentCmd(ERModel* model,int id):Command()
{
	ID = id;
	eRModel = model;
	componentCopy = NULL;
	connectorBeDelete = false;
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
		cout << "conectionCopy ==>"<<endl;
		for (int i = 0; i < connectionCopy.size();i++)
		{
			cout << connectionCopy[i]->getID() <<"  "; 
		}
	}
	else
	{
		componentCopy = eRModel->componentsClone(eRModel->getComponentsVector()[eRModel->getIndexOfComponentID(ID)]->getType(),eRModel->getIndexOfComponentID(ID));
		for (int i = 0; i < eRModel->getConnectionsVector().size();i++)
		{
			if ((eRModel->getConnectionsVector()[i]->getID() == ID) && (eRModel->getConnectionsVector()[i-1]->getType() == "C"))
			{//node1
				connectorBeDelete = true;
				connectionCopy.push_back(eRModel->componentsClone(eRModel->getConnectionsVector()[i-1]->getType(), eRModel->getIndexOfComponentID(eRModel->getConnectionsVector()[i-1]->getID())));
				connectionCopy.push_back(eRModel->componentsClone(eRModel->getConnectionsVector()[i]->getType(), eRModel->getIndexOfComponentID(eRModel->getConnectionsVector()[i]->getID())));
				connectionCopy.push_back(eRModel->componentsClone(eRModel->getConnectionsVector()[i+1]->getType(), eRModel->getIndexOfComponentID(eRModel->getConnectionsVector()[i+1]->getID())));
			}
			else if ((eRModel->getConnectionsVector()[i]->getID() == ID) && (eRModel->getConnectionsVector()[i-1-1]->getType() == "C"))
			{//node2
				connectorBeDelete = true;
				connectionCopy.push_back(eRModel->componentsClone(eRModel->getConnectionsVector()[i-2]->getType(), eRModel->getIndexOfComponentID(eRModel->getConnectionsVector()[i-2]->getID())));
				connectionCopy.push_back(eRModel->componentsClone(eRModel->getConnectionsVector()[i-1]->getType(), eRModel->getIndexOfComponentID(eRModel->getConnectionsVector()[i-1]->getID())));
				connectionCopy.push_back(eRModel->componentsClone(eRModel->getConnectionsVector()[i]->getType(), eRModel->getIndexOfComponentID(eRModel->getConnectionsVector()[i]->getID())));
			}
		}
		cout << "conectionCopy ==>"<<endl;
		for (int i = 0; i < connectionCopy.size();i++)
		{
			cout << connectionCopy[i]->getID() <<"  "; 
		}
	}
	eRModel->deleteComponent(ID);
}
void DeleteComponentCmd::unexecute()
{
	if (connectorBeDelete)
	{
		eRModel->setComponentsVector(connectionCopy[0]);
	}
	eRModel->setComponentsVector(componentCopy);
	for (int i = 0; i < connectionCopy.size();i++)
	{
		eRModel->setConnectionsVector(connectionCopy[i]);
	}
	cout <<"= =!!"<<endl;
}
