from typing import *

First = TypeVar('First')
Second = TypeVar('Second')

class PairList(Generic[First, Second]):
  __first: List[First]
  __second: List[Second]

  def __init__(self: Self):
    self.__first, self.__second = [], []

  def __getitem__(self: Self, i: int) -> Tuple[First, Second]:
    return (self.__first[i], self.__second[i])

  def __len__(self: Self) -> int:
    return len(self.__first)

  def append(self: Self, x: Tuple[First, Second]) -> None:
    self.__first.append(x[0])
    self.__second.append(x[1])

l: PairList[int, str] = PairList()
l.append((1, "foo"))
l.append((2, "bar"))
