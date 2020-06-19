
import matplotlib.pylab as plt
import numpy as np


#Carga de los archivos con data
x,y,z = np.loadtxt("20fn.txt", delimiter = " ", unpack=True)
x1,y1,z1 = np.loadtxt("8fsn.txt", delimiter = " ", unpack=True)
x2,y2,z2 = np.loadtxt("8hn.txt", delimiter = " ", unpack=True)
TITULO = "TITULO" #Para el título del gráfico
TEXTO="aca va una descripcion sobre lo que se en el \n grafico para poder explicar mejor"


plt.figure()
#plt.subplot(321)
plt.plot(x,y," ",marker="o",color="b",label="FN")
plt.plot(x1,y1," ",marker="o",color="r",label="FSN")
plt.plot(x2,y2,"--",marker="o",color="g",label="HN")

#Para la desviacion estandar
#plt.errorbar(x,y,yerr=z,fmt="o")

#Para representar muchos graficos en una figura
'''
plt.subplot(322)
plt.plot(x,y," ",marker="o",color="b",label="FN")
plt.plot(x1,y1," ",marker="o",color="r",label="FSN")
plt.plot(x2,y2,"--",marker="o",color="g",label="HN")
'''

#Para la cuadrícula
plt.grid(b=True, which='major', color='#666666', linestyle='-')
plt.minorticks_on()
plt.grid(b=True, which='minor', color='k', linestyle=':', alpha=1)

#Para la leyenda
plt.legend(loc="upper right",title="interacciones")
#Para los ejes
plt.xlabel("Q",fontweight='bold',size=20)
plt.ylabel("<S_máx>/A",fontweight='bold',size=15)

#Para el título del gráfico
plt.title(TITULO,fontweight='bold',size=20)

#Para escala logarítmica
#plt.xscale('log')

#Para añadir texto descriptivo en algún gráfico
plt.text(25, 0.25, TEXTO, fontsize=10)

plt.show()


