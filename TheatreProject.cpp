#include <iostream>
#include <string>

using namespace std;

class Actor{
    string name;
    int age;
public:
    friend istream& operator>>(istream&, Actor&);
    friend ostream& operator<<(ostream&, Actor&);
};

istream& operator>>(istream& in, Actor& act) {
    cout << "Insert the name of the actor: ";
    in >> act.name;
    cout << "Insert the age of the actor: ";
    in >> act.age;
    return in;
}

ostream& operator<<(ostream& out, Actor& act) {
    out << "Actor's name is " << act.name << endl;
    out << "Actor's age is " << act.age << endl;
    return out;
}

int main()
{
    Actor test;
    cin >> test;
    cout << endl;
    cout << test;
    return 0;
}