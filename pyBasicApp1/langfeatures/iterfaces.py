from abc import ABC, abstractmethod
from typing import List

"""
ABC stands for Abstarct base class, This is actaully a interface
"""
class SerializedObject(ABC):
    @abstractmethod
    def toJSON(self):
        pass

"""
Derived object, but did not mentioned 
any decorator on top of the method for overridden items
"""
class Point2D(SerializedObject):
    def __init__(self,x:int, y:int) -> None:
        super().__init__()
        self.x = x
        self.y = y

    def toJSON(self):
        strOutput = "Point 2D:"
        strOutput += str(self.x)
        strOutput += " " + str(self.y)

        return strOutput

class Location(SerializedObject):
    """
    Ovwridden method
    """
    def toJSON(self):
        return "Location object"

serObjects:List[SerializedObject] = []

"""
This method actually holds different type of objects
which is dervied from SerializedObject
"""
def iterateListObject(objs:List[SerializedObject]):
    for obj in objs: print(obj.toJSON())

serObjects.append(Point2D(3,7))
serObjects.append(Location())
serObjects.append(Point2D(2,22))
serObjects.append(Location())

iterateListObject(serObjects)
