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
        p_t_c = -1;
        p_t_i = -1;
    }
    char pop_c()
    {
        p_t_c--;
        return STACK_CHAR[p_t_c+1];
        
    }
    void push_c(char v)
    {   
        p_t_c++;
        STACK_CHAR[p_t_c]=v;
        
    }
    int check_pt_c()
    {
        return p_t_c;
    }
    int pop_i()
    {
        p_t_i--;
        return STACK_INT[p_t_i+1];
    }
    void push_i(int v)
    {
        p_t_i++;
        STACK_INT[p_t_i] = v;
    }
    int check_top_i()
    {
        return p_t_i;
    }
};

std::string console_interp(int, char*[]);
int num_of_elements(std::string);
std::string* divide_into_elements(std::string, int);
std::string* sort_station(std::string*, int*);
char priority(char, char);
int get_through(std::string*, int);
int pow(int, int);

int main(int _argc, char* _argv[])
{
    std::string infix = console_interp(_argc, _argv);
    //std::string infix;                            //debug testing
    //getline(std::cin, infix);
    
    int n = num_of_elements(infix);
    std::string* infix_alg = divide_into_elements(infix, n);

    std::string* out_temp = sort_station(infix_alg, &n);
    std::string* out = new std::string[n];
    out = out_temp;

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
    int count_el = 0;
    bool flag = true;
    for (int i = 0; i < S.length(); i++)
    {
        switch (S[i])
        {
        case '+':
        case '/':
        case '^':
        case '*':
        case '(':
        case ')':
            flag = true;
            count_el++;
            break;
        case '-':
            if (i == 0)
                ;
            else if (S[i - 1] == '(')
                ;
            else
            {
                count_el++;
                
            }
            flag = true;
            break;
        default:
            if (flag)
            {
                count_el++;
                flag = false;
            }
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
    if (D[0] == '-')
    {
        j = 1;
    }
    while (j < D.length())
    {
        if ((isdigit(D[j]) == 0) and (k - j == 0) and (isdigit(D[j + 1]) != 0))
        {
            L[i] = D.substr(j, 1);
            k++;
            i++;
        }
        else if ((isdigit(D[j]) == 0) and (D[j] == '(') and (D[j+1] == '-'))
        {
            k = j;
            j += 2;
            L[i] = D.substr(k, 1);
            i++;
            k++;
            while (isdigit(D[j]) != 0)
            {
                j++;
            }
            L[i] = D.substr(k, j - k);
            i++;
            k = j;
            if (D[j] == ')')
            {
                L[i] = D.substr(k, 1);
                j++;
                k++;
                i++;
            }
            if (j >= D.length())
            {
                return L;
            }
            
            L[i] = D.substr(k, 1);
            k++;
            i++;
        }
        else if ((isdigit(D[j]) == 0))
        {
            L[i] = D.substr(k, j - k);
            k = j;
            i++;
            L[i] = D.substr(k, 1);
            i++;
            k++;
        }
        j++;
    }
    if (i < n)
    {
        L[i] = D.substr(k, j - k);
    }
    return L;
}

std::string* sort_station(std::string* L, int* n_ext) //Shunting-Yard algorithm
{
    int n = *n_ext;
    stack ST;
    char l;
    std::string* out = new std::string[n];
    int i = 0;
    int j = 0;
    bool flag;
    while (j < n)
    {
        if ((L[j].length() > 1) or (isdigit(L[j][0]) != 0))
        {
            out[i] = L[j];
            i++;
        }
        else
        {
            if ((L[j][0] != ')') and (L[j][0] != '('))
            {
                while (ST.check_pt_c() > -1)
                {
                    l = ST.pop_c();
                    if (l == '(')
                    {
                        ST.push_c(l);
                        break;
                    }
                    else if (priority(l, L[j][0]) == l)
                    {
                        out[i] = l;
                        i++;
                    }
                    else
                    {
                        ST.push_c(l);
                        break;
                    }
                }
                ST.push_c(L[j][0]);
            }
            else if (L[j][0] == '(')
            {
                ST.push_c(L[j][0]);
            }
            else if (L[j][0] == ')')
            {
                while (ST.check_pt_c() > -1)
                {
                    l = ST.pop_c();
                    if (l == '(')
                    {
                        *n_ext -= 2;
                        break;
                    }
                    out[i] = l;
                    i++;
                }
            }
        }
        j++;
    }
    while (ST.check_pt_c() > -1)
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
    char PRIORITY_LIST[10] = { '^','2','*','1','/','1','+','0','-','0' };
    for (int i = 0; i < 10; i += 2)
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
    else if ((a_n < b_n) or ((a_n == b_n) and (a == '^')))
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
        if ((L[i].length() > 1) or ((isdigit(L[i][0]))!= 0))
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
            case '^':
            {
                int A, B;
                A = ST.pop_i();
                B = ST.pop_i();
                if (A >= 0)
                {
                    ST.push_i(pow(B, A));
                }
                else
                {
                    ST.push_i(1/pow(B,A));
                }
                break;
            }
            }
        }
    }
    return ST.pop_i();
}

int pow(int a, int b) //recursive power function
{
    if (b > 0)
    {
        return a*pow(a,b-1);
    }
    else
    {
        return 1;
    }
}