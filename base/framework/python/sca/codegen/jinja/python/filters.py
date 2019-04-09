
def do_tuple(values):
    """
    Returns a string representation of the items in 'values' as a Python tuple.
    """
    valout = ','.join(values)
    if valout and not ',' in valout:
        valout += ','
    return '(' + valout + ')'
