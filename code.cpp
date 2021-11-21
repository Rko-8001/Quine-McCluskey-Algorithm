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
