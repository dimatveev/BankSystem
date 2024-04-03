from flask import Flask, render_template, request, redirect, url_for, session
from flask_bootstrap import Bootstrap

app = Flask(__name__)
app.secret_key = '2517'
bootstrap = Bootstrap(app)

@app.route("/")
def index():
    return render_template("BankPage.html", h1="Главная страница банка")

@app.route("/about")
def get_page_about():
    return render_template("about.html", h1="О приложении")

@app.route("/create_account", methods=["GET", "POST"])
def create_account():
    if request.method == "POST":
        # Получение данных из формы
        first_name = request.form.get("firstName")
        last_name = request.form.get("lastName")
        passport_number = request.form.get("passport")
        phone_number = request.form.get("phone")
        username = request.form.get("username")
        password = request.form.get("password")

        #вызов внешней C++ функции
        
        # После создания аккаунта перенаправление на главную страницу
        return redirect(url_for("index"))
    
    # Если метод GET, отображаем форму для создания аккаунта
    return render_template("index.html")

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        # Здесь должна быть проверка имени пользователя и пароля
        username = request.form['username']
        # Если проверка успешна, сохраняем имя пользователя в сессию
        session['username'] = username
        # Перенаправляем на персональную страницу пользователя
        return redirect(url_for('user_page', username=username))
    # Если GET-запрос, отображаем страницу входа
    return render_template('login.html')

@app.route('/user/<username>')
def user_page(username):
    # Проверяем, залогинен ли пользователь и верен ли доступ к странице
    if 'username' in session and session['username'] == username:
        # Отображаем страницу пользователя
        return render_template('user_page.html', username=username)
    # Если нет доступа, перенаправляем на страницу входа
    return redirect(url_for('login'))

@app.route('/user/<username>/create_bill', methods=['GET', 'POST'])
def create_bill(username):
    # Логика создания счета
    pass

@app.route('/user/<username>/deposit', methods=['GET', 'POST'])
def deposit(username):
    # Логика пополнения баланса
    pass

@app.route('/user/<username>/transfer', methods=['GET', 'POST'])
def transfer(username):
    # Логика перевода денег
    pass

if __name__ == "__main__":
    app.run(debug=True)
