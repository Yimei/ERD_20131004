#include <string>
#include <iostream>
#include "TextUI.h"
#include "ERModel.h"
using namespace std;
//#define WKONDYWTA "What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation\n> ";
TextUI::TextUI(){
	eRModel = new ERModel();
}
void TextUI::displayMenu(){
	cout << "1. Load ER diagram file" << endl;
	cout << "2. Save ER diagram file" << endl;
	cout << "3. Add a node" << endl;
	cout << "4. Connect two nodes" << endl;
	cout << "5. Display the current diagram" << endl;
	cout << "6. Set a primary key" << endl;
	cout << "7. Display the table" << endl;
	cout << "8. Delete a component"<< endl;
	cout << "9. Undo" << endl;
	cout << "10. Redo" << endl;
	cout << "11. Exit" << endl <<"> ";
	processCommand();
}
void TextUI::processCommand(){
	int _command;
	string _typeName;
	string _type;
	cin >> _command;
	switch (_command){
	case 1:
		eRModel = new ERModel();
		eRModel->loadFile();
		cout << "Components: " << endl;
		eRModel->displayComponentTable();
		eRModel->displayConnectionTable();
		displayMenu();
	case 2:
		eRModel->saveFile();
		displayMenu();
	case 3: 
		eRModel->addNode();
		cout << "Components: " << endl;
		eRModel->displayComponentTable();
		displayMenu();
	case 4:
		eRModel->connectTwoNode();
		displayMenu();
	case 5:
		cout << "The ER diagram is displayed as follows:"<<endl<<"Nodes:"<<endl;
		eRModel->displayComponentTable();
		eRModel->displayConnectionTable();
		displayMenu();
	case 6:
		eRModel->displayEntityTable();
		eRModel->setPrimaryKey();
		
		
		eRModel->checkPrimaryKey();
		eRModel->showPrimary();
		displayMenu();
	case 7:
		eRModel->displayTable();
		displayMenu();
	case 8:
		eRModel->deleteComponent();

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

