#include <iostream>
using namespace std;

int main(){
	int n;
	cout << "enter n: ";
	cin >> n;
	if (n % 2 == 0) {
		cout << "SUMM" << (n-1) * (n-1);
	}
	else {
		cout << "SUMM" << n * n;
	}
	return(0);
}
