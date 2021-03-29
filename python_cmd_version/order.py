import abc
class order(object):
    __metaclass__ = abc.ABCMeta
    @abc.abstractmethod
    def execute(self):
        pass
