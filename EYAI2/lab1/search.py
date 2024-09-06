from sklearn.feature_extraction.text import TfidfVectorizer
import numpy as np
from preprocess import preprocess_text


def extract_keywords(documents):
    processed_docs = [preprocess_text(doc) for doc in documents]
    
    vectorizer = TfidfVectorizer(ngram_range=(1, 2))
    tfidf_matrix = vectorizer.fit_transform(processed_docs)
    
    return vectorizer, tfidf_matrix


def search_documents(query, vectorizer, tfidf_matrix, documents):
    query = preprocess_text(query)
    query_vector = vectorizer.transform([query])
    
    results = []
    for idx, doc_vector in enumerate(tfidf_matrix):
        if all(query_vector.toarray()[0][i] > 0 for i in query_vector.nonzero()[1]):
            results.append((documents[idx], vectorizer.inverse_transform(doc_vector)[0]))
    
    return results

def precision_recall(results, relevant_docs):
    tp = len([doc for doc in results if doc in relevant_docs])
    fp = len([doc for doc in results if doc not in relevant_docs])
    fn = len([doc for doc in relevant_docs if doc not in results])
    
    precision = tp / (tp + fp) if (tp + fp) > 0 else 0
    recall = tp / (tp + fn) if (tp + fn) > 0 else 0
    
    return precision, recall

