#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

while True:
    df = pd.read_csv("MyFile.csv")
    #df


    # In[2]:


    idq = input("Ingrese el id del paciente : ")
    df_1 = df[df["ID"] == int(idq)]
    df_1


    # In[3]:


    def plot_pat(line_color,column,title,xtitle,ytitle):
        sns.set(rc={'figure.figsize':(20,15)})
        sns.set(font_scale = 2)
        sns.set_style("whitegrid")
        plt.title(title)
        plt.xlabel(xtitle)
        plt.ylabel(ytitle)
        sns.lineplot(x=[i for i in range(df_1.shape[0])], 
                    y=df_1[column],color = line_color,linewidth  = 2)
        plt.show()


    # In[4]:


    title = "Patient with Id = {} and it BPM behavior".format(idq)
    plot_pat("#00b68f","bpmSENSOR",title, "Time", "bpm measure")


    # In[5]:


    title = "Patient with Id = {} and it SpO2 behavior".format(idq)
    plot_pat("#641be5","spo2SENSOR",title, "Time", "bpm measure")


    # In[ ]:




