#pragma once
#include "Account.h"

struct Builder {
  virtual void Reset() = 0;
  virtual void SetName() = 0;
  virtual void SetSurname() = 0;
  virtual void SetAddress() = 0;
  virtual void SetPassportNum() = 0;
  virtual void SetLogin() = 0;
  virtual void SetPassword() = 0;
  virtual Account& GetAccount() = 0;
};

