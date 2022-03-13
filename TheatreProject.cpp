#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

class Actor{
    string name;
    int age;
public:
    friend istream& operator>>(istream&, Actor&);
    friend ostream& operator<<(ostream&, const Actor&);
    Actor& operator=(Actor&);
    Actor() { this->name = "-"; this->age = 0; }
    //~Actor() {
    //    cout << this->name << " is no longer working in the theatre.";
    //}
};

class Spectacle {
    char* spectacle_name;
    int number_of_actors;
    vector<Actor> actors;
    double rating;

public:
    friend istream& operator>>(istream&, Spectacle&);
    friend ostream& operator<<(ostream&, const Spectacle&);
    Spectacle& operator=(Spectacle&);
    //~Spectacle();
};

class Theatre {
    char* address;
    vector<Spectacle> spectacles;
public:
    void set_address(const char* s);
    char* get_address();
};

int main()
{
    Spectacle sp1, sp2;

    cin >> sp1;
    sp2 = sp1;

    cout << endl << sp1 << endl << endl << sp2;

    return 0;
}

//Theatre
void Theatre::set_address(const char* input) {
    this->address = new char[strlen(input) + 1];
    strcpy(this->address, input);
}

char* Theatre::get_address() {
    return address;
}

// Spectacle
Spectacle& Spectacle::operator= (Spectacle& spec) {
    if (this != &spec) {
        cout << "Copying spectacle details..." << endl;
        this->spectacle_name = spec.spectacle_name;
        this->number_of_actors = spec.number_of_actors;
        this->rating = spec.rating;

        for (int i = 0; i < spec.number_of_actors; i++)
            this->actors.push_back(spec.actors[i]);
    }
    return *this;
}

istream& operator>>(istream& in, Spectacle& spec) {
    char s[255];
    cout << "Enter the name of the play: ";
    in.ignore();
    in.get(s, 255);
    spec.spectacle_name = new char[strlen(s) + 1];
    strcpy(spec.spectacle_name, s);
    in.get();
    cout << "Enter the rating of the play: ";
    in >> spec.rating;

    cout << "Enter how many actors there will be: ";
    in >> spec.number_of_actors;

    for (int i = 0; i < spec.number_of_actors; i++) {
        Actor temp;
        in >> temp;
        spec.actors.push_back(temp);
    }

    return in;
}

ostream& operator<<(ostream& out, const Spectacle& spec) {
    out << "The name of the spectacle: " << spec.spectacle_name << endl;
    out << "Rating of the spectacle: " << spec.rating << endl;
    out << "Number of actors " << spec.number_of_actors << endl;
    for (int i = 0; i < spec.number_of_actors; i++) {
        out << spec.actors[i] << endl;
    }
    return out;
}

//Spectacle::~Spectacle() {
//    cout << this->spectacle_name << " is no longer in our theatres.";
//}


// Actor
istream& operator>>(istream& in, Actor& act) {
    cout << "Insert the name of the actor: ";
    in >> act.name;
    cout << "Insert the age of the actor: ";
    in >> act.age;
    return in;
}

ostream& operator<<(ostream& out, const Actor& act) {
    out << "Actor's name is " << act.name << endl;
    out << act.name << "'s age is " << act.age << endl;
    return out;
}

Actor& Actor::operator=(Actor& act) {
    if (this != &act) {
        cout << "Copying actor details..." << endl;

        this->age = act.age;
        this->name = act.name;

    }
    return *this;
}