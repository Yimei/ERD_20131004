#include "CommandManager.h"
#include <stack>
CommandManager::CommandManager()
{
	hint = " ";
}
CommandManager::~CommandManager()
{
	while(!redoCommands.empty()){
		Command* command = redoCommands.top();
		redoCommands.pop();
		delete command;
	}
	while(!undoCommands.empty()){
		Command* command = undoCommands.top();
		undoCommands.pop();
		delete command;
	}
}
void CommandManager::execute(Command* command)
{
	command->execute();


	undoCommands.push(command);



	while(!redoCommands.empty())
	{
		Command* c = redoCommands.top();
		redoCommands.pop();
		delete c;
	}

}
void CommandManager::redo()
{
	
	if (redoCommands.size() == 0)
	{
		hint = "Cannot redo.";
		return;
	}
	hint = "redo succeed!";	

	Command* c = redoCommands.top();
	redoCommands.pop();
	c->execute(); //redo the command
	undoCommands.push(c);
}
void CommandManager::undo()
{
	if (undoCommands.size() == 0)
	{
		hint = "Cannot undo.";
		return;
	}
	hint = "Undo succeed!";
	Command*  c = undoCommands.top();
	undoCommands.pop();
	c->unexecute();//undo the command
	redoCommands.push(c);
}
string CommandManager::getHint()
{
	return hint;
}