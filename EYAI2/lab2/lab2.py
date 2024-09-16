import re
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.ensemble import RandomForestClassifier
import numpy as np
import string

def clean_text(text):
    text = text.lower()
    text = re.sub(r'\d+', '', text)
    text = text.translate(str.maketrans('', '', string.punctuation))
    tokens = text.split()
    return ' '.join(tokens)

def split_sentences(text):
    sentences = re.split(r'(?<=[.!?]) +', text)
    return sentences

def sentence_extraction(text, num_sentences=5):
    sentences = split_sentences(text)
    cleaned_sentences = [clean_text(sent) for sent in sentences]
    
    vectorizer = TfidfVectorizer(stop_words='english')
    sentence_vectors = vectorizer.fit_transform(cleaned_sentences)

    sentence_scores = sentence_vectors.sum(axis=1).flatten().tolist()[0]

    ranked_sentences = [sentences[i] for i in np.argsort(sentence_scores)[-num_sentences:]]
    return ranked_sentences

def train_ml_model(documents, labels):
    vectorizer = TfidfVectorizer(stop_words='english')
    X = vectorizer.fit_transform(documents)
    model = RandomForestClassifier()
    model.fit(X, labels)
    return model, vectorizer

def generate_summary(text, ml_model, vectorizer):
    sentences = split_sentences(text)
    cleaned_sentences = [clean_text(sent) for sent in sentences]
    
    sentence_vectors = vectorizer.transform(cleaned_sentences)
    predictions = ml_model.predict(sentence_vectors)
    
    summary = [sentences[i] for i in range(len(predictions)) if predictions[i] == 1]
    return summary

def load_data_from_file(filename):
    documents = []
    labels = []
    with open(filename, 'r', encoding='utf-8') as file:
        for line in file:
            sentence, label = line.rsplit(' ', 1)
            documents.append(sentence)
            labels.append(int(label.strip()))
    return documents, labels

train_documents, train_labels = load_data_from_file('train.txt')

text_for_summary = load_data_from_file('test.txt')[0]

ml_model, vectorizer = train_ml_model(train_documents, train_labels)

summary_extracted = sentence_extraction(text_for_summary, num_sentences=3)
print("Summary (Sentence Extraction):")
print("\n".join(summary_extracted))

summary_ml = generate_summary(text_for_summary, ml_model, vectorizer)
print("\nSummary (ML):")
print("\n".join(summary_ml))
