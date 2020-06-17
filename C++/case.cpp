#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <map>
#include <math.h>
#include <memory>
#include <sstream>
#include <stdio.h>
#include <vector>
#include<queue>
using namespace std;
/**
 * @brief spilt same as in python
 * 
 * @param s 
 * @param v 
 * @param c 
 */
void spilt(const std::string &s, std::vector<std::string> &v, const std::string &c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}

/**
 * @brief remove all c in s
 * 
 * @param s 
 */
void trim(string &s, char c)
{
    size_t index = 0;
    if (!s.empty())
    {
        while ((index = s.find(c, index)) != string::npos)
        {
            s.erase(index, 1);
        }
    }
}

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    //bool operator==(const ListNode &l2);
};

/**
 * @brief BinaryTree
 * 
 */
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool ListNodeEqual(ListNode *p1,ListNode * p2){
    while(p1!=nullptr and p2!=nullptr){
        if(p1->val!=p2->val){
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    if(p1!=nullptr or p2!=nullptr){
        return false;
    }else{
        return true;
    }
}

class Case
{
private:
    ifstream f;

public:
    string prefix;
    string filename;
    vector<string> orders;

    Case(string prefix, string filename)
    {
        this->prefix = prefix;
        this->filename = prefix + filename;
        f = ifstream(filename);
        if (not f)
        {
            cout << "Error happends when read file: " << prefix << filename << endl;
        }
    }

    template <typename T1 = int &, typename T2 = int &, typename T3 = int &, typename T4 = int &, typename T5 = int &, typename T6 = int &>
    void data(T1 &t1 = ki, T2 &t2 = ki, T3 &t3 = ki, T4 &t4 = ki, T5 &t5 = ki, T6 &t6 = ki);

private:
    /**
         * @brief 不同重载的insertData函数，参数为int时不读取
         * 
         * @param i 
         * @return true 
         * @return false 
         */
    bool insertData(int &i);

    template <typename T>
    bool insertData(vector<T> &elem);

    template <typename T>
    bool insertData(vector<vector<T>> &arrayV);

    template <typename T>
    bool insertData(vector<vector<vector<T>>> &twoD_array_v);

    static int ki;
    static string ks;

private:
    /**
         * @brief some basic function
         * 
         */
    string readline();
    // int getElem(string s, int &elem = ki);
    // string getElem(string s, string &elem = ks);
    // ListNode *getElem(string s, ListNode *&elem);
    // bool getElem(string s, bool &elem);
    // // char getElem(string s, char &elem);
    // TreeNode *getElem(string s, TreeNode *&elem);

    // vector<ListNode*> getArray(string s);
    template <typename T>
    T getElem(string s,T &elem);

    template <typename T>
    vector<T> getArray(string s);
    
    template <typename T>
    vector<vector<T>> get2dArray(string s);
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
void Case::data(T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 &t5, T6 &t6)
{
    string line;
    while (insertData(t1))
    {
        insertData(t2);
        insertData(t3);
        insertData(t4);
        insertData(t5);
        insertData(t6);
        readline();
    }
}

/**
 * @brief 参数是int,表明用户没有传这个重载的参数，所以什么也不做
 * 
 * @param i 
 * @return true 
 * @return false 
 */
bool Case::insertData(int &i)
{
    return false;
}

/**
 * @brief 从f里读取一行，转化为int，并pushback到iv中
 * 
 */

template <typename T>
bool Case::insertData(vector<T> &v)
{
    string line = readline();
    if (line.empty())
    {
        return false;
    }
    T elem;
    getElem(line, elem);
    v.push_back(elem);
    return true;
}

template <typename T>
bool Case::insertData(vector<vector<T>> &arrayV)
{

    string line = readline();
    if (line.empty())
    {
        return false;
    }
    vector<T> element = getArray<T>(line);
    arrayV.push_back(element);
    return true;
}

/**
 * @brief insert 2-d vector array
 * 
 * @param twoD_array_v 
 * @return true 
 * @return false 
 */
template <typename T>
bool Case::insertData(vector<vector<vector<T>>> &twoD_array_v)
{
    auto line = readline();
    if (line.empty())
    {
        return false;
    }
    auto element = get2dArray<T>(line);
    twoD_array_v.push_back(element);

    return true;
}

string Case::readline()
{
    string line;
    if (!getline(f, line))
    {
        return "";
    }
    return line;
}

template <typename T>
T Case::getElem(string s1,T &elem){
    stringstream s(s1);
    T i;
    s >> i;
    elem = i;
    return i;
}

/**
int Case::getElem(string s1, int &elem)
{
    stringstream s(s1);
    int i;
    s >> i;
    elem = i;
    return i;
}
**/

template<>
string Case::getElem(string s1, string &elem)
{

    trim(s1, ' ');
    if (s1[0] == '"')
    {
        s1 = string(s1.begin() + 1, s1.end() - 1);
    }
    elem = s1;
    return s1;
}

template<>
char Case::getElem(string s1, char &elem){
    trim(s1, ' ');
    if (s1[0] == '\'' or s1[0]=='"')
    {
        s1 = string(s1.begin() + 1, s1.end() - 1);
    }
    if(s1.size()!=1){
        cout << "char Case::getElem(string s1, char &elem),wrong input:" << s1 << endl;
    }
    char i=s1[0];
    elem = i;
    return elem;
}

template<>
bool Case::getElem(string s1, bool &elem){
    stringstream s(s1);
    int i;
    s >> i;
    if(i==1){
        elem = true;
    }else if(i==0){
        elem = false;
    }else{
        elem = true;
        cerr << "bool Case::getElem(string s1, bool &elem),wrong input" <<s1<< endl;
    }
    return elem;
}

ListNode* arr2ListNode(vector<int>arr){
    ListNode *head = new ListNode(0);
    ListNode *p = head;
    for(auto i:arr){
        ListNode *tp = new ListNode(i);
        p->next = tp;
        p = tp;
    }
    
    ListNode *realhead = head->next;
    delete head;
    return realhead;
}

template<>
ListNode * Case::getElem(string s, ListNode *&elem)
{
    vector<int> arr = getArray<int>(s);
    auto head = arr2ListNode(arr);
    elem = head;
    return head;
}

template<>
TreeNode * Case::getElem(string s, TreeNode *&elem)
{
    vector<string> arr = getArray<string>(s);
    queue<TreeNode*> q1;
    TreeNode *root=nullptr;
    size_t index = 0;
    while(index<arr.size() and index<arr.size()){
        TreeNode *t;
        auto e1 = arr[index];
        if(e1=="null"){
            t = nullptr;
        }else{
            t =new TreeNode(atoi(e1.c_str()));
            t->left = t->right = nullptr;
        }
        if(q1.empty()){
            root = t;
            if(root)
                q1.push(root);
        }else{
            auto parent=q1.front();
            parent->left = t;
            
            if(t){
                q1.push(t);
            }
            index++;
            if(index<arr.size()){
                e1 = arr[index];
                if(e1=="null"){
                    t = nullptr;
                }else{
                    t =new TreeNode(atoi(e1.c_str()));
                    t->left = t->right = nullptr;
                }
                parent->right = t;
                if(t){
                    q1.push(t);
                }
            }
            
            q1.pop();
        }
        index++;
    }
  
    elem = root;
    return root;
}




template <typename T>
vector<T> Case::getArray(string s1)
{
    vector<string> store1;
    trim(s1, ' ');
    trim(s1, '[');
    trim(s1, ']');

    spilt(s1, store1, ","); //将文本以逗号分隔开保存到store1里
    vector<T> rs = vector<T>();
    for (auto s : store1)
    {
        T elem;
        getElem(s, elem);
        rs.push_back(elem);
    }
    return rs;
}

template <>
vector<ListNode*> Case::getArray(string s1)
{ 
    vector<vector<int>> vvi=get2dArray<int>(s1);
    vector<ListNode *> rs;
    for(auto vi :vvi){
        rs.push_back(arr2ListNode(vi));
    }
    return rs;
}


template <typename T>
vector<vector<T>> Case::get2dArray(string s1)
{
    vector<vector<T>> rs;
    trim(s1, ' ');
    s1 = string(s1.begin() + 1, s1.end() - 1); //remove the  outer '[' and  ']'
    //cout << s1 << endl;

    vector<string> array_strings;
    //begin: store every string of vector<T>
    auto iter1 = s1.begin();
    auto iter2 = s1.begin();
    bool lock = true;
    while (iter2 != s1.end())
    {
        if (*iter2 == '[' and lock)
        {
            lock = false;
        }
        if (*iter2 == ']' and not lock)
        {
            lock = true;
            //add the string of vector<T>
            array_strings.push_back(string(iter1, iter2 + 1));
            while (iter2 != s1.end() and *iter2 != ',')
            {
                iter2++;
            }
            if (iter2 != s1.end())
            {
                iter1 = iter2 + 1;
                iter2 = iter2 + 1;
            }
            else
            {
                break;
            }
        }
        else
        {
            iter2 += 1;
        }
    }
    //end: store every string of vector<T>

    //transfer string to vector elements
    for (auto elem : array_strings)
    {
        if (not elem.empty())
        {
            vector<T> elems = getArray<T>(elem);
            rs.push_back(elems);
        }
    }
    return rs;
}

class Validator{
    public:
        static bool validateListNode(ListNode *l1, ListNode *l2);
        static bool validateTreeNode(TreeNode *r1, TreeNode *r2);
};
bool Validator::validateListNode(ListNode *l1, ListNode *l2){
    vector<int> sequence1, sequence2;
    while(l1){
        sequence1.push_back(l1->val);
        l1 = l1->next;
    }
    while(l2){
        sequence2.push_back(l2->val);
        l2 = l2->next;
    }
    return l1 == l2;
}

bool Validator::validateTreeNode(TreeNode *r1, TreeNode *r2){
    string sequence1, sequence2;
    queue<pair<TreeNode *, int>> q1;
    
    q1.push({r1, 0});
    
    while(q1.size()){
        // TreeNode *p;
        // int level;
        auto [ p,  level] = q1.front();
        sequence1 += p->val;
        sequence1 += '-';
        sequence1 += level;
        sequence1 += '-';
        if(p->left){
            q1.push({p->left,level+1});
        }
        if(p->right){
            q1.push({p->right,level+1});
        }
        q1.pop();
    }
    queue<pair<TreeNode *, int>> q2;
    q2.push({r2, 0});
    while(q2.size()){
       
        auto [ p,  level] = q2.front();
        sequence2 += p->val;
        sequence2 += '-';
        sequence2 += level;
        sequence2 += '-';
        if(p->left){
            q2.push({p->left,level+1});
        }
        if(p->right){
            q2.push({p->right,level+1});
        }
        q1.pop();
    }
    return sequence1 == sequence2;
};