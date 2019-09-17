/**
 * @Copyright (C)  2019  all rights reserved
 * @file MAX_SUM.cpp
 * @author Rinko
 * @date 2019-09-16 
 */

#include<iostream>
using namespace std;
#define MY_INT_MIN 0x80000000

int main(int argc, char const *argv[]){
    int t;
    cin >> t;
    for(unsigned i = 0; i < t; ++i){
        int n;
        //dk：长度为k的序列中的最大和
        //pk：长度为k的序列中包含最后一项的最大和
        //sk：输入的第k个数
        //以上三个变量中的k均可省略
        int dk = MY_INT_MIN, pk = MY_INT_MIN;
        int sk;
        int start = 1, end = 1; //首末位置
        int startpk = 1, endpk = 1; //pk所在首末位置
        cin >> n;
        for(unsigned j = 1; j <= n; ++j){
            cin >> sk;
            if(pk < 0){
                pk = sk;
                startpk = j;
                endpk = j;
            }else{  //pk = 0时startpk不变，需要第一个！
                pk = pk + sk;
                endpk = j;
            }
            if(sk < 0){
                if(dk < sk){
                    dk = sk;
                    start = j;
                    end = j;
                }
            }else{
                if(dk > pk){
                    dk = dk;
                }else{
                    dk = pk;
                    start = startpk;
                    end = endpk;
                }
            }
        }
        cout << "Case " << i + 1 << ":" << endl;
        cout << dk << " " << start << " " << end << endl;
        if(i != t - 1){
            cout << endl;
        } 
    }
    return 0;
}