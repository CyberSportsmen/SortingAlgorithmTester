import os
import random
import threading

# ---- constants ----
max_long_long = 2 ** 63 - 1
min_long_long = -2 ** 63
max_int = 2 ** 31 - 1
min_int = -2 ** 31
# ---- END_constants ----

# ---- config -----
listTags = ["sorted", "sorted descending", "almostsorted", "almostsorted descending", "random"]
listLengths = [100]  # reduced some lengths for demonstration
listValueIntervals = [
    (0, 100),
    (-100, 100),
    (-1000000, 1000000),
    (min_int, max_int),
    (min_long_long, max_long_long)
]
# Base directory to store generated files
baseDir = "generated_files"
# ---- END_config ----

def createRandomArray(length, valueinterval):
    interval_left, interval_right = valueinterval
    randomArray = []
    for _ in range(length):
        # using randint directly; it supports big numbers in Python
        randomArray.append(random.randint(interval_left, interval_right))
    return randomArray

def createFile(tags, length, valueinterval):
    # Prepare tag properties and file naming parts
    proprieties = tags.split()
    isSorted = "sorted" in proprieties
    isAlmostSorted = "almostsorted" in proprieties
    isRandom = "random" in proprieties
    isDescending = "descending" in proprieties
    intervalLeft, intervalRight = valueinterval

    sortedstr = "sorted_" if isSorted else ""
    almostsortedstr = "almostsorted_" if isAlmostSorted else ""
    randomstr = "random_" if isRandom else ""
    descendingstr = "descending_" if isDescending else ""

    # Build the file name
    fileNameOnly = f"{sortedstr}{almostsortedstr}{randomstr}{descendingstr}{length}_interval_{intervalLeft}_{intervalRight}.txt"

    # Create a directory for this tag inside the base directory.
    # Replace spaces with underscores to create valid folder names.
    tagDir = tags.replace(" ", "_")
    targetDir = os.path.join(baseDir, tagDir)
    os.makedirs(targetDir, exist_ok=True)

    # Full file path
    filePath = os.path.join(targetDir, fileNameOnly)

    with open(filePath, "w") as file:
        file.write(str(length) + "\n")
        arr = createRandomArray(length, valueinterval)

        if isSorted:
            arr.sort()
        if isAlmostSorted:
            arr.sort()
            for i in range(len(arr) - 1):
                if random.randint(0, 10) == 0:  # roughly 1 in 10 chance to swap
                    arr[i], arr[i + 1] = arr[i + 1], arr[i]
        if isDescending:
            arr = arr[::-1]
        for value in arr:
            file.write(str(value) + " ")

def main():
    threads = []
    testcaseNr = 0

    for tag in listTags:
        for length in listLengths:
            for valueInterval in listValueIntervals:
                testcaseNr += 1
                # Create a new thread for each file creation task
                thread = threading.Thread(target=createFile, args=(tag, length, valueInterval))
                threads.append(thread)
                thread.start()
                print(f"Started testcase {testcaseNr}")

    # Wait for all threads to finish
    for thread in threads:
        thread.join()

if __name__ == "__main__":
    main()
