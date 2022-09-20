#include<iostream>
using namespace std;

int main() {
	int value = 0, sum = 0;
	cout << "输入数据：";
	while (cin >> value) {
		sum += value;
	}
	cout << "The sum is :" << sum<<endl;
	system("pause");
	return 0;
}
