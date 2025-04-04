import os
import random
import struct
import threading

# ---- constants ----
max_long_long = 2 ** 63 - 1
min_long_long = -2 ** 63
max_int = 2 ** 31 - 1
min_int = -2 ** 31
# ---- END_constants ----

# ---- config -----
listTags = ["sorted", "sorted descending", "almostsorted", "almostsorted descending", "random"]
listLengths = [100]  # Adjust as needed
listValueIntervals = [
    (0, 100),
    (-100, 100),
    (-1000000, 1000000),
    (min_int, max_int),
    (min_long_long, max_long_long)
]
baseDir = "generated_files"
# ---- END_config ----

def createRandomArray(length, valueinterval):
    return [random.randint(*valueinterval) for _ in range(length)]

def createBinaryFile(tags, length, valueinterval):
    proprieties = tags.split()
    isSorted = "sorted" in proprieties
    isAlmostSorted = "almostsorted" in proprieties
    isDescending = "descending" in proprieties

    # Construct the filename
    fileNameOnly = f"{tags.replace(' ', '_')}_{length}_interval_{valueinterval[0]}_{valueinterval[1]}.bin"
    tagDir = os.path.join(baseDir, tags.replace(" ", "_"))
    os.makedirs(tagDir, exist_ok=True)
    filePath = os.path.join(tagDir, fileNameOnly)

    arr = createRandomArray(length, valueinterval)

    # Apply sorting logic
    if isSorted:
        arr.sort()
    if isAlmostSorted:
        arr.sort()
        for i in range(len(arr) - 1):
            if random.randint(0, 10) == 0:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
    if isDescending:
        arr.reverse()

    # Write in binary mode using struct
    with open(filePath, "wb") as file:
        for value in arr:
            file.write(struct.pack("q", value))  # "q" means signed long long (8 bytes)

def main():
    threads = []
    testcaseNr = 0

    for tag in listTags:
        for length in listLengths:
            for valueInterval in listValueIntervals:
                testcaseNr += 1
                thread = threading.Thread(target=createBinaryFile, args=(tag, length, valueInterval))
                threads.append(thread)
                thread.start()
                print(f"Started testcase {testcaseNr}")

    for thread in threads:
        thread.join()

if __name__ == "__main__":
    main()
