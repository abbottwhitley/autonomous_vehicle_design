# Read entire file contents


def main():
    print("Lesson 3 - read file contents\n")

    fileName = input("Enter file name: ")

    with open(fileName, 'r') as f:
        print("\nfile contents")
        data = f.read()
        print(data)
        print("type(data)", end=' ')
        print(type(data))
    
    print("program ending")


if __name__ == "__main__":
    main()