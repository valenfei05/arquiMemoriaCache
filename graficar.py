import pandas as pd
import matplotlib.pyplot as plt

# Leer el archivo CSV
df = pd.read_csv("resultados.csv")

# Crear la gráfica
plt.figure()
plt.bar(["Hits", "Misses"], [df["Hits"][0], df["Misses"][0]], color=["green", "red"])
plt.title("Resumen de Accesos a la Caché")
plt.ylabel("Cantidad")
plt.grid(axis='y')

# Mostrar la tasa de fallos como texto
tasa = df["TasaFallos"][0]
plt.text(0.5, max(df["Hits"][0], df["Misses"][0]) * 0.9,
         f"Tasa de fallos: {tasa:.2f}%", ha="center", fontsize=12)

plt.tight_layout()
plt.show()
ñ