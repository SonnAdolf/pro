class cmd_caller():
    __order_list = []
    def take_order(self,in_order):
        self.__order_list.append(in_order)
    def place_orders(self):
        for one_order in self.__order_list:
            one_order.execute()
        self.__order_list = []
