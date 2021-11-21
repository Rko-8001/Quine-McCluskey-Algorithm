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
