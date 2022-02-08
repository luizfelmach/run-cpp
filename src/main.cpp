#include "../includes/headers.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    Company company(argv[1]);

    thread getQuery1(&Company::getQuery1, ref(company));
    thread getAreaNameByCode(&Company::getAreaNameByCode, ref(company));
    thread getQuery2(&Company::getQuery2, ref(company));
    thread getQuery4(&Company::getQuery4, ref(company));

    getQuery1.join();
    company.query1();

    getQuery2.join();
    getAreaNameByCode.join();
    company.query2();

    company.query3();

    getQuery4.join();
    company.query4();
    return 0;
}