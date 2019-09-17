# unordered_set

### C++ 11，新的关联容器：**unordered_set**

### 基本介绍

* set和map内部实现是基于RB-Tree，而unordered_set和unordered_map内部实现是基于**哈希表**。

* unordered_set<T> 容器类型的模板定义在 <unordered_set> 头文件中。

```cpp
# include<unordered_set>
```

* unordered_set<T> 容器提供了和 unordered_map<T> 相似的能力，但 unordered_set<T> 可以用保存的元素作为它们自己的键。T 类型的对象在容器中的位置由它们的哈希值决定，因而需要定义一个 <font color=#0099ff>**Hash< T > 函数**</font>。基本类型可以省去Hash< T >方法。

* **不能存放重复元素**。

* 可指定buckets个数，可进行初始化，也可后期插入元素

    ```cpp
    std::unordered_set<string> example;
    std::unordered_set<string> things {16}; // 16 buckets
    std::unordered_set<string> words {"one", "two", "three", "four"};// Initializer list
    std::unordered_set<string> copy_wrds {words}; // Copy constructor
    ```

### 操作

1. unordered_set<Key, Hash, KeyEqual, Allocator>::**insert**

    * 可以插入作为参数传入的单个元素。在这种情况下，它会返回一个 **pair 对象**：

        * pair <迭代器, 布尔值>

        | 布尔值 |       迭代器       |
        | :----: | :----------------: |
        |  true  |     指向新元素     |
        | false  | 指向阻止插入的元素 |

    * 可以用一个迭代器作为 insert() 的第一个参数，它指定了元素被插入的位置，如果忽略插入位置，在这种情况下，只会返回一个迭代器。

        ```cpp
        // Returns a pair - an iterator & a bool value
        auto pr = words.insert("ninety");
        // 1st arg is a hint. Returns an iterator
        auto iter = words.insert (pr.first, "nine"); 
        ```

2. unordered_set<Key, Hash, KeyEqual, Allocator>::**find**

    * 调用 unordered_set 的 find() 会返回一个迭代器。这个迭代器指向和参数哈希值匹配的元素，如果没有匹配的元素，会返回这个容器的**结束迭代器(set.end())**。

        ```cpp
        #include <iostream>
        #include <unordered_set>
         
        int main(){  
            std::unordered_set<int> example = {1, 2, 3, 4};
         
            auto search = example.find(2);
            if (search != example.end()) {
                std::cout << "Found " << (*search) << '\n';
            } else {
                std::cout << "Not found\n";
            }
        }/*output:
        2
        */
        ```

3. **size(), empty()**

4. unordered_set<Key, Hash, KeyEqual, Allocator>::**erase**

    * 调用unordered_set容器的成员函数clear()可以删除它的全部元素。

    * 成员函数erase()可以删除容器中和传入参数的哈希值相同的元素。

    * 另一个版本的erase()函数可以删除迭代器参数指向的元素。这个版本的 erase() 会返回一个 size_t 类型的数作为被删除元素的个数。对于unordered_set来说，这个值只能是 0 或 1，但对于 unordered_multiset 容器来说，这个值可能会大于 1。显然，如果返回值是 0，那么容器中肯定没有这个元素。

        ```cpp
        std::pair<string, string> person { "John", "Smith"};
        auto iter = names.find(person);
        if(iter != std::end(names))
            names.erase(iter);
        ```

5. 迭代

    * 与正常容器迭代相同

        ```cpp
        unordered_set<balloon,balloon_hash>::iterator iter = balloons.begin();
        while(iter != balloons.end()){
            iter++;
        }
        ```



### 改变unordered_set中的值

* 在unordered_set<>每个对象的值是它的关键。因此，对象不能改变。

    ```cpp
    struct balloon{
        string color;           //颜色
        int count;     			//数量，初始为0
        balloon(string n):color(n),count(0){}
        void addCount(){
            count++;
        }
    };
    auto x = balloons.insert(balloon(temp));
    x.first->count += 1;	//wrong！不可修改
    ```

    解决方法：

    * 使用 **mutable** 修饰需要改变的变量，使之可变。

        * 引入 **mutable** 之后，C++ 可以有逻辑层面的 **const**。

            也就是对一个常量实例来说，从外部观察，它是常量而不可修改，但是内部可以有非常量的状态。

    ```cpp
    struct balloon{
        string color;           //颜色
        mutable int count;      //数量，初始为0，mutable表示可修改！！
        balloon(string n):color(n),count(0){}
        void addCount(){
            count++;
        }
    };
    auto x = balloons.insert(balloon(temp));
    x.first->count += 1;		//ok
    ```



### 在unordered_set中使用struct的完整例子

#### [HDUOJ 1004](http://acm.hdu.edu.cn/showproblem.php?pid=1004)  选出频率最大的字符串

```cpp
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

struct balloon_hash{     //指定hash函数，作为模板的第二个参数
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
```



### 参考资料

* [C++ 中的 mutable 关键字](https://liam.page/2017/05/25/the-mutable-keyword-in-Cxx/)

* [C++ unordered_set 使用struct或者class](http://www.voidcn.com/article/p-uqhjtghh-bd.html)

* [C++ unordered_set](http://c.biancheng.net/view/546.html)