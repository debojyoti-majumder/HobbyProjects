from typing import Collection, Dict
from datetime import datetime
import os
from gridfs import Database

# MongoDB Imports
from pymongo import MongoClient
from pymongo.database import Database
from pymongo.collection import Collection
from pymongo.results import InsertOneResult

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
            "caption" : self.taskCaption,
            "description" : self.taskDescription,
            "creationTime" : self.taskCreationTime
        }

        return returnObject;

# This class should retrun the DB URL that I am going to connect to
class ConnectionBuilder:
    def __init__(self,usr = "administrator") -> None:
        self.dbUserName = usr
        self.options = "?retryWrites=true&w=majority"
        self.cluster = "cluster0.ozsgds8.mongodb.net"

    def getConnectionString(self, isLocal = True) -> str:
        if isLocal: return "localhost:27017"

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

        # Returning the actual value
        return connectionString

# This repository should be bound the model class
# TodoItem  
class TodoRepository:
    def __init__(self, taskCol : Collection) -> None:
        self.dbCollection = taskCol

    def addTodo(self,task:TodoItem) -> str:
        tdObj = task.getDict()
        insertoneRes : InsertOneResult = self.dbCollection.insert_one(tdObj)

        return insertoneRes.inserted_id
    
    def findTodoItem(id:str) -> TodoItem:
        pass

    def deleteTodoItem(id:str) -> bool:
        return False;
    
    def updateDescription(id:str, desc:str) -> bool:
        return False;
    
    def updateCaption(id:str, caption:str) -> bool:
        return False;

dbConnection : MongoClient = None
todoDB : Database = None

def createTask(todoRepo : TodoRepository) -> None :
    newTaskCaption = input("Caption:")
    newTaskDescription = input("Description:")

    # Adding the task to the repository
    newTask = TodoItem(newTaskCaption, newTaskDescription);
    taskID = todoRepo.addTodo(newTask)
    print("Created Task ID:{0}".format(taskID))

# Function Entry point
def main():
    print("Running simple MongoDB CRUD Prog")

    connBuilder = ConnectionBuilder();
    connString = connBuilder.getConnectionString(False)
    print("Using connection string {0}".format(connString))

    # Database setup is being performed
    dbConnection = MongoClient(connString)
    todoDB = dbConnection.get_database("todo")
    tasksCollection : Collection = todoDB.get_collection("tasks")

    # Initing the repository
    todoRepo = TodoRepository(tasksCollection)

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

        # Say this happens to be the first operation, until this operation is
        # not performed then no validations are done
        if option == 1:
            createTask(todoRepo)
        elif option == 3:
            taskId = input("Id:")


# Function entry point
if __name__ == "__main__":
    main()
