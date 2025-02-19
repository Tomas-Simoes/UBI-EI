import tkinter as tk
from tkinter import ttk, messagebox, simpledialog, scrolledtext
import pyodbc


class DatabaseApp:
    DEBUG_MODE = True
    DB_IP = "192.168.100.14"
    DB_USER =  "User_BD_PL4_07"
    DB_PASSWORD = "diubi:2024!BD!PL4_07"
    DB_NAME = "BD_PL4_07"
    
    def __init__(self, root):
        self.root = root
        self.root.title("Aplicação")

        self.conn = None
        self.cursor = None
        
        if self.DEBUG_MODE:
            self.connect_to_default()

        self.create_menu()

    def create_menu(self):
        menu_bar = tk.Menu(self.root)

        # Menu de Conexão
        db_menu = tk.Menu(menu_bar, tearoff=0)
        db_menu.add_command(label="Ligar à Base de Dados", command=self.connect_to_db)
        db_menu.add_command(label="Connect Default Database", command=self.connect_to_default)
        db_menu.add_separator()
        db_menu.add_command(label="Sair", command=self.root.quit)
        menu_bar.add_cascade(label="Início", menu=db_menu)

        # Menu CRUD
        crud_menu = tk.Menu(menu_bar, tearoff=0)
        crud_menu.add_command(label="Adicionar Dados", command=self.add_data)
        crud_menu.add_command(label="Atualizar Dados", command=self.update_data)
        crud_menu.add_command(label="Apagar Dados", command=self.delete_data)
        crud_menu.add_command(label="Visualizar Dados", command=self.view_data)
        crud_menu.add_command(label="Query Genérica", command=self.generic_query)
        menu_bar.add_cascade(label="Operações CRUD", menu=crud_menu)

        # Menu About
        about_menu = tk.Menu(menu_bar, tearoff=0)
        about_menu.add_command(label="Sobre",
                               command=lambda: messagebox.showinfo("Sobre", "Aplicação CRUD com Tkinter e PyODBC"))
        menu_bar.add_cascade(label="Ajuda", menu=about_menu)

        self.root.config(menu=menu_bar)

    def connect_to_default(self):
        try:
            self.conn = pyodbc.connect(
                f"DRIVER={{SQL Server}};SERVER={self.DB_IP};DATABASE={self.DB_NAME};UID={self.DB_USER};PWD={self.DB_PASSWORD}")
            self.cursor = self.conn.cursor()
            messagebox.showinfo("Sucesso", "Ligação efetuada com sucesso!")
        except Exception as e:
            messagebox.showerror("Erro na ligação", f"Erro no acesso à base de dados: {e}")


    def connect_to_db(self):
        try:
            ip = simpledialog.askstring("Ligação", "Insira o IP do servidor:")
            user = simpledialog.askstring("Ligação", "Insira o utilizador:")
            password = simpledialog.askstring("Ligação", "Insira a password:", show="*")
            database = simpledialog.askstring("Ligação", "Insira o nome da base de dados:")

            self.conn = pyodbc.connect(
                f"DRIVER={{SQL Server}};SERVER={ip};DATABASE={database};UID={user};PWD={password}")
            self.cursor = self.conn.cursor()
            messagebox.showinfo("Sucesso", "Ligação efetuada com sucesso!")
        except Exception as e:
            messagebox.showerror("Erro na ligação", f"Erro no acesso à base de dados: {e}")
    
    def get_table_names(self):
        try:
            self.cursor.execute("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_TYPE = 'BASE TABLE'")
            return [row.TABLE_NAME for row in self.cursor.fetchall()]
        except Exception as e:
            messagebox.showerror("Erro", f"Erro ao obter tabelas: {e}")
            return []

    def add_data(self):
        if self.cursor:
            view_window = tk.Toplevel(self.root)
            view_window.title("Adicionar em tabela")

            tk.Label(view_window, text="Selecione a tabela: ").pack(pady=5)
            table_dropdown = ttk.Combobox(view_window, values=self.get_table_names())
            table_dropdown.pack(pady=5)

            tk.Label(view_window, text="Selecione a coluna: ").pack(pady=5)
            column_listbox = tk.Listbox(view_window, selectmode=tk.MULTIPLE, height=10)
            column_listbox.pack(pady=5)

            def update_column_dropdown(event):
                selected_table = table_dropdown.get()
                if selected_table:
                    self.cursor.execute(f"SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = '{selected_table}'")
                    columns = [row.COLUMN_NAME for row in self.cursor.fetchall()]
                    
                    column_listbox.delete(0, tk.END)
                    for col in columns:
                        column_listbox.insert(tk.END, col)
            
            table_dropdown.bind("<<ComboboxSelected>>", update_column_dropdown)

            tk.Label(view_window, text="Valores (separados por vírgula):").pack(pady=5)
            value_entry = tk.Entry(view_window, width=50)
            value_entry.pack(pady=5)

            def insert_data():    
                table = table_dropdown.get()
                selected_columns= [column_listbox.get(i) for i in column_listbox.curselection()]
                values = value_entry.get()

                if table and selected_columns and values:
                    try:
                        columns_str = ", ".join(selected_columns)
                        placeholders = ", ".join(["?"] * len(selected_columns))  
                        values_tuple = tuple(values.split(","))  

                        query = f"INSERT INTO {table} ({columns_str}) VALUES ({placeholders})"
                        self.cursor.execute(query, values_tuple)
                        self.conn.commit()
                        messagebox.showinfo("Sucesso", "Dados adicionados com sucesso!")
                    
                    except Exception as e:
                        messagebox.showerror("Erro", f"Erro ao adicionar dados: {e}")

                else:
                    messagebox.showwarning("Aviso", "Preencha todos os campos!")
        else:
            messagebox.showwarning("Aviso", "Precisa de se ligar à base de dados primeiro.")

    def update_data(self):
        if self.cursor:
            table = simpledialog.askstring("Atualizar Dados", "Nome da Tabela:")
            set_clause = simpledialog.askstring("Atualizar Dados", "SET (ex: coluna='valor'):")
            condition = simpledialog.askstring("Atualizar Dados", "Condição WHERE (opcional):")
            query = f"UPDATE {table} SET {set_clause}"
            if condition:
                query += f" WHERE {condition}"
            try:
                self.cursor.execute(query)
                self.conn.commit()
                messagebox.showinfo("Sucesso", "Dados atualizados com sucesso!")
            except Exception as e:
                messagebox.showerror("Erro", f"Erro ao atualizar dados: {e}")
        else:
            messagebox.showwarning("Aviso", "Ligue-se à base de dados primeiro.")

    def delete_data(self):
        if self.cursor:
            table = simpledialog.askstring("Apagar Dados", "Nome da Tabela:")
            condition = simpledialog.askstring("Apagar Dados", "Condição WHERE:")
            try:
                self.cursor.execute(f"DELETE FROM {table} WHERE {condition}")
                self.conn.commit()
                messagebox.showinfo("Sucesso", "Dados apagados com sucesso!")
            except Exception as e:
                messagebox.showerror("Erro", f"Erro ao apagar dados: {e}")
        else:
            messagebox.showwarning("Aviso", "Liggue-se à base de dados primeiro.")

    def view_data(self):
        if self.cursor:
            try:
                tables = self.get_table_names()

                def fetch_table_data():
                    selected_table = table_dropdown.get()
                    if selected_table:
                        self.cursor.execute(f"SELECT * FROM {selected_table}")
                        columns = [desc[0] for desc in self.cursor.description]
                        rows = self.cursor.fetchall()
                        output.delete("1.0", tk.END)
                        output.insert(tk.END, f"Colunas: {', '.join(columns)}\n\n")
                        for row in rows:
                            output.insert(tk.END, f"{row}\n")
                    else:
                        messagebox.showwarning("Aviso", "Selecione uma tabela.")

                view_window = tk.Toplevel(self.root)
                view_window.title("Visualizar Tabela")

                table_dropdown = ttk.Combobox(view_window, values=tables)
                table_dropdown.pack(pady=5)

                view_button = ttk.Button(view_window, text="Visualizar", command=fetch_table_data)
                view_button.pack(pady=5)

                output = scrolledtext.ScrolledText(view_window, width=80, height=20)
                output.pack(pady=5)

            except Exception as e:
                messagebox.showerror("Erro", f"Erro ao obter tabelas: {e}")
        else:
            messagebox.showwarning("Aviso", "Ligue-se à base de dados primeiro.")

    def generic_query(self):
        if self.cursor:
            query = simpledialog.askstring("Query Genérica", "Escreva a query SQL:")
            try:
                self.cursor.execute(query)
                columns = [desc[0] for desc in self.cursor.description]
                rows = self.cursor.fetchall()

                result_window = tk.Toplevel(self.root)
                result_window.title("Resultados da Query Genérica")

                output = scrolledtext.ScrolledText(result_window, width=80, height=20)
                output.pack(pady=5)
                output.insert(tk.END, f"Colunas: {', '.join(columns)}\n\n")
                for row in rows:
                    output.insert(tk.END, f"{row}\n")

            except Exception as e:
                messagebox.showerror("Erro", f"Erro na execução da query: {e}")
        else:
            messagebox.showwarning("Aviso", "Ligue-se à base de dados primeiro.")

if __name__ == "__main__":
    root = tk.Tk()
    app = DatabaseApp(root)
    root.mainloop()
