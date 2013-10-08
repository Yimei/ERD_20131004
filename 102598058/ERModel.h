#ifndef _ERModel_H_ 
#define _ERModel_H_
#include "string"
#include <vector>
#include "CommandManager.h"
#include "Component.h"
#include "ComponentFactory.h"
#include <iostream>
using namespace std;
class ERModel{
public:
	ERModel();
	virtual ~ERModel();
	void addNode(string);
	string getWholeName(string);
	void showTable();
	void setPrimaryKey();
	void checkFirstNodeId();
	void checkSecondNodeId();
	void showAttributeTable(string);
	void checkPrimaryKey();
	vector<string> splitString(string,string);
	
	void showPrimary();
	Component* getFirstNode();
	Component* getSecondNode();
	void addConnection(Component* nodeOne, Component* nodeTwo);
	void getTable();
	
	void exit();
	vector<Component*> getVector();
	void displayTable();
	void removePKfromAttribute();


	void loadFile();
	void saveFile();
	void addComponentsFromFile(vector<string>);
	void addConnectionFromFile(vector<string>);
	void addPrimaryKeyFromFile(vector<string>);
	
	int getPresentID();
	void initialPresentID();
	void displayComponentTable();
	void displayConnectionTable();
	void displayEntityTable();
	void displayAttributeOfEntity();

	void updateID();
	Component* convertIdtoComponent(int);
	
	bool existId(int);
	int checkDeleteComponentIDLoop();
	void deleteComponentsVector();
	void connectTwoNode();
	int checkAddConnectionNodeOneLoop();
	void checkEntityLoop();
	bool checkAddConnectionNodeTwo();
	void setConnectionNodes(int);
	bool checkExistConnection(vector<int>);//連過的兩個相同node不可再連
	void createConnector(vector<int>);
	void checkPrimaryKeyLoop();
	void setPKEntity(int);
	int getPKEntity();

	void deleteComponent(int);
	void undo();
	void redo();

	void deleteLastComponent();
	
	void addNodePresentation(string);
	void deleteComponentPresentation(int);
	void connectComponentPresentation();

	vector<Component*> getComponentsVector();
	void setComponentsVector(Component*);
	Component* clone(string);

	void setDeleteID(int);
	int getDelelteID();
	void updateComponentSize();
	int getPresentComponentsSize();
private:
	CommandManager commandManager;
	ERModel* eRModel;

	vector<Component*> _components;
	vector<Component*> _connections;//[0]connection [1]node1 [2]node2 [3]connection...
	vector<Component*> _primaryKeys;//[0]entity [1]attribute1 [2]attribute2 [3]entity... ps.有PK的Entity

	int _id;
	
	string _secondNodeId;
	int _nodeOne;
	int _nodeTwo;
	ComponentFactory* componentFactory;
	int _cardinality;
	
	Component* _entityTemp;
	Component* _entityAttribute;
	string _primaryKey;
	vector<int> _attributesId;
	vector<string> _primaryKeyVector;
	int thisKey;
	vector<Component*> _entityHasPrimaryKey;
	vector<vector<string>> _pkOfEntities;
	vector<Component*> _attributeWithOutPK;

	vector<string> splitStringItem;
	int _presentID;
	int id;
	int _deleteId;
	string nodeIDOne;
	string nodeIDTwo;
	vector<int> _connectionNodesVector;//[0]node1 [1]node2
	int entityID;
	string checkDeletIdTemp;

	int componentSize;
};
#endif