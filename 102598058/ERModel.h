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
	void setPrimaryKey();
	void checkPrimaryKey();
	vector<string> splitString(string,string);
	void showPrimary();
	void displayTable();
	void loadFile();
	void saveFile();
	void addComponentsFromFile(vector<string>);
	void addConnectionFromFile(vector<string>);
	void addPrimaryKeyFromFile(vector<string>);
	void displayComponentTable();
	void displayConnectionTable();
	void displayEntityTable();
	void displayAttributeOfEntity();
	void updateID();
	Component* convertIdtoComponent(int);
	bool existId(int);
	int checkDeleteComponentIDLoop();
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
	void addNodePresentation(string);
	void deleteComponentPresentation(int);
	void connectComponentPresentation();
	vector<Component*> getComponentsVector();
	void setComponentsVector(Component*);
	vector<Component*> getConnectionsVector();
	void setConnectionsVector(Component*);
	Component* clone(string);
	Component* connectionsClone(string,int);
	Component* componentsClone(string, int);
	void setDeleteID(int);
	int getDelelteID();
	int getIndexOfComponentID(int);
	int getIndexOfConnectionsID(int);
	string getCheckDeleteComponentHint(int);
private:
	CommandManager commandManager;
	ERModel* eRModel;
	vector<Component*> _components;
	vector<Component*> _connections;//[0]connection [1]node1 [2]node2 [3]connection...
	vector<Component*> _primaryKeys;//[0]entity [1]attribute1 [2]attribute2 [3]entity... ps.有PK的Entity
	ComponentFactory* componentFactory;
	Component* _entityTemp;
	string _primaryKey;
	vector<int> _attributesId;
	vector<string> _primaryKeyVector;
	int thisKey;
	vector<Component*> _entityHasPrimaryKey;
	vector<vector<string>> _pkOfEntities;
	vector<Component*> _attributeWithOutPK;
	vector<string> splitStringItem;
	int id;
	int _deleteId;
	string nodeIDOne;
	string nodeIDTwo;
	vector<int> _connectionNodesVector;//[0]node1 [1]node2
	int entityID;
	string checkDeletIdTemp;
	string checkDeleteComponentHint;
};
#endif