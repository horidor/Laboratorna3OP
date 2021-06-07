#include <iostream>
#include <string>

template <class T>
class stack //stack with template
{
private:
    int p_t;
    T STACK[256];
public:
    stack()
    {
        p_t = 0;
    }
    T pop()
    {
        p_t--;
        return STACK[p_t];
    }
    void push(T v)
    {   
        STACK[p_t]=v;
        p_t++;   
    }
    T check_pt()
    {
        return p_t;
    }
};

std::string console_interp(int, char*[]);
int num_of_elements(std::string);
std::string* divide_into_elements(std::string, int);
std::string* sort_station(std::string*, int);
char priority(char, char);
int get_through(std::string*, int);

int main(int _argc, char* _argv[])
{
    std::string infix = console_interp(_argc, _argv);
    //std::string infix;                            //DEBUG_test
    //getline(std::cin, infix);
    
    int n = num_of_elements(infix);
    std::string* infix_alg = divide_into_elements(infix, n);
    for (int i = 0; i < n; i++)
    {
        std::cout << infix_alg[i] << std::endl;
    }
    std::cout << std::endl;
    
    std::string* out = sort_station(infix_alg, n);
    for (int i = 0; i < n; i++)
    {
        std::cout << out[i] << std::endl;
    }

    int sum = get_through(out, n);
    std::cout << "Result: " << sum << std::endl;


}

std::string console_interp(int argc, char* argv[]) //interpreting console input
{
    std::string L = "";
    for (int i = 1; i < argc; i++)
    {
        L += argv[i];
    }
    return L;
}

int num_of_elements(std::string S) //getting number of elements
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

std::string* divide_into_elements(std::string D, int n) //dividing into operators and operands
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

std::string* sort_station(std::string* L, int n) //Shunting-Yard sort
{
    stack<char> ST;
    char l;
    std::string* out = new std::string[n];
    int i = 0;
    int j = 0;
    bool flag;
    while (j < n)
    {
        flag = true;
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
                while (flag)
                {
                    l = ST.pop();
                    if ((priority(l, L[j][0]) == l))
                    {
                        out[i] = l;
                        i++;
                    }
                    else
                    {
                        ST.push(l);
                        ST.push(L[j][0]);
                        j++;
                        flag = false;
                    }

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

char priority(char a, char b) //priority check
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

int get_through(std::string* L, int n) //getting through recieved postfix form
{
    stack<int> ST;
    for (int i = 0; i < n; i++)
    {
        if (isdigit(L[i][0]) != 0)
        {
            ST.push(stoi(L[i]));
        }
        else
        {
            switch (L[i][0])
            {
            case '+':
            {
                int A, B, C;
                A = ST.pop();
                B = ST.pop();
                C = B + A;
                ST.push(C);
                break;
            }
            case '-':
            {
                int A, B, C;
                A = ST.pop();
                B = ST.pop();
                C = B - A;
                ST.push(C);
                break;
            }
            case '*':
            {
                int A, B, C;
                A = ST.pop();
                B = ST.pop();
                C = B * A;
                ST.push(C);
                break;
            }
            case '/':
            {
                int A, B, C;
                A = ST.pop();
                B = ST.pop();
                C = B / A;
                ST.push(C);
                break;
            }
            }
        }
    }
    return ST.pop();
}
