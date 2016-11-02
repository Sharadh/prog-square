#this one uses sets
def dedupe_v2(x):
    return list(set(x))

a = [1,2,3,4,3,2,1]
print a
print dedupe_v2(a)
