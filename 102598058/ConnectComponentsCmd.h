#ifndef ConnectComponentsCmd_H_
#define ConnectComponentsCmd_H_
#include "Command.h"
#include "ERModel.h"
using namespace std;
class ConnectComponentsCmd:public Command
{
public:
	ConnectComponentsCmd(ERModel*,string);
	virtual ~ConnectComponentsCmd();
	void execute();
	void unexecute();
private:
	ERModel* eRModel;
	Component* componentCopy;
	string componentType;
	vector<Component*> connectionsCopy; 
};
#endif