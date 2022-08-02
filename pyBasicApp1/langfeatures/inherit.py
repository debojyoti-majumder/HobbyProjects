# A simple example to show inheritance in Python

from typing import Dict

globalPublicationMap:Dict[int,str] = {
     1: "Apress",
     2: "Orily"
}

class Publication:
    def __init__(self, pubID:int, title:str ) -> None:
        self.publisherID = pubID
        self.title = title

    def __str__(self) -> str:
        stringRep:str = self.title
        stringRep += " by "
        stringRep += globalPublicationMap[self.publisherID]

        # This is what would be dispayed in the cosole
        return stringRep

# Passing the base class name in () in the class declaration
# followed by calling super() method
class HardCopy(Publication):
    def __init__(self, pubID: int, title: str, store:str) -> None:
        super().__init__(pubID, title)
        self.physicalStore = store

class SoftCopy(Publication):
    def __init__(self, pubID: int, title: str, url:str) -> None:
        super().__init__(pubID, title)
        self.downloadLink = "AWS://" + url

cppBook = HardCopy(1,"Introduction to C++","BLR")
print(cppBook)

openGLBook = SoftCopy(2, "OpenGL Stuff", "amazon.com/abcd")
print(openGLBook)
