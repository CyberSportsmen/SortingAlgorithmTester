import random

#---- constants ----
max_long_long = 2**63 - 1
min_long_long = -2**63
max_int = 2**31 - 1
min_int = -2**31
#---- END_constants ----
#---- config -----
listTags = ["sorted", "sorted descending", "almostsorted", "almostsorted descending", "random"]
listLengths = [100000, 1000000, 10000000, 100000000, 1000000000] # a milliard will kill my time lol, we might need to implement threads for printing results and testing
listValueIntervals = [(0, 100), (-100, 100), (-1000000, 1000000), (min_int, max_int), (min_long_long, max_long_long)]
#---- END_config ----

def createRandomArray(length, valueinterval):
    randomArray = []
    for i in range(length):
        randomArray.append(random.randint(valueinterval[0], valueinterval[1]))
    return randomArray

def createFile(tags, length, valueinterval):
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
    fileName = sortedstr + almostsortedstr + randomstr + descendingstr + str(length) + "_interval_" + str(intervalLeft) + "_" + str(intervalRight) + ".txt"
    #print(fileName)
    with open(fileName, "w") as file:
        # create a vector with specific proprieties
        arr = createRandomArray(length, valueinterval)

def main():
    testcaseNr = 0
    for tag in listTags:
        for length in listLengths:
            for valueInterval in listValueIntervals:
                testcaseNr += 1
                createFile(tag, length, valueInterval)
                print(testcaseNr)

if __name__ == "__main__":
    main()