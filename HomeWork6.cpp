#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <vector>
#include <chrono>

//Задание 1. Создайте потокобезопасную оболочку для объекта cout
class MyCout: public std::ostringstream
{
public:
	MyCout() = default;
	~MyCout() {
		std::lock_guard<std::mutex> guard(mutexCout);
		std::cout << this->str();
	}

private:
	static std::mutex mutexCout;
};
std::mutex MyCout::mutexCout{};

//Задание 2. еализовать функцию, возвращающую i-ое простое число template<int n>
bool isPrime(int n)
{
    if (n > 1)
    {
        for (int i = 2; i < n; i++)
            if (n % i == 0) 
                return false;
        return true;
    }
    else
        return false;
}

void PrimeNum(int a)
{
	int primeCount = 0;
	int i;
		for (i = 1; primeCount <= a; i++)
		{
			if (isPrime(i))
			{
				++primeCount;
				std::cout << "prime count: " << primeCount << " prime number : " << i << std::endl;
			}
		}
}
//Задание 3 Промоделировать следующую ситуацию.
std::vector<int> home;
void Owner() {
	home.push_back(rand() % 1000 + 1);
	std::cout << home.size() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));

}
void Thief() {
	std::sort(home.begin(), home.end());
	std::cout << "thief stole: " << (home.size() - 1);
	home.pop_back();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main()
{
    // Задание 1
	MyCout{} << "HelloWorld" << std::endl;
	/*В C++20 Предлагают так :
	std::osyncstream(std::cout) << "Hello!";*/

	// Задание 2
	std::thread primeThred(PrimeNum, 1000); //миллион долго считать!
	primeThred.join();

	//Задание 3
	

}


