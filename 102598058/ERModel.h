#ifndef _ERModel_H_ 
#define _ERModel_H_
#include "string"
#include <vector>

#include "Component.h"
#include "ComponentFactory.h"
#include <iostream>
using namespace std;
class ERModel{
public:
	ERModel();
	virtual ~ERModel();
	void addNode();
	string getWholeName(string);
	void showTable();
	void setPrimaryKey();
	void checkFirstNodeId();
	void checkSecondNodeId();
	void checkEntity();
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
	void updateID();
	Component* convertIdtoComponent(int);
	void deleteComponent();
	bool existId(int);
	void checkDeleteComponentIDLoop();
	void deleteComponentsVector();
	void connectTwoNode();
	void checkAddConnectionNodeOneLoop();
	bool checkAddConnectionNodeTwo();
	void setConnectionNodes(int);
	bool checkExistConnection(vector<int>);//連過的兩個相同node不可再連
	void createConnector(vector<int>);
private:
	vector<Component*> _components;
	vector<Component*> _connections;//[0]connection [1]node1 [2]node2 [3]connection...
	vector<Component*> _primaryKeys;//[0]entity [1]attribute1 [2]attribute2 [3]entity...

	int _id;
	
	string _secondNodeId;
	int _nodeOne;
	int _nodeTwo;
	ComponentFactory* componentFactory;
	int _cardinality;
	string _entityId;
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
	string _deleteId;
	string nodeIDOne;
	string nodeIDTwo;
	vector<int> _connectionNodesVector;//[0]node1 [1]node2
};
#endif