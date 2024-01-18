//  @Author
// StudentName : Eylül Zeynep Pınarbaşı
// StudentID : 150220725
// Date : 10.29.2023 


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

using namespace std;
class Employee {
    private:
        int id;
        int salary;
        int department;

    public:
        Employee();
        ~Employee();
        void set_id(int);
        void set_salary(int);
        void set_department(int);
        int get_id();    
        int get_salary();    
        int get_department();    
}; 


Employee::Employee(){};
Employee::~Employee(){};
void Employee::set_id(int id) {
    this->id = id; }
void Employee::set_department(int department){
    this->department = department; }
void Employee::set_salary(int salary){     
    this->salary = salary; }
int Employee::get_id()
{
    return this->id;
};
    int Employee::get_salary()
    {
        return this->salary;
    };

    int Employee::get_department() 
    {
        return this->department;
    };

Employee* add(Employee* array, int &linecount, int salary, int department, int &maximum) {
    Employee* newarray = new Employee[linecount + 1];
    for (int i = 0; i < linecount; i++) {
        newarray[i] = array[i];
    }
    
    newarray[linecount].set_id(maximum+1);
    newarray[linecount].set_salary(salary);
    newarray[linecount].set_department(department);
    linecount=linecount+1;
    maximum++;
    return newarray;
}


void update(Employee* array, int id, int &linecount, int salary, int dept) {
    bool validID = false;
    if (linecount==0) {
        cerr << "ERROR: There is no employee ";
    }
    for (int i = 0; i < linecount; i++) {
        if(array[i].get_id() == id){
            validID = true;
            array[i].set_salary(salary);
            array[i].set_department(dept);
            break;
        }
    }
    if (!validID) {
        cout << "No employee found with id " << id << endl;
    }
}
Employee* del(Employee* array, int id, int &linecount) {
    bool validID = false;
    Employee* newarray = new Employee[linecount-1];

    if (linecount == 1 && linecount==0) {
        cout << "ERROR: There is no employee";
    }   
    int newsize=0;
    for (int i = 0; i < linecount; ++i) {
        if (array[i].get_id() == id) { 
            validID= true;
            continue;
        }
        newarray[newsize] = array[i] ;
        newsize++; 
    }
    if(validID==false) {
        cout << "ERROR: An invalid ID to delete"; 
    }
    linecount= newsize;
    return newarray;
}



int main(int argc, char **argv) {

    fstream myfile;
    string line;
    int maximum=0;
    string header;
    string id, salary, dept;
    myfile.open(argv[1], ios::in);
    getline(myfile, header);
    while (getline(myfile, line)) {
        maximum++;
    }
    int linecount= maximum;
    myfile.close();
    myfile.open("hw2.csv", ios::in);
    getline(myfile, header);
    Employee* array = new Employee[maximum+1];  
    

    for (int i = 0; i < linecount; i++) {
        getline(myfile, line);
        stringstream ss(line);
        string id, salary, department;
        Employee* employee = new Employee();
        getline(ss, id, ';');
        employee->set_id(stoi(id)); 
        getline(ss, salary, ';'); 
        employee->set_salary(stoi(salary));
        getline(ss, department, ';'); 
        employee->set_department(stoi(department));
        array[i] = *employee; // or *(array+1) = *employee
        delete employee;

    }

    string row, name, num1, num2, num3;
    fstream operationfile;
    operationfile.open(argv[2], ios::in);

    while(getline(operationfile, row)) {
        stringstream ss2(row);
        getline(ss2, name, ';');
        getline(ss2, num1, ';');
        getline(ss2, num2, ';') ;
        getline(ss2, num3);

        if(name == "ADD") {
            array = add(array, linecount, stoi(num1) ,stoi(num2), maximum);
        }        
        else if(name=="UPDATE") {
            update(array, stoi(num1), linecount ,stoi(num2), stoi(num3) );

         }
         else if(name=="DELETE") {
             array = del(array, stoi(num1), linecount);

        }
    }

    myfile.close();
    operationfile.close();
    ofstream lastfile ("array_solution.csv", ios::out);
    lastfile << header << endl;
    stringstream ss3;
    for(int i=0;i<linecount; i++) {
        ss3 << array[i].get_id() << ";" << array[i].get_salary() << ";" << array[i].get_department() << endl;
        lastfile << ss3.str();
        ss3.str("");
    }
    lastfile.close();
    delete[] array;
    return 0; 
}
