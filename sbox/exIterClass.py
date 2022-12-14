class classIter:
  def __iter__(self):
    self.a = 1
    return self

  def __next__(self):
    if self.a <= 20:
      x = self.a
      self.a += 1
      return x
    else:
      raise StopIteration

myIterObject = classIter()
myiter = iter(myIterObject)

for x in myiter:
  print(x)