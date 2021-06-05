#include <iostream>


#include <string>

class stack
{
private:
    int p_t;
    int STACK[256];
public:
    stack()
    {

    }

};

int num_of_elements(std::string);
std::string* divide_into_elements(std::string, int);

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
    std::cout << infix << std::endl;
    
    int n = num_of_elements(infix);
    std::string* infix_alg = divide_into_elements(infix, n);
    for (int i = 0; i < n; i++)
    {
        std::cout << infix_alg[i] << std::endl;
    }


}

int num_of_elements(std::string S)
{
    int count_el = 1;
    for (int i = 0; i < S.length(); i ++)
    {
        if (isdigit(S[i]) == 0)
        {
            count_el++;
            count_el++;
        }
    }
    return count_el;
}

std::string* divide_into_elements(std::string D, int n)
{
    std::string* L = new std::string[n];
    int i = 0;
    int k = 0;
    int j = 0;
    for (j = 0; j < D.length(); j++)
    {
        if ((isdigit(D[j]) == 0))
        {
            L[i] = D.substr(k, j - k);
            k = j;
            i++;
            L[i] = D.substr(k, 1);
            i++;
            k++;
        }
    }
    L[i] = D.substr(k, j - k);
    return L;
}
