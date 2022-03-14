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
         << "\t\t\t\t3 -> Show spectacles that are in the theatre now" << endl << endl;
    cout << "\tEnter your choice: ";
}

void adminMessage() {
    cout << "\t\t\t\t0 -> Exit admin panel." << endl 
         << "\t\t\t\t1 -> Show theatre address" << endl 
         << "\t\t\t\t2 -> Add a spectacle" << endl 
         << "\t\t\t\t3 -> Show spectacles that are in the theatre now" << endl 
         << "\t\t\t\t4 -> Modify theatre address" << endl << endl;
    cout << "\tEnter your choice: ";
}

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
    char* get_name();
    double get_rating();
    //~Spectacle();
};

class Theatre {
    char* address;
    vector<Spectacle> spectacles;
public:
    void set_address(const char* s);
    void add_spectacle(Spectacle spc);
    void show_spectacles_short();
    int get_number_of_spectacles();
    Spectacle get_spectacle_info(int index);
    char* get_address();
};

int main()
{
    Theatre theatre;
    Spectacle temp;
    int choice, choiceSpectacle, adminChoice;
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
                            case 3:
                                clear();
                                do {
                                    if (theatre.get_number_of_spectacles() != 0) {
                                        theatre.show_spectacles_short();
                                        cout << "Press the number coresponding to the spectacle if you want to learn more about it" << endl;
                                        cout << "Or 0 if you want to return to the main menu." << endl;
                                        cin >> choiceSpectacle;
                                        switch (choiceSpectacle)
                                        {
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
                                    }
                                } while (choiceSpectacle != 0);
                                break;
                            case 4:
                                clear();
                                cout << "Enter a valid address: ";
                                cin.ignore();
                                cin.get(address, 256);
                                cin.get();
                                theatre.set_address(address);
                                cout << "Your current address is set to: " << theatre.get_address() << endl;
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
                        cout << "Press the number coresponding to the spectacle if you want to learn more about it" << endl;
                        cout << "Or 0 if you want to return to the main menu." << endl;
                        cin >> choiceSpectacle;
                        switch (choiceSpectacle)
                        {
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
                    }
                } while (choiceSpectacle != 0);
                break;
            default:
                clear();
                cout << "Error! Can't process this command!" << endl;
                break;
        }

    } while (choice != 0);

    /*do
    {
        if (theatre.get_address() == NULL) {
            cout << "Warning! Your theatre address is unset! Please set your address by pressing 1!" << endl;
        }
        cout << "0. Quit" << endl << "1. Modify theatre address" << endl << "2. Show theatre address" << endl << "3. Add a spectacle" << endl << "4. Show spectacles that are in the theatre" << endl << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 0:
                cout << "Exit message";
                return 0;
            case 1:
                clear();
                cout << "Enter a valid address: ";
                cin.ignore();
                cin.get(address, 256);
                cin.get();
                theatre.set_address(address);
                cout << "Your current address is set to: " << theatre.get_address() << endl;
                break;
            case 2:
                clear();
                cout << "The address is " << theatre.get_address();
                break;
            case 3:
                clear();
                cin >> temp;
                theatre.add_spectacle(temp);
                break;
            case 4:
                clear();
                do {
                    theatre.show_spectacles_short();

                    cout << "Press the number coresponding to the spectacle if you want to learn more about it, or 0 if you want to return to the main menu." << endl;
               
                    cin >> choiceSpectacle;
                    switch (choiceSpectacle)
                    {
                    case 0:
                        clear();
                        break;
                    default:
                        clear();
                        theatre.get_spectacle_info(choiceSpectacle);
                        break;
                    }
                } while (choiceSpectacle != 0);
                break;
            default:
                clear();
                cout << "Error! Can't process the command!";
                break;
        }
        cout << endl << endl;
    } while (choice != 0);*/
    return 0;
}

//Theatre
void Theatre::set_address(const char* input) {
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
        out << spec.actors[i] << endl;
    }
    return out;
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


