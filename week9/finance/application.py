import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


############################
##                        ##
##         sql cmd        ##
##                        ##
############################


# CREATE TABLE history (
# transaction_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
# symbol TEXT NOT NULL,
# name TEXT NOT NULL, ### added afterwards
# quote INTEGER NOT NULL,
# shares INTEGER NOT NULL,
# total INTEGER NOT NULL,
# time DATETIME NOT NULL,
# u_id INTEGER NOT NULL,
# FOREIGN KEY(u_id) REFERENCES users(id));

# ENTER IN finance.db IN ONE LINE
# CREATE TABLE history (transaction_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, symbol TEXT NOT NULL, quote INTEGER NOT NULL, shares INTEGER NOT NULL, total INTEGER NOT NULL, time DATETIME NOT NULL, u_id INTEGER NOT NULL, FOREIGN KEY(u_id) REFERENCES users(id));

# in case of rename
# ALTER TABLE hitsory
# RENAME TO history

# in case of
# ALTER TABLE table_name
# ADD column_name datatype;

    # RESULT

    # CREATE TABLE users (
    # id INTEGER,
    # username TEXT NOT NULL,
    # hash TEXT NOT NULL,
    # cash NUMERIC NOT NULL DEFAULT 10000.00,
    # PRIMARY KEY(id)
    # );

    # CREATE TABLE history (
    # transaction_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    # symbol TEXT NOT NULL,
    # name TEXT NOT NULL, ### added afterwards
    # quote INTEGER NOT NULL,
    # shares INTEGER NOT NULL,
    # total INTEGER NOT NULL,
    # time DATETIME NOT NULL,
    # u_id INTEGER NOT NULL,
    # FOREIGN KEY(u_id) REFERENCES users(id)
    # );

    # CREATE UNIQUE INDEX username ON users (username);
    # CREATE TABLE sqlite_sequence(name,seq);


############################
##                        ##
##         Index          ##
##                        ##
############################


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # transaction_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    # symbol TEXT NOT NULL,

    # quote INTEGER NOT NULL,
    # shares INTEGER NOT NULL,
    # total INTEGER NOT NULL,
    # time DATETIME NOT NULL,
    # u_id INTEGER NOT NULL,
    # FOREIGN KEY(u_id) REFERENCES users(id));

    portfolio = db.execute(
        "select symbol as symbol, sum(shares) as shares from history where u_id = (?) group by symbol", session["user_id"])

    stocks = []
    assets = 0

    for row in portfolio:
        # if stock.get("shares") != 0:
        stock = lookup(row.get("symbol"))
        quote = stock.get("price")

        # add name
        name = stock.get("name")
        row["name"] = name

        # print(quote)

        shares = row.get("shares")
        total = shares * quote

        row["quote"] = usd(quote)
        row["total"] = usd(total)

        row["change"] = stock.get("change")
        row["extchange"] = stock.get("extchange")

        assets += round(total, 2)
        if shares != 0:
            stocks.append(row)

    cash = db.execute("select cash from users where id = (?)", session['user_id'])
    balance = cash[0]['cash']

    equity = assets
    assets += balance

    return render_template("index.html", stocks=stocks, equity=usd(equity), balance=usd(balance), assets=usd(assets))


############################
##                        ##
##          Buy           ##
##                        ##
############################


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":

        # symbol err
        if not request.form.get("symbol"):
            return apology("must provide symbol")
        elif lookup(request.form.get("symbol")) == None:
            return apology("stock not found")

        # shares empty err
        if request.form.get("shares") == None:
            return apology("must provide number of shares")

        # set vars
        stock_temp = request.form.get("symbol")
        stock_temp = stock_temp.upper()
        stock = lookup(stock_temp)
        shares = request.form.get("shares")

        # shares format err
        if not shares.isdigit():
            return apology("shares should be a whole number")
        elif int(shares) <= 0:
            return apology("buy at least one share")

        shares = int(shares)
        quote = stock.get("price")
        # quote = int(quote)
        # quote = usd(quote)

        cash = db.execute("SELECT cash FROM users WHERE id = (?)", session["user_id"])
        balance = cash[0]["cash"]
        # balance = int(balance)
        # balance = usd(balance)

        # print(balance)

        time = datetime.now()
        total = shares * quote

        if balance < total:
            return apology("not enough energy")
        else:
            # transaction_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
            # symbol TEXT NOT NULL,
            # quote INTEGER NOT NULL,
            # shares INTEGER NOT NULL,
            # total INTEGER NOT NULL,
            # time DATETIME NOT NULL,
            # u_id INTEGER NOT NULL,
            # FOREIGN KEY(u_id) REFERENCES users(id));

            balance -= total
            balance = round(balance, 2)

            symbol = stock.get("symbol")
            name = stock.get("name")
            db.execute(
                "INSERT INTO history (symbol, name, quote, shares, total, time, u_id) VALUES(?, ?, ?, ?, ?, ?, ?)", symbol, name, quote, shares, total, time, session["user_id"])
            db.execute("UPDATE users SET cash = (?) WHERE id = (?)", balance, session["user_id"])

        flash("({}) Successfully bought {} shares of {} at a price of {}\nCurrent balance: {}".format(time, shares, symbol, quote, balance))
        return redirect("/")


###########################
##                       ##
##        History        ##
##                       ##
###########################


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

# transaction_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
# symbol TEXT NOT NULL,
# quote INTEGER NOT NULL,
# shares INTEGER NOT NULL,
# total INTEGER NOT NULL,
# time DATETIME NOT NULL,
# u_id INTEGER NOT NULL,
# FOREIGN KEY(u_id) REFERENCES users(id));

    history = db.execute(
        "SELECT symbol AS Symbol, name AS name, shares AS Shares, quote AS Quote, time AS Time FROM history WHERE u_id = (?)", session["user_id"])

    return render_template("history.html", history=history)


###########################
##                       ##
##         login         ##
##  (distribution code)  ##
##                       ##
###########################


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


############################
##                        ##
##         logout         ##
##  (distribution code)   ##
##                        ##
############################


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


############################
##                        ##
##         quote          ##
##                        ##
############################


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # Specification
    # When a user visits /quote via GET
    # render one of those templates,
    # inside of which should be an HTML form that submits to /quote via POST.

    if request.method == "GET":
        return render_template("quote.html")

    # In response to a POST
        # quote can render that second template,
        # embedding within it one or more values from lookup.

    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology("invalid symbol")
        else:
            # how lookup('symbol') works:
            # pass in a symbol (e.g., NFLX)
            # returns a dict containing 3 keys:
            # name, whose value is a str
            # price, whose value is a float
            # symbol, whose value is a str
            name = stock.get("name")
            quote = stock.get("price")
            symbol = stock.get("symbol")
            return render_template("quoted.html", name=name, quote=usd(quote), symbol=symbol)

    # return apology("TODO")


############################
##                        ##
##        register        ##
##                        ##
############################


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("no username")
        elif not request.form.get("password"):
            return apology("no password")
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("password confirmation does not match")
        else:
            if len(db.execute("SELECT * FROM users WHERE username = (?)", request.form.get("username"))) != 0:
                return apology("username already taken")
            else:
                username = request.form.get("username")
                password = request.form.get("password")
                password_hash = generate_password_hash(password)
                db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password_hash)

                rows = db.execute("SELECT * FROM users WHERE username = (?)", username)
                session["user_id"] = rows[0]["id"]

                flash("Registered successfully!")
                return redirect("/")

    return render_template("register.html")


############################
##                        ##
##          Sell          ##
##                        ##
############################


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "GET":
        stocks = []
        # lines = db.execute
        portfolio = db.execute(
            "select symbol as symbol, sum(shares) as shares from history where u_id = (?) group by symbol", session["user_id"])
        for stock in portfolio:
            stocks.append(stock.get("symbol"))
        return render_template("sell.html", stocks=stocks)

    if request.method == "POST":

        if not request.form.get("shares"):
            return apology("shares unstated")

        stock_tosell = request.form.get("symbol")
        shares_tosell = request.form.get("shares")

        shares_current = db.execute(
            "select sum(shares) as shares from history where symbol = (?) and u_id = (?)", stock_tosell, session['user_id'])
        shares_current = int(shares_current[0]["shares"])

        if not shares_tosell.isdigit() or int(shares_tosell) < 1:
            return apology("incorrect shares format")
        elif int(shares_tosell) > shares_current:
            return apology("selling more than is owned")

        shares_tosell = int(shares_tosell)
        # stock_tosell = request.form.get("symbol")

        cash = db.execute(
            "select cash from users where id = (?)", session['user_id'])
        balance = cash[0]['cash']

        stock_current = lookup(stock_tosell)
        quote = stock_current.get("price")

        total = shares_tosell * quote
        balance += total

        time = datetime.now()

        shares_tosell = 0 - shares_tosell

        # symbol TEXT NOT NULL,
        # quote INTEGER NOT NULL,
        # shares INTEGER NOT NULL,
        # total INTEGER NOT NULL,
        # time DATETIME NOT NULL,
        # u_id INTEGER NOT NULL,

        balance = round(balance, 2)
        # print(balance)

        db.execute("update users set cash = (?) where id = (?)", balance, session['user_id'])
        db.execute(
            "insert into history (symbol, quote, shares, total, time, u_id) values(?, ?, ?, ?, ?, ?)", stock_tosell, quote, shares_tosell, total, time, session['user_id'])

        flash("({}) Successfully sold {} shares of {} at a price of {}\nCurrent balance: {}".format(
            time, -shares_tosell, stock_tosell, quote, balance))
        return redirect("/")

    # return apology("TODO")


############################
##                        ##
##  (distribution code)   ##
##                        ##
############################

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


#