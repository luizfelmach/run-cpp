#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include "../includes/headers.hpp"

using namespace std;
using namespace rapidjson;

// Constructor
Company::Company(string path) {
    string fileName = path;
    FILE* file = fopen(fileName.c_str(), "rb");
    char readBuffer[1024];
    FileReadStream jsonRaw(file, readBuffer, sizeof(readBuffer));
    Document json;
    json.ParseStream(jsonRaw);
    fclose(file);

    for (const auto& employee : json["funcionarios"].GetArray()) {
        string name = employee["nome"].GetString();
        string sobrenome = employee["sobrenome"].GetString();
        float salario = employee["salario"].GetFloat();
        string area = employee["area"].GetString();

        Employee emp = {
            name,
            sobrenome,
            salario,
            area,
        };
        this->employeeBySalary[salario].push_back(emp);
        this->employeeByLastName[sobrenome].push_back(emp);
        this->employeeByArea[area].push_back(emp);
        this->salaryByArea[area].push_back(salario);
        this->salaryAcumulatorByArea[area] += salario;
        this->salaryAcumulator += salario;
        this->highSalaryByLastName[sobrenome] =
            (salario > this->highSalaryByLastName[sobrenome])
                ? salario
                : this->highSalaryByLastName[sobrenome];
        this->totalEmployeeByArea[area] += 1;
        this->totalEmployeeByLastName[sobrenome] += 1;
        this->totalEmployee += 1;
    }
    for (const auto& area : json["areas"].GetArray()) {
        string code = area["codigo"].GetString();
        string name = area["nome"].GetString();
        this->areaNameByCode[code] = name;
    }
};

// Queries
void Company::query1() {
    auto [min, max] = minmax_element(
        this->employeeBySalary.begin(), this->employeeBySalary.end(),
        [&](auto const& f1, auto const& f2) { return f1.first < f2.first; });

    for (const auto m : max->second) {
        string fullName = m.nome + " " + m.sobrenome;
        cout << setprecision(2) << fixed;
        cout << "global_max|" << fullName << "|" << m.salario << endl;
    }
    for (const auto m : min->second) {
        string fullName = m.nome + " " + m.sobrenome;
        cout << setprecision(2) << fixed;
        cout << "global_min|" << fullName << "|" << m.salario << endl;
    }
    cout << setprecision(2) << fixed;
    cout << "global_avg|" << this->salaryAcumulator / this->totalEmployee
         << endl;
    this->employeeBySalary.clear();
};

void Company::query2() {
    for (const auto m : this->employeeByArea) {
        auto [min, max] = minmax_element(m.second.begin(), m.second.end(),
                                         [&](auto const& f1, auto const& f2) {
                                             return f1.salario < f2.salario;
                                         });
        string areaName = this->areaNameByCode[m.first];
        double averageArea = this->salaryAcumulatorByArea[m.first] /
                             this->totalEmployeeByArea[m.first];
        for (const auto s : m.second) {
            if (s.salario == (*max).salario) {
                string fullName = s.nome + " " + s.sobrenome;
                cout << setprecision(2) << fixed;
                cout << "area_max|" << areaName << "|" << fullName << "|"
                     << s.salario << endl;
            } else if (s.salario == (*min).salario) {
                string fullName = s.nome + " " + s.sobrenome;
                cout << setprecision(2) << fixed;
                cout << "area_min|" << areaName << "|" << fullName << "|"
                     << s.salario << endl;
            }
        }
        cout << fixed << setprecision(2);
        cout << "area_avg|" << areaName << "|" << averageArea << endl;
    }
    this->employeeByArea.clear();
};

void Company::query3() {
    auto [min, max] = minmax_element(
        this->totalEmployeeByArea.begin(), this->totalEmployeeByArea.end(),
        [&](auto const& f1, auto const& f2) { return f1.second < f2.second; });

    for (auto m : this->totalEmployeeByArea) {
        string areaName = this->areaNameByCode[m.first];
        if (m.second == max->second) {
            cout << "most_employees|" << areaName << "|" << m.second << endl;
        } else if (m.second == min->second) {
            cout << "least_employees|" << areaName << "|" << m.second << endl;
        }
    }
};

void Company::query4() {
    for (const auto m : this->employeeByLastName) {
        int totalEmployeeByLastName = this->totalEmployeeByLastName[m.first];
        float highSalaryByLastName = this->highSalaryByLastName[m.first];
        if (totalEmployeeByLastName > 1) {
            for (auto ma : m.second) {
                if (ma.salario == highSalaryByLastName) {
                    string fullName = ma.nome + " " + ma.sobrenome;
                    cout << setprecision(2) << fixed;
                    cout << "last_name_max|" << ma.sobrenome << "|" << fullName
                         << "|" << ma.salario << endl;
                }
            }
        }
    }
};
