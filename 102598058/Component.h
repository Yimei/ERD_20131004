#ifndef _Component_H_ 
#define _Component_H_
#include <vector>
#include <string>
using namespace std;
class Component{
public:
	Component();
	virtual ~Component();
	void setID(int);
	void setType(string type);
	void setText(string name);
	void setConnectionsNum();
	void setConnections(Component*);

	int getID();
	string getType();
	string getText();
	int getConnectionsNum();
	vector<Component*> getConnections();
	virtual void connectTo(Component *component)=0;
	virtual bool canConnectTo(Component *component)=0;
private:
	int _id;
	string _type;
	string _text;
	int _connectionsNum;
	vector<Component*> _connectionsVector;
};
#endif