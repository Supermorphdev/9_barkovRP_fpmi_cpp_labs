#include <iostream>
using namespace std;

int main(){
	int n;
	std::cout << "enter n: ";
	std::cin >> n;
	if (n % 2 == 0) {
		std::cout << "SUMM" << (n-1) * (n-1);
	}
	else {
		std::cout << "SUMM" << n * n;
	}
	return(0);
}
