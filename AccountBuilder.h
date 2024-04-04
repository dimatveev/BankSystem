#pragma once
#include "Builder.h"

// билдер создает аккаунт не привязанный к банку. Билдер будет вызываться из функции создания аккаунта вннутри класса банка, там мы и определим ссылку на наш банк.

struct AccountBuilder : public Builder {
  static int account_id;
  std::string name;
  std::string surname;
  std::string address;
  std::string login;
  std::string password;
  int passport_num;
  void Reset();
  void SetName(std::string&);
  void SetSurname(std::string&);
  void SetAddress(std::string&);
  void SetPassportNum(int);
  void SetLogin(std::string&);
  void SetPassword(std::string&);
  Account GetAccount(Bank&);
};