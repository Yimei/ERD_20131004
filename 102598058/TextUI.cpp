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
	cin >> command;
	if (command == "1")
	{
		eRModel = new ERModel();
		eRModel->loadFile();
		displayMenu();
	}
	else if (command == "2")
	{
		eRModel->saveFile();
		displayMenu();
	}
	else if (command == "3")
	{
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
	}
	else if (command == "4")
	{
		cout << "Please enter the first node ID "<< endl << "> ";
		eRModel->setConnectionNodes(eRModel->checkAddConnectionNodeOneLoop());
		cout << "Please enter the second node ID "<< endl << "> ";
		eRModel->connectComponentPresentation();
		displayMenu();
	}
	else if (command == "5")
	{
		cout << "The ER diagram is displayed as follows:"<<endl<<"Nodes:"<<endl;
		eRModel->displayComponentTable();
		eRModel->displayConnectionTable();
		displayMenu();
	}
	else if (command == "6")
	{
		eRModel->displayEntityTable();
		eRModel->setPrimaryKey();
		displayMenu();
	}
	else if (command == "7")
	{
		eRModel->displayTable();
		displayMenu();
	}
	else if (command == "8")
	{
		cout << "Please enter the component ID" << endl <<"> ";
		eRModel->deleteComponentPresentation(eRModel->checkDeleteComponentIDLoop());
		cout << "The component '" << eRModel->getDelelteID() <<"' has been deleted."<<endl;
		cout << "Component:"<<endl;
		eRModel->displayComponentTable();
		eRModel->displayConnectionTable();
		displayMenu();
	}
	else if (command == "9")
	{
		eRModel->undo();
		cout << "Components: " << endl;
		eRModel->displayComponentTable();
		eRModel->displayConnectionTable();
		displayMenu();
	}
	else if (command == "10")
	{
		eRModel->redo();
		eRModel->displayComponentTable();
		eRModel->displayConnectionTable();
		displayMenu();
	}
	else if (command == "11")
	{
		cout << "Goodbye!" <<endl;
		return;
	}
	else
	{
		cout << "No this option. Please enter the number again."<<endl;
		displayMenu();
	}
}


