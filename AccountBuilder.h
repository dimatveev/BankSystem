#pragma once
#include "Builder.h"

struct AccountBuilder : public Builder {
  void Reset() override;
  void SetName() override;
  void SetSurname() override;
  void SetAddress() override;
  void SetPassportNum() override;
  void SetLogin() override;
  void SetPassword() override;
  Account& GetAccount() override;
};