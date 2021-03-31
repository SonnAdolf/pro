#!/usr/bin/python
# -*- coding: UTF-8 -*-
import sys

reload(sys)
sys.setdefaultencoding( "utf-8" )

class pro:
    __writing_pro=0.00
    __art_learning_pro=0.00
    __reading_pro=0.00
    __total_pro=0.00
    __computer_learning_pro=0.00
    __note = ''

    def __init__(self,writing_pro,art_learning_pro,reading_pro,computer_learning_pro,note):
        self.__writing_pro = float(writing_pro)
        self.__art_learning_pro = float(art_learning_pro)
        self.__reading_pro = float(reading_pro)
        self.__computer_learning_pro = float(computer_learning_pro)
        self.__note = note
        self.__total_pro = 0.00
        self.__total_pro = self.__writing_pro+self.__art_learning_pro+self.__reading_pro+self.__computer_learning_pro

    def get_writing_pro_str(self):
        return str(self.__writing_pro)

    def get_art_learning_pro_str(self):
        return str(self.__art_learning_pro)
    
    def get_reading_pro_str(self):
        return str(self.__reading_pro)

    def get_computer_learning_pro_str(self):
        return str(self.__computer_learning_pro)

    def get_note(self):
        return str(self.__note)

    def get_total_pro_str(self):
        return str(self.__total_pro)
        
    def print_self(self):
        print('Writing pro:'+str(self.__writing_pro)+'\n')
        print('Computer learning pro:'+str(self.__computer_learning_pro)+'\n')
        print('Reading pro:'+str(self.__reading_pro)+'\n')
        print('Art learning pro:'+str(self.__art_learning_pro)+'\n')
        print('Total pro:'+str(self.__total_pro)+'\n')
        print('Note:'+self.__note+'\n')
