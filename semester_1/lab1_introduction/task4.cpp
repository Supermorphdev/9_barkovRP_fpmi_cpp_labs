#include <iostream>
using namespace std;

int main() {
	long long even = 1 ,odd = 1;
	int k;
	cout << "enter k: ";
	cin >> k;
	for (int i = 1; i <= k; i++) {
		if (i % 2 == 0) {
			even *= i;
		}
		else {
			odd *= i;	
		}
	}
	if (k % 2 == 0) {
		cout << "chet: " << even;
	}
	else {
		cout << "nechet: " << odd;
	}
	return(0);
}
