#ifndef DeleteComponentCmd_H_
#define DeleteComponentCmd_H_
#include "Command.h"
#include "ERModel.h"
using namespace std;
class DeleteComponentCmd:public Command{
public:
	DeleteComponentCmd(ERModel*,int);
	virtual ~DeleteComponentCmd();
	void execute();
	void unexecute();
private:
	ERModel* eRModel;
	int ID;
	Component* componentCopy;
	vector<Component*> connectionCopy;
	bool connectorBeDelete;
};
#endif