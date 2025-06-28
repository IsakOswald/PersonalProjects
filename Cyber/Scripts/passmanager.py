import json
import os

FILEPATH = "passwords.json"


def checkFile():
    if not os.path.exists(FILEPATH):
        with open(FILEPATH, "w") as file:
            json.dump([{"count": 0}], file)


def retCurrentList():
    try:
        with open(FILEPATH, "r") as file:
            return json.load(file)
    except Exception as e:
        print(f"Error {e}")
        return []


def printCurrentList():
    try:
        currentusrs = retCurrentList()
        for i in currentusrs:
            print(i)
    except Exception as e:
        print(f"Error: {e}")
        exit(1)


def getAmmountOfUsrs():
    ammount = retCurrentList()

    return ammount[0]["count"]


def createNewEntry(website, username, password):
    currentusrs: list = retCurrentList()
    ammountofusrs = getAmmountOfUsrs() + 1

    newEntry = {
        "website": website,
        "username": username,
        "password": password,
        "ID": ammountofusrs,
    }

    currentusrs.append(newEntry)
    currentusrs[0]["count"] += 1

    with open(FILEPATH, "w") as file:
        json.dump(currentusrs, file, indent=4)

    print("New entry appended")


def removeAll():
    with open(FILEPATH, "w") as file:
        json.dump([{"count": 0}], file)

    print("Removed all entries")


def main():
    print("|-------------------------------|")
    print("         Pass Manager            ")
    print("|-------------------------------|")

    checkFile()

    print("Usage:")
    print("[A] to append account ")
    print("[V] to view accounts")
    print("[R] REMOVEALL (WARNING!)")
    print("[~] any other key to quit")

    availableActions = ["A", "V", "R"]

    action = input("What do you want to do?: ").upper()

    while action in availableActions:
        if action == "A":
            website = input("Enter website: ").lower()
            username = input("Enter username: ")
            password = input("Enter password: ")

            createNewEntry(website, username, password)
            action = input("What do you want to do?: ").upper()

        elif action == "V":
            printCurrentList()
            action = input("What do you want to do?: ").upper()
        elif action == "R":
            removeAll()
            action = input("What do you want to do?: ").upper()

        else:
            break


if __name__ == "__main__":
    main()
