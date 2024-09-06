from flask import Flask, request, render_template
from preprocess import preprocess_text
from search import extract_keywords, search_documents
import os

app = Flask(__name__)

# Путь к директории с файлами
DOCUMENTS_DIR = 'documents/'

def load_documents():
    documents = []
    filenames = []
    for filename in os.listdir(DOCUMENTS_DIR):
        filepath = os.path.join(DOCUMENTS_DIR, filename)
        with open(filepath, 'r', encoding='utf-8') as file:
            documents.append(file.read())
        filenames.append(filename)
    return documents, filenames

# Загружаем тексты документов
documents, filenames = load_documents()

# Предобрабатываем документы и создаем TF-IDF матрицу
vectorizer, tfidf_matrix = extract_keywords(documents)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/search', methods=['POST'])
def search():
    query = request.form['query']
    results = search_documents(query, vectorizer, tfidf_matrix, documents)
    
    # Передаем индексы документов для создания ссылок
    results_with_links = [(idx, doc, keywords) for idx, (doc, keywords) in enumerate(results)]
    
    return render_template('results.html', query=query, results=results_with_links)

@app.route('/document/<int:doc_id>')
def document(doc_id):
    # Отображаем текст документа и ключевые слова
    document_text = documents[doc_id]
    doc_vector = tfidf_matrix[doc_id]
    keywords = vectorizer.inverse_transform(doc_vector)[0]
    
    return render_template('document.html', document=document_text, keywords=keywords, filename=filenames[doc_id])

if __name__ == "__main__":
    app.run(debug=True)
