#include "RunSession.h"
#include <ctime>
#include <cstdlib>

int main() {
    srand(static_cast<unsigned int>(time(0))); 
    RunSession session;
    session.start(); 
    return 0;
}