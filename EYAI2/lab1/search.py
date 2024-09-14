from sklearn.feature_extraction.text import TfidfVectorizer
import numpy as np
from preprocess import preprocess_text

def extract_keywords(documents):
    processed_docs = [preprocess_text(doc) for doc in documents]
    
    vectorizer = TfidfVectorizer(ngram_range=(1, 1))
    tfidf_matrix = vectorizer.fit_transform(processed_docs)
    
    return vectorizer, tfidf_matrix

def search_documents(query, vectorizer, tfidf_matrix, documents, threshold=0.0001):
    query = preprocess_text(query)
    print(f"Preprocessed query: {query}")

    query_vector = vectorizer.transform([query])
    print(f"Query vector shape: {query_vector.shape}")

    similarities = (query_vector @ tfidf_matrix.T).toarray()[0]
    print(f"Similarities: {similarities}")

    results = []
    for idx, similarity in enumerate(similarities):
        if similarity > threshold:
            print(f"Document {idx} matches with similarity {similarity}")
            results.append((idx, documents[idx], vectorizer.inverse_transform(tfidf_matrix[idx])[0]))
    
    return results
