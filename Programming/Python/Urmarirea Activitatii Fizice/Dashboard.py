import tkinter as tk
from tkinter import Toplevel
from tkinter import messagebox
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.dates import DateFormatter
import random

class Dashboard(Toplevel):
    def __init__(self, parent, progres):
        super().__init__(parent)
        self.title("Dashboard activitate")
        self.geometry("1920x1080")
        self.wm_minsize(1920, 1080)
        self.iconbitmap("TopG.ico")
        self.progres = progres

        self.sugestii_complet = [
            "Continuă progresul zilnic.",
            "Încearcă să adaugi 10 minute în fiecare zi la antrenamentele tale.",
            "Îmbunătățește durata exercițiilor pentru a crește arderea caloriilor.",
            "Explorează noi tipuri de activități pentru diversitate.",
            "Concentrează-te pe activități cu intensitate mai mare pentru\n a arde mai multe calorii.",
            "Încearcă să faci activități de grup pentru motivație suplimentară.",
            "Fă mai multe activități în aer liber pentru a te simți mai energic.",
            "Stabilește-ți obiective săptămânale pentru a măsura progresul.",
            "Încearcă să alternezi între activitățile cardio și cele de forță\n pentru rezultate echilibrate.",
            "Monitorizează progresul cu ajutorul unui jurnal de activități.",
            "Încearcă să te concentrezi pe posturarea corectă în timpul exercițiilor.",
            "Încearcă să îmbunătățești consistența activităților tale.",
            "Nu uita să te hidratezi înainte, în timpul și după exerciții.",
            "Incorporează exerciții de stretching la sfârșitul fiecărei sesiuni.",
            "Dacă ai o perioadă mai puțin activă, încearcă să îți crești\n treptat nivelul de activitate.",
            "Pentru rezultate rapide, încearcă să îmbini antrenamentele\n de intensitate mare cu cele moderate.",
            "Încearcă să monitorizezi timpul de recuperare între antrenamente.",
            "Căută noi provocări fizice care să te mențină motivat.",
            "Fă exerciții care te ajută să îți îmbunătățești flexibilitatea.",
            "Combină exercițiile de cardio cu antrenamente de forță\n pentru o formă fizică completă."
        ]

        self.setup_ui()

    def setup_ui(self):
        tk.Button(self, text="Actualizează dashboard", command=self.afiseaza_dashboard).pack(pady=10)

        self.canvas_frame = tk.Frame(self)
        self.canvas_frame.pack(fill="both", expand=True)
        self.afiseaza_dashboard()

    def afiseaza_dashboard(self):
        for widget in self.canvas_frame.winfo_children():
            widget.destroy()
    
        activitati = self.progres.activitati
        if not activitati:
            tk.Label(self.canvas_frame, text="Nu există activități înregistrate!").pack()
            return
    
        zile = {}
        tipuri_activitati = {}
        for activitate in activitati:
            zi = activitate.data.date()
            calorii = activitate.calculeaza_calorii()
            zile[zi] = zile.get(zi, 0) + calorii
            tipuri_activitati[activitate.tip_activitate] = tipuri_activitati.get(activitate.tip_activitate, 0) + activitate.durata
    
        zile_list = sorted(zile.keys())
        calorii_list = [zile[zi] for zi in zile_list]
    
        ani = {zi.year for zi in zile_list}
        if len(ani) == 1:
            date_format = DateFormatter('%m-%d')
        else:
            date_format = DateFormatter('%Y')
    
        fig, axs = plt.subplots(2, 2, figsize=(14, 10))
        fig.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.1, hspace=0.4, wspace=0.4)
    
        # Grafic 1: Progresul caloriilor arse pe zile
        axs[0, 0].plot(zile_list, calorii_list, marker='o', linestyle='-', linewidth=3, color='blue', label="Calorii Arse")
        axs[0, 0].fill_between(zile_list, calorii_list, color='skyblue', alpha=0.2)
        axs[0, 0].set_title("Progresul caloriilor arse", fontsize=14)
        axs[0, 0].set_xlabel("Dată", fontsize=12)
        axs[0, 0].set_ylabel("Calorii", fontsize=12)
        axs[0, 0].grid(True, linestyle='--', linewidth=0.5, alpha=0.7)
        axs[0, 0].legend()
        axs[0, 0].xaxis.set_major_formatter(date_format)
    
        # Grafic 2: Timp total petrecut pe activități pe zile
        durata_pe_zile = {}
        for activitate in activitati:
            zi = activitate.data.date()
            durata_pe_zile[zi] = durata_pe_zile.get(zi, 0) + activitate.durata
    
        zile_list_durata = sorted(durata_pe_zile.keys())
        durata_list = [durata_pe_zile[zi] for zi in zile_list_durata]
    
        axs[0, 1].plot(zile_list_durata, durata_list, marker='o', linestyle='-', linewidth=3, color='green', label="Timp Total")
        axs[0, 1].fill_between(zile_list_durata, durata_list, color='lightgreen', alpha=0.3)
        axs[0, 1].set_title("Timp total pe activități", fontsize=14)
        axs[0, 1].set_xlabel("Dată", fontsize=12)
        axs[0, 1].set_ylabel("Minute", fontsize=12)
        axs[0, 1].grid(True, linestyle='--', linewidth=0.5, alpha=0.7)
        axs[0, 1].legend()
        axs[0, 1].xaxis.set_major_formatter(date_format)
    
        # Grafic 3: Distribuția activităților pe tipuri
        tipuri = list(tipuri_activitati.keys())
        durate = list(tipuri_activitati.values())
    
        axs[1, 0].pie(durate, labels=tipuri, autopct='%1.1f%%', startangle=90, colors=plt.cm.tab20.colors)
        axs[1, 0].set_title("Distribuția activităților pe tipuri", fontsize=14)
    
        # Colțul din dreapta jos pentru sugestii
        axs[1, 1].axis("on")
        sugestii_display = self.generare_sugestii(activitati)
        sugestii_text = "\n\n".join(sugestii_display)
        
        axs[1, 1].add_patch(plt.Rectangle((0.05, 0.05), 0.9, 0.9, color='lightyellow', alpha=0.7))
        axs[1, 1].text(0.5, 0.5, sugestii_text, fontsize=7, ha='center', va='center', fontweight='bold',wrap=True)
        axs[1, 1].set_xticks([])
        axs[1, 1].set_yticks([])
    
        # Canvas-ul se actualizează acum pentru a reflecta noile grafice
        canvas = FigureCanvasTkAgg(fig, self.canvas_frame)
        canvas.get_tk_widget().pack(fill="both", expand=True)
        canvas.draw()

    def generare_sugestii(self, activitati):
        sugestii_relevante = []

        total_calorii = sum([activitate.calculeaza_calorii() for activitate in activitati])
        total_durata = sum([activitate.durata for activitate in activitati])

        if total_calorii < 500:
            sugestii_relevante.append("Încearcă să arzi mai multe calorii în fiecare zi.")
        if total_durata < 150:
            sugestii_relevante.append("Îți recomandăm să petreci mai mult timp activ pe zi.")
        if total_durata > 300:
            sugestii_relevante.append("Excelent! Poți încerca să diversifici activitățile pentru mai multe beneficii.")

        sugestii_relevante.extend(random.sample(self.sugestii_complet, 5))

        return sugestii_relevante
