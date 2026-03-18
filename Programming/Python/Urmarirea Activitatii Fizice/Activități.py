import ttkbootstrap as ttk
from ttkbootstrap.constants import *
import pickle
import json
from tkinter import messagebox
from tkinter import filedialog
from PIL import Image, ImageTk
from tkinter import colorchooser
from tkinter import simpledialog
from Profil import FereastraProfil
from datetime import datetime, timedelta
from tkinter import Listbox, Toplevel

CALORII_PE_MINUT = {
    "Jogging": 8,
    "Antrenament de forță": 6,
    "Ciclism": 8,
    "Înot": 12,
    "Mers pe jos": 4,
    "Yoga": 5,
    "Sărit coarda": 12,
    "Tenis": 7,
    "Fotbal": 9,
    "Baschet": 9,
    "Volei": 6,
    "Dans": 8,
    "Box": 13,
    "Alpinism": 10,
    "Plimbare rapidă": 6,
    "Ski": 10,
    "Alergare pe bandă": 9,
    "Vâslit": 12,
}

class Activitate:
    def __init__(self, tip_activitate, durata, intensitate, greutate, data=None):
        self.tip_activitate = tip_activitate
        self.durata = durata
        self.intensitate = intensitate
        self.greutate = greutate
        self.data = data or datetime.now()

    def __str__(self):
        calorii = self.calculeaza_calorii()
        return (
            f"{self.tip_activitate} - {self.durata} minute - Intensitate: {self.intensitate} "
            f"- {calorii} calorii - Greutate: {self.greutate} kg - Data: {self.data.strftime('%Y-%m-%d %H:%M:%S')}"
        )

    def calculeaza_calorii(self):
        calorii_per_minut = CALORII_PE_MINUT.get(self.tip_activitate, 5)
        intensitate_factor = {
            "Foarte scăzută": 0.8,
            "Scăzută": 1.0,
            "Mediu": 1.2,
            "Ridicată": 1.5,
            "Foarte ridicată": 2.0,
        }
        factor = intensitate_factor.get(self.intensitate, 1.0)
        return round(calorii_per_minut * self.durata * (self.greutate / 70) * factor, 3)

    def to_dict(self):
        """Convertire într-un format serializabil JSON."""
        return {
            "tip_activitate": self.tip_activitate,
            "durata": self.durata,
            "intensitate": self.intensitate,
            "greutate": self.greutate,
            "data": self.data.isoformat()
        }

    @staticmethod
    def from_dict(data):
        return Activitate(
            tip_activitate=data["tip_activitate"],
            durata=data["durata"],
            intensitate=data["intensitate"],
            greutate=data["greutate"],
            data=datetime.fromisoformat(data["data"])
        )

class Progres:
    def __init__(self):
        self.activitati = []

    def adauga_activitate(self, activitate):
        self.activitati.append(activitate)
        self.activitati.sort(key=lambda a: a.data)

    def elimina_ultima_activitate(self):
        if self.activitati:
            return self.activitati.pop()
        return None

    def afiseaza_progres(self):
        activitati_sortate = sorted(self.activitati, key=lambda a: a.data)
        progres = "Progresul tău:\n"
        for activitate in activitati_sortate:
            progres += f"{activitate}\n"
        progres += f"\nTotal calorii arse: {self.calculeaza_total_calorii()} calorii"
        return progres

    def calculeaza_total_calorii(self):
        return round(sum(activitate.calculeaza_calorii() for activitate in self.activitati), 3)

    def reseteaza(self):
        self.activitati = []

    def to_dict(self):
        return {"activitati": [activitate.to_dict() for activitate in self.activitati]}

    @staticmethod
    def from_dict(data):
        progres = Progres()
        progres.activitati = [Activitate.from_dict(activitate) for activitate in data.get("activitati", [])]
        return progres
    
    def elimina_activitate(self, index):
        """Elimină o activitate pe baza indexului."""
        if 0 <= index < len(self.activitati):
            return self.activitati.pop(index)
        return None

class AplicatieUrmatorActivitate(ttk.Frame):
    def __init__(self, parent, app_manager, email, username):
        super().__init__(parent)
        self.parent = parent
        self.app_manager = app_manager
        self.timer_id = None
        self.parent.protocol("WM_DELETE_WINDOW", self.on_close)
        self.email = email
        self.username = username
        self.data_activitate = None
        self.avatar_path = None
        self.avatar_border_color = "#000000"

        self.progres = self.app_manager.get_progres_utilizator(email)
        self.parent.title("Top Goals")
        self.parent.geometry("1100x1100")
        self.parent.minsize(950, 950)
        
        self.parent.resizable(True, True)
        self.parent.iconbitmap("TopG.ico")
        
        self.pack(fill="both", expand=True)
        self.setup_styles()
        self.configure(style="Custom.TFrame")

        self.setup_ui()

    def setup_styles(self):
        self.style = ttk.Style()
        self.style.configure("Custom.TFrame", background="#ffefd5")
        self.style.configure("Custom.TLabel", background="#ffefd5", font=("Roboto", 14))
        self.style.configure("Custom.TEntry", font=("Roboto", 12))
        self.style.configure("Custom.TButton", font=("Roboto", 12))
        #self.style.configure("Custom.TLabel", background="#ffffff", font=("Roboto", 14))

    def setup_ui(self):
        self.grid_rowconfigure(0, weight=0)
        for row in range(1, 12):
            self.grid_rowconfigure(row, weight=1)
        self.grid_columnconfigure(0, weight=1)
        self.grid_columnconfigure(2, weight=1)

        ##
        self.avatar_canvas = ttk.Canvas(self, width=300, height=300, bg="#d3d3d3", highlightthickness=2,highlightbackground="#000000")
        self.avatar_canvas.create_rectangle(
            0, 0, 300, 300,
            outline="#000000",
            width=3
        )
        self.avatar_canvas.grid(row=8, column=0, rowspan=6, columnspan=2, padx=20, pady=20, sticky="w")
        saved_avatar = self.app_manager.user_manager.users.get(self.email, {}).get("avatar")
        if saved_avatar:
            self.load_avatar(saved_avatar)
        ##else:
        ##    self.load_avatar("default_avatar.jpg")  # Default avatar
        ##
        self.label_bun_venit = ttk.Label(
            self,
            text=f"Bun venit, {self.username}!",
            style="Custom.TLabel"
        )
        self.label_bun_venit.grid(row=0, column=0, columnspan=3, pady=20)

        ttk.Separator(self, orient="horizontal").grid(row=1, column=0, columnspan=3, sticky="ew", pady=10)

        ttk.Label(
            self,
            text="Gestionarea progresului:",
            style="Custom.TLabel"
        ).grid(row=2, column=0, padx=10, pady=10, sticky="n")

        ttk.Button(self, text="Adaugă activitate", bootstyle="success", command=self.adauga_activitate).grid(
            row=3, column=0, padx=20, pady=10, sticky="nsew"
        )
        ttk.Button(self, text="Elimină activitate", bootstyle="danger", command=self.elimina_activitate).grid(
            row=4, column=0, padx=20, pady=10, sticky="nsew"
        )
        ttk.Button(self, text="Afișare progres", bootstyle="primary", command=self.afiseaza_progres).grid(
            row=5, column=0, padx=20, pady=10, sticky="nsew"
        )
        ttk.Button(self, text="Resetare progres", bootstyle="danger", command=self.confirmare_resetare).grid(
            row=6, column=0, padx=20, pady=10, sticky="nsew"
        )

        ttk.Separator(self, orient="vertical").grid(row=2, column=1, rowspan=5, sticky="ns")

        ttk.Label(
            self,
            text="Gestionarea contului:",
            style="Custom.TLabel"
        ).grid(row=2, column=2, padx=10, pady=10, sticky="n")
        
        ttk.Button(self, text="Editare profil", bootstyle="info", command=self.deschide_fereastra_profil).grid(
            row=3, column=2, padx=20, pady=10, sticky="nsew"
        )
        
        ttk.Button(self, text="Ștergere cont", bootstyle="danger", command=self.confirmare_stergere).grid(
            row=4, column=2, padx=20, pady=10, sticky="nsew"
        )
        ttk.Button(self, text="Ieșire din cont", bootstyle="warning", command=self.confirmare_logout).grid(
            row=5, column=2, padx=20, pady=10, sticky="nsew"
        )
        ttk.Button(self, text="Dashboard activitate", bootstyle="info", command=self.deschide_dashboard).grid(
        row=6, column=2, padx=20, pady=10, sticky="nsew"
        )
        ttk.Separator(self, orient="horizontal").grid(row=7, column=0, columnspan=3, sticky="ew", pady=10)

        ttk.Label(self, text="Tipul activității:", style="Custom.TLabel").grid(row=8, column=0, padx=10, pady=5, sticky="e")
        self.tip_activitate_var = ttk.StringVar()
        self.tip_activitate_var.set("Selectează activitatea")
        self.tip_activitate_menu = ttk.OptionMenu(self, self.tip_activitate_var, "Jogging", *CALORII_PE_MINUT.keys())
        self.tip_activitate_menu.grid(row=8, column=1, columnspan=2, padx=10, pady=5, sticky="ew")

        ttk.Label(self, text="Durata (minute):", style="Custom.TLabel").grid(row=9, column=0, padx=10, pady=5, sticky="e")
        self.entry_durata = ttk.Entry(self, style="Custom.TEntry")
        self.entry_durata.grid(row=9, column=1, columnspan=2, padx=10, pady=5, sticky="ew")

        ttk.Label(self, text="Intensitatea:", style="Custom.TLabel").grid(row=10, column=0, padx=10, pady=5, sticky="e")
        self.intensitate_var = ttk.StringVar()
        self.intensitate_var.set("Selectează intensitatea")
        self.intensitate_menu = ttk.OptionMenu(
            self,
            self.intensitate_var,
            "Foarte scăzută",
            "Foarte scăzută",
            "Scăzută",
            "Mediu",
            "Ridicată",
            "Foarte ridicată",
        )
        self.intensitate_menu.grid(row=10, column=1, columnspan=2, padx=10, pady=5, sticky="ew")

        ttk.Label(self, text="Greutatea (kg):", style="Custom.TLabel").grid(row=11, column=0, padx=10, pady=5, sticky="e")
        self.entry_greutate = ttk.Entry(self, style="Custom.TEntry")
        self.entry_greutate.grid(row=11, column=1, columnspan=2, padx=10, pady=5, sticky="ew")
        
        ttk.Label(self, text="Data activității:", style="Custom.TLabel").grid(row=12, column=0, padx=10, pady=5, sticky="e")
        self.btn_selecteaza_data = ttk.Button(self, text="Selectează data", command=self.selecteaza_data)
        self.btn_selecteaza_data.grid(row=12, column=1, columnspan=2, padx=10, pady=5, sticky="ew")
        
        ttk.Button(self, text="Resetează la data curentă", command=self.reseteaza_data).grid(
        row=13, column=1, columnspan=2, padx=10, pady=5, sticky="ew")

        self.text_progres = ttk.Text(self, height=10, wrap="word", state="disabled", font=("Roboto", 12))
        self.text_progres.grid(row=14, column=0, columnspan=3, padx=10, pady=20, sticky="nsew")

    def load_background_image(self, file_path=None):
        if file_path:
            self.avatar_path = file_path
        else:
            self.avatar_path = "default_background.jpg"
        try:
            img = Image.open(self.avatar_path).resize((950, 950))
            self.background_image = ImageTk.PhotoImage(img)
            self.background_canvas.delete("all")
            self.background_canvas.create_image(0, 0, image=self.background_image, anchor="nw")
        except Exception as e:
            print(f"Eroare la încărcarea imaginii: {e}")
    
    def change_avatar(self):
        file_path = filedialog.askopenfilename(filetypes=[("Imagini", "*.png;*.jpg;*.jpeg")])
        if file_path:
            self.load_avatar(file_path)
        else:
            print("Nicio imagine selectată.")
    
    def load_avatar(self, file_path=None):
        if file_path:
            self.avatar_path = file_path
        if not self.avatar_path:
            print("Eroare: Nu a fost selectat niciun fișier de avatar.")
            return
    
        try:
            canvas_width = int(self.avatar_canvas.cget("width"))
            canvas_height = int(self.avatar_canvas.cget("height"))
    
            img = Image.open(self.avatar_path).resize((canvas_width, canvas_height), Image.Resampling.LANCZOS)
    
            self.avatar_image = ImageTk.PhotoImage(img)
    
            self.avatar_canvas.delete("all")
            self.avatar_canvas.create_image(0, 0, image=self.avatar_image, anchor="nw")
    
            self.avatar_canvas.config(highlightbackground=self.avatar_border_color)
    
        except FileNotFoundError:
            print("Eroare: Fișierul selectat nu a fost găsit.")
        except Exception as e:
            print(f"Eroare la încărcarea avatarului: {e}")

    def deschide_fereastra_profil(self):
        def actualizeaza_profil(nume_nou, avatar_nou):
            self.username = nume_nou
            if avatar_nou:
                self.profil_utilizator.avatar_path = avatar_nou
                self.profil_utilizator.afiseaza_avatar()
            self.setup_ui()

        FereastraProfil(self.parent, self.email, self.username, actualizeaza_profil)
    
    def change_avatar(self):
        file_path = filedialog.askopenfilename(filetypes=[("Imagini", "*.png;*.jpg;*.jpeg")])
        if file_path:
            self.load_avatar(file_path)
    
    ##def change_border_color(self):
    ##    color = colorchooser.askcolor(title="Selectează culoarea bordurii")[1]
    ##    if color:
    ##        self.avatar_border_color = color
    ##        thickness = simpledialog.askinteger(
    ##            "Setează grosimea bordurii",
    ##            "Introduceți grosimea dorită a bordurii (în pixeli):",
    ##            minvalue=1,
    ##            maxvalue=20
    ##        )
    ##        if thickness is not None:
    ##            self.avatar_canvas.config(
    ##                highlightbackground=self.avatar_border_color,
    ##                highlightthickness=thickness
    ##            )
    ##            self.load_avatar()


    def update_text(self, mesaj, success=True, text_color="black"):
        bg_color = "#d4edda" if success else "#f8d7da"
        self.text_progres.config(state="normal", background=bg_color, foreground=text_color, relief="solid", bd=2)
        self.text_progres.delete("1.0", "end")
        self.text_progres.insert("end", mesaj)
        self.text_progres.config(state="disabled")

    def adauga_activitate(self):
        try:
            tip = self.tip_activitate_var.get()
            durata = int(self.entry_durata.get())
            intensitate = self.intensitate_var.get()
            greutate = float(self.entry_greutate.get())
            data = self.data_activitate if self.data_activitate else datetime.now()
    
            activitate = Activitate(tip, durata, intensitate, greutate)
            activitate.data = data
    
            self.progres.adauga_activitate(activitate)
            self.app_manager.progres_utilizatori[self.email] = self.progres
            self.update_text(f"Activitate adăugată: {activitate}", success=True)
        except ValueError:
            self.update_text("Eroare: Introdu date valide.", success=False)
    
    def elimina_activitate(self):
        activitati_window = Toplevel(self)
        activitati_window.title("Eliminare activitate")
        activitati_window.geometry("1100x600")
        activitati_window.resizable(False, False)
    
        activitati_initiale = self.progres.activitati[:]
       
        ttk.Label(activitati_window, text="Selectează activitatea pe care vrei să o elimini:", font=("Roboto", 12)).pack(pady=10)
    
        listbox = Listbox(activitati_window, font=("Roboto", 10), height=15, selectmode="single")
        listbox.pack(fill="both", expand=True, padx=20, pady=10)
    
        def actualizeaza_listbox():
            listbox.delete(0, "end")
            for i, activitate in enumerate(self.progres.activitati):
                listbox.insert(i, f"{i + 1}. {activitate}")
    
        actualizeaza_listbox()
    
        def confirma_eliminare():
            try:
                index = int(listbox.curselection()[0])
                activitate_eliminata = self.progres.elimina_activitate(index)
                if activitate_eliminata:
                    self.update_text(f"Activitate eliminată: {activitate_eliminata}", success=True)
                    self.app_manager.progres_utilizatori[self.email] = self.progres
                    actualizeaza_listbox()
                else:
                    self.update_text("Eroare: Nu s-a putut elimina activitatea.", success=False)
            except IndexError:
                self.update_text("Eroare: Nicio activitate selectată.", success=False)
    
        def anuleaza_modificari():
            self.progres.activitati = activitati_initiale[:]
            actualizeaza_listbox()
            self.update_text("Modificările au fost anulate.", success=True)
    
        ttk.Button(activitati_window, text="Elimină", bootstyle="danger", command=confirma_eliminare).pack(pady=10)
    
        ttk.Button(activitati_window, text="Anulează", bootstyle="secondary", command=anuleaza_modificari).pack(pady=10)
    
    #def elimina_ultima_activitate(self):
    #    ultima_activitate = self.progres.elimina_ultima_activitate()
    #    if ultima_activitate:
    #        self.update_text(f"Ultima activitate a fost eliminată: {ultima_activitate}", success=True)
    #    else:
    #        self.update_text("Nu există activități de eliminat.", success=False)

    def afiseaza_progres(self):
        progres = self.progres.afiseaza_progres()
        self.update_text(progres, success=True)

    def confirmare_resetare(self):
        self.parent.iconbitmap("TopG.ico")
        raspuns = messagebox.askyesno("Confirmare", "Ești sigur că vrei să resetezi progresul?")
        if raspuns:
            self.progres.reseteaza()
            self.update_text("Progresul a fost resetat.", success=True)

    def confirmare_stergere(self):
        self.parent.iconbitmap("TopG.ico")
        raspuns = messagebox.askyesno("Confirmare", "Ești sigur că vrei să ștergi contul?")
        if raspuns:
            self.app_manager.sterge_utilizator(self.email)
            messagebox.showinfo("Info", "Cont șters cu succes!")
            self.pack_forget()
            self.app_manager.show_user_management()

    def confirmare_logout(self):
        self.parent.iconbitmap("TopG.ico")
        raspuns = messagebox.askyesno("Confirmare", "Ești sigur că vrei să ieși din cont?")
        if raspuns:
            self.pack_forget()
            self.app_manager.show_user_management()
    
    def deschide_fereastra_profil(self):
        def actualizeaza_profil(nume_nou, avatar_nou):
            self.username = nume_nou
            self.label_bun_venit.config(text=f"Bun venit, {self.username}!")
            if avatar_nou:
                self.avatar_path = avatar_nou
                self.load_avatar(self.avatar_path)
    
        def save_user_changes(email, new_username, avatar_path, new_password=None):
            self.app_manager.user_manager.update_user(email, new_username, avatar_path, new_password)
    
        FereastraProfil(
            self.parent,          
            self.email,           
            self.username,        
            actualizeaza_profil,  
            save_user_changes     
        )
    def deschide_dashboard(self):
        from Dashboard import Dashboard
        Dashboard(self, self.progres)
    
    def selecteaza_data(self):
        try:
            self.stop_timers()
              
            data_window = ttk.Toplevel(self)
            data_window.title("Selectează data")
            data_window.geometry("525x500")
            data_window.resizable(False, False)
            data_window.iconbitmap("TopG.ico")
            data_window.lift()
            data_window.configure(background="#ffefd5")
            data_window.attributes("-topmost", True)
            def highlight_error(entry):
                entry.configure(style="Error.TEntry")
    
          
            style = ttk.Style()
            style.configure("Custom.TEntry", background="white")
            style.configure("Error.TEntry", background="lightcoral")
    
            
            ttk.Label(data_window, text="*Anul:", style="Custom.TLabel").grid(row=0, column=0, padx=10, pady=5, sticky="e")
            entry_an = ttk.Entry(data_window, style="Custom.TEntry")
            entry_an.grid(row=0, column=1, padx=10, pady=5)
    
            
            ttk.Label(data_window, text="*Luna:", style="Custom.TLabel").grid(row=1, column=0, padx=10, pady=5, sticky="e")
            entry_luna = ttk.Entry(data_window, style="Custom.TEntry")
            entry_luna.grid(row=1, column=1, padx=10, pady=5)
    
            
            ttk.Label(data_window, text="*Ziua:", style="Custom.TLabel").grid(row=2, column=0, padx=10, pady=5, sticky="e")
            entry_zi = ttk.Entry(data_window, style="Custom.TEntry")
            entry_zi.grid(row=2, column=1, padx=10, pady=5)
    
            
            ttk.Label(data_window, text="Ore:", style="Custom.TLabel").grid(row=3, column=0, padx=10, pady=5, sticky="e")
            entry_ora = ttk.Entry(data_window, style="Custom.TEntry")
            entry_ora.grid(row=3, column=1, padx=10, pady=5)
    
            
            ttk.Label(data_window, text="Minute:", style="Custom.TLabel").grid(row=4, column=0, padx=10, pady=5, sticky="e")
            entry_minut = ttk.Entry(data_window, style="Custom.TEntry")
            entry_minut.grid(row=4, column=1, padx=10, pady=5)
    
            
            ttk.Label(data_window, text="Secunde:", style="Custom.TLabel").grid(row=5, column=0, padx=10, pady=5, sticky="e")
            entry_secunda = ttk.Entry(data_window, style="Custom.TEntry")
            entry_secunda.grid(row=5, column=1, padx=10, pady=5)
    
            def confirma_data():
                if hasattr(self, "message_label"):
                    self.message_label.destroy()
            
                error_found = False
            
                for entry in [entry_an, entry_luna, entry_zi, entry_ora, entry_minut, entry_secunda]:
                    entry.configure(style="Custom.TEntry")
            
                if not entry_an.get().isdigit() or not entry_luna.get().isdigit() or not entry_zi.get().isdigit():
                    error_found = True
                    if not entry_an.get().isdigit():
                        highlight_error(entry_an)
                    if not entry_luna.get().isdigit():
                        highlight_error(entry_luna)
                    if not entry_zi.get().isdigit():
                        highlight_error(entry_zi)
            
                if entry_ora.get() and not entry_ora.get().isdigit():
                    highlight_error(entry_ora)
                    error_found = True
                if entry_minut.get() and not entry_minut.get().isdigit():
                    highlight_error(entry_minut)
                    error_found = True
                if entry_secunda.get() and not entry_secunda.get().isdigit():
                    highlight_error(entry_secunda)
                    error_found = True
            
                if error_found:
                    error_message = "Există câmpuri invalide! Verificați introducerea datelor. "
                    self.message_label = ttk.Label(data_window, text=error_message, foreground="red", font=("Arial", 10, "bold"))
                    self.message_label.grid(row=7, column=0, columnspan=2, pady=5)
                else:
                    try:
                        self.data_activitate = datetime(
                            int(entry_an.get()), int(entry_luna.get()), int(entry_zi.get()),
                            int(entry_ora.get()) if entry_ora.get() else 0,
                            int(entry_minut.get()) if entry_minut.get() else 0,
                            int(entry_secunda.get()) if entry_secunda.get() else 0
                        )
                        success_message = f"Data activității a fost modificată: {self.data_activitate.strftime('%Y-%m-%d %H:%M:%S')}"
                        self.update_text(success_message, success=True)
                        data_window.destroy() 
                    except ValueError:

                        error_message = "                  Data introdusă nu este validă!                      "
                        self.message_label = ttk.Label(data_window, text=error_message, foreground="red", font=("Arial", 10, "bold"))
                        self.message_label.grid(row=7, column=0, columnspan=2, pady=5)
                        
            self.message_label = ttk.Label(data_window, text="               Introduceți datele pentru activitate.                 ", 
                                        foreground="green", font=("Arial", 10, "bold"))
            self.message_label.grid(row=7, column=0, columnspan=2, pady=5)
                
            ttk.Button(data_window, text="Confirmă", bootstyle="success", command=confirma_data).grid(row=6, column=0, columnspan=2, pady=10)
            ttk.Button(data_window, text="Anulează", bootstyle="danger", command=data_window.destroy).grid(row=8, column=0, columnspan=2, pady=10)
    
        except Exception as e:
            messagebox.showerror("Eroare", f"A apărut o eroare: {e}")
    
    def reseteaza_data(self):
        self.data_activitate = datetime.now()
    
        self.update_text(f"Data activității curente: {self.data_activitate.strftime('%Y-%m-%d %H:%M:%S')}", success=True)
    
        self.start_date_timer()
    
    def start_date_timer(self):
        if self.data_activitate is None:
            self.data_activitate = datetime.now()
    
        self.data_activitate += timedelta(seconds=1)
    
        if self.winfo_exists():
            self.timer_id = self.after(1000, self.start_date_timer)
    
    def stop_timers(self):
        if self.timer_id is not None:
            self.after_cancel(self.timer_id)
            self.timer_id = None
    
    def on_close(self):
        self.app_manager.salveaza_progrese()
        self.stop_timers()
        self.parent.destroy()