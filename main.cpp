#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string text;
    bool completed;
};

vector<Task> loadTasks() {
    vector<Task> tasks;
    ifstream file("tasks.txt");
    string line;

    while (getline(file, line)) {
        Task task;
        task.completed = (line[0] == '1');
        task.text = line.substr(2);
        tasks.push_back(task);
    }

    return tasks;
}

void saveTasks(const vector<Task>& tasks) {
    ofstream file("tasks.txt");
    for (const auto& task : tasks) {
        file << (task.completed ? "1" : "0") << " " << task.text << endl;
    }
}

void displayTasks(const vector<Task>& tasks) {
    cout << "\n--- Your Tasks ---\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". [" << (tasks[i].completed ? "X" : " ") << "] " << tasks[i].text << endl;
    }
    cout << "------------------\n";
}

int main() {
    vector<Task> tasks = loadTasks();
    int choice;

    do {
        cout << "\n1. View Tasks\n2. Add Task\n3. Complete Task\n4. Delete Task\n0. Exit\nYour choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            displayTasks(tasks);
        } else if (choice == 2) {
            string text;
            cout << "Enter task description: ";
            getline(cin, text);
            tasks.push_back({text, false});
            saveTasks(tasks);
        } else if (choice == 3) {
            int num;
            cout << "Task number to complete: ";
            cin >> num;
            if (num > 0 && num <= tasks.size()) {
                tasks[num - 1].completed = true;
                saveTasks(tasks);
            }
        } else if (choice == 4) {
            int num;
            cout << "Task number to delete: ";
            cin >> num;
            if (num > 0 && num <= tasks.size()) {
                tasks.erase(tasks.begin() + num - 1);
                saveTasks(tasks);
            }
        }

    } while (choice != 0);

    return 0;
}
