import json
import pickle
import shutil
from cryptography.fernet import Fernet
from Activități import AplicatieUrmatorActivitate
from Activități import Progres
import ttkbootstrap as ttk
from ttkbootstrap.constants import *


class UserManager:
    def __init__(self, fisier="utilizatori.pkl", key_file="cheie_secreta.key"):
        self.fisier = fisier
        self.key_file = key_file
        self.key = self.incarca_cheie()
        self.fernet = Fernet(self.key)
        self.users = self.incarca_date()

    def incarca_cheie(self):
        try:
            with open(self.key_file, "rb") as f:
                return f.read()
        except FileNotFoundError:
            return self.genereaza_cheie()

    def genereaza_cheie(self):
        key = Fernet.generate_key()
        with open(self.key_file, "wb") as f:
            f.write(key)
        return key

    def incarca_date(self):
        try:
            with open(self.fisier, "rb") as f:
                encrypted_data = f.read()
                decrypted_data = self.fernet.decrypt(encrypted_data)
                return pickle.loads(decrypted_data)
        except (FileNotFoundError, EOFError, pickle.UnpicklingError, ValueError):
            print("Fișierul de utilizatori nu există sau este corupt. Creăm o structură goală.")
            return {}
            
    def salveaza_date(self):
        try:
            data = pickle.dumps(self.users)
            encrypted_data = self.fernet.encrypt(data)
            with open(self.fisier, "wb") as f:
                f.write(encrypted_data)
        except Exception as e:
            print(f"Eroare la salvarea datelor: {e}")
    
    def add_user(self, username, email, password):
        if email in self.users:
            return "Cont deja existent! Încercați să vă autentificați."
            
        if not username.strip():
            return "Numele de utilizator este obligatoriu!"

        if " " in email or " " in password:
            return "Numele, emailul și parola nu trebuie să conțină caractere albe!"

        valid_domains = ["@gmail.com", "@yahoo.com"]
        if not any(email.endswith(domain) for domain in valid_domains):
            return "Emailul trebuie să fie de forma 'nume@gmail.com' sau 'nume@yahoo.com'."

        local_part = email.split("@")[0]
        if not (6 <= len(local_part) <= 30):
            return "Emailul trebuie să aibă între 6 și 30 de caractere."

        if email in self.users:
            return "Email deja existent!"

        if not self.validate_password(password):
            return "Parola trebuie să conțină între 5 și 20 de caractere, cel puțin o cifră și un simbol!"

        self.users[email] = {"username": username, "password": password}
        self.salveaza_date()
        return "Utilizator adăugat cu succes!"

    def update_user(self, email, new_username, avatar_path=None, new_password=None):
        if email in self.users:
            self.users[email]["username"] = new_username
            if avatar_path:
                self.users[email]["avatar"] = avatar_path
            if new_password:
                self.users[email]["password"] = new_password
            self.salveaza_date()
            return True
        return False

    @staticmethod
    def validate_password(password):
        simboluri_permise = "@#$!%^&*()_+-=[]{}|;:',.<>?/`~"
        if " " in password:
            return False
        if not (5 <= len(password) <= 20):
            return False
        if not any(char.isdigit() for char in password):
            return False
        if not any(char in simboluri_permise for char in password):
            return False
        return True

    def authenticate_user(self, email, password):
        if email in self.users and self.users[email]["password"] == password:
            return True
        return False
        
    def sterge_utilizator(self, email):
        if email in self.users:
            del self.users[email]
            self.salveaza_date()
            return "Utilizator șters cu succes!"
        return "Utilizatorul nu există!"

class AplicatieUtilizatori(ttk.Frame):
    def __init__(self, parent, app_manager):
        super().__init__(parent)
        self.parent = parent
        self.app_manager = app_manager
        self.user_manager = self.app_manager.user_manager

        self.parent.title("Top Goals Login")
        self.parent.geometry("600x600")
        self.parent.minsize(600, 600)
        #self.parent.maxsize(600, 600)
        self.parent.iconbitmap("TopG.ico")
        self.pack(fill="both", expand=True)
        self.setup_styles()
        self.setup_ui()

    def setup_styles(self):
        self.style = ttk.Style()
        self.style.configure("Custom.TFrame", background="#ffefd5")
        self.style.configure("Custom.TLabel", background="#ffefd5", font=("Roboto", 12))
        self.style.configure("Custom.TEntry", font=("Roboto", 12))

    def setup_ui(self):
        self.configure(style="Custom.TFrame")

        ttk.Label(self, text="Nume:", style="Custom.TLabel").pack(pady=5)
        self.entry_username = ttk.Entry(self, style="Custom.TEntry", width=40)
        self.entry_username.pack(padx=10, pady=5, fill="x")

        ttk.Label(self, text="Email:", style="Custom.TLabel").pack(pady=5)
        self.entry_email = ttk.Entry(self, style="Custom.TEntry", width=40)
        self.entry_email.pack(padx=10, pady=5, fill="x")

        ttk.Label(self, text="Parolă:", style="Custom.TLabel").pack(pady=5)
        self.entry_password = ttk.Entry(self, show="*", style="Custom.TEntry", width=40)
        self.entry_password.pack(padx=10, pady=5, fill="x")

        ttk.Button(self, text="Creează cont", bootstyle="success", command=self.add_user).pack(pady=5)
        ttk.Button(self, text="Intră în cont", bootstyle="primary", command=self.authenticate_user).pack(pady=5)

        self.message_box = ttk.Text(self, height=5, wrap="word", state="disabled", font=("Roboto", 12))
        self.message_box.pack(pady=10, fill="both", expand=True)

    def display_message(self, message, success=True):
        bg_color = "#d4edda" if success else "#f8d7da"
        self.message_box.config(state="normal", background=bg_color, foreground="black")
        self.message_box.delete("1.0", "end")
        self.message_box.insert("end", message)
        self.message_box.config(state="disabled")

    def add_user(self):
        username = self.entry_username.get()
        email = self.entry_email.get()
        password = self.entry_password.get()
        message = self.user_manager.add_user(username, email, password)
        self.display_message(message, success="succes" in message.lower())

    def authenticate_user(self):
        email = self.entry_email.get()
        password = self.entry_password.get()
        if self.user_manager.authenticate_user(email, password):
            username = self.user_manager.users[email]["username"]
            self.display_message("Autentificare reușită!", success=True)
            self.app_manager.show_activity_tracking(email, username)
        else:
            self.display_message("Autentificare eșuată!", success=False)

class AplicatieManager:
    def __init__(self, root):
        self.root = root
        self.user_manager = UserManager()
        self.progres_utilizatori = self.incarca_progrese()
        self.current_frame = None
        self.show_user_management()

    def incarca_progrese(self, fisier="progrese.json"):
        try:
            with open(fisier, "r", encoding="utf-8") as f:
                data = json.load(f)
                self.progres_utilizatori = {email: Progres.from_dict(progres) for email, progres in data.items()}
            #print(f"Progrese încărcate: {self.progres_utilizatori}")
        except (FileNotFoundError, json.JSONDecodeError):
            #print("Fișierul nu există sau este corupt. Creăm o structură goală.")
            self.progres_utilizatori = {}
            self.salveaza_progrese(fisier)
        return self.progres_utilizatori

    def salveaza_progrese(self, fisier="progrese.json"):
        try:
            with open(fisier, "w", encoding="utf-8") as f:
                json.dump(
                    {email: progres.to_dict() for email, progres in self.progres_utilizatori.items()},
                    f,
                    indent=4,
                    ensure_ascii=False
                )
            #print(f"Progres salvat în {fisier}: {self.progres_utilizatori}")
        except Exception:
            print(f"Eroare la salvarea progreselor")

    def get_progres_utilizator(self, email):
        if email not in self.progres_utilizatori:
            self.progres_utilizatori[email] = Progres()
        return self.progres_utilizatori[email]

    def sterge_utilizator(self, email):
        mesaj = self.user_manager.sterge_utilizator(email)
        if email in self.progres_utilizatori:
            del self.progres_utilizatori[email]
        self.salveaza_progrese()
        return mesaj

    def show_user_management(self):
        if self.current_frame:
            self.current_frame.pack_forget()
        self.current_frame = AplicatieUtilizatori(self.root, self)
        self.current_frame.pack(fill="both", expand=True)

    def show_activity_tracking(self, email, username):
        if self.current_frame:
            self.current_frame.pack_forget()
        self.current_frame = AplicatieUrmatorActivitate(self.root, self, email, username)
        self.current_frame.pack(fill="both", expand=True)

    def salveaza_date(self):
        self.user_manager.salveaza_date()
        self.salveaza_progrese()
    
    def on_close(self):
        self.salveaza_progrese()
        self.root.destroy()

if __name__ == "__main__":
    root = ttk.Window(themename="cosmo")
    app = AplicatieManager(root)
    root.mainloop()
