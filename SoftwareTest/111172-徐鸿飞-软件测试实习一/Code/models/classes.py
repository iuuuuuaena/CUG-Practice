from enum import Enum, unique
from models.baggage import Baggage
from models.config import config


@unique
class Classes(Enum):
    LuxuryFirstClass = 0
    FirstClass = 1
    BusinessClass = 2
    EnjoyEconomyClass = 3
    SuperEconomyClass = 4
    EconomyClass = 5


class Class:
    def __init__(self, config):
        self.carry_num = config[0]  # 随身携带件数
        self.carry_weight = config[1]  # 携带重量
        self.free_num = config[2]  # 免费件数
        self.free_weight = config[3]  # 免费重量
        self.size = config[4]  # 最大尺寸限制
        self.fare = config[5]  # 当日的直达航班经济舱普通票价
        self.class_ = config[6]
        self.passenger=config[7]
        pass

    def canCarry(self, baggage: Baggage):
        return baggage.weight <= self.carry_weight and baggage.length <= config.getint(
            'common', 'carry_length') and baggage.width <= config.getint(
            'common', 'carry_width') and baggage.height <= config.getint('common', 'carry_height')


    def can(self, baggage: Baggage):
        if isinstance(self.size, list):
            return baggage.length <= self.size[0] and baggage.width <= self.size[1] and baggage.height <= self.size[
                2] and baggage.weight <= config.getint('common', 'weight4') and baggage.size >= config.getint(
                'common', 'size1') and baggage.weight >= config.getint('common', 'weight1')
        else:
            return self.size >= baggage.size >= config.getint('common', 'size1') \
                   and config.getint('common', 'weight4') >= baggage.weight >= config.getint('common', 'weight1')
