#pragma once
#include <rapidjson/document.h>

#include "headers.hpp"

using namespace std;
using namespace rapidjson;

struct Employee {
    // int id;
    string nome;
    string sobrenome;
    float salario;
    string area;
};

class Company {
   private:
    // Variables

    Document json;

    unordered_map<float, vector<Employee>> employeeBySalary;     // Check 1
    unordered_map<string, vector<Employee>> employeeByArea;      // Check 2
    unordered_map<string, vector<Employee>> employeeByLastName;  // Check 4
    unordered_map<string, double> highSalaryByLastName;          // Check 4
    // unordered_map<string, vector<float>> salaryByArea;
    unordered_map<string, string> areaNameByCode;          // Check 2 3
    unordered_map<string, double> salaryAcumulatorByArea;  // Check 2
    unordered_map<string, int> totalEmployeeByArea;        // Check 2 3
    unordered_map<string, int> totalEmployeeByLastName;    //
    double salaryAcumulator = 0;                           // Check 1
    int totalEmployee = 0;                                 // Check 1

   public:
    // Constructor
    Company(string path);

    // Parser data
    void getQuery1();
    void getAreaNameByCode();
    void getQuery2();
    void getQuery4();

    // Run queries
    void query1();
    void query2();
    void query3();
    void query4();
};
