# Random number file writer

#   1. Write random integers to a file named randData.txt
#   2. Range of random numbers: [1, 100]
#   3. User specifies quantity of random numbers to store in file

import random


def generateRandomNumber(min, max):
    randomValue = random.randint(min, max)
    return randomValue

def main():
    totalNumbers = int(input("How many random values do you " + \
                        "to store in the file? "))

    # open(filename, mode) returns file object
    outFile = open("randData.txt", "w")

    count = 0
    while count < totalNumbers:

        randomValue = generateRandomNumber(1, 500)
        # can only write a string to a file, append space
        outFile.write(str(randomValue) + ' ')
        count += 1

    outFile.write('\n')          # write newline at end of file

    # close file when finished with it. Immediately frees up system resources.
    outFile.close()

    print("task complete, wrote " + str(count) + " random values to file")


if __name__ == "__main__":
    main()