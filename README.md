# SortingAlgorithmTester

File Descriptions:
main.py
Generates random test cases and saves them in the generated_files folder.

sort_algorithm_tester.cpp
Contains the implementation of multiple sorting algorithms. It reads test cases and logs the execution times.

tester_script.ps1
A PowerShell script that compiles and runs sort_algorithm_tester.cpp, then stores the sorting performance results into log.txt.

graph.py
Reads data from log.txt and creates two visual charts:

One for the O(n log n) algorithms

One for the "special" or non-standard algorithms
The resulting graphs are saved as two separate image files.

▶️ How to Run the Project
Generate Test Files
Run the Python script:

bash
Copiază
Editează
python main.py
Run Sorting Benchmarks
Execute the PowerShell script (make sure you have the proper permissions):

powershell
Copiază
Editează
./tester_script.ps1
Generate Graphs
Create performance graphs from the log file:

bash
Copiază
Editează
python grafic.py
📝 Output
generated_files/ – Contains generated test inputs.

log.txt – Execution times for each sorting algorithm.

nlogn.png – Performance graph for standard O(n log n) algorithms.

speciali.png – Performance graph for special/custom sorting algorithms.

📌 Requirements
Python 3.x (for main.py and graph.py)

A C++ compiler (for compiling sort_algorithm_tester.cpp)

PowerShell (to run tester_script.ps1)

Python libraries: matplotlib, pandas (install via pip if needed)
