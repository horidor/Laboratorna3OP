#include <iostream>
#include <string>

class stack
{
private:
    int p_t;
    char STACK[256];
public:
    stack()
    {
        p_t = 0;
    }
    char pop()
    {
        p_t--;
        return STACK[p_t];
    }
    void push(char v)
    {   
        STACK[p_t]=v;
        p_t++;   
    }
    int check_pt()
    {
        return p_t;
    }
};

int num_of_elements(std::string);
std::string* divide_into_elements(std::string, int);
std::string* sort_station(std::string*, int);
char priority(char, char);

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

    std::string* out = sort_station(infix_alg, n);
    std::cout << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << out[i] << std::endl;
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

std::string* sort_station(std::string* L, int n)
{
    stack ST;
    char l;
    std::string* out = new std::string[n];
    int i = 0;
    int j = 0;
    while (j < n)
    {
        if (isdigit(L[j][0]) != 0)
        {
            out[i] = L[j];
            i++;
            j++;
        }
        else
        {
            if (ST.check_pt() == 0)
            {
                ST.push(L[j][0]);
                j++;
            }
            else
            {
                l = ST.pop();
                if (priority(l, L[j][0]) == l)
                {
                    out[i] = l;
                    ST.push(L[j][0]);
                    i++;
                    j++;
                }
                else
                {
                    ST.push(l);
                    ST.push(L[j][0]);
                    j++;
                }
            }
        }
    }
    while (ST.check_pt() > 0)
    {
        out[i] = ST.pop();
        i++;
    }
    return out;
}

char priority(char a, char b)
{
    char a_n = ' ';
    char b_n = ' ';
    char PRIORITY_LIST[8] = { '*','1','/','1','+','0','-','0' };
    for (int i = 0; i < 8; i += 2)
    {
        if (a == PRIORITY_LIST[i])
        {
            a_n = PRIORITY_LIST[i + 1];
        }
        if (b == PRIORITY_LIST[i])
        {
            b_n = PRIORITY_LIST[i + 1];
        }
    }
    if (a_n > b_n)
    {
        return a;
    }
    else if (a_n < b_n)
    {
        return b;
    }
    else
    {
        return a;
    }
}
