#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    cout << "\x1B[2J\x1B[H";
}

void userMessage() {
    cout << "\t\t\t\t==================================================" << endl
         << "\t\t\t\t0 -> Quit application" << endl 
         << "\t\t\t\t1 -> Admin panel" << endl 
         << "\t\t\t\t2 -> Show theatre address" << endl 
         << "\t\t\t\t3 -> Show spectacles that are in the theatre now" << endl 
         << "\t\t\t\t==================================================" << endl << endl;
    cout << "\tEnter your choice: ";
}

void adminMessage() {
    cout << "\t\t\t\t==================================================" << endl
         << "\t\t\t\t0 -> Exit admin panel." << endl 
         << "\t\t\t\t1 -> Show theatre address" << endl 
         << "\t\t\t\t2 -> Add a spectacle" << endl 
         << "\t\t\t\t3 -> Modify spectacle data" << endl
         << "\t\t\t\t4 -> Show spectacles that are in the theatre now" << endl 
         << "\t\t\t\t5 -> Modify theatre address" << endl 
         << "\t\t\t\t==================================================" << endl << endl;
    cout << "\tEnter your choice: ";
}

class Actor{
    string name;
    int age;
public:
    friend istream& operator>>(istream&, Actor&);
    friend ostream& operator<<(ostream&, const Actor&);
    Actor& operator=(Actor&);
    string get_name() { return name; }
    void set_name(string name) {
        this->name = name;
    }
    void set_age(int age) {
        this->age = age;
    }
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
    friend bool operator>(Spectacle&, Spectacle&);
    friend bool operator<(Spectacle&, Spectacle&);
    friend bool operator<(double&, Spectacle&);
    friend bool operator>(double&, Spectacle&);
    friend bool operator==(Spectacle&, string&);
    Spectacle& operator=(Spectacle&);

    char* get_name();
    double get_rating();
    void set_name(const char* name) {
        delete spectacle_name;
        spectacle_name = new char[strlen(name) + 1];
        strcpy(spectacle_name, name);
    }
    void set_rating(float rating) {
        this->rating = rating;
    }
    void set_nrActors(int number_of_actors) {
        this->number_of_actors = number_of_actors;
    }
    void set_newActors() {
        actors.clear();
        for (int i = 0; i < number_of_actors; i++) {
            Actor temp;
            cin >> temp;
            actors.push_back(temp);
        }
    }
    string get_actor_name(int input) { return actors[input].get_name(); }
    void print_actors() {
        for (int i = 0; i < number_of_actors; i++)
            cout << i + 1 << ". " << actors[i].get_name() << endl;
    }
    void set_actor_name(int input, string name) {
        actors[input].set_name(name);
    }
    void set_actor_age(int input, int age) {
        actors[input].set_age(age);
    }
    //~Spectacle();
};

class Theatre {
    char* address;
    vector<Spectacle> spectacles;
public:
    void set_address(const char* s);
    void add_spectacle(Spectacle spc);
    void show_spectacles_short();
    void show_spectacle_actor_names(int index) { spectacles[index].print_actors(); }
    int get_number_of_spectacles();
    Spectacle get_spectacle_info(int index);
    char* get_address();
    void set_spectacle_name(const char* input, int index);
    void set_spectacle_rating(float input, int index);
    void set_spectacle_nrActors(int input, int index);
    void set_spectacle_newActors(int index);
    void set_spectacle_newName(int spec_i, int act_i, string name) {
        spectacles[spec_i].set_actor_name(act_i, name);
    }
    void set_spectacle_newAge(int spec_i, int act_i, int age) {
        spectacles[spec_i].set_actor_age(act_i, age);
    }
    char* get_spectacle_name(int index);
    double get_spectacle_rating(int index);
    void spectacle_sort();
    void spectacle_reverse_sort();
    string get_spectacle_actor_name(int spec_i, int act_i) { return spectacles[spec_i].get_actor_name(act_i); }
};

int main()
{
    Theatre theatre;
    Spectacle temp;
    int choice, choiceSpectacle, adminChoice, editSpectacle, actorChoice, editActor;
    string password, verify;
    char address[256];

    cout << "Set admin password: ";
    cin >> password;
    
    clear();
    
    cout << "Set theatre address: ";
    cin.ignore();
    cin.get(address, 256);
    cin.get();
    theatre.set_address(address);
    
    clear();
    
    cout << "Your current address is set to: " << theatre.get_address() << endl << endl;
    
    do {
        userMessage();
        cin >> choice;
        switch (choice)
        {
            case 0:
                cout << "Exit message!" << endl << endl;
                return 0;
            case 1: // admin
                clear();
                cout << "Enter your password: ";
                cin >> verify;
                if (verify == password) {
                    clear();
                    cout << "Logged in as admin!" << endl << endl;
                    do {
                        adminMessage();
                        cin >> adminChoice;
                        switch (adminChoice)
                        {
                            case 0:
                                clear();
                                cout << "You've logged out! Logged in as user!" << endl << endl;
                                break;
                            case 1:
                                clear();
                                cout << "The address is " << theatre.get_address() << endl << endl;
                                break;
                            case 2:
                                clear();
                                cin >> temp;
                                theatre.add_spectacle(temp);
                                break;
                            case 3: // modify spectacle
                                clear();
                                do {
                                    if (theatre.get_number_of_spectacles() != 0) {
                                        clear();
                                        theatre.show_spectacles_short();
                                        cout << "Press the number coresponding to the spectacle if you want to modify it." << endl;
                                        cout << "Or 0 if you want to return to the main menu." << endl;
                                        cin >> choiceSpectacle;
                                        switch (choiceSpectacle)
                                        {
                                            case 0:
                                                clear();
                                                break;
                                            default:
                                                clear();
                                                do {
                                                    clear();
                                                    cout << "You're currently editing " << theatre.get_spectacle_name(choiceSpectacle - 1) << endl << endl;
                                                    cout << "\t\t\t\t0 -> Go back to spectacle list" << endl;
                                                    cout << "\t\t\t\t1 -> Edit spectacle name" << endl;
                                                    cout << "\t\t\t\t2 -> Edit spectacle rating" << endl;
                                                    cout << "\t\t\t\t3 -> Edit number of actors (you will need to re-enter every single actor)" << endl;
                                                    cout << "\t\t\t\t4 -> Edit actor data" << endl;
                                                    cout << "Enter the option you want to edit: ";
                                                    cin >> editSpectacle;

                                                    switch (editSpectacle)
                                                    {
                                                        case 0:
                                                            clear();
                                                            break;
                                                        case 1:
                                                            clear();
                                                            cout << "You're currently editing " << theatre.get_spectacle_name(choiceSpectacle - 1) << endl << endl;
                                                            cout << "Enter new name for the spectacle: ";
                                                            cin.ignore();
                                                            char new_spectacle_name[255];
                                                            cin.get(new_spectacle_name, 255);
                                                            cin.get();
                                                            theatre.set_spectacle_name(new_spectacle_name, choiceSpectacle - 1);
                                                            break;
                                                        case 2:
                                                            clear();
                                                            cout << "You're currently editing " << theatre.get_spectacle_name(choiceSpectacle - 1) << endl << endl;
                                                            cout << "Enter new rating for the spectacle (current rating is " << theatre.get_spectacle_rating(choiceSpectacle-1) << "): ";
                                                            float newRating;
                                                            cin >> newRating;
                                                            theatre.set_spectacle_rating(newRating, choiceSpectacle - 1);
                                                            break;
                                                        case 3:
                                                            clear();
                                                            cout << "You're currently editing " << theatre.get_spectacle_name(choiceSpectacle - 1) << endl << endl;
                                                            cout << "Enter how many actors are participating in the play: ";
                                                            int actorNumber;
                                                            cin >> actorNumber;
                                                            theatre.set_spectacle_nrActors(actorNumber, choiceSpectacle - 1);
                                                            // enter actors
                                                            theatre.set_spectacle_newActors(choiceSpectacle - 1);
                                                            break;
                                                        
                                                        case 4:
                                                            clear();
                                                            cout << "You're currently editing " << theatre.get_spectacle_name(choiceSpectacle - 1) << endl << endl;
                                                            
                                                            do {
                                                                theatre.show_spectacle_actor_names(choiceSpectacle - 1);

                                                                cout << "Press the number corresponding to the actor you want to edit." << endl;
                                                                cout << "Or press 0 if you want to go back." << endl;
                                                                cin >> actorChoice;

                                                                switch (actorChoice)
                                                                {
                                                                    case 0:
                                                                        clear();
                                                                        break;
                                                                    default:
                                                                        clear();
                                                                        cout << "You are currently editing " << theatre.get_spectacle_actor_name(choiceSpectacle - 1, actorChoice - 1) << endl << endl;
                                                                        cout << "\t\t\t\t0 -> Go back" << endl;
                                                                        cout << "\t\t\t\t1 -> Edit name" << endl;
                                                                        cout << "\t\t\t\t2 -> Edit age" << endl;
                                                                        cout << "Enter the option you want to edit: ";
                                                                        cin >> editActor;
                                                                        string actorName;
                                                                        int actorAge;
                                                                        switch (editActor)
                                                                        {
                                                                            case 0:
                                                                                clear();
                                                                                break;
                                                                            case 1:
                                                                                clear();
                                                                                cout << "Enter new name for the actor: ";
                                                                                cin >> actorName;
                                                                                theatre.set_spectacle_newName(choiceSpectacle - 1, actorChoice - 1, actorName);
                                                                                break;
                                                                            case 2:
                                                                                clear();
                                                                                cout << "Enter new age for the actor: ";
                                                                                cin >> actorAge;
                                                                                theatre.set_spectacle_newAge(choiceSpectacle - 1, actorChoice - 1, actorAge);
                                                                                break;

                                                                        }

                                                                        break;
                                                                        
                                                                }

                                                            } while (actorChoice != 0);

                                                        default:
                                                            clear();
                                                            cout << "Error! Can't process this command!" << endl;
                                                            break;
                                                    }

                                                } while (editSpectacle != 0);
                                        }
                                    }
                                    else {
                                        cout << "There are currently no spectacles in our theatre! We're sorry :(" << endl;
                                        cout << "Press any number and enter to return to the menu: ";
                                        cin >> choiceSpectacle;
                                        choiceSpectacle = 0;
                                        clear();
                                        cout << endl << endl;
                                    }
                                } while (choiceSpectacle != 0);
                                break;
                            case 4:
                                clear();
                                do {
                                    if (theatre.get_number_of_spectacles() != 0) {
                                        theatre.show_spectacles_short();
                                        cout << endl;
                                        cout << "Press the number coresponding to the spectacle if you want to learn more about it" << endl;
                                        cout << "Pres 0 if you want to return to the main menu." << endl;
                                        cout << "Press -1 if you want spectacles sorted in the ascending order (by the rating)." << endl;
                                        cout << "Press -2 if you want spectacles sorted in the descending order (by the rating)." << endl;
                                        cout << "Selection: ";
                                        cin >> choiceSpectacle;
                                        switch (choiceSpectacle)
                                        {
                                            case -1:
                                                clear();
                                                theatre.spectacle_sort();
                                                break;

                                            case -2:
                                                clear();
                                                theatre.spectacle_reverse_sort();
                                                break;

                                            case 0:
                                                clear();
                                                break;
                                            default:
                                                clear();
                                                cout << theatre.get_spectacle_info(choiceSpectacle);
                                                break;
                                        }
                                    }
                                    else {
                                        cout << "There are currently no spectacles in our theatre! We're sorry :(" << endl;
                                        cout << "Press any number to exit to exit: ";
                                        cin >> choiceSpectacle;
                                        choiceSpectacle = 0;
                                        clear();
                                        cout << endl << endl;
                                    }
                                } while (choiceSpectacle != 0);
                                break;
                            case 5:
                                clear();
                                cout << "Enter a valid address: ";
                                cin.ignore();
                                cin.get(address, 256);
                                cin.get();
                                theatre.set_address(address);
                                cout << "Your current address is set to: " << theatre.get_address() << endl;
                                break;
                            default:
                                clear();
                                cout << "Error! Can't process this command!" << endl;
                                break;
                        }
                    } while (adminChoice!=0);

                }
                else {
                    clear();
                    cout << "Invalid password!" << endl << endl;
                }
                break;
            case 2: // address
                clear();
                cout << "The address is " << theatre.get_address() << endl << endl;
                break;
            case 3:
                clear();
                do {
                    if (theatre.get_number_of_spectacles() != 0) {
                        theatre.show_spectacles_short();
                        cout << endl;
                        cout << "Press the number coresponding to the spectacle if you want to learn more about it" << endl;
                        cout << "Pres 0 if you want to return to the main menu." << endl;
                        cout << "Press -1 if you want spectacles sorted in the ascending order (by the rating)." << endl;
                        cout << "Press -2 if you want spectacles sorted in the descending order (by the rating)." << endl;
                        cout << "Selection: ";
                        cin >> choiceSpectacle;
                        switch (choiceSpectacle)
                        {
                            case -1:
                                clear();
                                theatre.spectacle_sort();
                                break;

                            case -2:
                                clear();
                                theatre.spectacle_reverse_sort();
                                break;
                            case 0:
                                clear();
                                break;
                            default:
                                clear();
                                cout << theatre.get_spectacle_info(choiceSpectacle);
                                break;
                        }
                    }
                    else {
                        cout << "There are currently no spectacles in our theatre! We're sorry :("<<endl;
                        cout << "Press any number to exit to exit: ";
                        cin >> choiceSpectacle;
                        choiceSpectacle = 0;
                        clear();
                        cout << endl << endl;
                    }
                } while (choiceSpectacle != 0);
                break;
            default:
                clear();
                cout << "Error! Can't process this command!" << endl;
                break;
        }

    } while (choice != 0);
    return 0;
}

//Theatre
void Theatre::set_address(const char* input) {
    delete this->address;
    this->address = new char[strlen(input) + 1];
    strcpy(this->address, input);
    cout << "Address successfully updated!"<<endl;
}

char* Theatre::get_address() {
    return address;
}

void Theatre::add_spectacle(Spectacle spc) {
    spectacles.push_back(spc);
}

void Theatre::show_spectacles_short() {
    if (spectacles.size() == 0)
        cout << "There are currently no spectacles in our theatre! We're sorry :(";
    else
        for (int i = 0; i < spectacles.size(); i++)
            cout << i+1 << ". " << spectacles[i].get_name() << " (rating: " << spectacles[i].get_rating() << "); "<<endl;
}

int Theatre::get_number_of_spectacles() {
    return spectacles.size();
}

Spectacle Theatre::get_spectacle_info(int index) {
    index = index - 1;
    return spectacles[index];
    //cout << spectacles[index];
}

void Theatre::set_spectacle_name(const char* input, int index) {
    spectacles[index].set_name(input);
}

void Theatre::set_spectacle_rating(float input, int index) {
    spectacles[index].set_rating(input);
}

void Theatre::set_spectacle_nrActors(int input, int index) {
    spectacles[index].set_nrActors(input);
}

void Theatre::set_spectacle_newActors(int index) {
    spectacles[index].set_newActors();
}

char* Theatre::get_spectacle_name(int index) {
    return spectacles[index].get_name();
}

double Theatre::get_spectacle_rating(int index) {
    return spectacles[index].get_rating();
}

void Theatre::spectacle_sort() {
    int ok = 1;
    cout << "Sortin spectacles. Please wait..." << endl;
    do {
        ok = 0;
        for(int i=0; i<spectacles.size()-1; i++)
            if (spectacles[i] > spectacles[i + 1]) {
                Spectacle aux;
                aux = spectacles[i];
                spectacles[i] = spectacles[i + 1];
                spectacles[i + 1] = aux;
                ok = 1;
            }
    } while (ok == 1);

}

void Theatre::spectacle_reverse_sort() {
    int ok = 1;
    cout << "Sorting spectacles. Please wait..." << endl;
    do {
        ok = 0;
        for (int i = 0; i < spectacles.size() - 1; i++)
            if (spectacles[i] < spectacles[i + 1]) {
                Spectacle aux;
                aux = spectacles[i];
                spectacles[i] = spectacles[i + 1];
                spectacles[i + 1] = aux;
                ok = 1;
            }
    } while (ok == 1);
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
    out << "Number of actors: " << spec.number_of_actors << endl;
    for (int i = 0; i < spec.number_of_actors; i++) {
        out << i+1 << ". " << spec.actors[i] << endl;
    }
    return out;
}

bool operator>(Spectacle& spc1, Spectacle& spc2) {
    return spc1.rating > spc2.rating;
}

bool operator<(Spectacle& spc1, Spectacle& spc2) {
    return spc1.rating < spc2.rating;
}

bool operator>(double& x, Spectacle& spc) {
    return x > spc.rating;
}

bool operator<(double& x, Spectacle& spc) {
    return x < spc.rating;
}

char* Spectacle::get_name() {
    return this->spectacle_name;
}

double Spectacle::get_rating() {
    return this->rating;
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
    out << "   " << act.name << "'s age is " << act.age << endl;
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