from configparser import ConfigParser


class Config:
    def __init__(self,f="./models/config.ini"):
        self.cf = ConfigParser()
        self.cf.read(f)

    def get(self, section, option):
        return self.cf.get(section, option)

    def getint(self, section, option):
        return self.cf.getint(section, option)


config = Config()
