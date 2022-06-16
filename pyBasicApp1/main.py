from uuid import UUID
from flask import Blueprint, Flask
from typing import List

class User:
    def __init__(self, name) -> None:
        self.alias : str = name
        self.password : str = "RandomPassword"
        self.guid : str = "To be generated"

class UserRepository:
    def __init__(self) -> None:
        self.allUsers : List[User] = []
        self.userLimit = 10
        pass

    def addUser(self, name:str) -> User:
        exsistingUsers = self.findUser(name)
        if len(exsistingUsers) == 0:
            return "PQ"
        
        newUser = User(name)

        if len(self.allUsers) > self.userLimit:
            return "Exception"

        self.allUsers.append(newUser)
        return newUser
    
    def removeUser(self, userUUID: str) -> bool:
        pass

    def getUserDetail(self, userUUID:str) -> User:
        pass

    def findUser(self, name:str) -> List[User]:
        return []
    
    def updateName(self, userID: UUID ):
        pass

app = Flask(__name__)

userBluePrint = Blueprint("user","usercontroller")

def createUser():
    print("Should create a new user")
    pass

def findUserById():
    print("Should find a user by ID")
    pass

def removeUserById():
    print("Should be able to remove the user by id")
    pass

def updateNameForUser():
    print("User with the ID alian would be updated")
    pass

def main():
    print("Invoking the main command")

    # This would make the server run on the dault port
    # which is 5000 in this case
    app.run()

if __name__ == "__main__":
    main()
