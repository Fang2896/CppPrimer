#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<sstream>
#include<stdexcept>

using namespace std;

// 生成转换文本
const string &
transform(const string &s, const map<string, string> &m) {
    // 实际的转换工作
    auto map_it = m.find(s);
    // 如果单词在转换规则中
    if(map_it != m.cend())
        return map_it->second;  // 使用替换短语
    else
        return s;
}

// 读入给定文件，建立起转换映射
map<string, string> buildMap(ifstream &map_file) {
    map<string, string> trans_map;          // 保存转换规则
    string key;
    string value;
    while(map_file >> key  && getline(map_file, value))
        if(value.size() > 1)
            trans_map[key] = value.substr(1);   // 跳过前导空格
        else
            throw runtime_error("no rule for " + key);
    return trans_map;
}

void word_transform(ifstream &map_file, ifstream &input) {
    auto trans_map = buildMap(map_file);    // 保存转换规则
    string text;                            
    while(getline(input, text)) {           // 读取一行输入
        istringstream stream(text);         // 读取每个单词
        string word;
        bool firstword = true;              // 控制是否打印空格
        while (stream >> word) {
            if (firstword)
                firstword = false;
            else
                cout << " ";
            cout << transform(word, trans_map);
        }
        cout << endl;
    }

}


int main() {
    return 0;
}

