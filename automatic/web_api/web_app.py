from flask import Flask, render_template, request

import pandas as pd
import  seaborn as sns
import  matplotlib.pyplot as plt

app = Flask(__name__)


def plot_pat(df_1,line_color,column,title,xtitle,ytitle,save_label):
    """ 
    Esta funcion sirve para generar el grafico
    de las medidas de los sensores vs tiempo
    """
    sns.set(rc={'figure.figsize':(10,7)})
    sns.set(font_scale = 2)
    sns.set_style("whitegrid")
    plt.title(title)
    plt.xlabel(xtitle)
    plt.ylabel(ytitle)
    sns.lineplot(x=[i for i in range(df_1.shape[0])], 
                y=df_1[column],color = line_color,linewidth  = 2)
    plt.savefig("static/img/"+save_label)
    plt.clf()

def generate_plot(id):
    df = pd.read_csv("../MyFile.csv") # Se lee el archivo y se carga en un dataframe

    df_1 = df[df["ID"] == int(id)] # se filtra por el paciente suministrado
    print(df_1)


    title = "Patient with Id = {} and it BPM behavior".format(id)
    label_a = 'bpm_{}.png'.format(id)
    plot_pat(df_1,"#00b68f","bpmSENSOR",title, "Time (days)", "bpm measure",label_a)

    
    title = "Patient with Id = {} and it SpO2 behavior".format(id)
    label_b = 'spo2_{}.png'.format(id)
    plot_pat(df_1,"#641be5","spo2SENSOR",title, "Time (days)", "bpm measure",label_b)
    return [label_a,label_b]

@app.after_request
def add_header(response):
    """
    Add headers to both force latest IE rendering engine or Chrome Frame,
    and also to cache the rendered page for 10 minutes.
    """
    response.headers['X-UA-Compatible'] = 'IE=Edge,chrome=1'
    response.headers['Cache-Control'] = 'public, max-age=0'
    return response

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/patient_form",methods = ["GET"])
def patient_get():
    return render_template("prediction.html")

@app.route("/show_behavior",methods = ["POST"])
def patien_post():
    id = request.form["cedula"]
    #print("patient id:",id)
    data = generate_plot(id)
    return render_template("show_behavior.html", data = data)

