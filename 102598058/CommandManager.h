#ifndef CommandManager_H_
#define CommandManager_H_
#include <stack>
#include "Command.h"
using namespace std;
class CommandManager{
public:
	CommandManager();
	virtual ~CommandManager();
	void execute(Command*);
	void redo();//���U�@��
	void undo();//�_��
private:
	
	stack<Command*> redoCommands;
	stack<Command*> undoCommands;


};
#endif