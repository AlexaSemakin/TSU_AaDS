#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
// using namespace std;

int random(int a, int b)
{
    int r = rand();
    if (a > 0)
        return a + r % (b - a);
    else
        return a + r % (abs(a) + b);
}

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
    std::ofstream fout(fileName);
    if (!fout.is_open()) 
        throw "file not opened";
    for (int i = 0; i < numbersCount; i++) {
        fout << random(0, maxNumberValue) << " ";
    }
    return true;
}

bool isFileContainsSortedArray(const std::string& fileName) {
    std::ifstream fin(fileName);
    if (!fin.is_open()) 
        throw "file not opened";
    int num, last_num;
    fin >> last_num;
    while (fin >> num) {
        if (last_num > num) {
            return false;
        }
    }
    return true;
}

int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue) {

    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
        return -1;
    }

    //sortFile(fileName); //Вызов вашей функции сортировки

    if (!isFileContainsSortedArray(fileName)) {
        return -2;
    }

    return 1;
}

int main()
{
    std::string fileName = "file.txt";
    const int numbersCount = 1000000;
    const int maxNumberValue = 100000;

    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        switch (createAndSortFile(fileName, numbersCount, maxNumberValue)) {
        case 1:
            std::cout << "Test passed." << std::endl;
            break;

        case -1:
            std::cout << "Test failed: can't create file." << std::endl;
            break;

        case -2:
            std::cout << "Test failed: file isn't sorted." << std::endl;
            break;
        }

        return 0;
    }
}