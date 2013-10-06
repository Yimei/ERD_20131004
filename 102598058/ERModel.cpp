#include "ERModel.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
ERModel::ERModel(){
	_id = 0;
	_nodeOne = 0;
	_nodeTwo = 0;
	_entityTemp=NULL;
	_entityAttribute = NULL;
	_primaryKey = "";
	thisKey=0;

	_presentID = 0;
	id=0;
}
ERModel::~ERModel()
{
	
	delete componentFactory;
	delete _entityTemp;
	delete _entityAttribute;
	
	for (int i = 0; i < _components.size();i++)
	{
		delete _components[i];
	}
	for (int i = 0; i < _entityHasPrimaryKey.size();i++)
	{
		delete _entityHasPrimaryKey[i];
	}
	for (int i = 0; i < _attributeWithOutPK.size();i++)
	{
		delete _attributeWithOutPK[i];
	}
}
void ERModel::deleteComponent()
{
	cout << "Please enter the component ID" << endl <<"> ";
	checkDeleteComponentIDLoop();
	  

	cout << "The component '" << atoi(_deleteId.c_str()) <<"' has been deleted."<<endl;
}
void ERModel::checkDeleteComponentIDLoop()
{
	cin >> _deleteId;
	if (existId(atoi(_deleteId.c_str())))
	{
		return;
	}
	else
	{
		cout << "The component ID You entered does not exist. Please enter a valid one again." <<endl;
		checkDeleteComponentIDLoop();
	}
}
bool ERModel::existId(int id)
{
	for(int i = 0; i < _components.size();i++)
	{
		if(_components[i]->getID() == id)
		{
			return true;
		}
	}
	return false;	
}
void ERModel::addComponentsFromFile(vector<string> nodeVectorFromFile)
{
		componentFactory = new ComponentFactory();
		Component* component = componentFactory->createComponent(nodeVectorFromFile[0].substr(0,1));
		component->setID(id);
		updateID();
		component->setType(nodeVectorFromFile[0].substr(0,1));
		if (nodeVectorFromFile.size() == 2 )
		{
			component->setText(nodeVectorFromFile[1]);
		}
		else
		{
			component->setText(" ");
		}
		_components.push_back(component);
}
void ERModel::updateID()
{
	id = id + 1;
}
void ERModel::addConnectionFromFile(vector<string> connectionVectorFromFile)
{
	componentFactory = new ComponentFactory();
	for (int i = 0; i < connectionVectorFromFile.size();i++)
	{
		Component* component = componentFactory->createComponent(convertIdtoComponent(atoi(connectionVectorFromFile[i].c_str()))->getType());
		component->setID(atoi(connectionVectorFromFile[i].c_str()));
		component->setType(convertIdtoComponent(atoi(connectionVectorFromFile[i].c_str()))->getType());
		component->setText(convertIdtoComponent(atoi(connectionVectorFromFile[i].c_str()))->getText());
		_connections.push_back(component);
	}
	/*cout << "connection = " << connectionVectorFromFile[0] <<endl;
	cout << "id = " << connectionVectorFromFile[1]<<", "<<connectionVectorFromFile[2] << endl;*/
}
Component* ERModel::convertIdtoComponent(int id)
{
	for (int i = 0; i < _components.size();i++)
	{
		if (id == _components[i]->getID())
			return _components[i];
	}
	return NULL;
}
void ERModel::deleteComponentsVector()
{
	for(int i = 0; i < _components.size();i++)
	{
		delete _components[i];
	}
}
void ERModel::loadFile(){
	string _filePath;
	string line;
	cout << "Please input a file path: "<<endl;
	cin >> _filePath;
	ifstream myfile(_filePath);
	if (myfile.is_open())
	{
		while (getline(myfile,line))
		{	
			if (line == "")
			{
				break;
			}
			addComponentsFromFile(splitString(line," "));
		}	
		while (getline(myfile,line))
		{	
			if (line == "")
			{
				break;
			}
			int pos = line.find(" ");
			if (pos == 1)
			{
				line.replace(line.find("  "), 2," ");
			}
			line.replace(line.find(","),1," ");
			addConnectionFromFile(splitString(line," "));
		}	
		while (getline(myfile,line))
		{	
			if (line == "")
			{
				break;
			}
			line.replace(line.find(" "),1,",");
			addPrimaryKeyFromFile(splitString(line,","));
		}	
		myfile.close();
	}
	else cout << "Unable to open file";
}
vector<string> ERModel::splitString(string line, string reference)
{
	//_primaryKeyVector.clear();
	int pos=1;
	splitStringItem.clear();
	//int loopCount = line.size();
	for (int i = 0; pos > 0; i++)
	{
		pos = line.find(reference);
		string stringItem = line.substr(0, pos);
		line = line.substr(pos+1,line.size());
		splitStringItem.push_back(stringItem);
		//_primaryKeyVector.push_back(keyString);
	}
	return splitStringItem;
	//_primaryKeyVector.push_back(line.substr((line.size()-1),primaryKeyString.size()));
}
int ERModel::getPresentID()
{
	_presentID++;
	return _presentID;
}
void ERModel::initialPresentID()
{
	_presentID = 0;
}
void ERModel::saveFile(){
	string _fileName;
	cout << "Please input the file name: ";
	cin >> _fileName;//輸出的檔名路徑

	ofstream myfile(_fileName);
	if(myfile.is_open())
	{
		for (int i = 0; i < _components.size();i++)
		{
			myfile << _components[i]->getType() << ", " << _components[i]->getText() << endl;
		}
		myfile << endl;
		
		for (int i = 0; i < _connections.size();i = i+3)
		{
			myfile <<setiosflags(ios::left) <<setw(3)<< _connections[i]->getID() << _connections[i+1]->getID()<< "," << _connections[i+2]->getID()<<endl;
		}
		//myfile << endl;
		int entityPresentIndex = 0;//Entity count
		for (int i = 0; i < _primaryKeys.size();i++)
		{
			if(_primaryKeys[i]->getType() == "E")
			{
				myfile << endl<<_primaryKeys[i]->getID()<<" ";
				entityPresentIndex = i;
			}
			else 
			{
				
				if (i == entityPresentIndex+1)
					myfile << _primaryKeys[i]->getID();
				else
					myfile <<"," << _primaryKeys[i]->getID();
					//myfile << _primaryKeys[i]->getID();
				
				
			}
			
		}

		/*myfile << "This is a line.\n" <<endl;
		myfile << "This is another line.\n"<<endl;*/
		myfile.close();
	}
	else cout << "Unable to open file";
}
void ERModel::addPrimaryKeyFromFile(vector<string> primaryKeyVectorFromFile)
{
	componentFactory = new ComponentFactory();
	for (int i = 0; i< primaryKeyVectorFromFile.size();i++)
	{
		Component* component = componentFactory->createComponent(convertIdtoComponent(atoi(primaryKeyVectorFromFile[i].c_str()))->getType());
		component->setID(atoi(primaryKeyVectorFromFile[i].c_str()));
		component->setType(convertIdtoComponent(atoi(primaryKeyVectorFromFile[i].c_str()))->getType());
		component->setText(convertIdtoComponent(atoi(primaryKeyVectorFromFile[i].c_str()))->getText());
		_primaryKeys.push_back(component);
	}
}
void ERModel::addNode(){
	string type;
	cout << "What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation" << endl<<"> ";
	cin >> type;
	while ((type != "A")&&(type != "E")&&(type != "R"))
	{
		cout << "You entered an invalid node. Please enter a valid one again.\n[A]Attribute [E]Entity [R]Relation" << endl<<"> ";
		cin >> type;
	}
	string text;
	cout<< "Enter the name of this node:" << endl<<"> ";
	cin >> text;
	componentFactory = new ComponentFactory();
	Component* component = componentFactory->createComponent(type);
	component->setID(id);
	updateID();
	component->setText(text);
	component->setType(type);
	_components.push_back(component);
	cout << "A node [" << getWholeName(type) << "]" << " has been added. ID: " << id-1 << ", Name: " << text << endl;
}
void ERModel::connectTwoNode()
{
	cout << "Please enter the first node ID "<< endl << "> ";
	checkAddConnectionNodeOneLoop();
	setConnectionNodes(atoi(nodeIDOne.c_str()));
	cout << "Please enter the second node ID "<< endl << "> ";
	if (checkAddConnectionNodeTwo()) 
	{
		setConnectionNodes(atoi(nodeIDTwo.c_str()));
		if (_connectionNodesVector[1] == _connectionNodesVector[0])//itself
		{
			cout << "The Node '" <<  _connectionNodesVector[1] <<"' cannot be connected to itself." << endl;
			_connectionNodesVector.clear();
		}//same type
		else if (_components[_connectionNodesVector[1]]->getType() == _components[_connectionNodesVector[0]]->getType())
		{
			cout << "The node '" <<  _connectionNodesVector[1] <<"' cannot be connected by the node '"<<  _connectionNodesVector[0] <<"'."<<endl; 
		    _connectionNodesVector.clear();
		}//已連過同一條connector
		else if (checkExistConnection(_connectionNodesVector))//true: 已存在
		{
			cout << "The node '" << _connectionNodesVector[1]<<"' has already been connected to node '" << _connectionNodesVector[0] <<"'."<<endl;
		    _connectionNodesVector.clear();
		}
		else if (!(_components[_connectionNodesVector[1]]->canConnectTo(_components[_connectionNodesVector[0]]))&&(_components[_connectionNodesVector[0]]->canConnectTo(   _components[_connectionNodesVector[1]])))
		{
			cout << "The node '"<<_connectionNodesVector[1]<<"' cannot be connected by the node '"<< _connectionNodesVector[0]<<"'."<<endl;
		    _connectionNodesVector.clear();
		}
		else
		{
			createConnector(_connectionNodesVector);
			_connections.push_back(_components[_connectionNodesVector[0]]);
			_connections.push_back(_components[_connectionNodesVector[1]]);
			cout << "The node '"<<_connectionNodesVector[1]<<"' has been connected to the node '"<<_connectionNodesVector[0]<<"'."<<endl;
			displayConnectionTable();
			_connectionNodesVector.clear();
		}
	}
	else
	{
		cout << "The node ID you entered does not exist." <<endl;
		_connectionNodesVector.clear();
	}

}
void ERModel::createConnector(vector<int> connectionNodes)
{
	componentFactory = new ComponentFactory();
	Component* component = componentFactory->createComponent("C");
	component->setID(id);
	updateID();
	component->setType("C");
	if ((_components[connectionNodes[0]]->getType() == "R") || (_components[connectionNodes[1]]->getType() == "R"))
	{
		string cardinality;
		cout << "Enter the type of the cardinality:" <<endl<<"[0]1 [1]N"<<endl<<"> ";
		cin >> cardinality;
		if (atoi(cardinality.c_str()) == 0)
		{
			component->setText("1");
		}
		else if (atoi(cardinality.c_str()) == 1)
		{
			component->setText("N");
		}
		else
		{
			cout << "Wrong cardinality."<<endl;
		}
	}
	else
	{
		component->setText(" ");
	}
	_components.push_back(component);

	_connections.push_back(component);
}
bool ERModel::checkExistConnection(vector<int> connectionNodes)
{
	for (int i = 0; i < _connections.size(); i++)
	{
		if (i%3 != 0)
		{
			if (_connections[i]->getID() == connectionNodes[0])
			{
				if (_connections[i+1]->getID() == connectionNodes[1])
				{
					return true;
				}
			}
			else if (_connections[i]->getID() == connectionNodes[1])
			{
				if (_connections[i+1]->getID() == connectionNodes[0])
				{
					return true;
				}
			}
		}
	}
	return false;
}
void ERModel::setConnectionNodes(int nodeOne)
{
	_connectionNodesVector.push_back(nodeOne);
}
string ERModel::getWholeName(string type){ 
	if (type == "A")
		return "Attribute";
	else if (type == "E")
		return "Entity";
	else if (type == "R")
		return "Relationship";
	else
		return "No name";
}
void ERModel::showTable()
{
	cout << "Components:" << endl;
	cout << "---------------------------------" << endl;
	cout << "Type | ID | Name  " << endl;
	cout << "-----+----+----------------------" << endl;
	for (int i = 0; i < _components.size();i++)
	{
		cout << "  " << _components[i]->getType() << "  |  " << _components[i]->getID() << " |  " << _components[i]->getText()	<< endl;
	}
	cout << "----------------------------------" << endl;
}
//void ERModel::checkFirstNodeId(){
//	
//	if(_firstNodeId == "0")
//	{
//		_nodeOne = 0;
//	}
//	else if (atoi(_firstNodeId.c_str()) >= _components.size() || atoi(_firstNodeId.c_str())==0)//不在vector內或輸入string
//	{
//		cout << "The node ID you entered does not exist. Please enter a valid one again." << endl << "> ";
//		checkFirstNodeId();
//	}
//	else
//	{
//		_nodeOne = atoi(_firstNodeId.c_str());
//	}
//}
bool ERModel::checkAddConnectionNodeTwo()
{
	cin >> nodeIDTwo;
	if (nodeIDTwo == "0")//string 不用轉換前就是0
	{
		return true;
	}
	else 
	{
		for (int i = 0; i < _components.size(); i++)
		{
			if ((atoi(nodeIDTwo.c_str()) == _components[i]->getID()) && (atoi(nodeIDTwo.c_str())!=0))
			{
				return true;
			}
		}
		cout << "The node ID you entered does not exist."<< endl;
		return false;
	}
}
void ERModel::checkAddConnectionNodeOneLoop()
{
	cin >> nodeIDOne;
	if (nodeIDOne == "0")//string 不用轉換前就是0
	{
		return;
	}
	else 
	{
		for (int i = 0; i < _components.size(); i++)
		{
			if ((atoi(nodeIDOne.c_str()) == _components[i]->getID()) && (atoi(nodeIDOne.c_str())!=0))
			{
				return;
			}
		}
		cout << "The node ID you entered does not exist. Please enter a valid one again." <<endl<<"> ";
		checkAddConnectionNodeOneLoop();
	}
}
void ERModel::checkSecondNodeId()
{
	cin >> _secondNodeId;
	if(_secondNodeId == "0") // secondNodeId = 0
	{
		 _nodeTwo = 0;
	}
	else if (atoi(_secondNodeId.c_str()) >= _components.size() || atoi(_secondNodeId.c_str())==0)//不在vector內或輸入string
	{
		cout << "The node ID you entered does not exist. Please enter a valid one again." << endl << "> ";
		checkSecondNodeId();
	}
	else
	{
		_nodeTwo = atoi(_secondNodeId.c_str());
	}
}
void ERModel::addConnection(Component* nodeOne, Component* nodeTwo)
{
	if (nodeOne->getID() == nodeTwo->getID()) //自己不能連 含Connector連Connector
	{
		cout << "The node '" << nodeTwo->getID() <<"' cannot be connected to itself."<<endl;
	}	
	else if (nodeOne->getType() == "C" || nodeTwo-> getType()=="C")
	{
		cout << "Connector could not be connected. " << endl;
	}
	else if (nodeOne->canConnectTo(nodeTwo))//R E A only
	{
		nodeOne->connectTo(nodeTwo);//setConnectionsNum() both
		nodeTwo->connectTo(nodeOne);
		Component* component = componentFactory->createComponent("C");
		component->setID(id);
		updateID();
		component->setText("connector");
		component->setType("C");
		_components.push_back(component);
		//_id++;
		component->connectTo(nodeOne);
		component->connectTo(nodeTwo);
		if((nodeOne->getType()=="R") || (nodeTwo->getType()=="R"))
		{
			cout << "Enter the type of the cardinality:\n[0]1 [1]N" << endl << "> " << endl;
			cin >> _cardinality;
			if (_cardinality == 0)
			{
				component->setText("connector: cardinality= 1");
			}
			else if (_cardinality == 1)
			{
				component->setText("connector: cardinality= N");
			}
			else
			{
				cout << "Please enter '0' or '1'."<< endl;
			}
			cout << "The node '" << nodeOne->getID() << "' had been connected to the node '" << nodeTwo->getID() << "'." << endl;
			cout << "Its cardinality of the relationship is '" << _cardinality << "'." << endl;
		}
		else
		{
			cout << "The node '" << nodeOne->getID() << "' has been connected to the node '" << nodeTwo->getID() << "'." << endl;
			displayConnectionTable();
		}
	}
	else
	{
		cout << "The node '"<< nodeOne->getID() << "' cannot be connected by the node '" << nodeTwo->getID() << "'." << endl;
	}
}
void ERModel::setPrimaryKey(){
	cout << "Entities:" << endl;
	cout << "---------------------------------" << endl;
	cout << "Type | ID | Name  " << endl;
	cout << "-----+----+----------------------" << endl;
	for (int i = 0; i < _components.size();i++)
	{
		if (_components[i]->getType() == "E")
		{
			cout << "  " << _components[i]->getType() << "  |  " << _components[i]->getID() << "  |  " << _components[i]->getText()	<< endl;
		}
	}
	cout << "------------------------------------" << endl;
	cout << "Enter the ID of the entity:" << endl << "> ";
}
void ERModel::checkEntity()
{
	cin >> _entityId;
	if ((_entityId == "0") && _components[0]->getType() == "E")
	{
		cout << "Attributes of the entity '" << _entityId << "' " << endl;
	}
	else if (atoi(_entityId.c_str()) == 0) // 是字串
	{
		cout << "The node ID you entered does not exist. Please enter a valid one again." << endl << "> "<< endl;
		
		checkEntity();
	}
	else if(_components[atoi(_entityId.c_str())]->getType() != "E")
	{
		cout << "The node '" << _entityId << "' is not an entity. Please enter a valid one again." << endl << "> "<< endl;
		checkEntity();
	}
	else
	{
		cout << "Attributes of the entity '" << _entityId << "' " << endl;
	}
	showAttributeTable(_entityId);
}
void ERModel::showAttributeTable(string entityID)
{
	cout << "---------------------------------" << endl;
	cout << "Type | ID | Name  " << endl;
	cout << "-----+----+----------------------" << endl;
	_entityTemp = _components[atoi(entityID.c_str())];
	/*for (int i = 0; i < _entityTemp->getConnections().size();i++)
	{
			_entityAttribute = _entityTemp->getConnections()[i];
			if(_entityAttribute->getType() == "A")
			{
				cout << "  " << _entityAttribute->getType() << "  |  " << _entityAttribute->getID() << "  |  " << _entityAttribute->getText()	<< endl;
				_attributesId.push_back(_entityAttribute->getID());
			}
	}*/
	cout << "------------------------------------" << endl;
	cout << "Enter the IDs of the attributes (use a comma to separate two attributes):" << endl << "> ";
}
void ERModel::checkPrimaryKey()
{
	cin >> _primaryKey;
	splitString(_primaryKey, ",");

	for (int i = 0; i < _primaryKeyVector.size();i++)
	{
		thisKey = 0;
		for (int j = 0; (j < _attributesId.size() && thisKey == 0);j++)
		{	
			if (_attributesId[j] == atoi(_primaryKeyVector[i].c_str()))
			{
				thisKey = 1;
			}
			else
			{
			}
		}
		if (thisKey == 0)
		{
			cout << "The node '" << _primaryKeyVector[i] <<"' does not belong to Entity '" << _entityTemp->getID() << "'. Please enter a valid one again." << endl << "> ";
			checkPrimaryKey();
		}
	}
}
//void ERModel::splitString(string string, string reference)
//{
//
//	//_primaryKeyVector.clear();
//
//	for (int i = 0; i < string.size(); i++)
//	{
//		if (string.size()==1)
//		{
//		}
//		else
//		{
//			int pos = string.find(reference);
//			string keyString = string.substr(0, pos);
//			string = string.substr(pos+1);
//			_primaryKeyVector.push_back(keyString);
//		}
//	}
//	_primaryKeyVector.push_back(string.substr((string.size()-1),primaryKeyString.size()));
//}
void ERModel::showPrimary()
{
	cout << "The entity '"<< _entityTemp->getID() <<"' has the primary key (";
	for (int s = 0; s < _primaryKeyVector.size();s++)
	{
		cout << _primaryKeyVector[s] <<",";
	}
	cout <<"). "<< endl;
	for (int i = 0; i <_attributeWithOutPK.size();i++)
	{
		cout << "_attribute WithOut PK= " << _attributeWithOutPK[i]->getID() << endl;
	}
	_entityHasPrimaryKey.push_back(_entityTemp);
	_pkOfEntities.push_back(_primaryKeyVector);
}
void ERModel::displayTable()
{
	cout << "Tables:" << endl;
	cout << "-----------------------------------" << endl;
	cout << "Entity | Attribute  " << endl;
	cout << "-------+----------------------" << endl;
	for (int i = 0; i < _entityHasPrimaryKey.size();i++)
	{
			//cout << i;
			cout << "  " << _entityHasPrimaryKey[i]->getText() << "  |  " << "PK(";
			for (int j = 0; j < _pkOfEntities[i].size();j++)
			{
				cout <<_pkOfEntities[i][j] << ",";
			}
			cout << "), " ;
			cout << endl; 
	}
	cout << endl<<"------------------------------------" << endl;
}
Component* ERModel::getFirstNode()
{
	return _components[_nodeOne];
}
Component* ERModel::getSecondNode()
{
	return _components[_nodeTwo];
}
vector<Component*> ERModel::getVector()
{
	return _components;
}
void ERModel::getTable()
{
	cout << "The ER diagram is display as follows:" << endl << "Nodes: " << endl;
	cout << "------------------------------------" << endl;
	cout << "Type | ID | Name  " << endl;
	cout << "-----+----+----------------------" << endl;
	for (int i = 0; i < _components.size();i++)
	{
		//cout << i;
		cout << " " << _components[i]->getType() << "  |  " << _components[i]->getID() << "  |  " << _components[i]->getText()	<< endl;
	}
	displayConnectionTable();
}
void ERModel::displayConnectionTable()
{
	cout << "Connections:" <<endl;
	cout << "------------------------------------" << endl;
	cout << "Connection | node | node  " << endl;
	cout << "------- ---+------+-----------------" << endl;
	for (int i = 0; i < _connections.size();i = i+3)
	{
			cout << setw(6) << _connections[i]->getID() << "     |  "<<setw(2) << _connections[i+1]->getID() << "  |  "<<setw(2) << _connections[i+2]->getID() << endl;
			//system("pause");
	}
	cout << "------------------------------------" << endl;
}
void ERModel::displayComponentTable()
{
	cout << "Components: " << endl;
	cout << "---------------------------------" << endl;
	cout << " Type |  ID  |  Name  " << endl;
	cout << "------+------+-------------------" << endl;

	for (int i = 0; i < _components.size();i++)
	{
		cout << "   " << _components[i]->getType() << "  |  "<< setw(2) << _components[i]->getID()  << "  |  " << _components[i]->getText() << endl;
	}
	cout << "---------------------------------" << endl;
}