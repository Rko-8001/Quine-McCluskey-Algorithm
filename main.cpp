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
class solver // class defined for minimizing
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
};
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
        invoking_two(truth_table, power , number);
        vector<string> minterms; // for storing expressions
        if (choice == 1)
        {
            for (int i = 0; i < power; i++)
            {
                if (truth_table[i] == 1)
                {
                }
            }
        }
        else if (choice == 2)
        {
            for (int i = 0; i < power; i++)
            {
                if (truth_table[i] == -1)
                {
                }
            }
        }
        else if (choice == 3)
        {
        }
        else
        {
            cout << "wrong input" << endl;
            system("cls");
            continue;
        }
        // checking(truth_table , power);
        system("pause");
        sort(minterms.begin(), minterms.end());
        char pass;

        cout << "you can check the answer" << endl;
        system("pause");
        cout << "\nwanna do it again?" << endl
             << "Enter 'y' for Yes and 'n' for No: ";
        cin >> pass;
        if (pass == 'y')
        {
            check = true;
            system("cls");
        }
        else
        {
            check = false;
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


