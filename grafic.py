import re
import matplotlib.pyplot as plt
import pandas as pd
from collections import defaultdict

data = defaultdict(list)
test_index = 0

file_line_pattern = re.compile(r"^==== File:")
time_line_pattern = re.compile(r"Thread (\w+) took (\d+) ms")

with open("log.txt", "r") as f:
    for line in f:
        line = line.strip()
        if file_line_pattern.match(line):
            test_index += 1
        else:
            match = time_line_pattern.match(line)
            if match:
                algorithm = match.group(1)
                time = int(match.group(2))
                data[algorithm].append((test_index, time))

df = pd.DataFrame()
for algorithm, values in data.items():
    for test_idx, time in values:
        df.loc[test_idx, algorithm] = time

df.sort_index(inplace=True)

group1 = ["MERGE", "QUICK", "HEAP", "STL"]
group2 = [col for col in df.columns if col not in group1]

def plot_group(group, title, filename):
    plt.figure(figsize=(14, 7))
    for algo in group:
        if algo in df.columns:
            plt.plot(df.index, df[algo], marker='o', label=algo)

    plt.xlabel("Numărul testului")
    plt.ylabel("Timp de execuție (ms)")
    plt.title(title)
    plt.legend()
    plt.grid(True)

    avg_text = " | ".join(
        f"{algo}: {df[algo].mean():.2f} ms" for algo in group if algo in df.columns
    )
    plt.figtext(0.5, -0.05, f"Medii: {avg_text}", ha="center", fontsize=10)

    plt.tight_layout()
    plt.savefig(filename, bbox_inches='tight')
    plt.show()

plot_group(group1, "Algoritmi de sortare in O(nlogn): MERGE, QUICK, HEAP, STL.", "nlogn.png")
plot_group(group2, "Algoritmi de sortare  speciali: SHELL, RADIX, BUCKET.", "speciali.png")
