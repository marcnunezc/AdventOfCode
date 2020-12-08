class GameBoy:
    def __init__(self, lines_list):
        self.lines_list = lines_list
        self.is_on = True
        self.accumulator = 0
        self.iterator = 0
        self.iterations_list = []
        self.hash_func_map = {
            "acc"  : lambda x: self.IncreaseAccumulator(x),
            "jmp"  : lambda x: self.IncreaseIterator(x),
            "nop"  : lambda x: self.IncreaseAccumulator(0),
        }
    def ReadInstruction(self):
        instruction, value = self.lines_list[self.iterator].split()
        self.ValidateAndExecuteInstruction(instruction, value)
    def ValidateAndExecuteInstruction(self, instruction, value):
        if not self.iterator in self.iterations_list:
            self.iterations_list.append(self.iterator)
            self.hash_func_map[instruction](int(value))
        else:
            print("Inifinte loop, switching off GameBoy")
            self.is_on = False
        if self.iterator == len(self.lines_list):
            self.is_on = False
    def IncreaseIterator(self, value):
        self.iterator += value
    def IncreaseAccumulator(self, value):
        self.accumulator += value
        self.iterator += 1
    def GetAccumulator(self):
        return self.accumulator
    def IsOn(self):
        return self.is_on

game_boy = GameBoy(open("input.txt").read().splitlines())
while (game_boy.IsOn()):
    game_boy.ReadInstruction()

print("Accumulator", game_boy.GetAccumulator())

class GameBoyHacked(GameBoy):
    def __init__(self, lines_list, hack_position):
        super().__init__(lines_list)
        self.hack_position = hack_position
        self.switch_map = {
            "jmp" : "nop",
            "nop" : "jmp"
        }
    def ValidateAndExecuteInstruction(self, instruction, value):
        if self.iterator == self.hack_position and instruction in self.switch_map.keys():
            instruction = self.switch_map[instruction]
        super().ValidateAndExecuteInstruction(instruction, value)

lines_list = open("input.txt").read().splitlines()
jmp_or_nop_positions = [i for i, value in enumerate(lines_list) if value.split()[0] == "jmp" or value.split()[0] == "nop"]
game_boy = GameBoyHacked(lines_list, "dummy")
for key in jmp_or_nop_positions:
    if game_boy.iterator != len(game_boy.lines_list):
        game_boy = GameBoyHacked(lines_list, key)
        while (game_boy.IsOn()):
            game_boy.ReadInstruction()
    else:
        break
print("Accumulator", game_boy.GetAccumulator())