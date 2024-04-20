from flask import Flask, render_template, request, redirect, url_for, session, abort
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

@app.route("/create_account", methods=["GET", "POST"])
def create_account() -> Any:
    if request.method == "POST":
        user_data: Dict[str, Any] = {
            "firstName": request.form.get("firstName"),
            "lastName": request.form.get("lastName"),
            "passport": request.form.get("passport"),
            "phone": request.form.get("phone"),
            "username": request.form.get("username"),
            "password": request.form.get("password")
        }

        response: requests.Response = requests.post('http://server_cpp/create_account', json=user_data)
        
        if response.status_code == 200:
            return redirect(url_for("index"))
        else:
            abort(400, "Ошибка при создании аккаунта")

    return render_template("index.html")

@app.route('/login', methods=['GET', 'POST'])
def login() -> Any:
    if request.method == 'POST':
        login_data: Dict[str, str] = {
            "username": request.form['username'],
            "password": request.form['password']
        }

        response: requests.Response = requests.post('http://server_cpp/login', json=login_data)
        
        if response.status_code == 200:
            session['username'] = login_data['username']
            return redirect(url_for('user_page', username=login_data['username']))
        else:
            abort(401, "Неверное имя пользователя или пароль")

    return render_template('login.html')

@app.route('/user/<username>/create_bill', methods=['GET', 'POST'])
def create_bill(username: str) -> Any:
    if request.method == 'POST':
        bill_data: Dict[str, str] = {
            "username": username,
            "bill_type": request.form.get('bill_type')
        }

        response: requests.Response = requests.post('http://server_cpp/create_bill', json=bill_data)
        
        if response.status_code == 200:
            return redirect(url_for('user_page', username=username))
        else:
            abort(400, "Ошибка при создании счета")

    return render_template('create_bill.html', username=username)

@app.route('/user/<username>/add_money', methods=['GET', 'POST'])
def add_money(username: str) -> Any:
    if request.method == 'POST':
        money_data: Dict[str, Any] = {
            "username": username,
            "bill_to": request.form.get('bill_to'),
            "amount": request.form.get('amount')
        }

        response: requests.Response = requests.post('http://server_cpp/add_money', json=money_data)
        
        if response.status_code == 200:
            return redirect(url_for('user_page', username=username))
        else:
            abort(400, "Ошибка при добавлении денег")

    return render_template('add_money.html', username=username)

@app.route('/user/<username>/transaction', methods=['GET', 'POST'])
def transaction(username: str) -> Any:
    if request.method == 'POST':
        transaction_data: Dict[str, Any] = {
            "username": username,
            "bill_from": request.form.get('bill_from'),
            "bill_to": request.form.get('bill_to'),
            "amount": request.form.get('amount')
        }

        response: requests.Response = requests.post('http://server_cpp/transaction', json=transaction_data)
        
        if response.status_code == 200:
            return redirect(url_for('user_page', username=username))
        else:
            abort(400, "Ошибка при выполнении транзакции")

    return render_template('transaction.html', username=username)

if __name__ == "__main__":
    app.run(debug=True)
