import sys

import requests


def getArg():
    if len(sys.argv) != 2:
        print("You forgot paramaters!")
        sys.exit(1)
    else:
        return str(sys.argv[1])


def checkArg(arg: str):
    if not arg.startswith("https://"):
        updatedTarget = str("https://" + arg)
        print(f"Sending GET req to {updatedTarget}")
        return updatedTarget
    return arg


def sendReq(url: str):
    try:
        response = requests.get(url)
        print(f"Status: {response.status_code}")
        print(f"Headers: {response.headers['content-type']}")
        print(f"Response: {response.headers}")
        print(f"JSON: {response.json()}")

    except Exception as e:
        print(f"Error: {e}")
    except KeyboardInterrupt:
        print("Interrupted")


sendReq(checkArg(getArg()))
