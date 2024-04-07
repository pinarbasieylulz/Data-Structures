/*@Author
StudentName :Eylül Zeynep Pınarbaşı
StudentID : 150220725
Date :10.11.2023  */ 

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
class Employee {
    private:
        int id;
        int salary;
        int department;
    public:
        Employee() {}
        ~Employee() {}
        void set_id(int id) {
            this->id = id;
        }void set_salary(int salary) {
            this->salary=salary;
        }void set_department(int department) {
            this->department=department;
        }int get_id() {
            return this->id;
        }int get_salary() {
            return this->salary;
        }int get_department() {
            return this->department;
        }
};
int main (int argc, char** argv) {
    fstream newfile;
    newfile.open(argv[1], ios::in);
    list<Employee> list;
    string line;
    string header;
    getline(newfile, header);
    int linecount=0;
    while(getline(newfile, line)) {
        linecount++;
        stringstream ss(line);
        string id, salary, department;
        getline(ss, id, ';');
        getline(ss, salary, ';');
        getline(ss, department, ';');
        Employee employee;
        employee.set_id(stoi(id));
        employee.set_salary(stoi(salary));
        employee.set_department(stoi(department));
        list.push_back(employee); 
    }
    int maximum=linecount;
    fstream operationfile;
    operationfile.open(argv[2], ios::in);
    string operation;
    while(getline(operationfile, operation)) {
        stringstream ss1(operation);
        string name, num1, num2, num3;
        getline(ss1, name, ';');
        getline(ss1, num1, ';');
        getline(ss1, num2, ';');
        getline(ss1, num3);

        if(name=="ADD") {
            Employee employee;
            employee.set_id(maximum+1);
            employee.set_salary(stoi(num1));
            employee.set_department(stoi(num2));
            list.push_back(employee);
            linecount++;
            maximum++;
        }
        else if(name=="UPDATE") {
            if (static_cast<size_t>(stoi(num1))>list.size()) {
                cout << "ERROR: An invalid ID to update";
                continue;
            }
            for(auto it = list.begin(); it != list.end(); ++it) {
                if(it->get_id()==stoi(num1)) {
                    it->set_salary(stoi(num2));
                    it->set_department(stoi(num3));
                }
            }
        }
        else if(name=="DELETE") {
            if (linecount==0) {
                cout << "ERROR: There is no Employee";
            }
            bool found = false;
            for(auto it = list.begin(); it != list.end(); ++it) {
                if(it->get_id()==stoi(num1)) {
                    it = list.erase(it);
                    linecount--;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "ERROR: An invalid ID to delete";
            }
        }
    }
    ofstream outputfile;
    outputfile.open("list_solution.csv", ios::out);
    string last;
    stringstream ss2(last);
    for(auto& i : list) {
        ss2 << i.get_id() << ";" << i.get_salary() << ";" << i.get_department() << endl;
    }
    outputfile << header << endl;
    outputfile << ss2.str();
    outputfile.close();
    newfile.close();
    operationfile.close();
    list.clear();
    return 0;
}

    
