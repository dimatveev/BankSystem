#pragma once
#include "Builder.h"
#include "Account.h"

struct Director {
  Builder Builder;
  Account& CreateAccount();
};