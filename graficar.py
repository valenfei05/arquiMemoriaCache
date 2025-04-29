import pandas as pd
import matplotlib
import matplotlib.pyplot as plt

matplotlib.style.use('bmh')
df = pd.read_csv("resultados.csv")


plt.figure()
plt.bar(["Hits", "Misses"], [df["Hits"][0], df["Misses"][0]], color=["#3E92CC", "#FA4659"])
plt.title("Resumen de Accesos a la Caché")
plt.ylabel("Cantidad")
plt.grid(axis='y')

tasa = df["TasaFallos"][0]
plt.text(0.5, max(df["Hits"][0], df["Misses"][0]) * 0.9,
         f"Tasa de fallos: {tasa:.2f}%", ha="center", fontsize=12)

plt.tight_layout()
plt.show()

