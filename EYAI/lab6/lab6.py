import tkinter as tk
from tkinter import messagebox
import pymorphy2

films = {
    "Интерстеллар": "Фантастический фильм режиссера Кристофера Нолана, рассказывающий о попытках людей найти новый дом для человечества в глубинах космоса из-за угрозы вымирания на Земле.",
    "Гордость и предубеждение": "Экранизация романа Джейн Остин, рассказывающая о любовных отношениях и общественных нравах в Англии начала XIX века.",
    "Пираты Карибского моря": "Приключенческий фильм о пиратах и их приключениях в мистических водах Карибского моря, режиссер - Гор Вербински."
}

morph = pymorphy2.MorphAnalyzer()

def find_films(query):
    found_films = []
    for film in films.keys():
        if query.lower() in film.lower():
            found_films.append(film)
    return found_films

def show_description(film_name):
    description = films.get(film_name, "Описание не найдено")
    chat_display.insert(tk.END, f"Фильм: {film_name}\nОписание: {description}\n\n")

def handle_question():
    question = entry_question.get()
    if question:
        chat_display.insert(tk.END, f"Вы: {question}\n")
        if "фильмы" in question.lower() or "кино" in question.lower():
            query = question.split("кино")[-1].strip()
            found_films = find_films(query)
            if found_films:
                chat_display.insert(tk.END, "Кинопомощник: " + "\nКинопомощник: ".join(found_films) + "\n\n")
            else:
                chat_display.insert(tk.END, "Кинопомощник: Фильмы не найдены\n\n")
        elif "информация о фильме" in question.lower():
            query_parts = question.split(" ")
            film_name = " ".join(query_parts[3:])
            show_description(film_name)
        else:
            chat_display.insert(tk.END, "Кинопомощник: Извините, я не могу ответить на этот вопрос.\n\n")
    else:
        chat_display.insert(tk.END, "Кинопомощник: Пожалуйста, задайте вопрос.\n\n")

root = tk.Tk()
root.title("Кинопомощник")

chat_display = tk.Text(root, width=70, height=20)
chat_display.grid(row=0, column=0, columnspan=3, padx=5, pady=5)

label_question = tk.Label(root, text="Введите вопрос:")
label_question.grid(row=1, column=0, padx=5, pady=5)

entry_question = tk.Entry(root, width=50)
entry_question.grid(row=1, column=1, padx=5, pady=5)

button_question = tk.Button(root, text="Отправить", command=handle_question)
button_question.grid(row=1, column=2, padx=5, pady=5)

root.mainloop()
