
#include "observer.hpp"
#include "observable.hpp"

#include <iostream>

struct Person : public Observable<Person>
{
    int _age;

    Person(int age): _age(age) {}

    int age() const { return _age;}

    void age(int a)
    {
        if(this->_age == a) return;

        this->_age = a;
        notify(*this, "age");
    }
};

struct ConsolePersonObserver : public Observer<Person>
{
    void field_changed(Person & source, std::string const & field) override
    {
        std::cout << &source << ": " <<  field << " has changed to " << source.age() << "\n";
    }
};

int main()
{
    Person p{20};

    ConsolePersonObserver cpo;

    p.subsribe(cpo);

    p.age(13);
    p.age(25);
    p.unsubscribe(cpo);
    p.age(20);

    return 0;
}
