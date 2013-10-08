#include <string>
#include <iostream>
#include "TextUI.h"
#include "ERModel.h"
using namespace std;
//#define WKONDYWTA "What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation\n> ";
TextUI::TextUI(ERModel* model){
	//eRModel = new ERModel();
	eRModel = model;
}
TextUI::~TextUI(){

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
	string type;
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
		
		cout << "What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation" << endl<<"> ";
		cin >> type;
		while ((type != "A")&&(type != "E")&&(type != "R"))
		{
			cout << "You entered an invalid node. Please enter a valid one again.\n[A]Attribute [E]Entity [R]Relation" << endl<<"> ";
			cin >> type;
		}

		eRModel->addNodePresentation(type);
		cout << "Components: " << endl;
		eRModel->displayComponentTable();
		displayMenu();

	case 4:
		cout << "Please enter the first node ID "<< endl << "> ";
		eRModel->setConnectionNodes(eRModel->checkAddConnectionNodeOneLoop());
		
		cout << "Please enter the second node ID "<< endl << "> ";
		eRModel->connectComponentPresentation();
		//eRModel->connectTwoNode();
		displayMenu();

	case 5:
		cout << "The ER diagram is displayed as follows:"<<endl<<"Nodes:"<<endl;
		eRModel->displayComponentTable();
		eRModel->displayConnectionTable();
		displayMenu();

	case 6:
		eRModel->displayEntityTable();
		eRModel->setPrimaryKey();
		displayMenu();
		//eRModel->checkPrimaryKey();
		//eRModel->showPrimary();
	case 7:
		eRModel->displayTable();
		displayMenu();
	case 8:
		cout << "Please enter the component ID" << endl <<"> ";
		eRModel->deleteComponentPresentation(eRModel->checkDeleteComponentIDLoop());
		system("pause");
	case 9:
		eRModel->undo();
		system("pause");
	case 10:
		eRModel->redo();
		system("pause");
	case 11:
		cout << "Goodbye!" <<endl;
		return;
		//eRModel->exit();
		
	default:
		system("pause");
	}
}
void TextUI::action_addCommand()
{

}
void TextUI::action_redo()
{


}
void TextUI::action_undo()
{

}


