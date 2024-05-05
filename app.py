from flask import Flask, render_template, jsonify, request, redirect, url_for, session, abort
from flask_bootstrap import Bootstrap
from typing import Dict, Any
import requests
from bank import Bank

app = Flask(__name__)
app.secret_key = '2517'
bootstrap = Bootstrap(app)
bank = Bank()

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

@app.route("/create_account", methods=["GET", "POST"])
def create_account() -> Any:
    if request.method == "POST":
        login = request.form.get("username")
        password = request.form.get("password")
        name = request.form.get("firstName")
        surname = request.form.get("lastName")
        address = request.form.get("address")
        passport_num = request.form.get("passport")

        bank.create_account(login, password, name, surname, address, passport_num)
        return redirect(url_for("index"))
    else:
        return render_template("index.html")

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        if bank.login_to(username, password):
            session['username'] = username
            return redirect(url_for('user_page', username=username))
        else:
            return abort(401, "Неверное имя пользователя или пароль")
    else:
        return render_template('login.html')

@app.route('/user/<username>')
def user_page(username):
    if 'username' in session and session['username'] == username:
        return render_template('user_page.html', username=username)
    return redirect(url_for('login'))

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
