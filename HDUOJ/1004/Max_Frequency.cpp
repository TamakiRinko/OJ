/**
 * @Copyright (C)  2019  all rights reserved
 * @file Max_Frequency.cpp
 * @author Rinko
 * @date 2019-09-17 
 */

#include<iostream>
#include<string>
#include<unordered_set>
using namespace std;
#define print(x) cout << x << endl
#define input(x) cin>>x

struct balloon{
    string color;           //颜色
    mutable int count;      //数量，初始为0，mutable表示可修改！！
    balloon(string n):color(n),count(0){}
    void addCount(){
        count++;
    }
};

//指定符合hash函数的operator==重载
//比较相等只看color
bool operator==(const struct  balloon & X,const struct balloon & Y){
    return hash<string>()(X.color) == hash<string>()(Y.color);
}

struct balloon_hash{     //指定hash，作为模板的第二个参数
    //hash值为color的hash值
    size_t operator()(const struct balloon& _r) const {
        string tmp=_r.color;
        return std::hash<string>()(tmp);
    }
};

int main()
{
    int n;
    while (cin >> n){
        if(n == 0)  break;
        unordered_set<balloon, balloon_hash> balloons;
        int maxCount = 0;
        string maxString = "";
        string temp;
        for(unsigned i = 0; i < n; ++i){
            input(temp);
            //成员函数 insert() 可以插入作为参数传入的单个元素。
            //在这种情况下，它会返回一个 pair 对象，
            //这个 pair 对象包含一个迭代器，以及一个附加的布尔值用来说明插入是否成功。
            //如果元素被插入，返回的迭代器会指向新元素；如果没有被插入，迭代器指向阻止插入的元素。
            //初始count = 0，若插入成功，则数量加一，若不成功，则已有的那个balloon数量加一
            auto x = balloons.insert(balloon(temp));
            x.first->count += 1;
        }
        unordered_set<balloon,balloon_hash>::iterator iter = balloons.begin();
        while(iter != balloons.end()){
            if(iter->count > maxCount){
                maxCount = iter->count;
                maxString = iter->color;
            }
            iter++;
        }
        print(maxString);
    }
    return 0;
}