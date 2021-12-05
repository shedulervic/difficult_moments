#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <locale>
#include <string.h>

using namespace std;

// Задание 1. Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов, и выводящую в консоль список уникальных слов
template<typename T>

// не уверен что так правильно, ведь пердаю я не итераторы.
void Iter(vector<T> &vec)
{
    set<T> mySet;
    copy(vec.begin(), vec.end(), inserter(mySet, mySet.end()));
    copy(mySet.begin(), mySet.end(), ostream_iterator<T>(cout, " "));
}

istream& col(istream& in) {
    if (in.peek() != '.' || in.peek() != '!' || in.peek() != '?' || isspace(in.ignore().peek())) {
        in.setstate(ios_base::failbit);
    }
    return in;
}

int main()
{
   /* setlocale(LC_ALL, "Russian");
    vector<int> v{ 5,2,4,2,1 };
    Iter(v);
    cout << endl;
    vector<string> s{ "one", "two", "four", "one" };
    Iter(s);
    cout << endl;*/

    //Задание 2. Используя ассоциативный контейнер, напишите программу, которая будет считывать данные введенные пользователем из стандартного потока ввода и
    // разбивать их на предложения. Далее программа должна вывести пользователю все предложения, отсортировав их по длине.
    set<string> myset;
    const int N = 100;
    const char *SEPARATORS = "!?.";
    string s;
    char S[N];
    cin >> S;
    char *ptr = 0;
    ptr = strtok(S, SEPARATORS);
    while (ptr)
    {
        strcpy(S, s.c_str());
        myset.insert(s);
    }
    for (auto i = myset.begin(); i != myset.end(); i++)
    {
        cout << ' || ' << *i;
    }
}

