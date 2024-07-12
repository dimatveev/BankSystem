# Структура для хранения информации о счетах
class Account:
    def __init__(self, account_id, login, password_hash, name, surname, address, passport_num):
        self.account_id = account_id
        self.login = login
        self.password_hash = password_hash
        self.name = name
        self.surname = surname
        self.address = address
        self.passport_num = passport_num