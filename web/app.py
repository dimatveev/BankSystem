from flask import Flask, render_template, request, redirect, url_for
from flask_bootstrap import Bootstrap

app = Flask(__name__)
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

if __name__ == "__main__":
    app.run(debug=True)
