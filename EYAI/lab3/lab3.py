import tkinter as tk
from tkinter import ttk
import pymorphy2
from bs4 import BeautifulSoup

class WordViewerApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Word Viewer")

        self.label = ttk.Label(root, text="Выберите слово:")
        self.label.grid(row=0, column=0, padx=10, pady=10)

        self.word_combobox = ttk.Combobox(root, state="readonly", width=30)
        self.word_combobox.grid(row=0, column=1, padx=10, pady=10)

        self.word_combobox.bind("<<ComboboxSelected>>", self.display_word_info)

        self.text_info = tk.Text(root, height=10, width=50)
        self.text_info.grid(row=1, column=0, columnspan=2, padx=10, pady=10)

        self.search_entry = tk.Entry(root, width=30)
        self.search_entry.grid(row=2, column=0, padx=10, pady=10)

        self.search_button = tk.Button(root, text="Найти", command=self.search_word_info)
        self.search_button.grid(row=2, column=1, padx=10, pady=10)

        self.search_result_text = tk.Text(root, height=10, width=50)
        self.search_result_text.grid(row=3, column=0, columnspan=2, padx=10, pady=10)

        self.edit_distance_button = tk.Button(root, text="Расстояние между словами", command=self.display_edit_distance_all_forms)
        self.edit_distance_button.grid(row=4, column=0, padx=10, pady=10)

        self.edit_distance_all_forms_button = tk.Button(root, text="Расстояние между всеми формами слова", command=self.display_edit_distance_all_forms_for_selected_word)
        self.edit_distance_all_forms_button.grid(row=4, column=1, padx=10, pady=10)

        self.words = self.load_data_from_file("lab3/test.html")
        self.word_combobox["values"] = self.words

        self.morph_analyzer = pymorphy2.MorphAnalyzer()

    def load_data_from_file(self, filename):
        with open(filename, 'r', encoding='utf-8') as file:
            content = file.read()
        words = self.extract_words_from_html(content)
        return words
    
    def extract_words_from_html(self, content):
        soup = BeautifulSoup(content, 'html.parser')
        words = [tag.get_text() for tag in soup.find_all('p')]
        return words

    def display_word_info(self, event=None):
        selected_word = self.word_combobox.get()
        forms = self.get_word_forms(selected_word)
        self.text_info.delete(1.0, tk.END)
        self.text_info.insert(tk.END, f"Слово: {selected_word}\n")
        self.text_info.insert(tk.END, f"Формы: {', '.join(forms)}\n")
        self.search_result_text.delete(1.0, tk.END)

    def search_word_info(self):
        query = self.search_entry.get()
        selected_word = self.word_combobox.get()

        query_parts = query.split(maxsplit=1)            

        criteria = None
        query_value = None
        
        if len(query_parts) >= 2:
            
            if query_parts[0] in ["род", "число", "падеж", "часть"]:
                criteria = query_parts[0]
                query_value = query_parts[1]
            elif query_parts[1] in ["род", "число", "падеж", "часть"]:
                criteria = query_parts[1]
                query_value = query_parts[0]
            else:
                pass
            
            if criteria in ["род", "число", "падеж", "часть"]:
                if query_value == "женский":
                    query_value = "femn"
                elif query_value == "мужской":
                    query_value = "masc"
                elif query_value == "средний":
                    query_value = "neut"
                elif query_value == "множественное":
                    query_value = "plur"
                elif query_value == "единственное":
                    query_value = "sing"
                elif query_value == "именительный":
                    query_value = "nomn"
                elif query_value == "родительный":
                    query_value = "gent"
                elif query_value == "дательный":
                    query_value = "datv"
                elif query_value == "винительный":
                    query_value = "accs"
                elif query_value == "творительный":
                    query_value = "ablt"
                elif query_value == "предложный":
                    query_value = "loct"
                elif query_value == "звательный":
                    query_value = "voct"
                elif query_value == "деепричастие":
                    query_value = "GRND"
                elif query_value == "причастие":
                    query_value = "PRTS"
                elif query_value == "краткое":
                    query_value = "ADJS"
                elif query_value == "компаратив":
                    query_value = "COMP"
                elif query_value == "существительное":
                    query_value = "NOUN"
                elif query_value == "прилагательное":
                    query_value = "ADJF"
                elif query_value == "глагол":
                    query_value = "VERB"
                elif query_value == "наречие":
                    query_value = "ADVB"
                elif query_value == "числительное":
                    query_value = "NUMR"
                elif query_value == "местоимение":
                    query_value = "NPRO"
                elif query_value == "междометие":
                    query_value = "INTJ"
                elif query_value == "предикатив":
                    query_value = "PRED"

        forms = self.get_word_forms(selected_word, criteria, query_value)
        
        self.search_result_text.delete(1.0, tk.END)
        self.search_result_text.insert(tk.END, f"Формы слова {selected_word} по критерию '{query}':\n")
        self.search_result_text.insert(tk.END, f"{', '.join(forms)}\n")

    def get_word_forms(self, word, criteria=None, query_value=None):
        analyzed_word = self.morph_analyzer.parse(word)[0]
        if criteria == "род" and query_value:
            forms = [parsed_word.word for parsed_word in analyzed_word.lexeme if query_value in (parsed_word.tag.gender or [])]
        elif criteria == "число" and query_value:
            forms = [parsed_word.word for parsed_word in analyzed_word.lexeme if query_value in (parsed_word.tag.number or [])]
        elif criteria == "падеж" and query_value:
            forms = [parsed_word.word for parsed_word in analyzed_word.lexeme if query_value in (parsed_word.tag.case or [])]
        elif criteria == "часть" and query_value:
            forms = [parsed_word.word for parsed_word in analyzed_word.lexeme if query_value in (parsed_word.tag.POS or [])]
        else:
            forms = [parsed_word.word for parsed_word in analyzed_word.lexeme]
        return forms
    
    def edit_distance(self, word1, word2):
        len1 = len(word1)
        len2 = len(word2)
        
        dp = [[0] * (len2 + 1) for _ in range(len1 + 1)]
        
        for i in range(len1 + 1):
            dp[i][0] = i
        for j in range(len2 + 1):
            dp[0][j] = j
        
        for i in range(1, len1 + 1):
            for j in range(1, len2 + 1):
                cost = 0 if word1[i - 1] == word2[j - 1] else 1
                dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost)
        
        return dp[len1][len2]
    
    def edit_distance_all_forms(self):
        all_forms = self.words
        len_all_forms = len(all_forms)
        
        distance_dict = {}
        
        for i in range(len_all_forms):
            for j in range(i + 1, len_all_forms):
                distance = self.edit_distance(all_forms[i], all_forms[j])
                distance_dict[(all_forms[i], all_forms[j])] = distance
        
        return distance_dict
        
    def display_edit_distance_all_forms(self):
        distance_dict = self.edit_distance_all_forms()
        self.search_result_text.delete(1.0, tk.END)
        self.search_result_text.insert(tk.END, "Редакционное расстояние между всеми парами слов:\n")
        for pair, distance in distance_dict.items():
            word1, word2 = pair
            self.search_result_text.insert(tk.END, f"Между '{word1}' и '{word2}': {distance}\n")

    def display_edit_distance_all_forms_for_selected_word(self):
        selected_word = self.word_combobox.get()
        word_forms = self.get_word_forms(selected_word)
        distance_dict = {}
        
        for i in range(len(word_forms)):
            for j in range(i + 1, len(word_forms)):
                distance = self.edit_distance(word_forms[i], word_forms[j])
                distance_dict[(word_forms[i], word_forms[j])] = distance

        self.search_result_text.delete(1.0, tk.END)
        self.search_result_text.insert(tk.END, f"Редакционное расстояние между всеми формами слова '{selected_word}':\n")
        for pair, distance in distance_dict.items():
            word1, word2 = pair
            self.search_result_text.insert(tk.END, f"Между '{word1}' и '{word2}': {distance}\n")
        
    def edit_distance_all_forms_for_selected_word(self):
        selected_word = self.word_combobox.get()
        word_forms = self.get_word_forms(selected_word)
        distance_dict = {}
        
        for i in range(len(word_forms)):
            for j in range(i + 1, len(word_forms)):
                distance = self.edit_distance(word_forms[i], word_forms[j])
                distance_dict[(word_forms[i], word_forms[j])] = distance

        self.search_result_text.delete(1.0, tk.END)
        self.search_result_text.insert(tk.END, f"Редакционное расстояние между всеми формами слова '{selected_word}':\n")
        for pair, distance in distance_dict.items():
            word1, word2 = pair
            self.search_result_text.insert(tk.END, f"Между '{word1}' и '{word2}': {distance}\n")


if __name__ == "__main__":
    root = tk.Tk()
    app = WordViewerApp(root)
    root.mainloop()
