#include <iostream>
#include <string>

class stack
{
private:
    int p;
    int STACK[256];
public:
    stack()
    {

    }

};


int main(int _argc, char* _argv[])
{
    std::cout << _argc << " - here." << std::endl;

    for (int i = 0; i < _argc; i++)
    {
        std::cout << _argv[i] << std::endl;
    }

    std::string infix = "";
    for (int i = 1; i < _argc; i++)
    {
        infix += _argv[i];
    }



    std::cout << infix;
    
}

