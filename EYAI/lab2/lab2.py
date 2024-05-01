import tkinter as tk
from tkinter import messagebox
import pymorphy2
from collections import Counter

morph = pymorphy2.MorphAnalyzer()

corpus_file = 'lab2/test.txt'
corpus_content = ""
try:
    with open(corpus_file, 'r', encoding='utf-8') as file:
        corpus_content = file.read()
except FileNotFoundError:
    messagebox.showerror("Ошибка", "Файл с корпусом не найден.")

def normalize_word(word):
    parsed_word = morph.parse(word)[0]
    return parsed_word.normal_form, parsed_word.tag

def search_word():
    search_word = entry.get().strip()
    if search_word:
        search_word_normalized, _ = normalize_word(search_word)
        found_words = []
        word_counts = Counter()
        word_forms = Counter()
        lemmas = {}
        grammatical_categories = {}
        metadata = {}
        for word in corpus_words:
            word_normalized, word_tag = normalize_word(word)
            if search_word_normalized in word_normalized:
                found_words.append(word)
                word_counts[word] += 1
                word_forms[word_normalized] += 1
                lemmas[word] = word_normalized
                if word_tag:
                    grammatical_categories[word] = word_tag
                    metadata[word] = {
                        'род': word_tag.gender,
                        'число': word_tag.number,
                        'падеж': word_tag.case
                    }
                else:
                    grammatical_categories[word] = None
                    metadata[word] = {
                        'род': None,
                        'число': None,
                        'падеж': None
                    }
        if found_words:
            result_message = "Найденные слова и их характеристики с количеством вхождений:\n\n"
            for word in found_words:
                result_message += f"{word} (Частота: {word_counts[word]}, Лемма: {lemmas[word]}, " \
                                  f"Грамматическая категория: {grammatical_categories[word]}, " \
                                  f"Форма: {word_forms[lemmas[word]]}, " \
                                  f"Род: {metadata[word]['род']}, " \
                                  f"Число: {metadata[word]['число']}, " \
                                  f"Падеж: {metadata[word]['падеж']})\n"
            messagebox.showinfo("Результаты поиска", result_message)
        else:
            messagebox.showinfo("Результаты поиска", "Слово или его форма не найдены в корпусе.")
    else:
        messagebox.showwarning("Ошибка", "Введите слово или его форму для поиска.")

root = tk.Tk()
root.title("Поиск слова в корпусе")

label = tk.Label(root, text="Введите слово или его форму:")
label.pack(pady=5)

entry = tk.Entry(root, width=30)
entry.pack(pady=5)

search_button = tk.Button(root, text="Поиск", command=search_word)
search_button.pack(pady=5)

corpus_text = tk.Text(root, width=50, height=20)
corpus_text.pack(pady=10)
corpus_text.insert(tk.END, corpus_content)

corpus_words = []
for word in corpus_content.split():
    corpus_words.append(word.strip())

root.mainloop()
