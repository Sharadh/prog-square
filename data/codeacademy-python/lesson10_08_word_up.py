pyg = 'ay'

original = raw_input('Enter a word:')

if len(original) > 0 and original.isalpha():
    print original
    word = original.lower()
    first = word[0]
else:
    print 'empty'
