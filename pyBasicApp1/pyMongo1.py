# This is very simple console application which will try to make the 
# basic MongoDB opreations. All the code should be in a seperate files
# for simplicity I am putting all of them on a single file. In this example
# We are not using a ORM type library all the querys are hand written

from typing import Dict, List
from datetime import datetime
import os
from bson import ObjectId

# MongoDB Imports
from pymongo import MongoClient
from pymongo.database import Database
from pymongo.collection import Collection
from pymongo.results import InsertOneResult
from pymongo.cursor import Cursor

# This is the model class that we would be using the
class TodoItem:
    def __init__(self, caption : str, desc : str = "") -> None:
        self.taskCaption : str = caption
        self.taskDescription : str = desc
        self.taskCreationTime : datetime = datetime.now()
        self.Id : ObjectId = None

        if len(desc) != 0 :
            self.taskDescription = desc
    
    def __init__(self, dbObject : Dict) -> None:
        self.taskCaption = dbObject["caption"]
        self.taskDescription = dbObject["description"]
        self.Id = dbObject["_id"]

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
    
    def findTodoItem(self, id:str) -> TodoItem:
        pass

    def deleteTodoItem(self, id:str) -> bool:
        return False;
    
    def updateDescription(self, id:str, desc:str) -> bool:
        return False;
    
    def updateCaption(self, id:str, caption:str) -> bool:
        return False;
    
    """
    Retruns list of tasks by it's name
    As of now the search query needs to be exactly same 
    so it does not actually makes a sreach more of a lookup
    """
    def findTaskByCaption(self, caption:str) -> List[TodoItem]:
        retValue:List[TodoItem] = []

        queryObject = {
            "caption" : caption
        }

        foundItems:Cursor = self.dbCollection.find(queryObject)
        for task in foundItems:
            item = TodoItem(task)
            retValue.append(item)    
        
        return retValue

dbConnection : MongoClient = None
todoDB : Database = None

def createTask(todoRepo : TodoRepository) -> None :
    newTaskCaption = input("Caption:")
    newTaskDescription = input("Description:")

    # Adding the task to the repository
    newTask = TodoItem(newTaskCaption, newTaskDescription);
    taskID = todoRepo.addTodo(newTask)
    print("Created Task ID:{0}".format(taskID))

def findTask(todoRepo : TodoRepository) -> None:
    taskString = input("Task Name:")
    
    # This logic is there just to show case multiple type of
    # seaches.
    if len(taskString) != 0:
        # This query should provide a list of item
        taskItems = todoRepo.findTaskByCaption(taskString)

        # This list should have been capped will try to add that up.
        # By deafult it should show top 10 itmes sorted by it's due date
        for task in taskItems:
            print("{0}[{2}]\n\t{1}\n\n".format(
                task.taskCaption, 
                task.taskDescription,
                task.Id)
            )
    
    else:
        # This should ideally retrun none or single item
        taskString = input("Task ID")
        foundItems = todoRepo.findTodoItem(taskString)
        print(foundItems)

    
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
        elif option == 4:
            findTask(todoRepo)
        elif option == 3:
            taskId = input("Id:")


# Function entry point
if __name__ == "__main__":
    main()
