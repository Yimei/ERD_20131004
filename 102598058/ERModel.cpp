#include "ERModel.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include "AddComponentCmd.h"
#include "DeleteComponentCmd.h"
#include "ConnectComponentsCmd.h"
#define TWO 2;
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
	//eRModel  = this;
	//eRModel = new ERModel();
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
void ERModel::undo()
{
	commandManager.undo();
	cout << commandManager.getHint() <<endl;
}
void ERModel::redo()
{
	commandManager.redo();
	cout << commandManager.getHint() <<endl;
}
void ERModel::addNodePresentation(string type)
{
	commandManager.execute(new AddComponentCmd(this, type));
}
void ERModel::deleteComponentPresentation(int deleteComponent)
{
	commandManager.execute(new DeleteComponentCmd(this,deleteComponent));
}
void ERModel::connectComponentPresentation()
{
	commandManager.execute(new ConnectComponentsCmd(this,"C"));
}
//void ERModel::setComponentsVector(Component* component)
//{
//	for (int i = 0; i < _components.size();i++)
//	{
//		_components[i]
//	}
//	
//}

vector<Component*> ERModel::getComponentsVector()
{
	return _components;
}
void ERModel::addNode(string type){
	
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
void ERModel::setComponentsVector(Component* component)
{
	_components.push_back(component);
}
vector<Component*> ERModel::getConnectionsVector()
{
	return _connections;
}
void ERModel::setConnectionsVector(Component* component)
{
	_connections.push_back(component);
}
Component* ERModel::clone(string type)
{
	componentFactory = new ComponentFactory();
	Component* component = componentFactory->createComponent(type);
	component->setID(_components.back()->getID());
	component->setText(_components.back()->getText());
	component->setType(type);
	return component;
}
Component* ERModel::connectionsClone(string type,int pos)
{
	componentFactory = new ComponentFactory();
	Component* component = componentFactory->createComponent(type);
	component->setID(_connections.at(pos)->getID());
	component->setText(_connections.at(pos)->getText());
	component->setType(type);
	return component;
}
Component* ERModel::componentsClone(string type, int pos)
{
	componentFactory = new ComponentFactory();
	Component* component = componentFactory->createComponent(type);
	component->setID(_components.at(pos)->getID());
	component->setText(_components.at(pos)->getText());
	component->setType(type);
	return component;
}

void ERModel::updateComponentSize()
{
	componentSize = _components.size();
}
int ERModel::getPresentComponentsSize()
{
	return componentSize;
}
void ERModel::setDeleteID(int deleteId)
{

	_deleteId = deleteId;
}
int ERModel::getDelelteID()
{
	return _deleteId;
}
int ERModel::checkDeleteComponentIDLoop()
{
	cin >> checkDeletIdTemp;
	if (existId(atoi(checkDeletIdTemp.c_str())))
	{
		return atoi(checkDeletIdTemp.c_str());
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
	cout << "Please input a file path: ";
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
		cout << "Components: " << endl;
		displayComponentTable();
		displayConnectionTable();
	}
	else cout << "File not found!!"<<endl;
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
			}
		}
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
void ERModel::connectTwoNode()
{
	if (checkAddConnectionNodeTwo()) 
	{
		setConnectionNodes(atoi(nodeIDTwo.c_str()));
		cout << _connectionNodesVector.size() <<endl;
		if (_connectionNodesVector[1] == _connectionNodesVector[0])//itself
		{
			cout << "&"<<endl;
			cout << "The Node '" <<  _connectionNodesVector[1] <<"' cannot be connected to itself." << endl;
			_connectionNodesVector.clear();
		}//same type
		else if (_components[_connectionNodesVector[1]]->getType() == _components[_connectionNodesVector[0]]->getType())
		{
			cout << "@~"<<endl;
			cout << "The node '" <<  _connectionNodesVector[1] <<"' cannot be connected by the node '"<<  _connectionNodesVector[0] <<"'."<<endl; 
		    _connectionNodesVector.clear();
		}//已連過同一條connector
		else if (checkExistConnection(_connectionNodesVector))//true: 已存在
		{
			cout << "***"<<endl;
			cout << "The node '" << _connectionNodesVector[1]<<"' has already been connected to node '" << _connectionNodesVector[0] <<"'."<<endl;
		    _connectionNodesVector.clear();
		}
		else if (!(_components[_connectionNodesVector[1]]->canConnectTo(_components[_connectionNodesVector[0]]))&&(_components[_connectionNodesVector[0]]->canConnectTo(   _components[_connectionNodesVector[1]])))
		{
			cout << "+++"<<endl;
			cout << "The node '"<<_connectionNodesVector[1]<<"' cannot be connected by the node '"<< _connectionNodesVector[0]<<"'."<<endl;
		    _connectionNodesVector.clear();
		}
		else
		{
			
			cout << "The node '"<<_connectionNodesVector[1]<<"' has been connected to the node '"<<_connectionNodesVector[0]<<"'."<<endl;
			createConnector(_connectionNodesVector);
			_connections.push_back(_components[_connectionNodesVector[0]]);
			_connections.push_back(_components[_connectionNodesVector[1]]);
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
		string cardinalityTemp;
		cout << "Enter the type of the cardinality:" <<endl<<"[0]1 [1]N"<<endl<<"> ";
		cin >> cardinality;
		if (atoi(cardinality.c_str()) == 0)
		{
			component->setText("1");
			cardinalityTemp = "1";
		}
		else if (atoi(cardinality.c_str()) == 1)
		{
			component->setText("N");
			cardinalityTemp = "N";
		}
		else
		{
			cout << "Wrong cardinality."<<endl;
		}
		cout << "Its cardinality of the relationship is '"<< cardinalityTemp << "'."<< endl;
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
int ERModel::checkAddConnectionNodeOneLoop()
{
	cin >> nodeIDOne;
	if (nodeIDOne == "0")//string 不用轉換前就是0
	{
		return atoi(nodeIDOne.c_str());
	}
	else 
	{
		for (int i = 0; i < _components.size(); i++)
		{
			if ((atoi(nodeIDOne.c_str()) == _components[i]->getID()) && (atoi(nodeIDOne.c_str())!=0))
			{
				return atoi(nodeIDOne.c_str());
			}
		}
		cout << "The node ID you entered does not exist. Please enter a valid one again." <<endl<<"> ";
		checkAddConnectionNodeOneLoop();
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
	cout << "Enter the ID of the entity:" << endl << "> ";
	checkEntityLoop();
	displayAttributeOfEntity();//ok
	cout << "Enter the IDs of the attributes (use a comma to separate two attributes):" << endl << "> ";
	checkPrimaryKeyLoop();
	cout << "The entity '"<< getPKEntity() <<"' has the primary key ("<<endl;
	for (int i = 0; i < _primaryKeys.size()-1;i++)
	{
		cout << _primaryKeys[i]  <<",";
	}
	cout << _primaryKeys[_primaryKeys.size()-1] <<")."<<endl;
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
void ERModel::checkPrimaryKeyLoop()
{
	_primaryKeys.clear();
	string PKString;
	cin >> PKString;
	vector<string> pkTemp = splitString(PKString,",");//id is string
	for (int i = 0; i < pkTemp.size(); i++)
	{
		//if (_components[getPKEntity()]->getConnections())
		vector<Component*> entityAttributes =  _components[getPKEntity()]->getConnections();
		 _primaryKeys.push_back(_components[getPKEntity()]);
		for (int j = 0; j < entityAttributes.size();j++)
		{
			if(entityAttributes[j]->getType()=="A")
			{
				if (atoi(pkTemp[i].c_str()) == entityAttributes[j]->getID())
				{
					_primaryKeys.push_back(_components[atoi(pkTemp[i].c_str())]);
				}
			}
			
		}
		if(_primaryKeys.size() != i+1)
		{
			cout << "The node '"<< pkTemp[i] <<"' does not belong to Entity '"<< getPKEntity() <<"'. Please enter a valid one again."<<endl<<"> ";
			checkPrimaryKeyLoop();
		}
	}
	return ;
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
void ERModel::displayAttributeOfEntity()
{
	Component* entityTemp;
	entityTemp = _components[getPKEntity()];
	cout << "Attributes of the entity '"<< getPKEntity() <<"'"<<endl;
	cout << "---------------------------------" << endl;
	cout << "Type | ID | Name  " << endl;
	cout << "-----+----+----------------------" << endl;
	for (int i = 0; i < entityTemp->getConnections().size();i++)
	{
		if (entityTemp->getConnections()[i]->getType()=="A")
			cout << "  " << entityTemp->getConnections()[i]->getType() << "  |  " << entityTemp->getConnections()[i]->getID() << "  |  " << entityTemp->getConnections()[i]->getText()<< endl;
	}
	cout << "------------------------------------" << endl;
}
void ERModel::checkEntityLoop()
{
	string entityId;
	cin >> entityId;
	if ((entityId == "0") && (_components[0]->getType()=="E"))
	{
		setPKEntity(atoi(entityId.c_str()));
		return;
	}
	else if (atoi(entityId.c_str()) == 0) //是字串
	{
		cout << "The node ID you entered does not exist. Please enter a valid one again." << endl << "> "<< endl;
		checkEntityLoop();
	}
	else if (_components[atoi(entityId.c_str())]->getType() != "E")
	{
		cout << "The node '" << entityId << "' is not an entity. Please enter a valid one again." << endl << "> "<< endl;
		checkEntityLoop();
	}
	else
	{
		setPKEntity(atoi(entityId.c_str()));
		return;
	}
}
void ERModel::setPKEntity(int entityid)
{
	entityID = entityid;
}
int ERModel::getPKEntity()
{
	return entityID;
}
void ERModel::displayEntityTable()
{
	cout << "Entities:" << endl;
	cout << "---------------------------------" << endl;
	cout << "Type | ID | Name  " << endl;
	cout << "-----+----+----------------------" << endl;
	for (int i = 0; i < _components.size();i++)
	{
		if (_components[i]->getType() == "E")
		{
			cout <<"  "<<_components[i]->getType()<< "  |  "<<_components[i]->getID()<<"  |  "<< _components[i]->getText()<<endl;
		}
	}
	cout << "---------------------------------" << endl;
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
	cout << "---------------------------------" << endl;
	cout << " Type |  ID  |  Name  " << endl;
	cout << "------+------+-------------------" << endl;
	updateComponentSize();
	for (int i = 0; i < _components.size();i++)
	{
		cout << "   " << _components[i]->getType() << "  |  "<< setw(2) << _components[i]->getID()  << "  |  " << _components[i]->getText() << endl;
	}
	cout << "---------------------------------" << endl;
}
void ERModel::deleteComponent(int id)
{
	
	setDeleteID(id);
	
	if (_components[id]->getType() == "C")
	{
		cout << _connections.size()<<endl;
		for (int i = 0; i < _connections.size();i++)
		{
			if(_connections[i]->getID() == id)
			{
				//cout << i <<endl;
				//cout <<"......"<<endl;
				_connections.erase(_connections.begin()+i+1+1);
				//cout <<"......"<<endl;
				_connections.erase(_connections.begin()+i+1);
				//cout <<"......"<<endl;
				_connections.erase(_connections.begin()+i);
				//cout <<"......"<<endl;
				continue;
				/*delete _connections[i+1+1];
				delete _connections[i+1];
				delete _connections[i];*/
			}
		}
		for (int i = 0; i < _components.size(); i++)
		{
			cout << "*&)(*"<<endl;
			if (_components[i]->getID()==id)
			{
				//cout << _components[id]->getText()<<endl;
				_components.erase(_components.begin()+i);
				//delete _components[i];
				//cout << _components.size()<<endl;
			}
		}
		updateComponentSize();
	}
	else
	{
		//cout <<"....."<<endl;
		int updateConnectionsSize = _connections.size();
		for(int i = 0; i < _connections.size();i++)
		{
			if(_connections[i]->getID() == id)
			{
				if(_connections[i-1]->getType() == "C")//表i為node1
				{
					_connections.erase(_connections.begin()+i+1);
					_connections.erase(_connections.begin()+i);
					_connections.erase(_connections.begin()+i-1);
					/*delete _connections[i+1];
					delete _connections[i];
					delete _connections[i-1];*/
				}
				else 
				{
					_connections.erase(_connections.begin()+i);
					_connections.erase(_connections.begin()+i-1);
					_connections.erase(_connections.begin()+i-1-1);
					/*delete _connections[i];
					delete _connections[i-1];
					delete _connections[i-1-1];*/
				}
				updateConnectionsSize = _connections.size();
				i=0;
			}
		}
		
		for (int i = 0; i < _components.size(); i++)
		{
			if (_components[i]->getID()==id)
			{
				//cout << _components[id]->getText()<<endl;
				_components.erase(_components.begin()+i);
				//delete _components[i];
				//cout << _components.size()<<endl;
			}
		}
	}
	/*while (_components.size() > 0)
	{
	Component* deleteData = _components.back();
	_components.pop_back();
	delete deleteData;
	}*/
}
int ERModel::getIndexOfComponentID(int componentID)
{
	for (int i = 0; i < _components.size();i++)
	{
		if(_components[i]->getID() == componentID)
			return i;
	}
}
int ERModel::getIndexOfConnectionsID(int connectionsID)
{
	for (int i = 0; i < _connections.size();i++)
	{
		if (_connections[i]->getID() == connectionsID)
			return i;
	}
}
void ERModel::deleteLastComponent()
{

}