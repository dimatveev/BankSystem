# Структура для хранения информации о счетах
class Bill:
    def __init__(self, unique_id, bill_type, money):
        self.unique_id = unique_id
        self.bill_type = bill_type
        self.money = money