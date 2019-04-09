
from generator import BaseComponentGenerator, loader
from mapping import BaseComponentMapper

def factory(**opts):
    return BaseComponentGenerator(**opts)
