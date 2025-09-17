#include <iostream>

int main() {
	int k;
	int summ = 0;
	std::cout << "enter k: ";
	std::cin >> k;
	for (int i = 1; i < k; i++) {
		if (k % i == 0) {
			summ += i;
		}
	}
	if (summ == k) {
		std::cout << "k perfect number";
	}
	else {
		std::cout << "k imperfect number";
	}
	return(0);
}
