from flask import Flask, render_template, jsonify, request, request, redirect, url_for, session, abort
from flask_bootstrap import Bootstrap
from typing import Dict, Any
import requests

app: Flask = Flask(__name__)
app.secret_key = '2517'
bootstrap: Bootstrap = Bootstrap(app)

@app.route("/")
def index() -> str:
    return render_template("BankPage.html", h1="Главная страница банка")

@app.route("/about")
def get_page_about() -> str:
    return render_template("about.html", h1="О приложении")

@app.route("/customs")
def customs() -> str:
    return render_template("customs.html", h1="Наши услуги")

@app.route("/contacts")
def contacts() -> str:
    return render_template("contacts.html", h1="Контакты")

def send_created_account(user_data: Dict[str, Any]) -> requests.Response:

    # Отправляет данные пользователя на C++ сервер для создания аккаунта.

    # :param user_data: Словарь с данными пользователя.
    # :return: Ответ от сервера.

    url = 'http://localhost:8888/create_account'
    # Отправка POST-запроса на сервер C++
    response = requests.post(url, json=user_data)
    return response

@app.route("/create_account", methods=["GET", "POST"])
def create_account() -> Any:
    if request.method == "POST":
        # Собираем данные пользователя из формы
        user_data: Dict[str, Any] = {
            "firstName": request.form.get("firstName"),
            "lastName": request.form.get("lastName"),
            "passport": request.form.get("passport"),
            "phone": request.form.get("phone"),
            "username": request.form.get("username"),
            "password": request.form.get("password")
        }

        # Отправляем данные пользователя на сервер C++
        response = send_created_account(user_data)

        # Проверяем статус ответа от сервера
        if response.status_code == 200:
            return redirect(url_for("index"))
        else:
            abort(400, "Ошибка при создании аккаунта")

    return render_template("index.html")

def send_login(login_data: Dict[str, str]) -> requests.Response:
    url = 'http://localhost:8888/login'
    response = requests.post(url, json=login_data)
    return response

@app.route('/login', methods=['GET', 'POST'])
def login() -> Any:
    if request.method == 'POST':
        login_data: Dict[str, str] = {
            "username": request.form['username'],
            "password": request.form['password']
        }

        response = send_login(login_data)

        if response.status_code == 200:
            session['username'] = login_data['username']
            return redirect(url_for('user_page', username=login_data['username']))
        else:
            abort(401, "Неверное имя пользователя или пароль")

    return render_template('login.html')

def send_bill(bill_data: Dict[str, str]) -> requests.Response:
    url = 'http://localhost:8888/create_bill'
    response = requests.post(url, json=bill_data)
    return response

@app.route('/user/<username>/create_bill', methods=['GET', 'POST'])
def create_bill(username: str) -> Any:
    if request.method == 'POST':
        bill_data: Dict[str, str] = {
            "username": username,
            "bill_type": request.form.get('bill_type')
        }

        # Отправляем данные о счете через выделенную функцию
        response = send_bill(bill_data)

        if response.status_code == 200:
            return redirect(url_for('user_page', username=username))
        else:
            abort(400, "Ошибка при создании счета")

    return render_template('create_bill.html', username=username)

def send_money(money_data: Dict[str, Any]) -> requests.Response:
    url = 'http://localhost:8888/add_money'
    response = requests.post(url, json=money_data)
    return response

@app.route('/user/<username>/add_money', methods=['GET', 'POST'])
def add_money(username: str) -> Any:
    if request.method == 'POST':
        money_data: Dict[str, Any] = {
            "username": username,
            "bill_to": request.form.get('bill_to'),
            "amount": request.form.get('amount')
        }

        # Отправляем данные о добавлении денег через выделенную функцию
        response = send_money(money_data)

        if response.status_code == 200:
            return redirect(url_for('user_page', username=username))
        else:
            abort(400, "Ошибка при добавлении денег")

    return render_template('add_money.html', username=username)

def send_transaction(transaction_data: Dict[str, Any]) -> requests.Response:
    url = 'http://localhost:8888/transaction'
    response = requests.post(url, json=transaction_data)
    return response

@app.route('/user/<username>/transaction', methods=['GET', 'POST'])
def transaction(username: str) -> Any:
    if request.method == 'POST':
        transaction_data: Dict[str, Any] = {
            "username": username,
            "bill_from": request.form.get('bill_from'),
            "bill_to": request.form.get('bill_to'),
            "amount": request.form.get('amount')
        }

        # Отправляем данные транзакции через выделенную функцию
        response = send_transaction(transaction_data)

        if response.status_code == 200:
            return redirect(url_for('user_page', username=username))
        else:
            abort(400, "Ошибка при выполнении транзакции")

    return render_template('transaction.html', username=username)

if __name__ == "__main__":
    app.run(debug=True)
