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
        case 3:
            cout << "Enter boolean expression terms one by one with atmost " << num1;
            cout << " variables named as below\n";
            char i;
            cout << "< ";
            for (i = 'a'; i <= 'z' && x < num1; i++)
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
                    ll h = exp_to_minterms(num1, s);
                    truth_table[h] = 1;
                }
            } while (s != "-1");
            cout << "Enter don't care boolean expression terms one by one with atmost " << num1;
            cout << " variables named as below\n";
            nn;
            cout << " enter -1 for stopping";
            do
            {
                cin >> s;
                if (s != "-1")
                {
                    ll h = exp_to_minterms(num1, s);
                    truth_table[h] = 2;
                }
            } while (s != "-1");
            break;
        default:
            break;
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
