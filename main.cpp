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


typedef vector<string> vector_string;
#define pb push_back
#define nn cout << "\n"
#define tt cout <<"\t"
#define dbg(x) cout<<#x<<" = "<<x<<endl
#define all(v) v.begin(), v.end()

void intro();
void instructions();
void ending();
void checking(int arr[], int size);
int exp_to_minterms(int sizes, string t);
vector_string generateGrayarr(int n);
void printing_binary_string(int num_to_convert_to_binary, int var);
int bin_to_int( string s);
void kmap_display( int minterm[], int var);
void invoking_one(int type);
void invoking_two(int arr[], int size, int n);
void invoking_three(int arr[], int size, int n);
void star();


class solver
{
public:
    int varis;
    string donts;
    int data;
    solver(int num) // constrcutor
    {
        varis = num;
        donts.append(num, '-');
    }

    vector_string variables();
    string binary_convertor(int decimal);
    int grey_code_check(string one, string two);
    bool check_present(vector_string one, string two);
    string compliments(string one, string two);
    vector_string minimization(vector_string min_terms);
    string get_answer(string ans);
    bool string_equal(string one, string two);
    bool vector_equal(vector_string one, vector_string two);
};

vector_string solver ::variables()
{
    vector_string v_m;
    string arguments[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    int i;
    for (i = 0; i < varis; i++)
    {
        v_m.pb(arguments[i]);
    }
    return v_m;
}
string solver ::binary_convertor(int num)
{
    int temp = num;
    string binary_s = "";
    if (temp == 0)
    {
        binary_s = "0";
    }
    else
    {
        while (temp > 0)
        {
            if (temp % 2 == 0)
            {
                binary_s = "0" + binary_s;
            }
            else
            {
                binary_s = "1" + binary_s;
            }
            temp = temp / 2;
        }
    }
    int remainder = varis - binary_s.size();
    while (remainder > 0)
    {
        binary_s = "0" + binary_s;
        remainder--;
    }
    return binary_s;
}
int solver ::grey_code_check(string one, string two)
{
    int diff = 0;
    for (int i = 0; i < two.size(); i++)
    {
        if (two[i] != one[i])
        {
            diff++;
        }
    }
    if (diff == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool solver ::check_present(vector_string one, string two)
{
    for (int i = 0; i < one.size(); i++)
    {
        int check = one[i].compare(two);
        if (check == 0)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    intro();
    instructions();

    bool check = false;
    do
    {
        int number;
        cout << "\n Enter number of variables: ";
        cin >> number;
        if (number > 26 || number < 1)
        {
            cout << "Sorry, you have entered invalid no. of variables";
            cout << endl
                 << "Try Again!!" << endl;
            continue;
        }
        invoking_one(number);
        solver k_map(number);
        long long int power = pow(2, number);
        int truth_table[power];
        for (int j = 0; j < power; j++)
        {
            truth_table[j] = -1;
        }

        cout << "Press '1' for inputing SOP i.e. min terms." << endl;
        cout << "Press '2' for inputing POS i.e. max terms." << endl;
        cout << "Press '3' for inputing a boolean expression" << endl;
        int choice;
        cin >> choice;

        int num;
        int x = 0;
        string s;
        switch (choice)
        {
        case 1:
            cout << "Enter min terms: ( Range : 0 - " << pow(2, number) - 1 << " )" << endl;
            cout << "Enter -1 for stoppping" << endl;
            do
            {
                cin >> num;
                if (num != -1)
                {
                    truth_table[num] = 1;
                }
            } while (num != -1);
            break;
        case 2:
            for (int i = 0; i < power; i++)
            {
                truth_table[i] = 1;
            }
            cout << "Enter max terms: ( Range : 0 - " << pow(2, number) - 1 << " )" << endl;
            cout << "Enter -1 for stoppping" << endl;
            do
            {
                cin >> num;
                if (num != -1)
                    truth_table[num] = 0;
            } while (num != -1);
            break;
        case 3:
            cout << "Enter boolean expression terms one by one with atmost " << number;
            cout << " variables named as below\n";
            char i;
            cout << "< ";
            for (i = 'a'; i <= 'z' && x < number; i++)
            {
                cout << i << " ";
                x++;
            }
            cout << ">";
            cout << endl
                 << "enter -1 for stopping" << endl;
            do
            {
                cin >> s;
                if (s != "-1")
                {
                    int h = exp_to_minterms(number, s);
                    truth_table[h] = 1;
                }
            } while (s != "-1");
            break;
        default:
            break;
        }

        invoking_two(truth_table, power, number);

        vector<string> minterms; // for storing expressions
        for (int i = 0; i < power; i++)
        {
            if (truth_table[i] == 1)
            {
                minterms.pb(k_map.binary_convertor(i));
            }
        }
        // checking(truth_table , power);
        system("pause");

        sort(all(minterms));
        do
        {
            minterms = k_map.minimization(minterms);
            sort(all(minterms));
        } while (!k_map.vector_equal(minterms, k_map.minimization(minterms)));


        invoking_three(truth_table, power, number);
        cout << "Answer: " << endl;
        nn;
        int j = 0;
        for (int i = 0; i < minterms.size() - 1; i++)
        {
            cout << k_map.get_answer(minterms[i]);
            cout << "+";
            j++;
        }
        cout << k_map.get_answer(minterms[j]);
        nn;
        nn;
        system("pause");
        system("cls");


        invoking_three(truth_table, power, number);
        cout << "Answer: " << endl;
        int i;
        for (i = 0; i < minterms.size() - 1; i++)
        cout << k_map.get_answer(minterms[i])<<"+";
        cout << k_map.get_answer(minterms[i]);
        nn;
        star();
        cout << "Enter (1) for displaying K- Map: ";
        int kmap;
        cin >> kmap;
        if (kmap == 1)
        {
            cout << "Here is the Karnaugh Graph: ";
            nn;
            kmap_display(truth_table , number);
        }
        system("pause");
        system("cls");


        cout << "\nwanna do it again?" << endl
             << "Enter 'y' for Yes and 'n' for No: ";

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
void intro()
{
    system("cls");
    cout << "\t\t\t\t Welcome to our CS203 Project - Logic Minimizer" << endl;
    cout << "\t\t\t\t **********************************************"<<endl<<endl;
    cout << "It's a c++ program to simplify Boolean expressions inspired by Karnaugh map.\n\nFunctionality:\n";
    cout << "This project takes the input of number of Boolean variables from the user. ";
    cout << "The user should enter the input either in form of min terms(SOP),";
    cout << "max terms(POS) or can also enter the Boolean expression itself.\n\n";
    // cout<<"The program will make the k map of the given the expression,";
    // cout<<" also the minimized form of the Boolean expression.\n";
    cout << endl;
    system("pause");
    system("cls");
}
int exp_to_minterms(int sizes, string t)
{
    int sum = 0;
    int k = sizes - 1;
    int p = 0;
    for (int j = 0; j < t.size(); j++)
    {
        if (t[j] == 97 + p && t[j + 1] != 39)
        {
            p++;
            sum = sum + pow(2, k);
            k--;
        }
        if (t[j] == 97 + p && t[j + 1] == 39)
        {
            p++;
            k--;
        }
    }
    return sum;
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
    cout << "Hi There, \nHere some info regarding inputing data: ";
    cout << endl;
    cout << endl;
    cout<<"Solving Steps: ";
    cout << endl;
    cout << "====>\tEnter number of variables";
    cout << endl;
    cout << endl;
    cout << "\t\tPick one choice of inputing i.e. ===>";
    cout << endl;
    cout << " Press '1' for inputing SOP i.e. min terms." << endl;
    cout << " Press '2' for inputing POS i.e. max terms." << endl;
    cout << " Press '3' for inputing a boolean expression" << endl;
    cout << endl;
    cout << " if pressed '1', then input min terms and enter '-1' for stopping ";
    cout << endl;
    cout << " if pressed '2', then input max terms and enter '-1' for stopping ";
    cout << endl;
    cout << " if pressed '3', then input each expression one by one and enter '-1' for stopping ";
    cout << endl;
    cout << endl;
    cout << "You are ready to go";
    cout << endl;
    cout << endl;
    cout << endl;
    system("pause");
    system("cls");
}
void checking(int arr[], int size)
{
    cout<<"min terms stored are: ";
    for (int y = 0; y < size; y++)
    {
        if (arr[y] == 1)
            cout << y << " ";
    }
    cout<<endl;
}
void invoking_one (int type)
{
    system("cls");
    cout<<"Your Input:";
    cout<<endl;
    cout<<"\tNo. of variables: "<<type;
    cout<<endl;
    cout << "**********************************************";
    cout << "*********************" << endl;
    cout<<endl;
}
void invoking_two (int arr[] , int size , int n)
{
    system("cls");
    cout<<"Your Input:";
    cout<<endl;
    cout<<"\tNo. of variables: "<<n;
    cout<<endl;
    cout<<"Min Terms: ";
    for(int i = 0; i<size; i++)
    {
        if(arr[i] == 1)
        {
            cout<<i<<" ";
        }
    }
    cout<<endl;
    cout << "**********************************************";
    cout << "***********************" << endl;
    cout<<endl;
}
void invoking_three(int arr[], int size, int n)
{
    system("cls");
    cout << "Your Input:";
    cout << endl;
    cout << "\tNo. of variables: " << n;
    cout << endl;
    cout << "\tMin Terms: ";
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == 1)
        {
            cout << i << " ";
        }
    }
    nn;
    cout << "**********************************************";
    cout << "***********************" << endl;
    nn;
}
void star()
{
    cout << "**********************************************";
    cout << "***********************";
    nn;nn;
}

vector_string generateGrayarr(int variables_number)
{

    vector<string> grey_code_vector;
    if(variables_number<=1)
    {
        grey_code_vector.pb(" ");
        return grey_code_vector;
    }
    grey_code_vector.pb("0");
    grey_code_vector.pb("1");
    int i, j;
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
int bin_to_int( string s)
{
    int sum = 0;
    for(int i=0; i<s.size(); i++)
    {
        if(s[i] == '0')
        {
            sum = sum*2;
        }
        else
        {
            sum = sum*2 +1;
        }
    }
    return sum;
}
void kmap_display( int minterm[], int var)
{
    int fi = var/2 + var%2;
    int se = var/2;
    dbg(fi);
    dbg(se);
    string vari[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    cout<<"Horizontal side variables: ";
    int i;
    for( i=0; i<fi; i++)
    {
        cout<<vari[i]<<" ";
    }
    nn;
    int x = i;
    cout<<"Vertical Side variables: ";
    for(int j = 0; j<se; j++)
    {
        cout<<vari[x]<<" ";
        x++;
    }
    nn;
    tt;
    vector_string hori = generateGrayarr(fi);
    for( i=0; i<hori.size(); i++)
    {
        cout<<hori[i];
        tt;
    }
    nn;
    vector_string veri = generateGrayarr(se);
    for(int x=0; x<veri.size(); x++)
    {
        cout<<veri[x];
        tt;
        for(int y = 0; y<hori.size(); y++)
        {
            int index = bin_to_int(hori[y] + veri[x]);
            if(minterm[index] == 1)
            {
                cout<<"X"<<"("<<index<<")";
            }
            else
            {
                cout<<".";
            }
            tt;
        }
        nn;
    }

}



