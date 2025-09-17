#include <iostream>

int main() {
	int n, g = 0;
	std::cout << "vvedite n:";
	std::cin >> n;
	for (int k = 1; k <= n; k++ ) {
		g = g + pow(k,n);
	}
	std::cout << g;
	return(0);
}
