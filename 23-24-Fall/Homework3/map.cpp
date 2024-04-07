/*@Author
StudentName : Eylül Zeynep Pınarbaşı
StudentID : 150220725 
Date : 17.12.2023*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <time.h>

using namespace std;

class Employee
{
private:
    int id;
    int salary;
    int department;

public:
    Employee(){};
    void set_id(int id)
    {
        this->id = id;
    }
    void set_salary(int salary)
    {
        this->salary = salary;
    }
    void set_department(int department)
    {
        this->department = department;
    }
    int get_id()
    {
        return this->id;
    }
    int get_salary()
    {
        return this->salary;
    }
    int get_department()
    {
        return this->department;
    }
};
int main(int argc, char** argv)
{
    ifstream file;
    file.open(argv[1]);
    string line;
    stringstream ss(line);
    map<int, Employee *> employee_map;
    int maxemp = 0;
    getline(file, line);
    string id, salary, department;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, id, ';');
        getline(ss, salary, ';');
        getline(ss, department);
        Employee *employee = new Employee();
        employee->set_id(stoi(id));
        employee->set_salary(stoi(salary));
        employee->set_department(stoi(department));
        employee_map[employee->get_id()] = employee; 
        maxemp++;
    }
    file.close();
    fstream operationfile;
    operationfile.open(argv[2], ios::in);
    string line2;
    string operation, num1, num2, num3;
    while (getline(operationfile, line2))
    {
        stringstream ss2(line2);
        getline(ss2, operation, ';');
        getline(ss2, num1, ';');
        getline(ss2, num2, ';');
        getline(ss2, num3, ';');

        if (operation == "ADD")
        {
            Employee *employee = new Employee();
            employee->set_id(maxemp+1);
            employee->set_salary(stoi(num1));
            employee->set_department(stoi(num2));
            employee_map[maxemp + 1] = employee;
            maxemp++;
        }
        else if (operation == "UPDATE")
        {
            int id = stoi(num1);
            int salary = stoi(num2);
            int department = stoi(num3);

            if (employee_map.count(id))
            {
                employee_map[id]->set_salary(salary);
                employee_map[id]->set_department(department);
            }
            else
            {
                cout << "ERROR: An invalid ID to update"
                     << "\n";
            }
        }
        else if (operation == "DELETE")
        {
            if (employee_map.empty())
            {
                cout << "ERROR: There is no Employee"
                     << "\n";
            }
            else if (!employee_map.count(stoi(num1)))
            {
                cout << "ERROR: An invalid ID to delete"
                     <"\n";
            }
            else
            {
                employee_map.erase(stoi(num1));
            }
        }
    }

    operationfile.close();
    ofstream output_file;
    output_file.open("output.csv");
    output_file << "Employee_ID;Salary;Department" << endl;
    for (auto it = employee_map.begin(); it != employee_map.end(); it++) {
        output_file << it->second->get_id() << ";" << it->second->get_salary() << ";" << it->second->get_department() << endl;
    }
    output_file.close();
    return 0;
}
< "\