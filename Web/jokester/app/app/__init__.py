
from flask import Flask


UPLOAD_FOLDER = '/tmp/pdfcache'
ALLOWED_EXTENSIONS = {'pdf'}

app = Flask(__name__)
app.secret_key = "asdkasjlflakdjssad"
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER


from app import routes