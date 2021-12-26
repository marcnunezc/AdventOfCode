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
        self.assign_value(a, b)

    def add(self, a, b):
        value, b =  self.get_values(a, b)
        value += b
        self.assign_value(a, value)

    def mul(self, a, b):
        value, b =  self.get_values(a, b)
        value *= b
        self.assign_value(a, value)

    def div(self, a, b):
        value, b =  self.get_values(a, b)
        if b==0:
            raise(ZeroDivisionError)
        value //= b

        self.assign_value(a, value)

    def mod(self, a, b):
        value, b =  self.get_values(a, b)
        if value<0 or b<=0:
            raise(Exception("Wront input for mod"))
        value %= b
        self.assign_value(a, value)

    def eql(self, a, b):
        value, b =  self.get_values(a, b)
        value = int(value==b)
        self.assign_value(a, value)

def process_input(lines_list, string_to_read, alu):
    string_to_list = list(string_to_read)
    for line in lines_list:
        split_line = [int(char) if char.isnumeric() else -1*int(char.lstrip("-")) if char.lstrip("-").isdigit() else char for char in line.split()]
        if split_line[0] == 'inp':
            alu.inp(split_line[1], int(string_to_list.pop(0)))
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

class ReverseEngineeringALU(ALU):
    def __init__(self, mode='maximize'):
        super().__init__()
        self.constraints = {value:0 for value in range(1,15)}
        self.n_input = 0
        self.mode = mode

    def assign_value(self,a, value):
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

    def inp(self, a,b):
        self.w="w["+str(self.n_input)+"]"
        self.n_input += 1

    def add(self, a, b):
        value, b =  self.get_values(a, b)
        if isinstance(value, int) and isinstance(b, int):
            value  = value+b
        elif isinstance(b, int):
            if b>0:
                value = str(value)+"+"+str(b)
            elif b<0:
                value = str(value)+"-"+str(abs(b))
            else:
                value = str(value)
        elif isinstance(value, int):
            if value == 0:
                value = b
        else:
            if value == "0":
                value = str(b)
            elif b == "0":
                value = str(value)
            else:
                value = str(value)+"+"+str(b)
        self.assign_value(a, value)

    def mul(self, a, b):
        value, b =  self.get_values(a, b)
        if b == 0:
            value = 0
        elif b==1:
            value = value
        elif isinstance(value, int) and isinstance(b, int):
            value = value*b
        elif isinstance(value, str) and isinstance(b, int):
            value ="("+str(value)+")*"+str(b)
        else:
            value ="("+str(value)+")*("+str(b)+")"

        self.assign_value(a, value)

    def div(self, a, b):
        value, b =  self.get_values(a, b)
        if b == 0:
            raise(ZeroDivisionError)
        elif isinstance(value, int) and isinstance(b, int):
            value = value//b
        elif isinstance(value, str) and isinstance(b, int):
            value ="("+str(value)+")//"+str(b)
        else:
            value ="("+str(value)+")//("+str(b)+")"
        self.assign_value(a, value)

    def mod(self, a, b):
        value, b =  self.get_values(a, b)
        if b == 0:
            raise(ZeroDivisionError)
        elif isinstance(value, int) and isinstance(b, int):
            value = value%b
        elif isinstance(value, str):
            numbers = re.findall("(\+\d+|-\d+)", value)
            if isinstance(b, int):
                if len(numbers)==1 and int(numbers[0])+9 < b:
                    value = 0
                else:
                    value ="("+str(value)+")%"+str(b)
            else:
                value ="("+str(value)+")%("+str(b)+")"
        self.assign_value(a, value)

    def eql(self, a, b):
        value, b =  self.get_values(a, b)
        if isinstance(value, str) and "-" in value:
            variables = re.findall("w\[\d\]", value)
            this_w_value = self.n_input-1
            found_w, prev_w = 0, 0
            test_range = range(1,10) if self.mode == "maximize" else range(9,0,-1)
            for test_w in test_range:
                for test_prev in range(1, 10):
                    w = [test_prev for i in range(0, this_w_value)]
                    eval_value = eval(value)
                    if eval_value-test_w == 0:
                        found_w=test_w
                        prev_w = test_prev
            if found_w > 0:
                self.constraints[this_w_value+1] = found_w
                for variable in variables:
                    digit = int(re.findall("\d+", variable)[0])
                    if this_w_value == digit+1:
                        self.constraints[this_w_value] = prev_w
            value = 1
        elif isinstance(b, str):
            value = 0
        elif b == 0:
            value = int(value == 0)
        self.assign_value(a, value)

def find_first_model_number(permutations):
    for p in itertools.product(*permutations):
        string_input = "".join(p)
        x,y,z,w = process_input(lines_list, string_input, ALU())
        if z == 0:
            return string_input

if __name__ == '__main__':

    import itertools, re

    lines_list = open('input.txt').read().splitlines()

    hacker_alu = ReverseEngineeringALU(mode="maximize")
    process_input(lines_list, "66666666666666", hacker_alu)
    permutations = [str(value) if value > 0 else list("987654321") for value in hacker_alu.constraints.values()]
    print("Part 1", find_first_model_number(permutations))

    hacker_alu = ReverseEngineeringALU(mode="minimize")
    process_input(lines_list, "66666666666666", hacker_alu)
    permutations = [str(value) if value > 0 else list("123456789") for value in hacker_alu.constraints.values()]
    print("Part 2", find_first_model_number(permutations))