#include <cstdint>
#include "testlib.h"
#include <cstdbool>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

int f(unsigned int a, unsigned int b) {
	return a * b == 2308508647;
}

int main(int argc, char *argv[]) {
    registerChecker("checker-test", argc, argv);
    stringstream s(ouf.readLine());
    unsigned int a, b;
    s >> a >> b;
    if (f(a, b)) {
        quit(_ok, "shash");
    } else {
        quit(_wa, "sham");
    }
}