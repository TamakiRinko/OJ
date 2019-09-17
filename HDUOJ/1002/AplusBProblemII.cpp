/**
 * @Copyright (C)  2019  all rights reserved
 * @file AplusBProblemII.cpp
 * @author Rinko
 * @date 2019-09-13 
 */

#include<iostream>
#include<string>
using namespace std;

int main(int argc, char const *argv[]){
    int n;
    cin >> n;
    for(unsigned i = 0; i < n; ++i){
        string a, b;
        cin >> a >> b;
        string tempA = a;
        string tempB = b;
        int length = 0;
        int lengthA = a.length();
        int lengthB = b.length();
        int carry = 0;  //进位
        int sum = 0;    //某位的和
        string result = "";
        //扩展到等长
        if(lengthA > lengthB){
            length = lengthA;
            for(unsigned j = 0; j < lengthA - lengthB; ++j){
                b = "0" + b;
            }
        }else{
            length = lengthB;
            for(unsigned j = 0; j < lengthB - lengthA; ++j){
                a = "0" + a;
            }
        }
        for(unsigned j = 0; j < length; ++j){
            sum = carry + (a[length - j - 1] - '0') + (b[length - j - 1] - '0');
            if(sum >= 10){
                sum -= 10;
                carry = 1;
            }else{
                carry = 0;
            }
            result = to_string(sum) + result;
        }
        if(carry == 1){ //最高位进位
            result = "1" + result;
        }
        cout << "Case " << i + 1 << ":" << endl;
        cout << tempA << " + " << tempB << " = " << result << endl;
        if(i != n - 1){
            cout << endl;
        } 
    }

    return 0;
}
