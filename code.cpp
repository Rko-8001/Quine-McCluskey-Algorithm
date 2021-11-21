// CS203  Project
/*
 Vinay kumar        2020csb1141
 Yadwinder Singh    2020csb1143
*/

// Header files
#include <iostream>
#include <stdio.h>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>

using namespace std;
// creating macro for long long int as ll
#define ll long long int
#define pb push_back
#define nn cout << "\n"
#define tt cout << "\t"
#define dbg(x) cout << #x << " = " << x << endl
#define all(v) v.begin(), v.end()
// typedefing for easier code writing and reading
typedef vector<ll> vint;
typedef vector<string> vector_string;

// Function contains brief info about project
void intro();
// functions displays all the instructons regarding input and output
void instructions();
// functions displays collaborators names
void ending();
// functions erases all the input user has input
// from user interface and displays only important info
void invoking_one(ll num);
// functions convert each expression user input after pressing 3
// to long long int
// for example input (abcd) = output(15);
ll exp_to_minterms(ll sizes, string t);
// class containting qm-solver functions
class solver
{
    // are the varables, dynamic arrays, strings, vector
    // and funcitons are declared in public
public:
    ll num_var;     // contains no. of variable user has input
    ll num_min;     // contains no. of min terms are there
    ll num_dont;    // contains no.of dont care terms
    ll num_PI = 0;  // contains no. of prime implicants
    ll num_EPI = 0; // contains data about no. of essential prime implicants
    // are there
    ll num_rem_min = 0; // contains no. of remaining terms
    // that wernt reduced i.e paired with other min terms.
    ll num_rem_PI = 0; // contains no. of remaining Prime implicants
    // that werent reduced i.e. paired with other prime implicants.
    ll logic_probe; // fpr checking whether the two binary terms
    // are same or not as we have to remove duplicates PIs
    ll pot_EPI = 0;
    ll *min_term_dec; // dynamic array thatcontains all min terms
    //  in form of decimal
    ll *dont_term_dec; // dyanmic array that contains all dont care terms
    //  in form of decimal
    ll **min_term_bin; // 2D dynamic array that contains all min terms
    // in form of binary
    ll ****qm_columns; // this is an 4D main dynamic array which contains
    // all min terms in colun on the basis of set bits and soon their reduced forms
    ll *NumberCounter; // contains how many times a min term occur
    ll **index_PI;     // dynamic conatains the prime implicants (say {2,4})
    ll **index_EPI;    // dynamic conatains the essential prime implicants
    ll *reduc_PI_one;ll **reduc_PI_two;ll **reduc_PI_three; // contains info of
    // whether the PI has been selected or not
    ll *For;// used in recursion function
    ll **maybe_EPI;// stores combo of PIs which covers all min terms
    solver(ll x, ll y, ll z) // constructor
    {
        num_var =  x; //initialization of number of varibales
        num_min =  y; //initialization of number of min terms
        num_dont = z; //initialization of number of dont cares
    }
    vector_string variables();     // creating a vector string
    void conversion_DectoBinary(); // function for converting
    // decimal to binary form //updates the min_term_bin
    void storing_min_terms(vector<ll> one, vector<ll> two);
    // function for storing min terms taking input as 2 vector one containing min terms
    // and other containing dont care
    ll count_setbit(ll *one, ll two); // count whether it contains
    // one in binary form as int var given
    void storing_binary();// function extension of conversion_DectoBinary
    ll num_same_setbits(ll one, ll two); //
    void creating_column();// creates a 4D dynamic array
    // and groups of min terms
    bool is_two_power(ll one);// to check whther number is power of two or not
    void grouping();// function that gorups the PIs
    void prime_implicants();// stores PIs in index_PI
    void remove_dontcare(); // remove the dont care terms
    void essential_implicants();// filter out essential implicants
    void recursion(ll one);// finds potential EPIs
    void printing();// prints minimized expression
    void checking(ll arr[], ll num);// just for debugginh
    vector_string generateGrayarr(ll n); // this function genrated the grey code
    // for displaying k map
    void invoking_two(ll arr[], ll size);// functions erases all the input user has input
    // from user interface and displays only important info
    void invoking_three(ll arr[], ll size);
    // functions erases all the input user has input
    // from user interface and displays only important info
    void star(); // prints star line
    ll bin_to_int(string s); //convert binary to int 
    void kmap_display(ll minterm[], ll var); // displays k map upto 5 variables
};
//main function
int main()
{
    intro();
    instructions();
    bool check = false;
    do
    {
        ll num1;
        cout << "\n Enter number of variables (1-10): ";
        cin >> num1;
        if (num1 > 10 || num1 < 1)
        {
            cout << "Sorry, you have entered invalid no. of variables";
            nn;
            cout << "Try Again!!";
            nn;
            system("pause");
            system("cls");
            continue;
        }
        ll power = pow(2, num1);
        ll *truth_table = (ll *)malloc(power * sizeof(ll));
        for (ll j = 0; j < power; j++)
        {
            truth_table[j] = -1;
        }
        invoking_one(num1);
        cout << "Press '1' for inputing SOP i.e. min terms." << endl;
        cout << "Press '2' for inputing POS i.e. max terms." << endl;
        cout << "Press '3' for inputing a boolean expression" << endl;
        ll choice;
        cin >> choice;
        int wrong = 0;
        ll num;
        ll x = 0;
        string s;
        switch (choice)
        {
        case 1:
            cout << "Enter min terms: ( Range : 0 - " << pow(2, num1) - 1 << " )" << endl;
            cout << "Enter -1 for stoppping" << endl;
            do
            {
                cin >> num;
                if (num != -1)
                {
                    truth_table[num] = 1;
                }
            } while (num != -1);
            nn;
            cout << "Enter don't care terms: ";
            cout << "Enter -1 for stoppping";
            nn;
            do
            {
                cin >> num;
                if (num != -1)
                    truth_table[num] = 2;
            } while (num != -1);
            nn;
            break;
        case 2:
            for (ll i = 0; i < power; i++)
            {
                truth_table[i] = 1;
            }
            cout << "Enter max terms: ";
            cout << "( Range : 0 - " << pow(2, num1) - 1 << " )" << endl;
            cout << "Enter -1 for stoppping" << endl;
            do
            {
                cin >> num;
                if (num != -1)
                    truth_table[num] = 0;
            } while (num != -1);
            nn;
            cout << "Enter don't care terms:";
            cout << "( Range : 0 - " << pow(2, num1) - 1 << " )" << endl;
            cout << "Enter -1 for stoppping";
            nn;
            do
            {
                cin >> num;
                if (num != -1)
                    truth_table[num] = 2;
            } while (num != -1);
            nn;
            break;
        cout << "Enter boolean expression terms one by one with atmost " << num1;
            cout << " variables named as below\n";
            char i;
            cout << "< ";
            for (i = 'A'; i <= 'Z' && x < num1; i++)
            {
                cout << i << " ";
                x++;
            }
            cout << ">";
            cout << endl;
            cout << "enter -1 for stopping" << endl;
            do
            {
                cin >> s;
                if (s != "-1")
                {
                    int checking_exp = check_exp(s, num1);
                    if (checking_exp == 1)
                    {
                        ll h = exp_to_minterms(num1, s);
                        truth_table[h] = 1;
                    }
                    else
                    {
                        wrong = 1;
                        cout << "Warning!! \nPlease enter correct SOP term!!";
                        nn;
                        cout << "Try again";
                        nn;
                        system("pause");
                        system("cls");
                        break;
                    }
                }
            } while (s != "-1");
            if (wrong == 1)
            {
                break;
            }
            cout << "Enter don't care boolean expression terms one by one with atmost " << num1;
            cout << " variables named as below\n";
            nn;
            cout << " enter -1 for stopping";
            do
            {
                cin >> s;
                if (s != "-1")
                {
                    bool checking_exp = check_exp(s, num1);
                    if (checking_exp)
                    {
                        ll h = exp_to_minterms(num1, s);
                        truth_table[h] = 2;
                    }
                    else
                    {
                        cout << "Warning!! \nPlease enter correct SOP term!!";
                        nn;
                        cout << "Try again";
                        nn;
                        system("pause");
                        system("cls");
                        nn;
                        wrong = 1;
                        // return 0;
                        break;
                    }
                }
            } while (s != "-1");
            break;
        default:
            break;
        }
        if (wrong == 1)
        {
            check = true;
            continue;
        }
        ll y = 0;
        ll z = 0;
        for (ll i = 0; i < power; i++)
        {
            if (truth_table[i] == 1)
            {
                y++;
            }
            if (truth_table[i] == 2)
            {
                z++;
            }
        }
        vector<ll> minis;
        vector<ll> donts;

        for (ll i = 0; i < power; i++)
        {
            if (truth_table[i] == 1)
            {
                minis.pb(i);
            }
            if (truth_table[i] == 2)
            {
                donts.pb(i);
            }
        }
        solver k_map(num1, y, z);
        cout << "Input has been taken.";
        nn;
        if (num1 < 6)
        {
            system("pause");
            k_map.invoking_two(truth_table, power);
            cout << "Here is the Karnaugh Graph: ";
            nn;
            k_map.kmap_display(truth_table, num1);
            nn;
        }

        system("pause");
        system("cls");
        k_map.invoking_three(truth_table, power);
        nn;
        nn;
        k_map.storing_min_terms(minis, donts);
        k_map.printing();
        nn;
        nn;
        nn;
        system("pause");
        system("cls");
        cout << "\nwanna do it again?";
        nn;
        cout << "Enter 'y' for Yes and 'n' for No: ";
        char pass;
        cin >> pass;
        if (pass == 'y')
        {
            check = true;
            system("cls");
        }
        else
        {
            check = false;
            system("cls");
        }

    } while (check);
    ending();
    return 0;
}

ll exp_to_minterms(ll sizes, string t)
{
    ll arr[size];
    for(ll i=0; i<size;i++)
    {
        arr[i] = 0;
    }
    for(ll i=0; i<s.size(); i++)
    {
        if(s[i+1] != 39)
        {
            arr[s[i]-65] = 1;
        }
    }
    ll sum = 0;
    for(ll i = 0; i <size; i++)
    {
        sum = sum*2 + arr[i];
    }
    return sum;
}
ll solver ::bin_to_int(string s)
{
    ll sum = 0;
    for (ll i = 0; i < s.size(); i++)
    {
        if (s[i] == '0')
        {
            sum = sum * 2;
        }
        else
        {
            sum = sum * 2 + 1;
        }
    }
    return sum;
}
void solver ::kmap_display(ll minterm[], ll var)
{
    ll fi = var / 2 + var % 2;
    ll se = var / 2;
    // dbg(fi);
    // dbg(se);
    nn;
    string vari[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    cout << "Horizontal side variables: ";
    ll i;
    for (i = 0; i < fi; i++)
    {
        cout << vari[i] << " ";
    }
    nn;
    ll x = i;
    cout << "Vertical Side variables: ";
    for (ll j = 0; j < se; j++)
    {
        cout << vari[x] << " ";
        x++;
    }
    nn;
    nn;
    tt;
    vector_string hori = generateGrayarr(fi);
    for (i = 0; i < hori.size(); i++)
    {
        cout << hori[i];
        tt;
    }
    nn;
    vector_string veri = generateGrayarr(se);
    for (ll x = 0; x < veri.size(); x++)
    {
        cout << veri[x];
        tt;
        for (ll y = 0; y < hori.size(); y++)
        {
            ll index = bin_to_int(hori[y] + veri[x]);
            if (minterm[index] == 1)
            {
                cout << "X";
                cout << "(";
                cout << index << ")";
            }
            else if (minterm[index] == 2)
            {
                cout << "*";
                cout << "(" << index << ")";
            }
            else
            {
                cout << ".";
            }
            tt;
        }
        nn;
    }
}
void solver::checking(ll arr[], ll num)
{
    cout << "min terms stored are: ";
    for (ll y = 0; y < num; y++)
    {
        if (arr[y] == 1)
            cout << y << " ";
    }
    nn;
    cout << "Don't terms stored are: ";
    for (ll y = 0; y < num; y++)
    {
        if (arr[y] == 2)
            cout << y << " ";
    }
    nn;
}
void invoking_one(ll num)
{
    system("cls");
    cout << "Your Input:";
    cout << endl;
    cout << "\tNo. of variables: " << num;
    cout << endl;
    cout << "**********************************************";
    cout << "*********************" << endl;
    cout << endl;
}
void solver::invoking_two(ll arr[], ll size)
{
    system("cls");
    cout << "Your Input:";
    cout << endl;
    cout << "\tNo. of variables: " << num_var;
    cout << endl;
    cout << "Min Terms: ";
    for (ll i = 0; i < size; i++)
    {
        if (arr[i] == 1)
        {
            cout << i << " ";
        }
    }
    nn;
    cout << "Don't care: ";
    for (ll i = 0; i < size; i++)
    {
        if (arr[i] == 2)
        {
            cout << i << " ";
        }
    }
    cout << endl;
    cout << "**********************************************";
    cout << "***********************" << endl;
    cout << endl;
}
void solver::invoking_three(ll arr[], ll size)
{
    system("cls");
    cout << "Your Input:";
    cout << endl;
    cout << "\tNo. of variables: " << num_var;
    cout << endl;
    cout << "\tMin Terms: ";
    for (ll i = 0; i < size; i++)
    {
        if (arr[i] == 1)
        {
            cout << i << " ";
        }
    }
    nn;
    cout << "Don't care: ";
    for (ll i = 0; i < size; i++)
    {
        if (arr[i] == 2)
        {
            cout << i << " ";
        }
    }
    nn;
    nn;
    cout << "**********************************************";
    cout << "***********************" << endl;
    nn;
}
vector_string solver::generateGrayarr(ll variables_number)
{

    vector<string> grey_code_vector;
    if (variables_number <= 1)
    {
        grey_code_vector.pb(" ");
        return grey_code_vector;
    }
    grey_code_vector.pb("0");
    grey_code_vector.pb("1");
    ll i, j;
    for (i = 2; i < (1 << variables_number); i = i << 1)
    {
        for (j = i - 1; j >= 0; j--)
        {
            grey_code_vector.pb(grey_code_vector[j]);
        }
        for (j = 0; j < i; j++)
        {
            grey_code_vector[j] = "0" + grey_code_vector[j];
        }
        for (j = i; j < 2 * i; j++)
        {
            grey_code_vector[j] = "1" + grey_code_vector[j];
        }
    }
    return grey_code_vector;
}
void ending()
{
    system("pause");
    system("cls");
    cout << "\t\t-----***You are welcome***-----";
    cout << endl
         << "Created by" << endl;
    cout << "\t\t 2020csb1141 \t Vinay Kumar" << endl;
    cout << "\t\t 2020csb1143 \t Yadwinder Singh" << endl;
}
void instructions()
{
    cout << "Hi There, \nHere is some info regarding inputing data: ";
    nn;
    nn;
    cout << "Solving Steps: ";
    nn;
    cout << "Enter number of variables : say num_var (ll)";
    nn;
    nn;
    cout << "You are given 3 choices for inputing: ";
    nn;
    tt;
    cout << " \tPress '1' for inputing SOP i.e. min terms.";
    tt;
    nn;
    tt;
    cout << " \tPress '2' for inputing POS i.e. max terms.";
    tt;
    nn;
    tt;
    cout << " \tPress '3' for inputing a boolean expression";
    nn;
    nn;
    cout << "Pick any one of above";
    nn;
    nn;
    cout << "if pressed '1', then input min terms and enter '-1' for stopping ";
    nn;
    tt;
    tt;
    cout << "then enter don't care terms and enter '-1' for stopping";
    nn;
    nn;
    cout << "if pressed '2', then input max terms and enter '-1' for stopping ";
    nn;
    tt;
    tt;
    cout << "then enter don't care terms and enter '-1' for stopping";
    nn;
    nn;
    cout << " if pressed '3', then input each expression one by one and enter '-1' for stopping ";
    nn;
    tt;
    tt;
    cout << "then enter don't care expression and enter '-1' for stopping";
    nn;
    nn;
    cout << "You are ready to go";
    nn;
    nn;
    nn;
    cout << "\t\t\t\t **Note**";
    nn;
    nn;
    cout << "In the input, if you have pressed '3' i.e you have chosen to enter boolean expression then";
    cout << " enter terms of expression one by one and the program accepts only SOP tems";
    nn;
    cout << " for example num_var = 4 so variables are (a,b,c,d).";
    cout << " sample expression is a'bcd' or a'b'c'd or abcd and so on";
    nn;
    nn;
    nn;
    system("pause");
    system("cls");
}
void intro()
{
    system("cls");
    cout << "\t\t\t\t Welcome to our CS203 Project - Logic Minimizer" << endl;
    cout << "\t\t\t\t **********************************************" << endl
         << endl;
    cout << "It's a c++ program to simplify Boolean expressions inspired by Karnaugh map based on qm method.\n\nFunctionality:\n";
    cout << "This project takes the input of number of Boolean variables from the user. ";
    cout << "The user should enter the input either in form of min terms(SOP), ";
    cout << "max terms(POS) or can also enter the Boolean expression itself.";
    cout << " then user enter don't care terms";
    nn;
    nn;
    cout << "User will get k-map alongside minimized boolean expression.";
    nn;
    // cout<<"The program will make the k map of the given the expression,";
    // cout<<" also the minimized form of the Boolean expression.\n";
    cout << endl;
    system("pause");
    system("cls");
}
void solver::star()
{
    cout << "**********************************************";
    cout << "***********************";
    nn;
    nn;
}void solver::printing()
{
    essential_implicants();
    ll NumberOfPossibleEPI = 1;
    ll i, j, k, l;
    ll MinimumNo;
    if (num_rem_PI == 0)
    {
        cout << "Your minimized expression is: ";
        nn;
        ll x, y;
        for (x = 0; x < num_EPI; x++)
        {
            for (y = 0; y < num_var; y++)
            {
                ll a = index_EPI[x][0];
                ll b = index_EPI[x][1];
                ll c = index_EPI[x][2];
                if (qm_columns[a][b][c][y] == 1)
                {
                    int es  =65 + y;
                    cout<<char(es);
                }
                else if (qm_columns[a][b][c][y] == 0)
                {
                    int es = 65 + y;
                    cout<<char(es)<<"'";
                }
            }
            if (x < num_EPI - 1)
            {
                cout << " +";
            }
        }
    }
    else
    {
        for (i = 0; i < num_rem_min; i++)
            reduc_PI_three[i] = (ll *)malloc(num_rem_PI * sizeof(ll));
        for (i = 0; i < num_rem_min; i++)
            for (j = 0; j < num_rem_PI; j++)
                reduc_PI_three[i][j] = 0;
        for (i = 0; i < num_rem_PI; i++)
            for (j = 0; j < pow(2, reduc_PI_two[i][0]); j++)
                for (k = 0; k < num_rem_min; k++)
                    if (qm_columns[reduc_PI_two[i][0]][reduc_PI_two[i][1]][reduc_PI_two[i][2]][num_var + 3 + reduc_PI_two[i][0] + j] == reduc_PI_one[k])
                    {
                        reduc_PI_three[k][i] = 1;
                    }
        For = (ll *)malloc(num_rem_min * sizeof(ll));
        for (i = 0; i < num_rem_min; i++)
        {
            For[i] = -1;
        }
        for (i = 0; i < num_rem_min; i++)
            NumberOfPossibleEPI = NumberOfPossibleEPI * NumberCounter[reduc_PI_one[i]];
        maybe_EPI = (ll **)malloc(NumberOfPossibleEPI * sizeof(ll *));
        for (i = 0; i < NumberOfPossibleEPI; i++)
        {
            maybe_EPI[i] = (ll *)malloc(num_rem_min * sizeof(ll));
        }
        recursion(num_rem_min - 1);
        ll *NoOfPIForEPI = (ll *)malloc(NumberOfPossibleEPI * sizeof(ll));

        for (i = 0; i < NumberOfPossibleEPI; i++)
            NoOfPIForEPI[i] = 0;
        for (i = 0; i < NumberOfPossibleEPI; i++)
            for (j = 0; j < num_rem_min; j++)
                if (maybe_EPI[i][j] != -1)
                {
                    NoOfPIForEPI[i]++;
                    for (k = j + 1; k < num_rem_min; k++)
                        if (maybe_EPI[i][k] == maybe_EPI[i][j])
                            maybe_EPI[i][k] = -1;
                }

        for (i = 1; i < NumberOfPossibleEPI; i++)
            if (NoOfPIForEPI[i] < NoOfPIForEPI[MinimumNo])
                MinimumNo = i;
        for (i = 0; i < num_rem_min; i++)
            if (maybe_EPI[MinimumNo][i] != -1)
                index_EPI[num_EPI++] = reduc_PI_two[maybe_EPI[MinimumNo][i]];

        cout << "Your minimized expression is: ";
        nn;
       ll x, y;
        for (x = 0; x < num_EPI; x++)
        {
            for (y = 0; y < num_var; y++)
            {
                ll a = index_EPI[x][0];
                ll b = index_EPI[x][1];
                ll c = index_EPI[x][2];
                if (qm_columns[a][b][c][y] == 1)
                {
                    int es  =65 + y;
                    cout<<char(es);
                }
                else if (qm_columns[a][b][c][y] == 0)
                {
                    int es = 65 + y;
                    cout<<char(es)<<"'";
                }
            }
            if (x < num_EPI - 1)
            {
                cout << " +";
            }
        }
    }
}
void solver::recursion(ll num)
{
    ll temp = num;
    for (For[temp] = 0; For[temp] < num_rem_PI; For[temp]++)
    {
        if (reduc_PI_three[num_rem_min - 1 - temp][For[temp]])
        {
            if (temp > 0)
            {
                num = temp;
                num--;
                recursion(num);
            }
            else if (temp == 0)
            {
                for (ll i = 0; i < num_rem_min; i++)
                {
                    maybe_EPI[pot_EPI][i] = For[num_rem_min - 1 - i];
                }
                pot_EPI++;
            }
        }
    }
}
void solver::essential_implicants()
{
    prime_implicants();
    remove_dontcare();
    index_EPI = (ll **)malloc(num_min * sizeof(ll *));
    ll i, j, k, l;
    for (i = 0; i < pow(2, num_var); i++)
        if (NumberCounter[i] == 1)
            for (j = 0; j < num_PI; j++)
                for (k = 0; k < pow(2, index_PI[j][0]); k++)
                {
                    if (qm_columns[index_PI[j][0]][index_PI[j][1]][index_PI[j][2]][num_var + 3 + index_PI[j][0] + k] == i)
                    {
                        index_EPI[num_EPI] = index_PI[j];
                        for (l = 0; l < pow(2, index_PI[j][0]); l++)
                            NumberCounter[qm_columns[index_PI[j][0]][index_PI[j][1]][index_PI[j][2]][num_var + 3 + index_PI[j][0] + l]] = 0;
                        num_EPI++;
                        k = pow(2, index_PI[j][0]);
                    }
                }
    num_rem_min = 0;
    for (i = 0; i < pow(2, num_var); i++)
        if (NumberCounter[i] != 0)
            num_rem_min++;
    reduc_PI_one = (ll *)malloc(num_rem_min * sizeof(ll));
    for (i = 0; i < num_rem_min; i++)
        reduc_PI_one[i] = -1;
    reduc_PI_two = (ll **)malloc(num_PI * sizeof(ll *));
    for (i = 0; i < num_PI; i++)
        reduc_PI_two[i] = NULL;
    reduc_PI_three = (ll **)malloc(num_rem_min * sizeof(ll *));

    for (i = 0, j = 0; j < pow(2, num_var); j++)
        if (NumberCounter[j] != 0)
        {
            reduc_PI_one[i] = j;
            i++;
        }
    num_rem_PI = 0;
    for (i = 0; i < num_PI; i++)
        for (j = 0; j < pow(2, index_PI[i][0]); j++)
        {
            if (NumberCounter[qm_columns[index_PI[i][0]][index_PI[i][1]][index_PI[i][2]][num_var + 3 + index_PI[i][0] + j]] != 0)
            {
                j = pow(2, index_PI[i][0]);
                reduc_PI_two[num_rem_PI] = index_PI[i];
                num_rem_PI++;
            }
        }
}
void solver::remove_dontcare()
{
    for (ll i = 0; i < num_dont; i++)
    {
        NumberCounter[dont_term_dec[i]] = 0;
    }
}
void solver::prime_implicants()
{
    grouping();
    ll a = num_var;
    ll logic_probe;
    NumberCounter = (ll *)malloc(pow(2, a) * sizeof(ll));
    for (ll i = 0; i < pow(2, a); i++)
        NumberCounter[i] = 0;

    index_PI = (ll **)malloc(num_min * sizeof(ll *));
    for (ll i = 0; i < num_min; i++)
    {
        index_PI[i] = (ll *)malloc(3 * sizeof(ll));
    }
    ll i, j, k, l, m, n;
    for (i = 0; i < a + 1; i++)
        for (j = 0; j < a + 1 - i; j++)
            for (k = 0; k < num_same_setbits(i, j); k++)
                if (qm_columns[i][j][k] != NULL && qm_columns[i][j][k][a + 1] == 0)
                {
                    logic_probe = 0 - pow(2, i); /*logic_probe is used to
                         check whether this PI is a duplicate*/
                    for (l = k - 1; l >= 0; l--)
                        if (logic_probe != 0)
                        {
                            logic_probe = 0 - pow(2, i);
                            for (m = 0; m < pow(2, i); m++)
                                for (n = 0; n < pow(2, i); n++)
                                    if (qm_columns[i][j][l][a + 3 + i + m] == qm_columns[i][j][k][a + 3 + i + n])
                                    {
                                        logic_probe++;
                                    }
                        }

                    if (logic_probe != 0)
                    {
                        index_PI[num_PI][0] = i;
                        index_PI[num_PI][1] = j;
                        index_PI[num_PI][2] = k;
                        num_PI++;
                        for (l = 0; l < pow(2, i); l++)
                        {
                            NumberCounter[qm_columns[i][j][k][a + 3 + i + l]]++;
                        }
                    }
                }
}
void solver::grouping()
{
    creating_column();
    ll i, j, k, m, l, n, p, position;
    ll form_grp = 1;
    ll logic_probe;
    for (i = 0; i < num_var + 1; i++)
    {
        if (form_grp)
        {
            form_grp = 0;
            for (j = 0; j < num_var - i; j++)
            {
                m = 0;
                for (k = 0; k < num_same_setbits(i, j); k++)
                    if (qm_columns[i][j][k] != NULL)
                    {
                        for (l = 0; l < num_same_setbits(i, j + 1); l++)
                        {
                            if (qm_columns[i][j + 1][l] != NULL && qm_columns[i][j + 1][l][num_var + 2 + i] > qm_columns[i][j][k][num_var + 2 + i] &&
                                is_two_power(qm_columns[i][j + 1][l][num_var + 2 + i] - qm_columns[i][j][k][num_var + 2 + i]))
                            {
                                logic_probe = 0 - i;
                                for (n = 1; n <= i; n++)
                                    for (p = 1; p <= i; p++)
                                        if (qm_columns[i][j + 1][l][num_var + 1 + n] == qm_columns[i][j][k][num_var + 1 + p])
                                        {
                                            logic_probe++;
                                        }
                                if (logic_probe == 0)
                                {
                                    form_grp = 1;
                                    qm_columns[i][j][k][num_var + 1] = 1;
                                    qm_columns[i][j + 1][l][num_var + 1] = 1;
                                    qm_columns[i + 1][j][m] = (ll *)malloc((num_var + 4 + i + pow(2, i + 1)) * sizeof(ll));
                                    for (n = 0; n <= num_var + 1 + i; n++)
                                    {
                                        qm_columns[i + 1][j][m][n] = qm_columns[i][j][k][n];
                                    }
                                    qm_columns[i + 1][j][m][num_var + 3 + i] = qm_columns[i][j][k][num_var + 2 + i];
                                    for (n = num_var + 4 + i; n < num_var + 4 + i + pow(2, i + 1); n++)
                                        qm_columns[i + 1][j][m][n] = 0;
                                    position = log((qm_columns[i][j + 1][l][num_var + 2 + i] -
                                                    qm_columns[i][j][k][num_var + 2 + i])) /
                                               log(2);
                                    qm_columns[i + 1][j][m][num_var - 1 - position] = 2;
                                    qm_columns[i + 1][j][m][num_var + 1] = 0;
                                    qm_columns[i + 1][j][m][num_var + 2 + i] = position;
                                    for (p = 0; p < pow(2, i); p++)
                                    {
                                        qm_columns[i + 1][j][m][num_var + 4 + i + p] = qm_columns[i][j][k][num_var + 3 + i +
                                                                                                           p];
                                    }
                                    for (p = pow(2, i); p < pow(2, i + 1); p++)
                                    {
                                        qm_columns[i + 1][j][m][num_var + 4 + i + p] = qm_columns[i][j + 1][l][num_var + 3 +
                                                                                                               i + p - (ll)pow(2, i)];
                                    }
                                    m++;
                                }
                            }
                        }
                    }
            }
        }
    }
}
bool solver ::is_two_power(ll check)
{
    if (floor(log(check) / log(2)) == (log(check) / log(2)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
void solver::creating_column()
{
    storing_binary();
    qm_columns = (ll ****)malloc((num_var + 1) * sizeof(ll ***));
    for (ll i = 0; i < num_var + 1; i++)
    {
        qm_columns[i] = (ll ***)malloc((num_var + 1 - i) * sizeof(ll **));
    }
    for (ll i = 0; i < num_var + 1; i++)
    {
        for (ll j = 0; j < num_var + 1 - i; j++)
        {
            qm_columns[i][j] = (ll **)malloc(num_same_setbits(i, j) * sizeof(ll *));
            for (ll k = 0; k < num_same_setbits(i, j); k++)
            {
                qm_columns[i][j][k] = NULL;
            }
        }
    }
    for (ll i = 0; i < num_var + 1; i++)
    {
        ll k = 0;
        for (ll j = 0; j < num_min; j++)
        {
            if (min_term_bin[j][num_var] == i)
            {
                qm_columns[0][i][k] = min_term_bin[j];
                k++;
            }
        }
    }
}
ll solver::num_same_setbits(ll column_no, ll set_bits)
{
    ll ntok, kto1, temp;
    ntok = 1;
    kto1 = 1;
    temp = num_var;
    ll i = temp;
    while (i >= temp + 1 - set_bits + 1 - column_no)
    {
        ntok = i * ntok;
        i--;
    }
    i = set_bits;
    while (i)
    {
        kto1 = i * kto1;
        i--;
    }
    ll result = ntok / kto1;
    return result;
}
ll solver::count_setbit(ll *arr, ll num)
{
    ll count = 0;
    for (ll i = 0; i < num; i++)
    {
        if (arr[i] == 1)
        {
            count++;
        }
    }
    return count;
}
void solver::conversion_DectoBinary()
{
    for (ll i = 0; i < num_min; i++)
    {
        ll x = min_term_dec[i];
        ll j = num_var - 1;
        while (j >= 0)
        {
            min_term_bin[i][j] = x % 2;
            x = x / 2;
            j--;
        }
    }
}
void solver ::storing_binary()
{
    min_term_bin = (ll **)malloc(num_min * sizeof(ll *));
    for (ll i = 0; i <= num_min; i++)
    {
        min_term_bin[i] = (ll *)malloc((num_var + 4) * sizeof(ll));
    }
    conversion_DectoBinary();
    for (ll i = 0; i < num_min; i++)
    {
        min_term_bin[i][num_var] = count_setbit(min_term_bin[i], num_var);
        min_term_bin[i][num_var + 1] = 0;
        min_term_bin[i][num_var + 2] = min_term_dec[i];
        min_term_bin[i][num_var + 3] = min_term_dec[i];
    }
}
vector_string solver ::variables()
{
    vector_string v_m;
    string arguments[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    ll i;
    for (i = 0; i < num_var; i++)
    {
        v_m.pb(arguments[i]);
    }
    return v_m;
}
void solver ::storing_min_terms(vector<ll> min_term, vector<ll> donts)
{
    min_term_dec = (ll *)malloc(num_min * sizeof(ll));
    dont_term_dec = (ll *)malloc(num_dont * sizeof(ll));
    for (ll i = 0; i < min_term.size(); i++)
    {
        min_term_dec[i] = min_term[i];
    }
    for (ll i = 0; i < donts.size(); i++)
    {
        dont_term_dec[i] = donts[i];
    }
}
bool check_exp(string s, ll size)
{
    ll arr[size];
    for(ll i=0; i<size;i++)
    {
        arr[i] = -1;
    }
    for(ll i=0; i<s.size(); i++)
    {
        if(s[i+1] != 39)
        {
            ll x = s[i] -65;
            if(x >= size)
            {
                return false;
            }
            arr[x] = 1;
        }
    }
    
    for(ll i = 0; i <size; i++)
    {
        if(arr[i] == -1)
        {
            return false;
        }
    }
    return true;
}
