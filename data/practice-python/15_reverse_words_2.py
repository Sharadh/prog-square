# method 1: loop through the words and insert each word at the begining of the result list
def reverse(x):
  y = x.split()
  result = []
  for word in y:
    result.insert(0,word)
  return " ".join(result)

# test code
test1 = raw_input("Enter a sentence: ")
print reverse(test1)
