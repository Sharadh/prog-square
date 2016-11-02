# method 4
def reverse(x):
  y = x.split()
  y.reverse()
  return " ".join(y)

# test code
test1 = raw_input("Enter a sentence: ")
print reverse(test1)
