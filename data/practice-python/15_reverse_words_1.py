def reverseWord(w):
  return ' '.join(w.split()[::-1])

# test code
test1 = raw_input("Enter a sentence: ")
print reverseWord(test1)
