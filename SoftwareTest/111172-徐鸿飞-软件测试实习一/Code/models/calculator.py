from models.baggage import Baggage, isover, weight_type
from models.classes import *
from models.config import config
from configparser import NoOptionError


class Calculator:
    def __init__(self, _class: Class, area, start):
        self.baggages: list[Baggage] = []
        self.special_baggages: list[Baggage] = []
        self.class_ = _class
        self.area = area
        self.start = start
        self.cost = 0
        self.special_cost = 0
        self.error = ''

    def calculate(self):
        if self.area == 'domestic':
            if not self.calculateDomestic(): return False
        else:
            if not self.calculateForeign(): return False
        if not self.calculateSpecial(): return False
        return True

    # 增加一件行李
    def addBaggage(self, baggage: Baggage):
        if baggage.type != 'usual':
            self.special_baggages.append(baggage)
        else:
            self.baggages.append(baggage)

    # 计算国内航班
    def calculateDomestic(self):
        cost = 0
        # 先尽量随身携带,以重量排序尽量带更重的
        self.baggages.sort(key=lambda x: x.weight, reverse=True)
        i = 0
        j = 0
        while i < self.class_.carry_num and j < len(self.baggages):
            if self.class_.canCarry(self.baggages[j]):
                self.baggages[j].calculated = True
                self.baggages[j].handle_way = "随身携带,费用为0"
                i += 1
            j += 1
        # 计算普通行李
        free_weight = self.class_.free_weight
        for baggage in self.baggages:
            if not baggage.calculated:
                if not self.class_.can(baggage):
                    self.error = "行李" + str(baggage.id) + ":单一行李尺寸或重量过大或过小，请重新分配"
                    return False
                if baggage.weight <= free_weight:
                    baggage.calculated = True
                    baggage.handle_way = "免费行李"
                    free_weight -= baggage.weight
                else:
                    t_cost = self.class_.fare * 0.015 * (baggage.weight - free_weight)
                    cost += t_cost
                    baggage.calculated = True
                    baggage.handle_way = "超出" + str(baggage.weight - free_weight) + "kg,收费" + str(t_cost) + "元"
        self.cost += cost
        return True

    def calculateForeign(self):
        cost = 0
        # 先尽量随身携带,以重量排序尽量带更重的
        self.baggages.sort(key=lambda x: x.weight, reverse=True)
        i = 0
        j = 0
        while i < self.class_.carry_num and j < len(self.baggages):
            if self.class_.canCarry(self.baggages[j]):
                self.baggages[j].calculated = True
                self.baggages[j].handle_way = "随身携带,费用为0"
                i += 1
            j += 1
        # 计算普通行李
        self.baggages.sort(key=lambda x: x.weight, reverse=True)
        i = 0
        for baggage in self.baggages:
            if not baggage.calculated:
                if not self.class_.can(baggage):
                    self.error = "行李" + str(baggage.id) + ":单一行李尺寸或重量过大或过小，请重新分配"
                    return False
                i += 1
                over = isover(baggage)
                try:
                    if i > self.class_.free_num:
                        t = i - self.class_.free_num
                        if t >= 3:
                            t = 3
                        t_cost = config.getint(self.area, 'excess' + str(t) + '_' + self.start)
                        cost += t_cost
                        baggage.handle_way = "超出的第" + str(i - self.class_.free_num) + '件,收费' + str(
                            t_cost) + self.start + ','
                    if not over:
                        continue
                    if self.class_.free_weight != config.getint('common', 'weight4'):
                        t_cost = config.getint(self.area, over + '_' + self.start)
                        cost += t_cost
                        baggage.calculated = True
                        baggage.handle_way += over + "收费" + str(t_cost) + self.start
                    else:
                        if over == 'overweight1' or over == 'overweight2':
                            baggage.calculated = True
                            baggage.handle_way += "not over"
                        else:
                            t_cost = config.getint(self.area, 'oversize_' + self.start)
                            cost += t_cost
                            baggage.calculated = True
                            baggage.handle_way += 'oversize,收费' + str(t_cost) + self.start
                except NoOptionError:
                    self.error = self.area + " not support " + self.start
                    return False
        self.cost += cost
        return True

    def calculateSpecial(self):
        cost = 0
        for baggage in self.special_baggages:
            if baggage.type not in ['special1', 'special2', 'special3']:
                self.error = "Not support special type"
                return False
            if baggage.type == 'special1':
                baggage.handle_way = "此行李免费"
                continue
            else:
                if baggage.weight > config.getint('common', config.get(baggage.type, 'max_weight')) \
                        or baggage.weight < config.getint('common', 'weight1'):
                    self.error = "特殊行李" + str(baggage.id) + "重量不符合标准"
                    return False
                t_cost = config.getint(baggage.type, weight_type(baggage) + 'cny')
                baggage.handle_way = "特殊行李,收费" + str(t_cost) + 'cny'
                cost += t_cost
        self.special_cost += cost
        return True

    def gethandleways(self):
        res = []
        for baggage in self.baggages:
            res.append({'baggage_id': baggage.id, 'handle_way': baggage.handle_way})
        for baggage in self.special_baggages:
            res.append({'baggage_id': baggage.id, 'handle_way': baggage.handle_way})
        return res


def handle(data):
    # print(data)
    try:
        area = data['area']
        if area not in ['domestic', 'area1', 'area2', 'area3', 'area4', 'area5']:
            return False, "Not support area", None
        start = data['start']
        if start not in ["cny", "eur", "eur", "cad", "usd"]:
            return False, "Not support start", None
        class_ = data['class_']
        if class_ not in ["LuxuryFirstClass", "FirstClass", "BusinessClass", "EnjoyEconomyClass", "SuperEconomyClass", "EconomyClass"]:
            return False, "Not support class", None
        baggages = data['baggages']
        passenger = data['passenger']
        if passenger not in ["common","baby"]:
            return False, "Not support passenger", None
        # class的配置
        class_config = []
        class_config.append(config.getint(class_, 'carry_num'))
        class_config.append(config.getint(class_, 'carry_weight'))
        if area == 'domestic':
            class_config.append(0)
        else:
            if class_ == 'EconomyClass':
                class_config.append(config.getint(class_, 'free_num_' + config.get(area, 'type')))
            else:
                class_config.append(config.getint(class_, 'free_num'))
        if area == 'domestic':
            if passenger == 'baby':
                class_config.append(config.getint('baby', 'domestic_weight'))
            else:
                class_config.append(config.getint(class_, 'domestic_weight'))
        else:
            class_config.append(config.getint(class_, 'free_weight'))
        if area == 'domestic':
            class_config.append([config.getint('domestic', 'length'), config.getint('domestic', 'width'),
                                 config.getint('domestic', 'height')])
        else:
            class_config.append(config.getint('common', 'size3'))
        if float(data['fare']) < 0:
            return False, "输入了负值", None
        class_config.append(float(data['fare']))
        class_config.append(class_)
        class_config.append(passenger)
        _class = Class(class_config)
    except ValueError:
        return False, "输入不规范", None
    except KeyError:
        return False, "输入不完整", None

    cal = Calculator(_class, area, start)
    for baggage in baggages:
        try:
            if float(baggage['length']) < 0 or float(baggage['width']) < 0 or \
                    float(baggage['height']) < 0 or float(baggage['weight']) < 0:
                return False, "输入了负值", None
            bag = Baggage(baggage['length'], baggage['width'], baggage['height'], baggage['weight'], baggage['type'],
                      baggage['id'])
        except ValueError:
            return False, "输入不规范", None
        except KeyError:
            return False, "baggage输入不完整",None
        cal.addBaggage(bag)
    if cal.calculate():
        return True, str(cal.cost) + cal.start + ',' + str(cal.special_cost) + 'cny', cal.gethandleways()
    return False, cal.error, None
