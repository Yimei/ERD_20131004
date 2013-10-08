#include "ConnectComponentsCmd.h"

ConnectComponentsCmd::ConnectComponentsCmd(ERModel* model):Command()
{
	eRModel = model;
}
ConnectComponentsCmd::~ConnectComponentsCmd(){

}
void ConnectComponentsCmd::execute()
{
	eRModel->connectTwoNode();
}
void ConnectComponentsCmd::unexecute()
{

}
