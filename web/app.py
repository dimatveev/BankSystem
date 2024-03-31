from flask import Flask, render_template, request, redirect, url_for
from flask_bootstrap import Bootstrap  # Используйте Bootstrap здесь

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
        username = request.form.get("username")
        password = request.form.get("password")
        # Здесь будет вызов функции для создания аккаунта
        # Например, вызов функции C++ или другой логики
        return redirect(url_for("index"))
    return render_template("index.html")

if __name__ == "__main__":
    app.run(debug=True)
