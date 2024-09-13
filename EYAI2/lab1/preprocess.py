import spacy
from nltk.corpus import stopwords
import string

nlp = spacy.load('ru_core_news_sm')

stop_words = set(stopwords.words('russian'))

def preprocess_text(text):
    text = text.lower().translate(str.maketrans('', '', string.punctuation))

    doc = nlp(text)

    filtered_words = [token.lemma_ for token in doc if token.text not in stop_words and not token.is_punct]
    
    return ' '.join(filtered_words)
