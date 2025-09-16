#include <iostream>
using namespace std;

int main() {
	int n, g = 0;
	cout << "vvedite n:";
	cin >> n;
	for (int k = 1; k <= n; k++ ) {
		g = g + pow(k,n);
	}
	cout << g;
	return(0);
}
