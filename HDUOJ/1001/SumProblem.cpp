/**
 * @Copyright (C)  2019  all rights reserved
 * @file SumProblem.cpp
 * @author Rinko
 * @date 2019-09-13 
 */

#include<iostream>
using namespace std;

int main(){
    int n;
    int x;
    while(cin >> n){
        x = 0;
        for(int i = 1; i <= n; ++i){
            x += i;
        }
        cout << x << endl << endl;
    }
    return 0;
}