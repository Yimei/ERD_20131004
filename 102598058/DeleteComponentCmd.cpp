#include "DeleteComponentCmd.h"

DeleteComponentCmd::DeleteComponentCmd(ERModel* model,int id):Command()
{
	ID = id;
	eRModel = model;
}
DeleteComponentCmd::~DeleteComponentCmd(){

}
void DeleteComponentCmd::execute()
{
	eRModel->deleteComponent(ID);
}
void DeleteComponentCmd::unexecute()
{

}
