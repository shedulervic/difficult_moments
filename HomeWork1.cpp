#include <iostream>
#include <optional>
#include <fstream>

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
    PhoneNumber() : countryCode(), sityCode(), number(), additionalNumber() {}
    PhoneNumber(int cc, int sc, std::string n, std::optional<int> an) {
        countryCode = cc;
        sityCode = sc;
        number = n;
        additionalNumber = an;
    }
    friend std::ostream& operator << (std::ostream& out, const PhoneNumber& pnumber)
    {
        if (pnumber.additionalNumber.has_value())
        {
            return out << pnumber.countryCode << "(" << pnumber.sityCode << ")" << pnumber.number << pnumber.additionalNumber.has_value() << std::endl;
        }
        else
        {
            return out << pnumber.countryCode << "(" << pnumber.sityCode << ")" << pnumber.number << std::endl;
        }

    }
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
    friend std::ostream& operator <<(std::ostream& out, const PhoneBook& pb)
    {
       // return out << pb.person.surname << pb.person.name << pb.phoneNumber.countryCode << pb.phoneNumber.sityCode << pb.phoneNumber.number  << std::endl;
        return out << pb.person.surname << pb.person.name << pb.person.patronymic.value() << pb.phoneNumber.countryCode << pb.phoneNumber.sityCode << pb.phoneNumber.number << pb.phoneNumber.additionalNumber.value() << std::endl;
    }
public:
    PhoneBook(std::ifstream& in);
    //~PhoneBook();
    

private:
    Person person;
    PhoneNumber phoneNumber;
};

    PhoneBook::PhoneBook(std::ifstream& in)
    {
    if (in.is_open())
    {
        while (!in.eof())
        {
            std::string p = person.patronymic.value_or("");
            if (phoneNumber.additionalNumber.has_value())
            {
                in >> person.surname >> person.name >> p >> phoneNumber.countryCode >> phoneNumber.sityCode >> phoneNumber.number >> phoneNumber.additionalNumber.value();
            }
            else
            {
                in >> person.surname >> person.name >> p >> phoneNumber.countryCode >> phoneNumber.sityCode >> phoneNumber.number;
            }
        }
    }
    else
    {
        std::cout << "wrong file";
    }
    }

int main()
{
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
    std::cout << phone ;
    //Задание 3
    std::ifstream file("PhoneBook.txt");
    PhoneBook book(file);
    std::cout << book;
}

