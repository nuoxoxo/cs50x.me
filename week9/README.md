Specification

##

`register`
```
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

`quote`
```

```
