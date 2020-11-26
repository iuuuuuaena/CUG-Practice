import unittest
from models.calculator import handle
from ddt import ddt, file_data


@ddt
class MyTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        pass

    @file_data('./test_files/test_whitebox.json')
    def test_white_box(self, args, result):
        _, msg, _ = handle(args)
        self.assertEqual(msg, result)

    @file_data('./test_files/test_blackbox.json')
    def test_black_box(self, args, result):
        _, msg, _ = handle(args)
        self.assertEqual(msg, result)


if __name__ == '__main__':
    unittest.main(verbosity=1)
