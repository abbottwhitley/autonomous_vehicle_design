# Read strings from a file, line by line

def main():
    print("Lesson 4 - read line by line\n")

    fileName = input("Enter file name: ")
   
    with open(fileName, 'r') as f:
            for line in f.readlines():
                print(line, end='') # don't print additional new line character
    
    print("program ending")


if __name__ == "__main__":
    main()