import os

from flask import render_template, request, flash, redirect, url_for, send_from_directory, current_app
from werkzeug.utils import secure_filename

from app import app
from app.pdfmaster import PDFReverser
from app import ALLOWED_EXTENSIONS


def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        # check if the post request has the file part
        if 'file' not in request.files:
            flash('No file part', 'error')
            return render_template('index.html')
        file = request.files['file']
        # If the user does not select a file, the browser submits an
        # empty file without a filename.
        if file.filename == '':
            flash('No selected file','error')
            return render_template('index.html')
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            path = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            file.save(path)
            try:
                pdfmaster = PDFReverser(path)
            except:
                flash('Error', 'error')
                return render_template('index.html')
            else:
                return render_template('index.html', pdf_version=pdfmaster.version(), page_count=pdfmaster.page_count(),
                                                     metadata=pdfmaster.meta_data(), filename=pdfmaster.reverse())
    return render_template('index.html')

@app.route('/uploads/<name>')
def download_file(name):
    return send_from_directory(app.config["UPLOAD_FOLDER"], name, as_attachment=True)
    