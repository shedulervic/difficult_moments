#include <iostream>
#include <vector>
#include <optional>
#include <fstream>
#include <algorithm>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

//Создайте структуру Person с 3 полями: фамилия, имя, отчество. Поле отчество должно быть опционального типа,
//т.к. не у всех людей есть отчество. Перегрузите оператор вывода данных для этой структуры. Также перегрузите операторы < и == (используйте tie).
struct Person {

    std::string name, surname;
    std::optional<std::string> patronymic;
    Person() : name(), surname(), patronymic() {}
    Person(std::string n, std::string s, std::optional<std::string> p) {
        name = n;
        surname = s;
        patronymic = p;
    }
    ~Person() {}

    void Print()
    {
        std::cout << name << " " << patronymic.value_or("") << " " << surname << std::endl;
    }
    friend ostream& operator<< (ostream &out, const Person &person)
    {
        out << setw(15) << person.surname << setw(15) << person.name << setw(20);
        if (person.patronymic.has_value())
            out << person.patronymic.value();
        else
            out << " ";
        return out;
    }
    friend bool operator<(const Person& p1, const Person& p2) { return tie(p1.name, p1.surname, p1.patronymic) < tie(p2.name, p2.surname, p2.patronymic); };
    friend bool operator==(const Person& p1, const Person& p2) { return tie(p1.name, p1.surname, p1.patronymic) == tie(p2.name, p2.surname, p2.patronymic); };
};

//Создайте структуру PhoneNumber с 4 полями
struct PhoneNumber
{
    int countryCode;
    int sityCode;
    std::string number;
    std::optional<int> additionalNumber;
    //PhoneNumber();
    PhoneNumber() : countryCode(), sityCode(), number(), additionalNumber() {}
    PhoneNumber(int cc, int sc, std::string n, std::optional<int> an) {
        countryCode = cc;
        sityCode = sc;
        number = n;
        additionalNumber = an;
    }
    friend std::ostream& operator<< (ostream& out, const PhoneNumber& pnumber);
    friend bool operator<(const PhoneNumber& pn1, const PhoneNumber& pn2) {
        return tie(pn1.additionalNumber, pn1.countryCode, pn1.number, pn1.sityCode) <
            tie(pn2.additionalNumber, pn2.countryCode, pn2.number, pn2.sityCode);
    }
    friend bool operator==(const PhoneNumber& pn1, const PhoneNumber& pn2) {
        return tie(pn1.additionalNumber, pn1.countryCode, pn1.number, pn1.sityCode) ==
            tie(pn2.additionalNumber, pn2.countryCode, pn2.number, pn2.sityCode);
    }
};



//Создайте класс PhoneBook
class PhoneBook
{
private:
    std::vector<std::pair<Person, PhoneNumber>> Note;
public:
    PhoneBook()
    {
        Person person1{ "Ivanov", "Ivan", "Ivanovich" };
        //PhoneNumber phoneNumber1{ 1, 1, "1111111" };
        PhoneNumber phoneNumber(1, 1, "1", 1);
        Note.push_back(make_pair(person1, phoneNumber));
    }
    ~PhoneBook() {
        Note.clear();
    }
    PhoneBook(ifstream &file){
        cout << "грузим список контактов";
        if (file.is_open())
        {
            while (!file.eof())
            {
                Person person;
                PhoneNumber phoneNumber;
                string patronymic;
                string additionalNumber;
                file >> person.surname >> person.name >> patronymic >> phoneNumber.countryCode
                    >> phoneNumber.sityCode >> phoneNumber.number >> additionalNumber;
                if (patronymic == "-")  person.patronymic = patronymic;
                else person.patronymic = patronymic;
                if (additionalNumber == "-") phoneNumber.additionalNumber = nullopt;
                else phoneNumber.additionalNumber = stoi(additionalNumber);
                Note.push_back(make_pair(person, phoneNumber));
            }
            file.close();
        }
    }
    
    friend ostream& operator<< (ostream &out, const PhoneBook &phooneBook)
    {
        for (const auto& [person, phoneNumber] : phooneBook.Note)
        {
            out << person << "\t" << phoneNumber << endl;
        }
        return out;
    }
    void SortByName() {
        sort(Note.begin(), Note.end(), [](pair<Person, PhoneNumber> note1, pair<Person, PhoneNumber> note2)
            {return note1.first < note2.first;});
    }
};

//ostream& operator<< ( ostream& out, const PhoneBook& phooneBook)
//{
//    for (const auto& [person, phoneNumber] : phooneBook.Note)
//    {
//        out << person << "\t" << phoneNumber << endl;
//    }
//    return out;
//}

//ostream& operator<< (ostream& out, const PhoneBook &phone_book)
//{
//    for (const auto& [person, number] : phone_book.Note)
//    {
//        out << person << "\t" << number << endl;
//    }
//    return out;
//}

int main()
{
    setlocale(LC_ALL, "Russian");
    //Задание 1
    Person person("Jhon", "Larry", "");
    person.Print();
    Person person2("Anny", "Vader", "Skywalker");
    Person person3("Jhon", "Larry", "");
    person2.Print();
    std::cout << std::boolalpha << (person < person2) << std::endl;
    std::cout << std::boolalpha << (person2 < person) << std::endl;
    std::cout << std::boolalpha << (person3 == person) << std::endl;
    //Задание2
    PhoneNumber phone;
    phone.countryCode = 8;
    phone.sityCode = 812;
    phone.number = "4448332";
    std::cout << phone;
    //Задание 3
    std::ifstream file("PhoneBook.txt");
    PhoneBook book(file);
    cout << book;
}

