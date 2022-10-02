#ifndef _WINDOWBASECLASS_H_
#define _WINDOWBASECLASS_H_


#include <string>

class WindowBaseClass
{

public:
	WindowBaseClass();

	virtual ~WindowBaseClass();

	virtual void Start();

	virtual void Draw();

	std::string name;

	bool isEnabled;

};

#endif // !_WINDOWBASECLASS_H_