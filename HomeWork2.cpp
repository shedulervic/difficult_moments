#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;


//Задание 1: Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения, 
//на которые указывают эти указатели (нужно обменивать именно сами указатели, переменные должны оставаться в тех же адресах памяти).
void swapPtr(int*& a, int*& b) {
    int* c = a;
    a = b;
    b = c;
}

//Реализуйте шаблонную функцию SortPointers, которая принимает вектор указателей и сортирует указатели по значениям, на которые они указывают.

void show_vector(vector<int>& a)
{
    for (vector<int>::iterator it = a.begin(); it != a.end(); ++it)
        cout << *it << ", ";
}

void SortPointers(vector<int>& a)
{
    sort(a.begin(), a.end());
}

//Задание третье: Подсчитайте количество гласных букв в книге “Война и мир”. 
//
//     Если чесно на написание функции по обозначенным в дз методам меня на ночь глядя уже не хватило, но постарался спилить как можно более эффективно.
//
int countWP(string file)
{
    char lowel[] = "АаЕеЁёИиОоУуЫыЭэЮюЯя";
    ifstream in(file, ios::in | ios::binary);
    char tl;
    int lcount = 0;
    while (in.get(tl))
    {
        if (strchr(lowel, tl))
        {
            lcount++;
        }
    }
    return lcount;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    //Задание 1
    int a = 10;
    int b = 6;
    int* ptra = &a;
    int* ptrb = &b;
    cout << "before swap ptr " << "a= " << *ptra << " b= " << *ptrb << endl;
    swapPtr(ptra, ptrb);
    cout << "after swap ptr " << "a= " << *ptra << " b= " << *ptrb << endl;
    //Задание 2
    int mas[]{ 18,12,3,7,66,8, 20, 1 };
    vector<int> vec;
    for (int i = 0; i < 7; i++)
    {
        vec.push_back(mas[i]);
    }
    vector<int*> vecPtr;
    for (int i = 0; i < 7; i++)
    {
        vecPtr.push_back(&vec[i]);
    }
    cout << "not sorted: ";
    show_vector(vec);
    SortPointers(vec);
    cout << "sorted: ";
    show_vector(vec);
    //Задание 3
    string file = "Толстой Лев. Война и мир. Книга 1.txt";
    cout << "гласных в книге: " << countWP(file);
}
