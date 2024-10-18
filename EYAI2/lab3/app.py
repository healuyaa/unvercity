from flask import Flask, render_template, request, redirect, url_for, flash, send_file
from deep_translator import GoogleTranslator
import os
import nltk
import spacy

nltk.download('punkt')
nlp = spacy.load("en_core_web_sm")

app = Flask(__name__)
app.secret_key = 'your_secret_key'
app.config['UPLOAD_FOLDER'] = 'lab3/uploads'
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() == 'txt'

def translate_text(input_text):
    translator = GoogleTranslator(source='en', target='ru')
    return translator.translate(input_text)

def count_words(input_text):
    words = nltk.word_tokenize(input_text)
    words = [word for word in words if word.lower()]
    return len(words)

def analyze_morphology(input_text):
    doc = nlp(input_text)
    return [(token.text, token.lemma_, token.pos_) for token in doc]

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        if 'file' not in request.files:
            flash('Нет файла для анализа!')
            return redirect(request.url)
        
        file = request.files['file']
        if file.filename == '':
            flash('Файл не выбран!')
            return redirect(request.url)
        
        if file and allowed_file(file.filename):
            filename = file.filename
            file_path = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            file.save(file_path)
            
            with open(file_path, 'r', encoding='utf-8') as f:
                input_text = f.read()
                
                word_count = count_words(input_text)
                morphology_info = analyze_morphology(input_text)
                translation = translate_text(input_text)
                
                # Сохраним результаты анализа
                analysis_file_path = os.path.join(app.config['UPLOAD_FOLDER'], 'analysis_results.txt')
                with open(analysis_file_path, 'w', encoding='utf-8') as output_file:
                    output_file.write(f"Количество слов: {word_count}\n")
                    output_file.write("Морфологический анализ:\n")
                    for token_info in morphology_info:
                        token, lemma, pos = token_info
                        output_file.write(f"{token} ({lemma}, {pos})\n")
                
                # Сохраним перевод
                translation_file_path = os.path.join(app.config['UPLOAD_FOLDER'], 'translation_results.txt')
                with open(translation_file_path, 'w', encoding='utf-8') as output_file:
                    output_file.write(translation)
                
                return render_template('index.html', word_count=word_count, morphology_info=morphology_info, translation=translation)
    
    return render_template('index.html')

if __name__ == '__main__':
    if not os.path.exists(app.config['UPLOAD_FOLDER']):
        os.makedirs(app.config['UPLOAD_FOLDER'])
    app.run(debug=True)
