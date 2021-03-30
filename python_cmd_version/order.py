#!/usr/bin/python
# -*- coding: UTF-8 -*-
import sys
import abc

reload(sys)
sys.setdefaultencoding( "utf-8" )

class order(object):
    __metaclass__ = abc.ABCMeta
    @abc.abstractmethod
    def execute(self):
        pass
