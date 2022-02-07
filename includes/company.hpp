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
    unordered_map<float, vector<Employee>> employeeBySalary;
    unordered_map<string, vector<Employee>> employeeByArea;
    unordered_map<string, vector<Employee>> employeeByLastName;
    unordered_map<string, double> highSalaryByLastName;
    unordered_map<string, vector<float>> salaryByArea;
    unordered_map<string, string> areaNameByCode;
    unordered_map<string, double> salaryAcumulatorByArea;
    unordered_map<string, int> totalEmployeeByArea;
    unordered_map<string, int> totalEmployeeByLastName;
    double salaryAcumulator = 0;
    int totalEmployee = 0;

   public:
    // Constructor
    Company(string path);

    // Queries
    void query1();
    void query2();
    void query3();
    void query4();
};
