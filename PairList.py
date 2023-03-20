from typing import *

First = TypeVar('First')
Second = TypeVar('Second')

class PairList(Generic[First, Second]):
    """
    A list of (First, Second) pairs.
    """

    __first: List[First]
    "The first part of each element."
    __second: List[Second]
    "The second part of each element."

    def __init__(self: Self):
        "Creates an empty instance."
        self.__first, self.__second = [], []

    def __getitem__(self: Self, i: int) -> Tuple[First, Second]:
        """
        Returns the ith element.

        Precondition: i < len(self)
        """
        return (self.__first[i], self.__second[i])

    def __len__(self: Self) -> int:
        "Returns the length."
        return len(self.__first)

    def append(self: Self, x: Tuple[First, Second]) -> None:
        "Adds x to the end."
        self.__first.append(x[0])
        self.__second.append(x[1])

l: PairList[int, str] = PairList()
l.append((1, "foo"))
l.append((2, "bar"))
