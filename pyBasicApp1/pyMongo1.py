from typing import Dict
from datetime import datetime
import os
import pymongo

# This is the model class that we would be using the
class TodoItem:
    def __init__(self, caption : str, desc : str = "") -> None:
        self.taskCaption : str = caption
        self.taskDescription : str = desc
        self.taskCreationTime : datetime = datetime.now()

        if len(desc) != 0 :
            self.taskDescription = desc
    
    def getDict(self) -> Dict:
        returnObject = {
            "caption" : self.taskDescription,
            "description" : self.taskCaption
        }

        return returnObject;

# This class should retrun the DB URL that I am going to connect to
class ConnectionBuilder:
    def __init__(self,usr = "administrator") -> None:
        self.dbUserName = usr
        self.options = "?retryWrites=true&w=majority"
        self.cluster = "cluster0.ozsgds8.mongodb.net"

    def getConnectionString(self) -> str:
        connectionString = ""
        connectionString += "mongodb+srv://"
        connectionString += self.dbUserName

        # Updating the password
        databasePassword = os.environ['DBPASSWORD']
        connectionString += ":"
        connectionString += databasePassword

        # Updating the hostname
        connectionString += "@"
        connectionString += self.cluster
        connectionString += "/"

        # Adding the options
        connectionString += self.options

        return connectionString

# This repository should be bound the model class
# TodoItem  
class TodoRepository:
    def __init__(self) -> None:
        pass

    def addTodo(task:TodoItem) -> str:
        return ""
    
    def findTodoItem(id:str) -> TodoItem:
        pass

    def deleteTodoItem(id:str) -> bool:
        return False;
    
    def updateDescription(id:str, desc:str) -> bool:
        return False;
    
    def updateCaption(id:str, caption:str) -> bool:
        return False;

dbConnection : pymongo.MongoClient = None
todoDB = None

# Function Entry point
def main():
    print("Running simple MongoDB CRUD Prog")

    connBuilder = ConnectionBuilder();
    connString = connBuilder.getConnectionString()
    print("Using connection string {0}".format(connString))

    dbConnection = pymongo.MongoClient(connString)
    todoDB = dbConnection.get_database("todo")
    print(todoDB)

    # TODO: This can be automated using some kind of helper
    # library, there might be packages that are present but not going to
    # use it
    option:int = -1
    while option != 0:
        print("1. Add Todo Item task")
        print("2. Remove Todo Item task")
        print("3. Update Task")
        print("4. Find Task")
        print("0. Exit")

        userInput = input("Your Option:")
        option = int(userInput)

        if option == 1:
            newTaskCaption = input("Caption:")
            newTaskDescription = input("Description:")

            newTask = TodoItem(newTaskCaption, newTaskDescription);
            print(newTask)
        elif option == 3:
            taskId = input("Id:")


# Function entry point
if __name__ == "__main__":
    main()
