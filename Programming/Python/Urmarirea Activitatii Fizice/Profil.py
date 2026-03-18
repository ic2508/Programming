import tkinter as tk
from tkinter import filedialog, simpledialog, messagebox
from PIL import Image, ImageTk
from tkinter import ttk
from ttkbootstrap import Style

class FereastraProfil(tk.Toplevel):
    def __init__(self, parent, email, username, callback_update_profil, save_user_changes):
        super().__init__(parent)
        self.title("Editare profil")
        self.geometry("400x800")
        self.resizable(False, False)
        self.iconbitmap("TopG.ico")
        
        self.email = email
        self.username = username
        self.callback_update_profil = callback_update_profil
        self.save_user_changes = save_user_changes

        self.avatar_path = None
        self.avatar_image = None

        self.bg_color = "#ffefd5" 
        self.configure(bg="#ffefd5")

        self.setup_ui()
        self.attributes("-topmost", True)

        self.grab_set()
    
        
    def setup_ui(self):
        style = ttk.Style()
        style.configure("Custom.TLabel", background="#ffefd5", font=("Roboto", 14))
        
        self.avatar_canvas = tk.Canvas(
            self, width=300, height=300, bg=self.bg_color,
            highlightthickness=0
        )
        self.avatar_canvas.pack(pady=20)
        
        self.avatar_canvas.create_rectangle(
            0, 0, 300, 300,
            outline="black", width=3
        )
        
            
        btn_incarca_avatar = tk.Button(
            self, text="Schimbă imagine", command=self.incarca_imagine_profil, fg="white"
        )
        btn_incarca_avatar.pack(pady=10)

        ttk.Label(self, text="Nume utilizator:", style="Custom.TLabel").pack(pady=5)
        self.entry_username = tk.Entry(self, font=("Arial", 12), justify="center", bg=self.bg_color, relief="solid")
        self.entry_username.insert(0, self.username)
        self.entry_username.pack(pady=10)

        ttk.Label(self, text="Parolă nouă:", style="Custom.TLabel").pack(pady=5)
        self.entry_new_password = tk.Entry(self, font=("Arial", 12), justify="center", show="*", bg=self.bg_color, relief="solid")
        self.entry_new_password.pack(pady=10)

        ttk.Label(self, text="Confirmă parola:", style="Custom.TLabel").pack(pady=5)
        self.entry_confirm_password = tk.Entry(self, font=("Arial", 12), justify="center", show="*", bg=self.bg_color, relief="solid")
        self.entry_confirm_password.pack(pady=10)

        btn_salvare = ttk.Button(
            self, text="Salvează modificările", command=self.salvare_modificari, bootstyle="success"
        )
        btn_salvare.pack(pady=20)
    def incarca_imagine_profil(self):
        self.attributes("-topmost", False) 
        file_path = filedialog.askopenfilename(filetypes=[("Imagini", "*.png;*.jpg;*.jpeg")])
        self.attributes("-topmost", True)
        if file_path:
            self.avatar_path = file_path
            self.afiseaza_avatar()

    def afiseaza_avatar(self):
        if self.avatar_path:
            try:
                img = Image.open(self.avatar_path).resize((300, 300))
                self.avatar_image = ImageTk.PhotoImage(img)
                canvas_width = int(self.avatar_canvas.cget("width"))
                canvas_height = int(self.avatar_canvas.cget("height"))
                self.avatar_canvas.delete("all")
                x_center = (canvas_width - 300) // 2
                y_center = (canvas_height - 300) // 2
                self.avatar_canvas.create_image(x_center, y_center, image=self.avatar_image, anchor="nw")
            except Exception as e:
                print(f"Eroare la încărcarea imaginii de profil: {e}")

    def valideaza_parola(self, parola):
        simboluri_permise = "@#$!%^&*()_+-=[]{}|;:',.<>?/`~"
        if not (5 <= len(parola) <= 20):
            return "Parola trebuie să aibă între 5 și 20 de caractere."
        if not any(char.isdigit() for char in parola):
            return "Parola trebuie să conțină cel puțin o cifră."
        if not any(char in simboluri_permise for char in parola):
            return "Parola trebuie să conțină cel puțin un simbol."
        return None

    def salvare_modificari(self):
        new_username = self.entry_username.get()
        new_password = self.entry_new_password.get()
        confirm_password = self.entry_confirm_password.get()
    
        if not new_password and not confirm_password:
            self.save_user_changes(self.email, new_username, self.avatar_path, None)
            self.callback_update_profil(new_username, self.avatar_path)
            self.destroy()
            return
    
        if new_password != confirm_password:
            messagebox.showerror("Eroare", "Parolele nu se potrivesc!")
            return
    
        mesaj_eroare = self.valideaza_parola(new_password)
        if mesaj_eroare:
            messagebox.showerror("Eroare", mesaj_eroare)
            return
   
        self.save_user_changes(self.email, new_username, self.avatar_path, new_password)
        self.callback_update_profil(new_username, self.avatar_path)
        self.destroy()
