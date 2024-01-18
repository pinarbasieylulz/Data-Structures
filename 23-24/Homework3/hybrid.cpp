/*@Author
StudentName : Eylül Zeynep Pınarbaşı
StudentID : 150220725 
Date : 17.12.2023*/



#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>

using namespace std;
class Employee {
    private:
        int id;
        int salary;
        int department;
    public: 
        Employee() {};
        void set_id(int id) {
            this->id = id;
        }
        void set_salary(int salary){
            this->salary = salary;
        }
        void set_department(int department){
            this->department = department;
        }
        int get_id() {
            return this->id;
        }
        int get_salary() {
            return this->salary;
        }
        int get_department() {
            return this->department;
        }
};

class Node {
    private:
        Employee* employee;
        Node* left;
        Node* right;
    public:
        Node(Employee* employee) {
            this->employee = employee;
            this->left = NULL;
            this->right = NULL;
        }
        void set_employee(Employee* employee) {
            this->employee = employee;
        }
        void set_left(Node *left) {
            this->left = left;
        }
        void set_right(Node *right) {
            this->right = right;
        }
        Employee* get_employee() {
            return this->employee;
        }
        Node* get_left() {
            return this->left;
        }
        Node* get_right() {
            return this->right;
        }

};
class BinaryTree {
    private:
        Node* root;
        Node* removeHelper(Node* node, int id) {
                if (node == nullptr) {
                    return node;
                }

                if (id < node->get_employee()->get_id()) {
                    node->set_left(removeHelper(node->get_left(), id));
                } else if (id > node->get_employee()->get_id()) {
                    node->set_right(removeHelper(node->get_right(), id));
                } else {
                    if (node->get_left() == nullptr) {
                        Node* temp = node->get_right();
                        delete node;
                        return temp;
                    } else if (node->get_right() == nullptr) {
                        Node* temp = node->get_left();
                        delete node;
                        return temp;
                    }

                    Node* temp = node->get_right();
                    while (temp->get_left() != nullptr)
                        temp = temp->get_left();

                    node->set_employee(temp->get_employee());

                    node->set_right(removeHelper(node->get_right(), temp->get_employee()->get_id()));
                }
                return node;
                }
        void printToConsoleHelper(Node* node) {
            if (node == nullptr) {
                return;
            }
            cout << node->get_employee()->get_id() << ";" << node->get_employee()->get_salary() << ";" << node->get_employee()->get_department() << "\r\n";
            printToConsoleHelper(node->get_left());
            printToConsoleHelper(node->get_right());
        }
        Node* searchHelper(Node* root, int id) {
            if (root == nullptr || root->get_employee()->get_id() == id) {
                return root;
            }
            else if (id < root->get_employee()->get_id()) {
                return searchHelper(root->get_left(), id);
            }
            else {
                return searchHelper(root->get_right(), id);
            }
        }
        int getHeightHelper(Node* node) {
            if (node == nullptr) {
                return 0;
            }
            int leftHeight = getHeightHelper(node->get_left());
            int rightHeight = getHeightHelper(node->get_right());
            return max(leftHeight, rightHeight) + 1;
        }
        void printToFileHelper(Node* node, ofstream &output_file) {
            if (node == nullptr) {
                return;
            }
            printToFileHelper(node->get_left(), output_file);
            output_file << node->get_employee()->get_id() << ";" << node->get_employee()->get_salary() << ";" << node->get_employee()->get_department() << endl;
            printToFileHelper(node->get_right(), output_file);
        }
    public:
        BinaryTree () {
            root= NULL;
        }
        void insert(Employee* employee) {
            Node* newNode = new Node(employee);
            if (root == NULL) {
                root = newNode;
                return;
            } else {
                Node* current = root;
                Node* parent = nullptr;
                while (true) {
                    parent = current;
                    if (employee->get_id() < current->get_employee()->get_id()) {
                        current = current->get_left();
                        if (current == nullptr) {
                            parent->set_left(newNode);
                            return;
                        }
                    } else {
                        current = current->get_right();
                        if (current == nullptr) {
                            parent->set_right(newNode);
                            return;
                        }
                    }
                }
            }
        }
        void remove(int id) {
            if (search(id)==nullptr) {
                cerr << "ERROR: An invalid ID to delete\r\n";
                return;
            }
            else {
                root=removeHelper(root, id);
            }
        }
        Employee* search(int id) {
            Node* current = root;
            while (current->get_employee()->get_id() != id) {
                if (id < current->get_employee()->get_id()) {
                    current = current->get_left();
                } else {
                    current = current->get_right();
                }
                if (current == nullptr) {
                    return nullptr;
                }
            }
            return current->get_employee();
        }
        int getHeight() {
            return getHeightHelper(root);
        }
        void printToFile(ofstream &output_file) {
            if (root == nullptr) {
                return;
            } else {
                printToFileHelper(root, output_file);
            }
        }
        void printToConsole() {
            if (root == nullptr) {
                return;
            } else {
                printToConsoleHelper(root);
                cout << "\r\n";
            }
        }
};

int main(int argc, char** argv) {
    ifstream input_file;
    int datanumber=0;
    string line;
    input_file.open(argv[1]);
    while(getline(input_file, line)) {
        datanumber++;
    }
    input_file.close();
    input_file.open(argv[1]);
    int treenumber= datanumber/5000;
    vector<BinaryTree*> trees(treenumber);
    for (int i=0; i<treenumber; i++) {
        trees[i]=new BinaryTree();
    }
    getline(input_file, line);
    while (getline(input_file, line)) {
        stringstream ss(line);
        string id, salary, department;
        getline(ss, id, ';');
        getline(ss, salary, ';');
        getline(ss, department);
        Employee* employee = new Employee();
        employee->set_id(stoi(id));
        employee->set_salary(stoi(salary));
        employee->set_department(stoi(department));
        size_t treeindex = stoi(id) / 5000;
        if (treeindex >= trees.size()) {
            trees.resize(treeindex + 1);
        }
        if (trees[treeindex] == nullptr) {
            trees[treeindex] = new BinaryTree();
        }
        trees[treeindex]->insert(employee);
    }
    input_file.close();
    string line2;
    fstream operation_file;
    operation_file.open(argv[2]);
    stringstream ss;
    ss.clear();
    while(getline(operation_file, line2)) {
        string operation, num1, num2, num3;
        stringstream ss(line2);

        if (line2.find(";") != string::npos) {
            ss.clear(); // Clear the stringstream
            ss.str(line2); // Put the line into the stringstream
            getline(ss, operation, ';');
            getline(ss, num1, ';');
            getline(ss, num2, ';');
            getline(ss, num3, ';');
            if (operation == "ADD") {
                Employee* employee = new Employee();
                datanumber++;  // Increment datanumber before setting the employee's ID
                employee->set_id(datanumber-1);
                employee->set_salary(stoi(num1));
                employee->set_department(stoi(num2));

                size_t index = datanumber / 5000;
                if (index >= trees.size()) {
                    trees.resize(index+1);
                }
                if (trees[index] == nullptr) {
                    trees[index] = new BinaryTree();
                }
                trees[index]->insert(employee);
            }
            else if (operation=="UPDATE") {
                int id = stoi(num1);
                size_t index = id / 5000;
                if (index < trees.size() && trees[index] != nullptr) {
                    Employee* employee = trees[index]->search(id);
                    if (employee == nullptr) {
                        cerr << "ERROR: An invalid ID to update\r\n";
                    } else {
                        employee->set_salary(stoi(num2));
                        employee->set_department(stoi(num3));
                    }
                } else {
                    cerr << "ERROR: An invalid ID to update\r\n";
                }
            }
            else if (operation== "DELETE") {
                int id = stoi(num1);
                size_t index = id / 5000;
                if (index < trees.size() && trees[index] != nullptr) {
                    trees[index]->remove(id);
                } else {
                    cerr << "ERROR: An invalid ID to delete\r\n";
                }
            }
        }
        else if (line2.find("HEI") != std::string::npos) {
            for (size_t i = 0; i < trees.size(); i++) {
                if (trees[i] != nullptr) {
                    cerr << "H " << (trees[i]->getHeight()) << endl;
                }
            }
        } 
        else if (line2.find("PR") != std::string::npos){
            for (size_t i = 0; i < trees.size(); i++) {
                if (trees[i] != nullptr) {
                    cout << "P" << endl;
                    trees[i]->printToConsole();
                }
            }
        }
    }
    ofstream output_file("output.csv");
    output_file << "Employee_ID;Salary;Department" << endl;
    for (size_t i = 0; i < trees.size(); i++) {
        if (trees[i] != nullptr) {
            trees[i]->printToFile(output_file);
        }
    }
    output_file.close();
    return 0;
}




