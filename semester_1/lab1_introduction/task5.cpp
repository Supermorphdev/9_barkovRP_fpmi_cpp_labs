#include <iostream>
using namespace std;

int main() {
	int n, m,bigger;
	cout << "enter n,m";
	cin >> n >> m;
	if (n > m) {
		bigger = n;
	}
	else {
		bigger = m;
	}
	cout << "common divs: ";
	for (int i = 1; i <= bigger; i++) {
		if (n % i == 0 && m % i == 0) {
			cout << i << ",";
		}
	}
	return(0);
}
