#include <string>
#include <iostream>
#include "TextUI.h"
#include "ERModel.h"
using namespace std;
#define MENU_ONE "3. Add a node\n";
#define MENU_TWO "4. Connect two nodes\n";
#define MENU_THREE "5. Display the current diagram\n";
#define MENU_FOUR "6. Set a primary key\n";
#define MENU_FIVE "7. Display the table\n";
#define MENU_SIX "11. Exit\n> ";
#define WKONDYWTA "What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation\n> ";
TextUI::TextUI(){
	eRModel = new ERModel();
}
void TextUI::displayMenu(){
	cout << "1. Load ER diagram file\n";
	cout << "2. Save ER diagram file\n";
	cout << MENU_ONE
	cout << MENU_TWO;
	cout << MENU_THREE;
	cout << MENU_FOUR;
	cout << MENU_FIVE;
	cout << MENU_SIX;
	processCommand();
}
void TextUI::processCommand(){
	int _command;
	string _typeName;
	string _type;
	cin >> _command;
	switch (_command){
	case 1:
		eRModel->loadFile();
		eRModel->displayComponentTable();
		eRModel->displayConnectionTable();
		displayMenu();
	case 2:
		eRModel->saveFile();

	case 3: 
		cout << "What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation" << endl<<"> ";
		cin >> _type;
		while ((_type != "A")&&(_type != "E")&&(_type != "R"))
		{
			cout << "You entered an invalid node. Please enter a valid one again.\n[A]Attribute [E]Entity [R]Relation" << endl<<"> ";
			cin >> _type;
		}
		eRModel->addNode(_type);
		displayMenu();
	case 4:
		cout << "Please enter the first node ID "<< endl << "> ";
		eRModel->checkFirstNodeId();
		cout << "Please enter the second node ID "<< endl << "> ";
		eRModel->checkSecondNodeId();
		
		eRModel->addConnection(eRModel->getFirstNode(),eRModel->getSecondNode());
		displayMenu();
	case 5:
		eRModel->getTable();
		displayMenu();
	case 6:
		eRModel->setPrimaryKey();
		
		eRModel->checkEntity();
		eRModel->checkPrimaryKey();
		eRModel->showPrimary();
		displayMenu();
	case 7:
		eRModel->displayTable();
		displayMenu();
	case 11:
		cout << "Goodbye!" <<endl;

		//eRModel->exit();
		break;
	default:
		system("pause");
	}
}
TextUI::~TextUI(){

}

