#include <chrono>

#include "../includes/headers.hpp"

using namespace std::chrono;

using namespace std;

int main(int argc, char *argv[]) {
    Company company(argv[1]);
    company.query1();
    company.query2();
    company.query3();
    company.query4();
    return 0;
}