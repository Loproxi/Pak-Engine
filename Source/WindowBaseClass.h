#include "imgui.h"

#include <string>

class WindowBaseClass
{

public:
	WindowBaseClass();

	virtual ~WindowBaseClass();

	virtual void Draw();

	std::string name;

	bool isEnabled;

};

