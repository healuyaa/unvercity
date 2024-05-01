import tkinter as tk
from tkinter import ttk
import spacy
from anytree import Node, RenderTree

class WordViewerApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Word Viewer")

        self.text_info = tk.Text(root, height=20, width=80)
        self.text_info.grid(row=0, column=0, padx=10, pady=10)

        self.nlp = spacy.load("ru_core_news_sm")

        self.analyze_sentence()

    def analyze_sentence(self):
        sentence = self.get_sentence_from_file("lab4/test.txt")
        doc = self.nlp(sentence)

        self.text_info.delete(1.0, tk.END)
        self.text_info.insert(tk.END, "Синтаксический разбор предложения:\n")

        root_token = next((token for token in doc if token.dep_ == "ROOT"), None)
        if root_token is None:
            self.text_info.insert(tk.END, "Корневой узел не найден.\n")
            return

        nodes = {}
        for token in doc:
            nodes[token.i] = Node(f"{token.text} ({token.dep_})")

        for token in doc:
            if token.head.i != token.i:
                if token.head.i in nodes:
                    nodes[token.i].parent = nodes[token.head.i]
            else:    
                nodes[token.i].parent = None

        tree_str = self.render_dependency_tree(nodes[root_token.i])
        self.text_info.insert(tk.END, tree_str + "\n\n")

        self.text_info.insert(tk.END, "Анализ токенов:\n")
        for token in doc:
            pos_translation = self.translate_pos(token.pos_)
            dep_translation = self.translate_dep(token.dep_)
            self.text_info.insert(tk.END, f"Токен: {token.text}, Лемма: {token.lemma_}, Часть речи: {pos_translation}, Зависимость: {dep_translation}\n")

    def render_dependency_tree(self, root_node):
        tree_str = ""
        for pre, _, node in RenderTree(root_node):
            tree_str += f"{pre}{node.name}\n"
        return tree_str

    def translate_pos(self, pos):
        if pos == "ADJ":
            return "Прилагательное"
        elif pos == "ADP":
            return "Предлог"
        elif pos == "ADV":
            return "Наречие"
        elif pos == "AUX":
            return "Вспомогательный глагол"
        elif pos == "CONJ":
            return "Союз"
        elif pos == "CCONJ":
            return "Сочинительный союз"
        elif pos == "DET":
            return "Детерминатив"
        elif pos == "INTJ":
            return "Междометие"
        elif pos == "NOUN":
            return "Существительное"
        elif pos == "NUM":
            return "Числительное"
        elif pos == "PART":
            return "Частица"
        elif pos == "PRON":
            return "Местоимение"
        elif pos == "PROPN":
            return "Имя собственное"
        elif pos == "PUNCT":
            return "Пунктуация"
        elif pos == "SCONJ":
            return "Подчинительный союз"
        elif pos == "SYM":
            return "Символ"
        elif pos == "VERB":
            return "Глагол"
        elif pos == "X":
            return "Другое"
        else:
            return pos

    def translate_dep(self, dep):
        if dep == "ROOT":
            return "Корень"
        elif dep == "acl":
            return "Дополнение с модификатором"
        elif dep == "advcl":
            return "Временной модификатор с союзом"
        elif dep == "advmod":
            return "Наречие-модификатор"
        elif dep == "amod":
            return "Прилагательное-модификатор"
        elif dep == "appos":
            return "Приложение"
        elif dep == "aux":
            return "Вспомогательный глагол"
        elif dep == "case":
            return "Предлоговое управление"
        elif dep == "cc":
            return "Союз"
        elif dep == "ccomp":
            return "Соответствие"
        elif dep == "clf":
            return "Счетное слово"
        elif dep == "compound":
            return "Сложное слово"
        elif dep == "conj":
            return "Соединение"
        elif dep == "cop":
            return "Копулятивный глагол"
        elif dep == "csubj":
            return "Главное предложение"
        elif dep == "dep":
            return "Неполная зависимость"
        elif dep == "det":
            return "Детерминатив"
        elif dep == "discourse":
            return "Дискурсив"
        elif dep == "dislocated":
            return "Выдвижение"
        elif dep == "expl":
            return "Экспонент"
        elif dep == "fixed":
            return "Фиксированное"
        elif dep == "flat":
            return "Слитное слово"
        elif dep == "goeswith":
            return "Сложный компонент"
        elif dep == "iobj":
            return "Косвенное дополнение"
        elif dep == "list":
            return "Список"
        elif dep == "mark":
            return "Маркер"
        elif dep == "nmod":
            return "Модификатор существительного"
        elif dep == "nsubj":
            return "Подлежащее"
        elif dep == "nummod":
            return "Числовое модификатор"
        elif dep == "obj":
            return "Прямое дополнение"
        elif dep == "obl":
            return "Обстоятельство"
        elif dep == "orphan":
            return "Сирота"
        elif dep == "parataxis":
            return "Параграф"
        elif dep == "punct":
            return "Пунктуация"
        elif dep == "reparandum":
            return "Ремаркандум"
        elif dep == "root":
            return "Корень"
        elif dep == "vocative":
            return "Звательное"
        elif dep == "xcomp":
            return "Главное дополнение"
        else:
            return dep

    def get_sentence_from_file(self, filename):
        with open(filename, 'r', encoding='utf-8') as file:
            sentence = file.read().strip()
        return sentence

if __name__ == "__main__":
    root = tk.Tk()
    app = WordViewerApp(root)
    root.mainloop()
