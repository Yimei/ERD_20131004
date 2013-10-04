#ifndef _TextUI_H_ 
#define _TextUI_H_
#include "ERModel.h"
#include <string>
using namespace std;
class TextUI{
public:
	TextUI();
	virtual ~TextUI();
	void displayMenu();
	void processCommand();
private:
	ERModel* eRModel;
	int _firstId;
};
#endif