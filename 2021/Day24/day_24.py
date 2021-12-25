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
            # print("xyzw", alu.return_value('x'), alu.return_value('y'), alu.return_value('z'), alu.return_value('w'))
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



class ReverseEngineeringALU(ALU):
    def __init__(self):
        super().__init__()
        self.constraints = []
        self.current_constraints = {value:0 for value in range(1,15)}


    def assign_value(self,a, value):
        print ("Assigning", value, "to", a)
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

    def assign_current_w(self, n_input):
        self.w="w"+str(n_input)

    def add(self, a, b):
        value, b =  self.get_values(a, b)
        print("Add: ", value, "by", b)
        if isinstance(value, int) and isinstance(b, int):
            value  = value+b
        elif isinstance(b, int):
            if b>0:
                value  = str(value)+"+"+str(b)
            elif b<0:
                value  = str(value)+"-"+str(abs(b))
            else:
                value  = str(value)
        elif isinstance(value, int):
            if value == 0:
                value = b
            else:
                value


        else:
            if value == "0":
                value = str(b)

            elif b == "0":
                value = str(value)
            else:
                value  = str(value)+"+"+str(b)

        self.assign_value(a, value)

    def mul(self, a, b):
        value, b =  self.get_values(a, b)
        print("Mul: ", value, "by", b)
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
        # if b == 1:
            # return
        value, b =  self.get_values(a, b)
        print("Div: ", value, "by", b)
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
        print("Mod of ", value, "by", b)
        if b == 0:
            raise(ZeroDivisionError)
        elif isinstance(value, int) and isinstance(b, int):
            value = value%b
        elif isinstance(value, str):
            numbers = re.findall("(\+\d+|-\d+)", value)
            # print("numbres", numbers, int(numbers[0]))
            if len(numbers) >1:
                print("Got more than 1 number", numbers)
            if isinstance(b, int):
                if len(numbers)==1 and int(numbers[0])+9 < b:
                    value = 0
                else:
                    value ="("+str(value)+")%"+str(b)
            else:
                value ="("+str(value)+")%("+str(b)+")"
            self.assign_value(a, value)

    def correct_constraints(self, test_value, w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14):
        for i in range(1, 15):
            if i == 1 and self.current_constraints[1]>= test_value:
                w1 = self.current_constraints[1]
            elif i == 2 and self.current_constraints[2]>= test_value:
                w2 = self.current_constraints[2]
            elif i == 3 and self.current_constraints[3]>= test_value:
                w3 = self.current_constraints[3]
            elif i == 4 and self.current_constraints[4]>= test_value:
                w4 = self.current_constraints[4]
            elif i == 5 and self.current_constraints[5]>= test_value:
                w5 = self.current_constraints[5]
            elif i == 6 and self.current_constraints[6]>= test_value:
                w6 = self.current_constraints[6]
            elif i == 7 and self.current_constraints[7]>= test_value:
                w7 = self.current_constraints[7]
            elif i == 8 and self.current_constraints[8]>= test_value:
                w8 = self.current_constraints[8]
            elif i == 9 and self.current_constraints[9]>= test_value:
                w9 = self.current_constraints[9]
            elif i == 10 and self.current_constraints[10]>= test_value:
                w10 = self.current_constraints[10]
            elif i == 11 and self.current_constraints[11]>= test_value:
                w11 = self.current_constraints[11]
            elif i == 12 and self.current_constraints[12]>= test_value:
                w12 = self.current_constraints[12]
            elif i == 13 and self.current_constraints[13]>= test_value:
                w13 = self.current_constraints[13]
            elif i == 14 and self.current_constraints[14]>= test_value:
                w14 = self.current_constraints[14]
        return w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14


    def eql(self, a, b):
        value, b =  self.get_values(a, b)
        print("Eql: ", value, "==", b)
        if isinstance(value, str) and "-" in value:
            variables = re.findall("w\d+", value)
            this_value = re.findall("-\d+", value)
            print("DETECTED NEGASTIVE", this_value)
            found = False
            this_w_value =int(re.findall("\d+", b)[0])
            # for test_w in range(1, 10):
            #     if b in value:
            #         raise(Exception("Cannot happen"))
            #     for test in range(1, 10):
            #         w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14 = test,test,test,test,test,test,test,test,test,test,test,test,test,test
            #         w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14 = self.correct_constraints(test, w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14)
            #         # correct_values =
            #         eval_value = eval(value)
            #         # print("evaluated with", w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14)
            #         # print("Eval value", eval_value-test_w, "for test", test)
            #         if eval_value-test_w == 0:
            #             # print("Found candiate constraint for variables", variables, "should be >=", test)

            #             meeting_constraint = False
            #             for variable in variables:
            #                 digit = int(re.findall("\d+", variable)[0])
            #                 if self.current_constraints[digit] <= test:
            #                     meeting_constraint = True
            #                     break

            #             if meeting_constraint:
            #                 print("Found a constraint for variables", variables, "should be >=", test, eval_value-test_w)
            #                 print("evaluated with", w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14)
            #                 print("current constriants are", self.current_constraints)
            #                 self.constraints.append((variables,">=", test))
            #                 for variable in variables:
            #                     digit = int(re.findall("\d+", variable)[0])
            #                     if self.current_constraints[digit] < test:
            #                         self.current_constraints[digit] = test
            #                 if self.current_constraints[this_w_value] < test_w:
            #                     self.current_constraints[this_w_value] = test_w
            #                 print("They are update to", self.current_constraints)
            #                 found = True
            #     #     if found:
            #     #         break
            #     # if found:
            #     #     break
            if not this_w_value in []:
                print("FOUND")
                value = 1
            else:
                print("NOT FOUND")
                value = 0
        elif isinstance(b, str) and "w" in b:
            print("Value, b", value, b)
            # numbers = re.findall("(\+\d+|-\d+)", value)
            if isinstance(value, int):
                if (value>8):
                    print("Impossible that ", value,"is equal to ", b)
                    value = 0
                else:
                    stop
            else:
                print("assuming value", value, "is not equal to ", b)
                value = 0
        elif b == 0:
            # print("Evaluation eql with", value, "and", b)
            value = int(value == 0)
        self.assign_value(a, value)



if __name__ == '__main__':

    import itertools
    import sympy
    import re

    lines_list = open('input.txt').read().splitlines()

    alu = ReverseEngineeringALU()
    list_of_expressions = []
    n_input = 0
    for line in lines_list:
        # print(line)
        split_line = [int(char) if char.isnumeric() else -1*int(char.lstrip("-")) if char.lstrip("-").isdigit() else char for char in line.split()]
        if split_line[0] == 'inp':
            n_input += 1
            print("xyzw", alu.return_value('x'), alu.return_value('y'), alu.return_value('z'), alu.return_value('w'))
            print()

            # print("x", alu.x)
            # print("y", alu.y)
            # print("z", alu.z)
            # print("w", alu.w)
            alu.assign_current_w(n_input)
            print("Working on input", n_input)
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

        # print()
    constraints = alu.constraints
    print("z", alu.z)
    for test in range(1, 9):
        w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14 = test,test,test,test,test,test,test,test,test,test,test,test,test,test
        z_eval = eval(alu.z)
        print("z_eval", z_eval, "for test", test)
        if eval(alu.z) == -1:
            print("Found a constraint for variables", variables, "should be >=", test)
            constraints.append((variables, ">=", test))
        if eval(alu.z) == 1:
            print("Found a constraint for variables", variables, "should be <=", test)
            constraints.append((variables, "<=", test))
    print(alu.current_constraints)
    for constraint in constraints:
        print(constraint)
    print("n input", n_input)
    # string_input = "".join(["9"]+["9"]+["9"]+["9"]+["9"]+["2"]+["9"]*1)
    # x,y,z,w = process_input(lines_list, string_input)
    # print("input", string_input, "z", z)


    # permutations = []
    # for i  in range(1,15):
    #     if "w"+str(i) in constraints[-1][0]:
    #         permutations.append([str(i) for i in range(constraints[-1][2], 10)])
    #     else:
    #         permutations.append(list("123456789"))
    # print(permutations)

    # alu = ALU()
    # max_string=0
    # for  p in itertools.product(*permutations):
    #     string_input = "".join(p)
    #     if (int(string_input)-1) % 100000 == 0:
    #         print(string_input)
    #     x,y,z,w = process_input(lines_list, string_input)
    #     print(z)
    #     if z == 0:
    #         print("input", string_input, "z", z)
    #         max_string = max(int(string_input), max_string)
    # if z == 0:
    #     print("input", string_input, "z", z)
    #     max_string = max(int(string_input), max_string)
    # print("Part 1", max_string)



# class ReverseEngineeringALU:
#     def __init__(self):
#         # self.x,self.y,self.z,self.w = sympy.symbols("x y z w")
#         # define self.w1 to self.w14
#         self.w1, self.w2,self.w3, self.w4, self.w5, self.w6, self.w7, self.w8, self.w9, self.w10, self.w11, self.w12, self.w13, self.w14 = sympy.symbols("w1 w2 w3 w4 w5 w6 w7 w8 w9 w10 w11 w12 w13 w14")
#         self.expr = self.z
#         self.x, self.y, self.z, self.w = 0,0,0,0

#     def initialize(self):
#         pass

#     def assign_current_w(self, n_input):
#         if n_input == 1:
#             self.w = self.w1
#         elif n_input == 2:
#             self.w = self.w2
#         elif n_input == 3:
#             self.w = self.w3
#         elif n_input == 4:
#             self.w = self.w4
#         elif n_input == 5:
#             self.w = self.w5
#         elif n_input == 6:
#             self.w = self.w6
#         elif n_input == 7:
#             self.w = self.w7
#         elif n_input == 8:
#             self.w = self.w8
#         elif n_input == 9:
#             self.w = self.w9
#         elif n_input == 10:
#             self.w = self.w10

#     def reset(self):
#         self.expr = self.z

#     def return_value(self, a):
#         if a == 'x':
#             return self.x
#         elif a == 'y':
#             return self.y
#         elif a == 'z':
#             return self.z
#         elif a == 'w':
#             return self.w
#         else:
#             raise ValueError('Invalid input', a)


#     def get_values(self, a, b):
#         if isinstance(a, str):
#             a = self.return_value(a)
#         else:
#             raise TypeError('Invalid type, expected string', type(a))
#         if isinstance(b, int):
#             pass
#         elif isinstance(b, str):
#             b = self.return_value(b)
#         else:
#             raise TypeError('Invalid type', type(b))
#         return a, b

#     def add(self, a, b):
#         a, b =  self.get_values(a, b)
#         self.expr = self.expr.subs(a, a+b)
#     def mul(self, a, b):
#         a, b =  self.get_values(a, b)
#         self.expr = self.expr.subs(a, a*b)

#     def div(self, a, b):
#         a, b =  self.get_values(a, b)
#         self.expr = self.expr.subs(a, a//b)

#     def mod(self, a, b):
#         a, b =  self.get_values(a, b)
#         self.expr = self.expr.subs(a, b-sympy.floor(a/b)*b)

#     def eql(self, a, b):
#         a, b =  self.get_values(a, b)
#         if b == 0:
#             test1 = self.expr.subs(a, 1)
#             test0 = self.expr.subs(a, 0)
#             if self.w in test1.free_symbols and self.w in test0.free_symbols:
#                 raise(Exception("Double eql!!"))
#             elif self.w in test1.free_symbols:
#                 print("about to apply a==b on",self.expr, "for ", a, b, "giving", test1)
#                 self.expr = self.expr.subs(a, 1)
#             else:
#                 print("about to apply a==b on",self.expr, "for ", a, b, "giving", test0)
#                 self.expr = self.expr.subs(a, 0)
#             print()
#         else:
#             print("avoiding applying a==b on",self.expr, "for ", a, b)
