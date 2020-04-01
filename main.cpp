#include "ZCEngine.h"
#include <stdlib.h> 

using namespace ZCPP;

class Example : public ZCEngine
{
public:
	Example()
	{

	}

public:
	bool Start() override
	{
		FrameRate = -1; // Set to run at infinite fps
		return true;
	}

	bool Update(float DeltaTime) override
	{
		for(int y = 0; y < ScreenHeight(); y++) {
			for(int x = 0; x < ScreenWidth(); x++) {
				std::string a;
				for(int i = 0; i < TextLimit(); i++)
				{
					std::string b(1,rand() % '!'+'~'-'!');
					a += b;
				}
				Draw(x,y,stoc(a));
			}
    	}
		DrawScreen(); // Must be used to draw screen
		return true;
	}

	bool Destroy() override
	{
		return true;
	}
};

int main()
{
	Example Main;
	if(Main.Build(30,20,2))
		Main.Initiate();
}
