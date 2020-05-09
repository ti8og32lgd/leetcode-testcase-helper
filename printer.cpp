#pragma once
#include <iostream>
#include <map>
#include <math.h>
#include <memory>
#include <stdio.h>
#include <vector>
#include<fstream>
#include<sstream>
#include<stack>
#include"case.cpp"
#include <iomanip> 
using namespace std;
class Printer{
    public:
    template<typename T>
    static void print(vector<T> v,ostream& os=cout,const string end="\n");

    template<typename T>
    static void print(T t1,ostream& os=cout,const string end="\n");
    

    template<typename T>
    static void print(vector<vector<T>> v2,ostream&os=cout,const string end="\n");
    static void print(int i,ostream& os=cout,const string end="\n");
    static void print(string s,ostream& os=cout,const string end="\n");
    static void print(char c,ostream& os=cout,const string end="\n");
    static void print(ListNode* head,ostream& os=cout,const string end="\n");
    static void print(TreeNode* root,ostream& os=cout,const string end="\n");

};

template<typename T>
void Printer::print(T t1,ostream& os,const string end){
    os << t1 << end;
}
void Printer::print(int i,ostream& os,const string end){
    os << i << end;
}

void Printer::print(string s,ostream& os,const string end){
    os<<'"'<<s<<'"'<< end;
}
void Printer::print(char c ,ostream& os,const string end){
    os<<'\''<<c<<'\''<< end;
}
void Printer::print(ListNode* head,ostream& os,const string end){
    while(head){
        os << head->val;
        head = head->next;
        if(head){
            os << " --> ";
        }
    }
    os << end;
}
int getDepth(TreeNode*root){
    if(root==nullptr){
        return 0;
    }
    int left = getDepth(root->left);
    int right = getDepth(root->right);
    return max(left, right) + 1;

}
void Printer::print(TreeNode* root,ostream& os,const string end){
    // cout << "pint tree begin";
    if(not root){
        os << "Nothing in tree." << endl;
        return;
    }
    
    int depth = getDepth(root);
    
    int bottomWidth = 4;
    int width = pow(2, depth - 1) * bottomWidth;
    vector<TreeNode *> s1, s2;
    int nowDep = 0;
    s1.push_back(root);
     
    while((s1.size() or s2.size()) and nowDep<depth){
       
        if(s2.size()){
            auto temp = s1;
            s1 = s2;
            s2 = temp;
        }
        //指定width
        auto perWidth = width / pow(2, nowDep);
       
        for(auto elem:s1){
            if(elem!=nullptr){
                auto elemwidth=perWidth - (to_string(elem->val)).size();
                

                string space(elemwidth/2, ' ');
                os << space << elem->val << space;
                s2.push_back(elem->left);
                s2.push_back(elem->right);
            }else{
                auto elemwidth=perWidth - 2;
 
                string space(elemwidth/2, ' ');
                os << space << "__" << space ;
                s2.push_back(nullptr);
                s2.push_back(nullptr);
            }
        }
        nowDep += 1;
        s1.clear();
        os << endl;
    }

    os << end;
}
/**
 * @brief print vector<T>
 * 
 * @tparam T 
 * @param v 
 */
template<typename T>
void Printer::print(vector<T> v,ostream&os,const string end){
    ostringstream ss;
    ss << "[";
    for (size_t i=0;i!=v.size();i++){
        print(v[i],ss,"");
        if(i!=v.size()-1){
            ss << ", ";
        }
        // cout << " ";
    }
    ss <<"]"<< end;
    os << ss.str();
}

template<typename T>
void Printer::print(vector<vector<T>> v2,ostream&os,const string end){
    ostringstream ss;
    ss<< "[" <<endl;
    for(auto v1:v2){
        ss << "   ";
        print(v1,ss);
    }
    ss << "]" << endl;
    os << ss.str() << endl;

}
