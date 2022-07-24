from typing import Dict

# This is the model class that we would be using the
class TodoItem:
    def __init__(self, caption : str, desc : str = "") -> None:
        self.taskCaption : str = caption
        self.taskDescription : str = desc

        if len(desc) != 0 :
            self.taskDescription = desc
    
    def getDict(self) -> Dict:
        returnObject = {
            "caption" : self.taskDescription,
            "description" : self.taskCaption
        }

        return returnObject;

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

# Function Entry point
def main():
    option:int = -1;
    print("Running simple MongoDB CRUD Prog")

    # TODO: This can be automated using some kind of helper
    # library, there might be packages that are present but not going to
    # use it
    while option != 0:
        print("1. Add Todo Item task")
        print("2. Remove Todo Item task")
        print("3. Update Task")
        print("4. Find Task")
        print("0. Exit")

        userInput = input("Your Option:");
        option = int(userInput)

        if option == 1:
            newTaskCaption = input("Caption:")
            newTaskDescription = input("Description:")
        elif option == 3:``
            taskId = input("Id:")


# Function entry point
if __name__ == "__main__":
    main()
