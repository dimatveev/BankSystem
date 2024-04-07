#pragma once
#include "Account.h"
#include "Bank.h"

struct Builder {
  virtual void Reset() = 0;
  virtual void SetName(std::string&) = 0;
  virtual void SetSurname(std::string&) = 0;
  virtual void SetAddress(std::string&) = 0;
  virtual void SetPassportNum(int) = 0;
  virtual void SetLogin(std::string&) = 0;
  virtual void SetPassword(std::string&) = 0;
  virtual Account GetAccount(Bank&) = 0;
};

