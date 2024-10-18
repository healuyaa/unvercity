import tkinter as tk
from tkinter import ttk
import pyttsx3

class TextToSpeechApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Text to Speech")

        self.engine = pyttsx3.init()

        self.create_widgets()
        self.populate_voice_options()

    def create_widgets(self):
        self.voice_label = tk.Label(self.root, text="Выберите голос:")
        self.voice_label.pack(pady=10)

        self.voice_vars = []
        self.voice_checkbuttons = []

        self.voices_frame = tk.Frame(self.root)
        self.voices_frame.pack(pady=5)

        controls_frame = tk.Frame(self.root)
        controls_frame.pack(pady=10)

        self.volume_label = tk.Label(controls_frame, text="Громкость:")
        self.volume_label.grid(row=0, column=0, padx=5)
        self.volume_combobox = ttk.Combobox(controls_frame, values=[0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0])
        self.volume_combobox.set(0.5)
        self.volume_combobox.grid(row=0, column=1, padx=5)

        self.rate_label = tk.Label(controls_frame, text="Темп:")
        self.rate_label.grid(row=0, column=2, padx=5)
        self.rate_combobox = ttk.Combobox(controls_frame, values=[50, 100, 150, 200, 250, 300])
        self.rate_combobox.set(150)
        self.rate_combobox.grid(row=0, column=3, padx=5)

        self.text_label = tk.Label(self.root, text="Введите текст:")
        self.text_label.pack(pady=5)
        self.text_entry = tk.Entry(self.root, width=50)
        self.text_entry.pack(pady=5)

        self.play_button = tk.Button(self.root, text="Воспроизвести", command=self.speak)
        self.play_button.pack(pady=20)

    def populate_voice_options(self):
        voices = self.engine.getProperty('voices')
        
        female_voices = voices[1:-1]

        for voice in female_voices:
            var = tk.BooleanVar(value=True)
            self.voice_vars.append(var)
            cb = tk.Checkbutton(self.voices_frame, text=voice.name, variable=var)
            self.voice_checkbuttons.append(cb)
            cb.pack(anchor='w')

    def speak(self):
        text = self.text_entry.get().strip()
        if not text:
            return

        selected_rate = self.rate_combobox.get()
        if selected_rate:
            self.engine.setProperty('rate', int(selected_rate))

        selected_volume = self.volume_combobox.get()
        if selected_volume:
            self.engine.setProperty('volume', float(selected_volume))

        for i, var in enumerate(self.voice_vars):
            if var.get():
                self.engine.setProperty('voice', self.engine.getProperty('voices')[i + 1].id)
                self.engine.say(text)

        self.engine.runAndWait()

if __name__ == "__main__":
    root = tk.Tk()
    app = TextToSpeechApp(root)
    root.mainloop()
