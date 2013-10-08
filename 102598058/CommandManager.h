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
	void redo();//做下一個
	void undo();//復原

	string getHint();
private:
	string hint;
	stack<Command*> redoCommands;
	stack<Command*> undoCommands;


};
#endif