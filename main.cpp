#include "runner.h"
#include "server.h"
#include <memory>

int main() {
    Runner().run(Server().create());
    return 0;
}

