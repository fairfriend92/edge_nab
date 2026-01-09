import pandas as pd
import matplotlib.pyplot as plt
import os

os.makedirs("./outputs/figs", exist_ok=True)

df = pd.read_csv("./outputs/scores.csv")

plt.figure(figsize=(12,4))
plt.plot(df["t"], df["score"], linewidth=1)
plt.xlabel("Time step")
plt.ylabel("Anomaly score")
plt.title("Anomaly score over time")
plt.tight_layout()
plt.savefig("./outputs/figs/scores.png")
plt.show()
