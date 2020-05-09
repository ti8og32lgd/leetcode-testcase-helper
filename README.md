# leetcode-testcase-helper

help you input and manage testcase when you solving problem locally.

本地做题的时候简便的输入和管理多个测试用例

### feature

- 从文件读取测试用例
- 支持多种数据类型
- 自动生成可用的函数参数
- 可输入多个测试用例

### File

- case.cpp       生成测试用例的文件
- printer.cpp    打印常用的数据结构



### Support

- basic data type
- ListNode*
- TreeNode*
- vector<>
- vector<vector<>>

### Example
目录结构 project directory
--- dir/
   -- case.cpp
   -- printer.cpp
--- a_problem.cpp

--- data

​    -- a_problem

```cpp
//a_problem.cpp
#include"dir/case.cpp"
#include"dir/printer.cpp"
//other include file
class Solution{
    public:
    //same with the template of leetcode problems
    ListNode* func(int p1,vector<string> p2,vector<vector<int>>p3){
      //...  
    };
}

int main(){
    Case c = Case("","data/a_problem");//a_problem:your testcase file name
    
    int e1;//fisrt parameter's type :int
    vector<string> e2;//second parameter's type
    vector<vector<int>> e3;    //2-d array
    ListNode*  _answer;//return type
    
    vector<decltype(e1)> p1; vector<decltype(e2)> p2;  vector<decltype(e3)> p3;  			vector<decltype(_answer)> answers;
    	
    c.data(p1, p2, p3,answers);   
    size_t L = 0, R = p1.size();

    Printer pr;
    for (size_t i = L; i != R;i++){
        Solution s;
        auto rs =s.func(p1[i],p2[i],p3[i]);
        if(rs==answers[i]){     
            cout << "PASS" << endl;
        }else{       
            cout << "NOT PASS" << endl;
            pr.print(answers[i]);//print vector<TreeNode*>
            pr.print(rs);//print vector<TreeNode*>
            cout<<endl;
        }
    }
    return 0;
}


```



//file: a_problem   warning: not support annotation

```
1   
["somestr","somestr2","somestr3"]
[[1,2,3],[4,5,6],[7,8,9]]

5252
["somestr4","somestr20","somestr53"]
[[11,32,3,55],[4,5,6],[7,8,9]]

4141
["somestr4","somestr20","somestr53"]
[[11,32,3,55],[4,5,6],[7,8,9]]
//...


```

