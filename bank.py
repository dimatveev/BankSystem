import csv
import hashlib
from bill import Bill
import account

# Константы для путей к файлам
BD_BILLS = "bd_bills.csv"
BD_ACCOUNTS = "bd_accounts.csv"
BD_HISTORY = "bd_history.csv"
# Функции для работы с файлами
def clear_bd():
    open('bd_bills.csv', 'w').close()
    open('bd_history.csv', 'w').close()
    open('bd_accounts.csv', 'w').close()
def add_account_in_file(account):
    with open('bd_accounts.csv', mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([account.account_id, account.login, account.password_hash, account.name, account.surname, account.address, account.passport_num])

def add_bill_in_file(bill, account_id):
    with open('bd_bills.csv', mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([account_id, bill.unique_id, bill.bill_type, bill.money])

def read_bd(file_path, n):
    with open(file_path, mode='r') as file:
        reader = csv.reader(file)
        return [row for row in reader]

def read_file_bd_bills():
    ans = read_bd('bd_bills.csv', 4)
    open('bd_bills.csv', 'w').close()
    return ans

def read_file_bd_accounts():
    return read_bd('bd_accounts.csv', 7)

def read_file_bd_history():
    return read_bd('bd_history.csv', 5)

# Добавление операции в историю
def add_operation_to_history(account_id, oper_type, bill_from, bill_to, amount_of_money):
    with open('bd_history.csv', mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([account_id, oper_type, bill_from, bill_to, amount_of_money])

# Структура банка
class Bank:
    def __init__(self):
        with open('id_for_accounts.csv', mode='r') as file_acc:
            reader = csv.reader(file_acc)
            self.id_for_accounts = int(next(reader)[0])
        with open('id_for_bills.csv', mode='r') as file_bills:
            reader = csv.reader(file_bills)
            self.id_for_bills = int(next(reader)[0])  # Использование next для получения первой строки и преобразование в int

        self.name = "TegridyBank"
        self.active_account_id = -1
    
    def update_id_for_accounts(self):
        with open('id_for_accounts.csv', mode='w') as file_acc:
            writer = csv.writer(file_acc)
            self.id_for_accounts = str(int(self.id_for_accounts) + 1)
            writer.writerow([self.id_for_accounts])

    def update_id_for_bills(self):
        with open('id_for_bills.csv', mode='w') as file_bills:
            writer = csv.writer(file_bills)
            self.id_for_bills = str(int(self.id_for_bills) + 1)
            writer.writerow([self.id_for_bills])        

    def create_account(self, login, password, name, surname, address, passport_num):
        newaccount = account.Account(self.id_for_accounts, login, hashlib.sha256(password.encode()).hexdigest(), name, surname, address, passport_num)
        accs = read_file_bd_accounts()
        for one_acc in accs:
            if login == str(one_acc[1]):
                return False
        add_account_in_file(newaccount)
        self.update_id_for_accounts()
        return True

    def login_to(self, login, password):
        bd_accounts = read_file_bd_accounts()
        for account in bd_accounts:
            if account[1] == login:
                self.active_account_id = account[0]
                return hashlib.sha256(password.encode()).hexdigest() == account[2]
        return False

    def create_bill(self, bill_type, account_id):
        if bill_type == 'credit' or bill_type == 'debit' or bill_type == 'deposit':
            newbill = Bill(self.id_for_bills, bill_type, 0)
            add_bill_in_file(newbill, account_id)
            self.update_id_for_bills()
        else:
            print("CreateBill error")
            return False
        return True

    def check_bills(self, account_id):
        bills = read_file_bd_bills()
        print("bill_id, type, amount")
        for bill in bills:
            if bill[0] == str(account_id):
                print(f"{bill[1]} {bill[2]} ${bill[3]}") # нужно изменить чтоб выводил пользователю
            newbill = Bill(bill[1], bill[2], bill[3])
            add_bill_in_file(newbill, bill[0])
        pass

    def check_history(self, account_id):
        transactions = read_file_bd_history()
        print("История операций")
        for transaction in transactions:
            if transaction[0] == str(account_id):
                print(f"{transaction[1]} {transaction[2]} {transaction[3]} {transaction[4]}") # нужно изменить чтоб выводил пользователю
        print("Конец")
        pass

    def add_money(self, account_id, bill_to, amount_of_money):
        if amount_of_money < 0:
            return "Некорректная сумма"
        found = False
        bills = read_file_bd_bills()
        for bill in bills:
            if bill[1] == str(bill_to):
                found = True
                bill[3] = str(int(float(bill[3])) + amount_of_money)
            newbill = Bill(bill[1], bill[2], bill[3])
            add_bill_in_file(newbill, bill[0])
        add_operation_to_history(account_id, "Add money", "", bill_to, "+" + str(amount_of_money))
        return found


    def withdraw_money(self, account_id, bill_from, amount_of_money):
        if amount_of_money < 0:
            return False
        bills = read_file_bd_bills()
        isfound = 0
        for bill in bills:
            if bill[1] == str(bill_from):
                isfound = 1
                if (int(float(bill[3])) < amount_of_money):
                    isfound = -1
                else:
                    bill[3] = str(int(float(bill[3])) - amount_of_money)
            newbill = Bill(bill[1], bill[2], bill[3])
            add_bill_in_file(newbill, bill[0])
        add_operation_to_history(str(account_id), "Withdraw money", "", "from " + str(bill_from), "-" + str(amount_of_money))
        return isfound

    def transaction(self, account_id_from, account_id_to, bill_from, bill_to, amount_of_money):
        if amount_of_money < 0:
            return "Некорректная сумма"
        bills = read_file_bd_bills()
        isfound = 404
        if bills:
            for bill in bills:
                if len(bill) >= 4:  # Check if bill has enough elements
                    if bill[1] == str(bill_from) and bill[0] == str(account_id_from):
                        isfound = 1
                        if (int(float(bill[3])) < amount_of_money):
                            isfound = -1
                        else:
                            bill[3] = str(int(float(bill[3])) - amount_of_money)
                    newbill = Bill(bill[1], bill[2], bill[3])
                    add_bill_in_file(newbill, bill[0])
        bills = read_file_bd_bills()
        if isfound == 1:
            isfound = 0
            for bill in bills:
                if bill[1] == str(bill_to):
                    isfound = 1
                    bill[3] = str(int(float(bill[3])) + amount_of_money)
                    add_operation_to_history(str(account_id_to), "transaction", "", "to " + str(bill_to), "+" + str(amount_of_money))
                    add_operation_to_history(str(account_id_from), "transaction", "", "from " + str(bill_from), "+" + str(amount_of_money))
                newbill = Bill(bill[1], bill[2], bill[3])
                add_bill_in_file(newbill, bill[0])
        elif isfound == 404:
            for bill in bills:
                newbill = Bill(bill[1], bill[2], bill[3])
                add_bill_in_file(newbill, bill[0])
        else:
            for bill in bills:
                if bill[1] == str(bill_from):
                        bill[3] = str(int(float(bill[3])) + amount_of_money)
                newbill = Bill(bill[1], bill[2], bill[3])
                add_bill_in_file(newbill, bill[0])
        return isfound

# Тестирование
if __name__ == "__main__":
    '''
    bank = Bank()
    clear_bd()
    bank.create_account("Paxan", "22848", "Pavel", "Dranov", "Pervomayskaya30k7", 224423)
    bank.create_account("DimaZ", "43348", "Dima", "Matveev", "Pervomayskaya30k7", 224424)
    bank.create_bill("deposit", 0)
    bank.create_bill("credit", 228)
    bank.create_bill("debit", 1)
    bank.add_money(1, 0, 1000)
    bank.add_money(1, 0, 1500)
    bank.add_money(0, 0, 1000)
    bank.transaction(0, 1, 0, 1, 300)
    bank.withdraw_money(228, 1, 290)
    bank.check_bills(0)
    bank.check_history(1)
    '''
