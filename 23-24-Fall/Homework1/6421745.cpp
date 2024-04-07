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

int main(int argc, char **argv) {
    fstream myfile;
    fstream operationfile;
    string row;
    string id, salary, department;
    string name, num1, num2, num3;
    int maximum = 0;
    int linecount = 0;

    // clock_t start=clock(); 
    // clock_t end=clock(); 
    // (double) (end−start) ∗ 1000 / CLOCKS PER SEC;

    myfile.open(argv[1], ios::in);
    while (getline(myfile, row)) {
        linecount++;
    }
    myfile.close();
    maximum = linecount;
    cout << "Maximum ID: " << maximum << endl;
    cout << "Linecount: " << linecount << endl;

    operationfile.open(argv[2], ios::in);
    while (getline(operationfile, row)) {
        stringstream ss(row);
        getline(ss, name, ';');
        getline(ss, num1, ';');
        getline(ss, num2, ';');
        getline(ss, num3, ';');

        if (name == "ADD") {
            myfile.open(argv[1], ios::app);
            string line;
            string id, department, salary;
            myfile << maximum << ";" << num1 << ";" << num2 << endl;
            myfile.close();
            maximum++;
            linecount++;
        } else if (name == "UPDATE") {
            string line;
            myfile.open(argv[1], ios::in);
            stringstream updatedData;
            while (getline(myfile, line)) {
                stringstream updt(line);
                getline(updt, id, ';');
                if (id == num1) {
                    updatedData << num1 << ";" << num2 << ";" << num3;
                } else {
                    getline(updt, salary, ';');
                    getline(updt, department, ';');
                    updatedData << id << ";" << salary << ";" << department;
                }
                updatedData << endl; 
            }
            myfile.close();

            ofstream outfile(argv[1], ios::out);
            outfile << updatedData.str();
            outfile.close();
        } else if (name == "DELETE") {
            linecount--;
            myfile.open(argv[1], ios::in);
            stringstream updatedData;
            string line;
            bool headerWritten = false;
            while (getline(myfile, line)) {
                stringstream ss(line);
                getline(ss, id, ';');
                if (id != num1) {
                    if (!headerWritten) {
                        updatedData << line;
                        headerWritten = true;
                    } else {
                        updatedData << endl << line;
                    }
                }
            }
            myfile.close();

            ofstream outfile(argv[1], ios::out);
            outfile << updatedData.str();
            outfile << endl;
            outfile.close();
        }
    }

    cout << maximum << " " << linecount << endl;
    operationfile.close();
    return 0;
}