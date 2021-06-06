#include <iostream>
#include <string>

class stack //stack with two stacks - one for char, other for int
{
private:
    int p_t_c;
    int p_t_i;
    char STACK_CHAR[256];
    int STACK_INT[256];
public:
    stack()
    {
        p_t_c = 0;
        p_t_i = 0;
    }
    char pop_c()
    {
        p_t_c--;
        return STACK_CHAR[p_t_c];
    }
    void push_c(char v)
    {   
        STACK_CHAR[p_t_c]=v;
        p_t_c++;   
    }
    int check_pt_c()
    {
        return p_t_c;
    }
    int pop_i()
    {
        p_t_i--;
        return STACK_INT[p_t_i];
    }
    void push_i(int v)
    {
        STACK_INT[p_t_i] = v;
        p_t_i++;
    }
    int check_pt_i()
    {
        return p_t_i;
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

    
    std::string* out = sort_station(infix_alg, n);

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
    stack ST;
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
            if (ST.check_pt_c() == 0)
            {
                ST.push_c(L[j][0]);
                j++;
            }
            else
            {
                while (flag)
                {
                    l = ST.pop_c();
                    if ((priority(l, L[j][0]) == l))
                    {
                        out[i] = l;
                        i++;
                    }
                    else
                    {
                        ST.push_c(l);
                        ST.push_c(L[j][0]);
                        j++;
                        flag = false;
                    }

                }
            }
        }
    }
    while (ST.check_pt_c() > 0)
    {
        out[i] = ST.pop_c();
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
    stack ST;
    for (int i = 0; i < n; i++)
    {
        if (isdigit(L[i][0]) != 0)
        {
            ST.push_i(stoi(L[i]));
        }
        else
        {
            switch (L[i][0])
            {
            case '+':
            {
                int A, B;
                A = ST.pop_i();
                B = ST.pop_i();
                ST.push_i(B + A);
                break;
            }
            case '-':
            {
                int A, B;
                A = ST.pop_i();
                B = ST.pop_i();
                ST.push_i(B - A);
                break;
            }
            case '*':
            {
                int A, B;
                A = ST.pop_i();
                B = ST.pop_i();
                ST.push_i(B * A);
                break;
            }
            case '/':
            {
                int A, B;
                A = ST.pop_i();
                B = ST.pop_i();
                ST.push_i(B / A);
                break;
            }
            }
        }
    }
    return ST.pop_i();
}
