

#include "observer.hpp"
#include "observable.hpp"


struct Person : public Observable
{
    int _age;

    int age() const { return _age;}

    void age(int a)
    {
        _age = a;
        Observable::notify(std::string{"Age modified to " + std::to_string(a)});
    }
};

struct AgeMonitor : public Observer
{
};


int main()
{
    Person p;

    AgeMonitor monitor;
    p.subsribe(monitor);

    p.age(13);
    p.age(12);
    p.unsubscribe(monitor);
    p.age(18);

    return 0;
}
