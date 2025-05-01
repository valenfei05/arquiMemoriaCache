import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("resultados.csv")

plt.style.use("bmh")
plt.figure(figsize=(10, 5))

plt.plot(df["Acceso"], df["TasaFallos"], color="#1f77b4", marker="o", linewidth=2, label="Tasa de Fallos (%)")

ultimo_acceso = df["Acceso"].iloc[-1]
tasa_final = df["TasaFallos"].iloc[-1]
plt.annotate(f"{tasa_final:.1f}%",
             (ultimo_acceso, tasa_final),
             textcoords="offset points",
             xytext=(-15, 10),
             ha='center',
             fontsize=10,
             color="black",
             bbox=dict(boxstyle="round,pad=0.3", fc="white", ec="black", lw=1))

plt.title("Tasa de Fallos de Caché (Miss Rate)")
plt.xlabel("Total de Accesos")
plt.ylabel("Misses (%)")
plt.ylim(0, 100)
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
