from flask import Flask, render_template, request, redirect, url_for, flash, session
from werkzeug.utils import secure_filename
from docx import Document
import re
import os
from flask_session import Session
from transformers import MBartForConditionalGeneration, MBart50TokenizerFast
import torch
import logging

logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)

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

def extract_text_from_docx(docx_file):
    try:
        doc = Document(docx_file)
        full_text = []
        for paragraph in doc.paragraphs:
            full_text.append(paragraph.text)
        return '\n'.join(full_text)
    except Exception as e:
        logger.error(f"Ошибка при извлечении текста из файла {docx_file}: {e}")
        return ""

try:
    logger.info("Загрузка модели MBart...")
    model_name = "facebook/mbart-large-50-many-to-many-mmt"
    model = MBartForConditionalGeneration.from_pretrained(model_name)
    tokenizer = MBart50TokenizerFast.from_pretrained(model_name)
    tokenizer.src_lang = "ru_RU"
    logger.info("Модель MBart успешно загружена.")
except Exception as e:
    logger.error(f"Ошибка при загрузке модели MBart: {e}")
    model = None
    tokenizer = None

def generate_ml_summary(text):
    if not model or not tokenizer:
        logger.error("Модель или токенизатор не загружены.")
        return "Ошибка: Модель не загружена."
    try:
        inputs = tokenizer.encode(text, return_tensors="pt", max_length=1024, truncation=True)
        summary_ids = model.generate(
            inputs, max_length=250, min_length=40, 
            num_beams=5, early_stopping=True, 
            forced_bos_token_id=tokenizer.lang_code_to_id["ru_RU"]
        )
        summary = tokenizer.decode(summary_ids[0], skip_special_tokens=True)
        return summary
    except Exception as e:
        logger.error(f"Ошибка при генерации реферата: {e}")
        return f"Ошибка при создании реферата: {e}"

@app.route('/', methods=['GET', 'POST'])
def index_():
    if request.method == 'POST':
        logger.debug("Получен POST запрос для загрузки файла.")
        if 'file' not in request.files:
            flash('Нет файла для загрузки')
            logger.warning("Нет файла в запросе.")
            return redirect(request.url)
        file = request.files['file']
        if file.filename == '':
            flash('Файл не выбран')
            logger.warning("Файл не выбран.")
            return redirect(request.url)
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file_path = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            try:
                file.save(file_path)
                logger.info(f"Файл {filename} успешно сохранён.")
                text = extract_text_from_docx(file_path)
                if text:
                    session['original_text'] = text
                    session['summary_text'] = ''
                    flash('Файл успешно загружен и текст извлечён!')
                    logger.info("Текст из файла успешно извлечён и сохранён в сессии.")
                else:
                    flash('Не удалось извлечь текст из файла.')
                    logger.warning("Текст из файла пуст или не был извлечён.")
            except Exception as e:
                flash(f"Ошибка при сохранении файла: {e}")
                logger.error(f"Ошибка при сохранении файла {filename}: {e}")
            return redirect(url_for('index_'))
        else:
            flash('Разрешены только файлы .docx')
            logger.warning("Загружен файл с недопустимым расширением.")
            return redirect(request.url)
    
    original_text = session.get('original_text', '')
    summary_text = session.get('summary_text', '')
    logger.debug("Отправка шаблона с текущими данными.")
    return render_template('index_.html', original_text=original_text, summary_text=summary_text)

@app.route('/summarize', methods=['POST'])
def summarize_text():
    logger.debug("Получен запрос на создание реферата.")
    text = session.get('original_text', '').strip()
    if text:
        try:
            logger.info("Начинается генерация реферата.")
            summary = generate_ml_summary(text)
            session['summary_text'] = summary
            flash('Текст успешно сжат!')
            logger.info("Резюме успешно создано и сохранено в сессии.")
        except Exception as e:
            flash(f"Ошибка при создании реферата: {e}")
            logger.error(f"Ошибка при создании реферата: {e}")
    else:
        flash('Нет текста для обработки!')
        logger.warning("Попытка создать резюме без исходного текста.")
    return redirect(url_for('index_'))

if __name__ == '__main__':
    if not os.path.exists(app.config['UPLOAD_FOLDER']):
        os.makedirs(app.config['UPLOAD_FOLDER'])
        logger.info(f"Создана папка для загрузок: {app.config['UPLOAD_FOLDER']}")
    if not os.path.exists(app.config['SESSION_FILE_DIR']):
        os.makedirs(app.config['SESSION_FILE_DIR'])
        logger.info(f"Создана папка для сессий: {app.config['SESSION_FILE_DIR']}")
    app.run(debug=True)
