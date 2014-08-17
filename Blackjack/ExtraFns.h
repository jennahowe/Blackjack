#ifndef EXTRAFNS_H
#define EXTRAFNS_H

#include <iostream>
#include "HumanPlayer.h"
#include "GenericPlayer.h"

int MyRandom(int i);
bool DropOut(GenericPlayer player);
bool BankEmpty(GenericPlayer player);
char GetYNInput(std::string);

#endif