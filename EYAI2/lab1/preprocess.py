import spacy
from nltk.corpus import stopwords
import string

# Загрузка русского модели spaCy
nlp = spacy.load('ru_core_news_sm')

stop_words = set(stopwords.words('russian'))

def preprocess_text(text):
    # Приведение к нижнему регистру и удаление пунктуации
    text = text.lower().translate(str.maketrans('', '', string.punctuation))
    
    # Токенизация и лемматизация с spaCy
    doc = nlp(text)
    
    # Удаление стоп-слов и лемматизация
    filtered_words = [token.lemma_ for token in doc if token.text not in stop_words and not token.is_punct]
    
    return ' '.join(filtered_words)
