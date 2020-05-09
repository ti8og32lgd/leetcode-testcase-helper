# leetcode-testcase-helper

help you input and manage testcase when you solving problem locally.

本地做题的时候简便的输入和管理多个测试用例

### feature

- 从文件读取测试用例
- 自动生成可用的函数参数
- 可输入多个测试用例

### File

- case.cpp       生成测试用例的文件
- printer.cpp    打印常用的数据结构

### Example

···

template<typename T>

void Printer::print(vector<vector<T>> v2,ostream&os,const string end){

  ostringstream ss;

  ss<< "[" <<endl;

  for(auto v1:v2){

​    ss << "  ";

​    print(v1,ss);

  }

  ss << "]" << endl;

  os << ss.str() << endl;



}

···