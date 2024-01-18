/*@Author
StudentName :Eylül Zeynep Pınarbaşı
StudentID : 150220725
Date :10.11.2023  */ 


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Employee {
    private:
        int id;
        int salary;
        int department;
        Employee *next;
        Employee* prev;
    public:
        void set_id(int id) {
            this->id = id;
        }
        void set_salary(int salary) {
            this->salary = salary;
        }
        void set_department(int department) {
            this->department = department;
        }
        void set_next(Employee* next) {
            this->next=next;
        }
        void set_prev(Employee* prev) {
            this->prev=prev;
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
        Employee *get_next() {
            return this->next;
        }
        Employee *get_prev() {
            return this->prev;
        }
};

class LinkedList {
    private:
        Employee *head;
        Employee *tail;
    public:
        LinkedList() {
            head = NULL;
            tail = NULL;
        }
        void add(int& maximum, int salary, int department);
        void update(int id, int salary, int department);
        void del(int id, int&maximum, int&linecount);
        void newFile();
};

void LinkedList::add(int& maximum, int salary, int department) {
    Employee *employee = new Employee();
    employee->set_id(maximum);
    employee->set_salary(salary);
    employee->set_department(department);
    employee->set_next(NULL);

    if (head == NULL) {
        head = employee;
        tail = employee;
    } else {
        tail->set_next(employee);
        tail = employee;
    }
    maximum++;
}

void LinkedList::update(int id, int salary, int department) {
    Employee* current = head;
    bool found = false;
    while (current != nullptr) {
        if (current->get_id() == id) {
            current->set_salary(salary);
            current->set_department(department);
            found = true;
            break;
        }
        current = current->get_next();
    }
    if (!found) {
        cout << "ERROR: An invalid ID to update";
    }
}

void LinkedList::del(int id, int &maximum, int &linecount) {
    Employee *current = head;
    Employee *prev = NULL;
    bool isValid = false;
    while (current != NULL) {
        if (current->get_id() == id) {
            isValid = true;
            break;
        }

        prev = current;
        current = current->get_next();
    }
    if (isValid == false) {
        cout << "ERROR: An invalid ID to delete";
        return;
    }
    if (linecount==1) {
        cout << "ERROR: There is no employee";
        return;
    }
    if(prev==NULL) {
        head = head->get_next();
    }
    else {
        prev->set_next(current->get_next());
    }
    delete current;
    linecount--;
}
void LinkedList::newFile() {
    stringstream ss;
    ofstream lastfile("linked_list_solution.csv");
    lastfile << "Employee_ID;Salary;Department" << endl;
    Employee* current = head;  
    while (current != nullptr) { 
        ss << current->get_id() << ";";
        ss << current->get_salary() << ";";
        ss << current->get_department() << endl;
        current = current->get_next();  
    }
    lastfile << ss.rdbuf();
    lastfile.close();
}

int main (int argc, char** argv) {
    fstream myfile;
    LinkedList employees;
    myfile.open(argv[1], ios::in);
    string line;
    string header;
    getline(myfile, header);
    int maximum=1;
    while (getline(myfile, line)) {
        stringstream ss(line);
        string id, salary, department;
        getline(ss, id, ';');
        getline(ss, salary, ';');
        getline(ss, department);
        employees.add(maximum, stoi(salary), stoi(department));
    }
    int linecount=maximum;
    myfile.close();
    fstream operationfile;
    operationfile.open(argv[2], ios::in);
    string operation;
    while(getline(operationfile, operation)) {
        stringstream ss(operation);
        string name;
        string num1,num2,num3;
        getline(ss, name, ';');

        if (name== "ADD") {
            getline(ss, num1, ';');
            getline(ss, num2, ';');
            employees.add(maximum, stoi(num1), stoi(num2));
        }
        else if (name == "UPDATE") {
            getline(ss, num1, ';');
            getline(ss, num2, ';');
            getline(ss, num3, ';');
            employees.update(stoi(num1), stoi(num2), stoi(num3));
        }
        else if (name == "DELETE") {
            getline(ss, num1, ';');
            employees.del(stoi(num1), maximum, linecount);
        }
    }
    employees.newFile();

    operationfile.close();
    return 0;
}