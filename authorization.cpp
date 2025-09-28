#include <iostream>
#include <vector>
using namespace std;

struct User {
    string username;
    string password; 
    vector<string> permissions;
    User* next;
    
    User(const string& u,const string& p,const vector<string>& perm = {"view"}) {
        username = u;
        password = p;
        permissions = perm;
        next = nullptr;
    }
};
bool insertUser (User*& head, const string& username, const string& password, const vector<string>& permissions = {"view"});
void printUsers (User* head);
User* findUser(User* head, const string& username);
bool authorize (User* head, const string& username, const string& action);


int main () {

    User* head = nullptr;

    insertUser(head, "Epi", "GEORgeP$#rice", {"edit", "create", "delete", "view"});
    insertUser(head, "Yessenia", "philip#!AUson", {"edit", "create" , "view"});
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
bool insertUser (User*& head, const string& username, const string& password, const vector<string>& permissions) {
    if (head == nullptr) {
        head = new User(username, password, permissions);
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
    current->next = new User(username, password, permissions);
    return true;
}

void printUsers (User* head) {
    User* current = head;
    while(current != nullptr) {
        cout << "Username: " << current->username ;
        for (const string& perm: current->permissions) {
            cout << perm << " " ;
        } 
        cout << endl;
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

    for (const string& permission : user->permissions) {
        if (permission == action) {
            return true;
        }
    }
    return false;
}