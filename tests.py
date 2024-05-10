from bank import Bank
import pytest
import csv

bank = Bank()
bank.create_account('Starboy', '1234', 'Atremy', 'Bobkov', 'Pervomayskaya 30k2', '-')

# функция собирающая информацию об аккаунте
def account_info(acc_id):
  with open('bd_accounts.csv', mode='r') as file:
        reader = csv.reader(file)
        accounts = [row for row in reader]
        for acc in accounts:
           if acc[0] == acc_id:
              return acc

# тестирование регистрации и входа в аккаунт
def test_create_account_err():
  bank.create_account('Starboy', '1234', 'Atremy', 'Bobkov', 'Pervomayskaya 30k2', '-')
  assert not bank.create_account('Starboy', '1234', 'Nikolay', 'Batkovich', 'Pervomayskaya 30k2', '-')

def test_login_to_ok():
  assert bank.login_to('Starboy', '1234')

def test_login_to_wrong_passw():
  assert not bank.login_to('Starboy', '4321')

def test_login_to_log_not_found():
  assert not bank.login_to('Badboy', '1234')

#def test_create_account_acc_info():
#  id = bank.id_for_accounts
#  bank.create_account('Bigboy', '1234', 'Atremy', 'Bobkov', 'Pervomayskaya 30k2', '-')
#  flag = True
#  acc = account_info(id)
#  assert acc[1] == 'Bigboy'