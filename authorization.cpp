#include <iostream>
using namespace std;

struct User {
    string username;
    string password; 
    string role;
    User* next;
    
    User(const string& u,const string& p,const string& r = "viewer") {
        username = u;
        password = p;
        role = r;
        next = nullptr;
    }
};
bool insertUser (User*& head, const string& username, const string& password, const string& role = "viewer");
void printUsers (User* head);
User* findUser(User* head, const string& username);
bool authorize (User* head, const string& username, const string& action);


int main () {

    User* head = nullptr;

    insertUser(head, "Epi", "GEORgeP$#rice", "admin");
    insertUser(head, "Yessenia", "philip#!AUson", "editor");
    insertUser(head, "Pat", "Guestpass");

    // test to see if new user defaults to "viewer".
    printUsers(head);

    // testing if authorization works
    cout << "Authorization tests: " << endl;
    cout << "Epi deleting: " << (authorize(head, "Epi", "delete")? "Allowed" : "Denied") << endl;
    cout << "Yessenia editing: " << (authorize(head, "Yessenia", "edit")? "Allowed" : "Denied") << endl;
    cout << "Pat editing: " << (authorize(head, "Pat", "edit")? "Allowed" : "Denied") << endl;


    return 0;
}
bool insertUser (User*& head, const string& username, const string& password, const string& role) {
    if (head == nullptr) {
        head = new User(username, password, role);
        return true;
    }
    User *current = head;
    while(current != nullptr) {
        if(current->username == username ) {
            return false;
        }
        if(current->next == nullptr) {
            break;
        }
        current = current->next;
    }
    current->next = new User(username, password, role);
    return true;
}

void printUsers (User* head) {
    User* current = head;
    while(current != nullptr) {
        cout << "Username: " << current->username << ", Role: " << current->role << endl;
        current = current->next;
    }
}

User* findUser(User* head, const string& username) {
    User* temp = head;
    while (temp != nullptr) {
        if(temp->username == username) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

bool authorize (User* head, const string& username, const string& action) {
    User* user = findUser(head, username);
    if(user == nullptr) {
        return false;
    }

    string role = user->role;

    if (role == "admin") {
        return true;
    } else if(role == "editor") {
        return (action == "view" || action == "edit" || action == "create");
    }else if (role == "viewer") {
        return action == "view";
    }
    return false;

}