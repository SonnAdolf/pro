import unittest

from pro_entity import pro

class mypro_test(unittest.TestCase):

    def test_pro_entity_create(self):
        tmp_pro = pro(1,2,3,4,'test')
        self.assertEqual(tmp_pro.get_writing_pro_str(), "1")
        self.assertEqual(tmp_pro.get_art_learning_pro_str(), "2")
        self.assertEqual(tmp_pro.get_reading_pro_str(), "3")
        self.assertEqual(tmp_pro.get_computer_learning_pro_str(), "4")
        self.assertEqual(tmp_pro.get_note(), "test")
        self.assertTrue(tmp_pro.get_total_pro_str()==str(1+2+3+4))
        
if __name__ == '__main__':
    unittest.main()