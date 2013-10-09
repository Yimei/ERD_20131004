#ifndef _TextUI_H_ 
#define _TextUI_H_
#include "ERModel.h"
#include <string>
using namespace std;
class TextUI{
public:
	TextUI(ERModel*);
	virtual ~TextUI();
	void displayMenu();
	void processCommand();
	void action_addCommand();
	void action_redo();
	void action_undo();
private:
	ERModel* eRModel;
	int _firstId;
	string command;
	string type;
};
#endif