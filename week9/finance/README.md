## SPECIFICATION

REGISTER
```py
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("Please type in your Username.")

        elif not request.form.get("password"):
            return apology("Password is required.")

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords don't match.")

        else:
        
            ## INSERT the new user into users: 
            ## store a hash of the password, not the password itself
            ## Hash the user’s password with generate_password_hash
        
            #check_username = len(db.execute("SELECT * FROM users WHERE username = {username}", username=request.form.get("username")))
            if len(db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))) != 0:
                return apology("This username already taken. Please choose another one.")
            else:
                password_hash = generate_password_hash(request.form.get("password"))
                uid = db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), password_hash)
                session["user_id"] = uid
                flash("registered successfully.")
                return redirect("/")
    return render_template("register.html")
```
##
QUOTE
```py
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":
        ## HELPER Function
        ## lookup
        ## pass in a symbol (e.g., NFLX)
        ## returns a stock quote in form of a dict containing 3 keys:
        ## name, whose value is a str
        ## price, whose value is a float
        ## symbol, whose value is a str
        quote = lookup(request.form.get("symbol"))

        if quote == None:
            return apology("Company symbol not found.")
        else:
            symbol = quote.get("symbol")
            price = quote.get("price")
            return render_template("quoted.html", symbol=synbol, price=usd(price))
```
