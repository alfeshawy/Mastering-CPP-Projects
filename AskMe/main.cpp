#include <iostream>
#include "System.h"


int main() {
    System* system = System::getIstantSystem();

    system->start();
    system->ClearMemory();
}