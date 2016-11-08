def distance_from_zero(value):
    if type(value) == int or type(value) == float:
        return abs(value)
    else:
        return 'Nope'
