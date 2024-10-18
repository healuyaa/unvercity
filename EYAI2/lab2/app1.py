from flask import Flask, render_template, request, redirect, url_for, flash, session
from werkzeug.utils import secure_filename
from summa import keywords
from summa.summarizer import summarize
from docx import Document
import re
import os
from flask_session import Session
app = Flask(__name__)
app.secret_key = 'your_secret_key'

app.config['SESSION_TYPE'] = 'filesystem'
app.config['SESSION_FILE_DIR'] = os.path.join(app.root_path, 'flask_session')
app.config['SESSION_PERMANENT'] = False
Session(app)

app.config['UPLOAD_FOLDER'] = 'lab2/uploads'
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024

ALLOWED_EXTENSIONS = {'docx'}

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def extract_text_from_docx(file_path):
    doc = Document(file_path)
    full_text = []
    for paragraph in doc.paragraphs:
        full_text.append(paragraph.text)
    return '\n'.join(full_text)

def clean_text(text):
    text = re.sub(r'\d+', '', text)
    text = re.sub(r'[^\w\s]', '', text)

    stopwords = ['в', 'на', 'не', 'но', 'он', 'же', 'с', 'по', 'со', 'при', 
                'а', 'ли', 'за', 'от', 'до', 'да', 'этом', 'то', 'для', 
                'из', 'под', 'к', 'у', 'о', 'об', 'и', 'или', 'как', 
                'что', 'это', 'их', 'ее', 'её', 'его']
    words = text.split()
    filtered_words = [word for word in words if word.lower() not in stopwords]

    return ' '.join(filtered_words)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        if 'file' not in request.files:
            flash('Нет файла для загрузки')
            return redirect(request.url)
        file = request.files['file']
        if file.filename == '':
            flash('Файл не выбран')
            return redirect(request.url)
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file_path = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            file.save(file_path)
            text = extract_text_from_docx(file_path)
            session['text'] = text
            return redirect(url_for('index'))
        else:
            flash('Разрешены только файлы .docx')
            return redirect(request.url)
    
    text = session.get('text', '')
    return render_template('index.html', text=text)

@app.route('/summarize', methods=['POST'])
def summarize_text():
    text = session.get('text', '').strip()
    if text:
        summarized = summarize(text)
        if summarized:
            session['text'] = summarized
            flash('Текст успешно сжат!')
        else:
            flash('Не удалось сжать текст. Попробуйте с другим текстом.')
    else:
        flash('Нет текста для обработки!')
    return redirect(url_for('index'))

@app.route('/keywords', methods=['POST'])
def extract_keywords_route():
    text = session.get('text', '').strip()
    if text:
        cleaned_text = clean_text(text)
        kws = keywords.keywords(cleaned_text, words=20)
        session['text'] = kws
        flash('Ключевые слова успешно извлечены!')
    else:
        flash('Нет текста для обработки!')
    return redirect(url_for('index'))

if __name__ == '__main__':
    if not os.path.exists(app.config['UPLOAD_FOLDER']):
        os.makedirs(app.config['UPLOAD_FOLDER'])
    if not os.path.exists(app.config['SESSION_FILE_DIR']):
        os.makedirs(app.config['SESSION_FILE_DIR'])
    app.run(debug=True)
