from flask import render_template, request, redirect, url_for, session
from DB import app, db, User
import re

@app.route('/')
@app.route('/login', methods = ['GET', 'POST'])
def login():
    msg = ''
    if request.method =='POST':
        username = request.form['username']
        password = request.form['password']
        userdata = User.query.filter_by(username=username).first()

        # print(userdata, file=sys.stderr)

        if userdata:
            if userdata.check_password(password):
                session['logged_in'] = True
                session['id'] = userdata.id
                session['username'] = userdata.username
                session['email'] = userdata.email
                return redirect(url_for('home'))
            else:
                msg = 'Incorrect username/password'
        else:
            msg = 'Incorrect username/password'
    return render_template('index.html', msg=msg)

@app.route('/logout')
def logout():
    # Remove session data.
    session.pop('logged_in', None)
    session.pop('id', None)
    session.pop('username', None)
    session.pop('email', None)
    return redirect(url_for('login'))

@app.route('/register', methods=['GET','POST'])
def register():
    msg = ''
    if request.method =='POST'and 'username' in request.form and 'password' in request.form and 'email' in request.form:
        username = request.form['username']
        password = request.form['password']
        email = request.form['email']
        data = User.query.filter_by(username=username, email=email).first()

        if data:
            msg = 'Account already exists!'
        elif not re.match(r'[^@]+@[^@]+\.[^@]+', email):
            msg = 'Invalid email address!'
        elif not re.match(r'[A-Za-z0-9]+', username):
            msg = 'Username must contain only characters and numbers!'
        elif not username or not password or not email:
            msg = 'Please fill out the form!'
        else:
            # Account doesnt exists and the form data is valid, now insert new account into accounts table
            msg = 'You have successfully registered!'
            user = User(username, email, password)
            db.session.add(user)
            db.session.commit()
            return render_template('index.html', msg=msg)
    elif request.method == 'POST':
        msg = 'Please fill out the form!'

    return render_template('register.html', msg=msg)

@app.route('/home')
def home():
    if 'logged_in' in session:
        return render_template('home.html',username=session['username'])

    return redirect(url_for('login'))

@app.route('/profile')
def profile():
    if 'logged_in' in session:
        user = User.query.filter_by(id = session['id']).first()
        return render_template('profile.html', user = user)
    return redirect(url_for('login'))


if __name__ == '__main__':
    app.debug = True
    app.run(port = '8080')