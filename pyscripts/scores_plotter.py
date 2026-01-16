import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("./outputs/scores.csv")

plt.figure(figsize=(14,6))

plt.plot(df["t"], df["state"], label="state", linewidth=1)
plt.plot(df["t"], df["baseline"], label="baseline", linewidth=2)
plt.plot(df["t"], df["score"], label="rectified score", linewidth=1)

plt.scatter(
    df[df["anomaly"] == 1]["t"],
    df[df["anomaly"] == 1]["score"],
    color="red", s=10, label="anomaly"
)

plt.xlabel("Time step")
plt.ylabel("Value")
plt.title("Temporal operator with rectified score and threshold")
plt.legend()
plt.tight_layout()
plt.savefig("./outputs/figs/scores.png")
plt.show()