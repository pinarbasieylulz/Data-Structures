/*@Author
StudentName :Eylül Zeynep Pınarbaşı
StudentID : 150220725
Date :10.11.2023  */ 



#include <iostream>
#include <vector>
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
    vector<Employee> v;
    string line;
    string header;
    getline(newfile, header);
    int linecount=0;
    int maximum=0;
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
        v.push_back(employee); 
    }
     maximum=linecount;
    fstream operationfile;
    operationfile.open(argv[2], ios::in);
    string operation;
    int deletecount=0;
    int addcount=0;
    int updatecount=0;

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
            v.push_back(employee);
            linecount++;
            maximum++;
            addcount++;
        }
        else if(name=="UPDATE") {
            if (static_cast<size_t>(stoi(num1))>v.size()) {
                cout << "ERROR: An invalid ID to update";
                continue;
            }
            for(size_t i=0; i<v.size(); i++) {
                if(v[i].get_id()==stoi(num1)) {
                    v[i].set_salary(stoi(num2));
                    v[i].set_department(stoi(num3));
                }
            }
            updatecount++;
        }
        else if(name=="DELETE") {
            if (linecount==0) {
                cout << "ERROR: There is no Employee";
            }
            bool found = false;
            for(size_t i=0; i<v.size(); i++) {
                if(v[i].get_id()==stoi(num1)) {
                    v.erase(v.begin()+i);
                    linecount--;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "ERROR: An invalid ID to delete";
            }
            deletecount++;
        }
    }

    fstream outputfile;
    outputfile.open("vector_solution.csv", ios::out);
    string last;
    stringstream ss2(last);
    for(size_t i=0; i<v.size(); i++) {
        ss2 << v[i].get_id() << ";" << v[i].get_salary() << ";" << v[i].get_department() << endl;
    }
    outputfile << header << endl;
    outputfile << ss2.str();
    outputfile.close();
    newfile.close();
    operationfile.close();
    v.clear();
    cout << deletecount << " " << addcount << " " << updatecount << endl;
    // for(int i=0; i<v.size(); i++) {
    //     cout << v[i].get_id()<< " " << v[i].get_salary() << " " << v[i].get_department() << endl;
    // }
    return 0;
}

    
