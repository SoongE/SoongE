from flask import Flask, render_template
from flask_sqlalchemy import SQLAlchemy
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)

app.config['SECRET_KEY'] = 'tHe secret code'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///site.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db = SQLAlchemy(app)

class User(db.Model):
    __table_name__ = 'user' #데이터베이스 테이블 이름을 명시적으로 정의
    __table_args__ = {'mysql_collate':'utf8_general_ci'} #DB에서 한글 인식을 못하는 경우 가능하게 만듬.

    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(100), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)
    password = db.Column(db.String(100), unique=True, nullable=False)

    def __init__(self, username, email, password, **kwargs):
        self.username = username
        self.email = email
        self.set_password(password)

    def set_password(self, password):
        self.password = generate_password_hash(password)

    def check_password(self, password):
        return check_password_hash(self.password, password)

    def __repr__(self):
        return f'<User: {self.id}, {self.username}, {self.email}>'

    '''
    DB에서 query한 결과를 받아올 때 QueryObject 타입으로 리턴된다. 이를 dict 타입으로 만들어주는 함수.
    '''
    def as_dict(self):
        return {x.name: getattr(self, x.name) for x in self.__table__.columns}
