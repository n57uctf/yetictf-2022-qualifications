from flask import Flask, render_template, request
import config
import requests

app = Flask(__name__)
app.secret_key = config.SECRET['KEY']


class InfoText:
	def __init__(self,info):
		self.info = info

def get_text(url,info_obj):
	try:
		r = requests.get(url)
		url = r.text
		url = url.format(info_obj = info_obj)
	except Exception as e:
		url=e
	return url

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/request", methods=['GET', 'POST'])
def getinfo():
	if request.method == 'POST':
		url = request.form.get('url')
		text = InfoText(str(url))
		result = get_text(text.info,info_obj=text)
		return render_template("index.html", result=result)
	else:
		return render_template("index.html")


@app.route("/flag")
def flag():
	token = request.args.get('token')
	if token == None:
		return render_template('index.html', result="Access denied, send valid token")
	elif token == app.secret_key or 'c10935eeb7626e2a53ada94e2a21c617' and request.remote_addr == '127.0.0.1':
		return render_template('flag.html')


if __name__ == '__main__':
        app.run(host='0.0.0.0',port=9999,debug=False)