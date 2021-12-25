class ALU:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.z = 0
        self.w = 0

    def return_value(self, a):
        if a == 'x':
            return self.x
        elif a == 'y':
            return self.y
        elif a == 'z':
            return self.z
        elif a == 'w':
            return self.w
        else:
            raise ValueError('Invalid input', a)

    def assign_value(self,a, value):
        print ("Assigning", value, "to", a)
        if not isinstance(a, str):
            raise TypeError('Invalid type, expected string', type(a))
        if not isinstance(value, int):
            raise TypeError('Invalid type, expected int', type(value))
        if a == 'x':
            self.x = value
        elif a == 'y':
            self.y = value
        elif a == 'z':
            self.z = value
        elif a == 'w':
            self.w = value
        else:
            raise ValueError('Invalid input', a)

    def get_values(self, a, b):
        if isinstance(a, str):
            a = self.return_value(a)
        else:
            raise TypeError('Invalid type, expected string', type(a))
        if isinstance(b, int):
            pass
        elif isinstance(b, str):
            b = self.return_value(b)
        else:
            raise TypeError('Invalid type', type(b))
        return a, b

    def inp(self, a, b):
        if not isinstance(b, int):
            raise TypeError('Invalid type, expected int and got', type(b))
        print("Input:", b, "stored in", a)
        self.assign_value(a, b)

    def add(self, a, b):
        value, b =  self.get_values(a, b)
        print("Add: ", value, "by", b)

        value += b
        self.assign_value(a, value)

    def mul(self, a, b):
        value, b =  self.get_values(a, b)
        print("Mul: ", value, "by", b)
        value *= b

        self.assign_value(a, value)

    def div(self, a, b):
        value, b =  self.get_values(a, b)
        if b==0:
            raise(ZeroDivisionError)
        print("Div: ", value, "by", b)
        value //= b

        self.assign_value(a, value)

    def mod(self, a, b):
        value, b =  self.get_values(a, b)
        print("Mod of ", value, "by", b)
        if value<0 or b<=0:
            raise(Exception("Wront input for mod"))
        value %= b
        self.assign_value(a, value)

    def eql(self, a, b):
        value, b =  self.get_values(a, b)
        print("Eql: ", value, "==", b)
        value = int(value==b)
        self.assign_value(a, value)

def process_input(lines_list, string_to_read):
    alu = ALU()
    string_to_list = list(string_to_read)
    n_input = 0
    for line in lines_list:
        split_line = [int(char) if char.isnumeric() else -1*int(char.lstrip("-")) if char.lstrip("-").isdigit() else char for char in line.split()]
        if split_line[0] == 'inp':
            n_input += 1
            print("xyzw", alu.return_value('x'), alu.return_value('y'), alu.return_value('z'), alu.return_value('w'))
            print()
            alu.inp(split_line[1], int(string_to_list.pop(0)))
            print("Solving w"+str(n_input))
        elif split_line[0] == 'add':
            alu.add(split_line[1], split_line[2])
        elif split_line[0] == 'mul':
            alu.mul(split_line[1], split_line[2])
        elif split_line[0] == 'div':
            alu.div(split_line[1], split_line[2])
        elif split_line[0] == 'mod':
            alu.mod(split_line[1], split_line[2])
        elif split_line[0] == 'eql':
            alu.eql(split_line[1], split_line[2])
        else:
            raise(Exception("Invalid input", split_line[0]))

    return alu.return_value('x'), alu.return_value('y'), alu.return_value('z'), alu.return_value('w')


if __name__ == '__main__':

    import itertools
    import sympy
    import re

    lines_list = open('input.txt').read().splitlines()

    # string_input = "99999212949"+"9"+"51"
    # string_input = "99999212949"+"9"+"51"
    # string_input = "11199212949"+"311"
    # string_input = "11199212"
    # string_input = "9979921"+"2"+"9"+"4"+"9967"
    # x,y,z,w = process_input(lines_list, string_input)
    # print("input", string_input, "z", z)
    # print(len(string_input))

    string_input = "3419811"+"1"+"8"+"1"+"6311"
    x,y,z,w = process_input(lines_list, string_input)
    print("input", string_input, "z", z)
    print(len(string_input))


