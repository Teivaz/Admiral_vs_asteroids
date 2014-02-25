#include "Precompiled.h"
#include "EsUtils_win.h"
#include "AppDelegate.h"

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, TCHAR *lpCmdLine, int nCmdShow)

#define IPHONE5 1136, 640
#define IPHONE4 960, 640

#include <iostream>
using namespace std;

struct base
{
    int x,y;
};

struct myStruct : base
{
    char c;
    int numOne;
}; base MS[10]; //array of myStruct

base * returnArray(char c)  //function that returns array type
{
    if (c == 'm'){ return MS; }
    //I plan to have other structs here similar to myStruct.
    return MS;
}

    myStruct m;
int main()
{
    m.numOne = 10;
    MS[0].x = 204;   //init 0 value in array
    MS[1].x = 97;    //init 1 value in array
    MS[2] = m;    //init 1 value in array

    int arrayCounter = 1; //count through array. if=0, returns correctly. If=1, then not correct...

    cout << returnArray('m')[arrayCounter].x << endl; //MS[1].x=204, MS[1].x=0

    system("pause");
}



#if 0

int main(int argn, char** argv)
{
    AppDelegate delegate;
    CreateGLWindowWithContext(&delegate, "Admiral vs Asteroids", IPHONE5);
    delegate.Init();
    WindowLoop(&delegate);

    return 0;
}

#endif // 0
