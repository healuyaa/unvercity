import tkinter as tk
from tkinter import ttk
import speech_recognition as sr
import threading

class SpeechApp:
    def __init__(self, root):
        self.root = root

        self.label = tk.Label(root, text="Нажмите кнопку и говорите:", font=("Arial", 16))
        self.label.pack(pady=20)

        self.result_text = tk.Text(root, height=10, width=50)
        self.result_text.pack(pady=20)

        self.language_var = tk.StringVar(value='en-US')  

        self.recognize_button = tk.Button(root, text="Распознать речь", command=self.start_recognition_thread, font=("Arial", 12))
        self.recognize_button.pack(pady=20)

    def start_recognition_thread(self):
        threading.Thread(target=self.recognize_speech).start()

    def recognize_speech(self):
        recognizer = sr.Recognizer()
        recognizer.pause_threshold = 1
        with sr.Microphone() as source:
            self.label.config(text="Слушаю...")
            try:
                audio = recognizer.listen(source, timeout=3, phrase_time_limit=12)
                language = self.language_var.get()
                text = recognizer.recognize_google(audio, language=language)
                print(text)
                self.result_text.delete(1.0, tk.END)
                self.result_text.insert(tk.END, text)
                self.label.config(text="Нажмите кнопку и говорите:")

            except sr.WaitTimeoutError as e:
                self.label.config(text=f"Не удалось получить результаты; {e}.")
            except sr.UnknownValueError:
                self.label.config(text="Не удалось распознать аудио.")
            except sr.RequestError as e:
                self.label.config(text=f"Не удалось получить результаты; {e}.")

if __name__ == '__main__':
    root = tk.Tk()
    app = SpeechApp(root)
    root.mainloop()