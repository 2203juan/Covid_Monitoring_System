import tkinter as tk
from tkinter.constants import W
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

root = tk.Tk() # VENTANA DE LA APLICACION

# Configurar la geometria, color y titulo de la ventana
root.geometry("400x100")
root.configure(bg="#D1DDF9")
root.title("COVID19 APP")

# Declaración de la variable que se lee en el formulario
name_var = tk.IntVar()

# Funcion para enviar los datos ingresados en el formulario
def submit():
    df = pd.read_csv("MyFile.csv") # Se lee el archivo y se carga en un dataframe

    idq = name_var.get() # Se toma el valor leido del formulario
    df_1 = df[df["ID"] == int(idq)] # se filtra por el paciente suministrado

    def plot_pat(line_color,column,title,xtitle,ytitle):
        """ 
        Esta funcion sirve para generar el grafico
        de las medidas de los sensores vs tiempo
        """
        sns.set(rc={'figure.figsize':(20,15)})
        sns.set(font_scale = 2)
        sns.set_style("whitegrid")
        plt.title(title)
        plt.xlabel(xtitle)
        plt.ylabel(ytitle)
        sns.lineplot(x=[i for i in range(df_1.shape[0])], 
                    y=df_1[column],color = line_color,linewidth  = 2)
        plt.show()


    title = "Patient with Id = {} and it BPM behavior".format(idq)
    plot_pat("#00b68f","bpmSENSOR",title, "Time", "bpm measure")

    title = "Patient with Id = {} and it SpO2 behavior".format(idq)
    plot_pat("#641be5","spo2SENSOR",title, "Time", "bpm measure")
	
# Etiqueta para el titulo de la aplicacion
nameapp_label = tk.Label(root, text = 'COVID MONITOR SYSTEM', font=('calibre',11, 'bold'))
# Etiqueta para indicarle al usuario lo que debe ingresar en el formulario
name_label = tk.Label(root, text = 'Enter\nPatient ID ', font=('calibre',10, 'bold'))

# Formulario
name_entry = tk.Entry(root,textvariable = name_var,font=('calibre',20,'normal'))

# Boton para enviar el id del paciente ingresado
sub_btn=tk.Button(root,text = 'Submit', command = submit, background="#608DF6", activebackground="#ffffff", width=5, height=2, anchor="center", font=('calibre',12,'normal'))

# Ubicar los widgets en la ventana creada (usando grillas matriciales)
nameapp_label.grid(row=1,column=1)
name_label.grid(row=2,column=0)
name_entry.grid(row=2,column=1)
sub_btn.grid(row=4,column=1)

# Mostrar continuamente la ventana
root.mainloop()
