#ifndef AddComponentCmd_H_
#define AddComponentCmd_H_
#include "Command.h"
#include "ERModel.h"

using namespace std;

class AddComponentCmd:public Command{

public:
		AddComponentCmd(ERModel*,string type);
		virtual ~AddComponentCmd();
		void execute();
		void unexecute();
private:
	ERModel* eRModel;
	string componentType;
	Component* componentCopy;
};
#endif