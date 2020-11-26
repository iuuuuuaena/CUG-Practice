from models.config import config


class Baggage:
    def __init__(self, _l, _w, _h, _wei, _t, id):
        lwh = [float(_l), float(_w), float(_h)]
        lwh.sort(reverse=True)
        self.length = lwh[0]
        self.width = lwh[1]
        self.height = lwh[2]
        self.weight = float(_wei)
        self.type = _t
        self.calculated = False
        self.handle_way = ''
        self.size = sum(lwh)
        self.id = id


def isover(baggage: Baggage):
    if config.getint('common', 'weight2') < baggage.weight <= config.getint('common', 'weight3') and config.getint(
            'common', 'size1') <= baggage.size <= config.getint('common', 'size2'):
        return 'overweight1'
    if config.getint('common', 'weight3') < baggage.weight <= config.getint('common', 'weight4') and config.getint(
            'common', 'size1') <= baggage.size <= config.getint('common', 'size2'):
        return 'overweight2'
    if config.getint('common', 'weight1') < baggage.weight <= config.getint('common', 'weight2') and config.getint(
            'common', 'size2') <= baggage.size <= config.getint('common', 'size3'):
        return 'oversize'
    if config.getint('common', 'weight2') < baggage.weight <= config.getint('common', 'weight4') and config.getint(
            'common', 'size2') <= baggage.size <= config.getint('common', 'size3'):
        return 'overall'
    return False


def weight_type(baggage: Baggage):
    if config.getint('common', 'weight1') <= baggage.weight <= config.getint('common', 'weight2'):
        return '1_2_'
    if config.getint('common', 'weight2') <= baggage.weight <= config.getint('common', 'weight4'):
        return '2_4_'
    if config.getint('common', 'weight4') <= baggage.weight <= config.getint('common', 'weight5'):
        return '4_5_'
