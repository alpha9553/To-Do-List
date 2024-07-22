#include <iostream>
#include <string>

using namespace std;

struct Node {
    string task;
    Node* next;
    Node* prev;

    Node(string t) : task(t), next(nullptr), prev(nullptr) {}
};

class TodoList {
private:
    Node* head;
    Node* tail;

public:
    TodoList() : head(nullptr), tail(nullptr) {}

    void addTask(const string& task) {
        Node* newNode = new Node(task);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void removeTask(const string& task) {
        Node* current = head;
        while (current) {
            if (current->task == task) {
                if (current == head) {
                    head = head->next;
                    if (head) head->prev = nullptr;
                } else {
                    current->prev->next = current->next;
                    if (current->next) current->next->prev = current->prev;
                }
                if (current == tail) tail = current->prev;
                delete current;
                cout << "\033[32mTask removed successfully!\033[0m" << endl;
                return;
            }
            current = current->next;
        }
        cout << "\033[31mTask not found!\033[0m" << endl;
    }

    void displayTasks() const {
        Node* current = head;
        if (!current) {
            cout << "\033[33mNo tasks in the to-do list.\033[0m" << endl;
            return;
        }
        cout << "\033[34mTo-Do List:\033[0m" << endl;
        while (current) {
            cout << "\033[36m- " << current->task << "\033[0m" << endl;
            current = current->next;
        }
    }

    ~TodoList() {
        Node* current = head;
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
};

void displayMenu() {
    cout << "\n\033[35mTo-Do List Menu\033[0m" << endl;
    cout << "\033[32m1. Add Task\033[0m" << endl;
    cout << "\033[32m2. Remove Task\033[0m" << endl;
    cout << "\033[32m3. Display Tasks\033[0m" << endl;
    cout << "\033[32m4. Exit\033[0m" << endl;
    cout << "\033[33mEnter your choice: \033[0m";
}

int main() {
    TodoList myList;
    int choice;
    string task;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "\033[33mEnter task to add: \033[0m";
            getline(cin, task);
            myList.addTask(task);
            cout << "\033[32mTask added successfully!\033[0m" << endl;
            break;
        case 2:
            cout << "\033[33mEnter task to remove: \033[0m";
            getline(cin, task);
            myList.removeTask(task);
            break;
        case 3:
            myList.displayTasks();
            break;
        case 4:
            cout << "\033[31mExiting...\033[0m" << endl;
            break;
        default:
            cout << "\033[31mInvalid choice. Please try again.\033[0m" << endl;
        }
    } while (choice != 4);

    return 0;
}
