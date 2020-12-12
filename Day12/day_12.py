class Ferry:
    def __init__(self):
        self.pos = [0,0]
        self.angle = 0
        self.func_map = {
            "N" : lambda x: self.MoveFerry([0,1], x),
            "S" : lambda x: self.MoveFerry([0,-1], x),
            "E" : lambda x: self.MoveFerry([1,0], x),
            "W" : lambda x: self.MoveFerry([-1,0], x),
            "F" : lambda x: self.func_map[self.GetFacing()](x),
            "L" : lambda x: self.RotateFerry(x),
            "R" : lambda x: self.RotateFerry(-1*x)
        }
    def MoveFerry(self, direction, value):
        movement = [coord*value for coord in direction]
        self.pos[0] += movement[0]
        self.pos[1] += movement[1]
    def RotateFerry(self, value):
        self.angle += value
    def GetFacing(self):
        return self._GetFacingMap()[str(int(self.angle % 360 / 90))]
    def ReadInstruction(self, line):        
        ins, value = [line[0], int(line[1:])]
        self.func_map[ins](value)
    def GetManhattanDistance(self):
        return sum([abs(x) for x in self.pos])
    @staticmethod
    def _GetFacingMap():
        return {
            "0" : "E",
            "1" : "N",
            "2" : "W",
            "3" : "S"
        }

lines_list = open("input.txt").read().splitlines()
ferry = Ferry()
for line in lines_list:
    ferry.ReadInstruction(line)
print("Part 1", ferry.GetManhattanDistance())

import math
class ActualFerry(Ferry):
    def __init__(self):
        super().__init__()
        self.way_point = [10,1]
        self.func_map = {
            "N" : lambda x: self.MoveWayPoint([0,1], x),
            "S" : lambda x: self.MoveWayPoint([0,-1], x),
            "E" : lambda x: self.MoveWayPoint([1,0], x),
            "W" : lambda x: self.MoveWayPoint([-1,0], x),
            "F" : lambda x: self.MoveFerry(x),
            "L" : lambda x: self.RotateWayPoint(x),
            "R" : lambda x: self.RotateWayPoint(-1*x)
        }
    def MoveWayPoint(self, direction, value):
        movement = [coord*value for coord in direction]
        self.way_point[0] += movement[0]
        self.way_point[1] += movement[1]
    def RotateWayPoint(self, value):
        current_vect = [wy-ps for wy, ps in zip(self.way_point, self.pos)]
        rotated_vect = [0, 0]
        angle = math.radians(value)
        rotated_vect[0] = math.cos(angle)*current_vect[0] - math.sin(angle)*current_vect[1]
        rotated_vect[1] = math.cos(angle)*current_vect[1] + math.sin(angle)*current_vect[0]
        self.way_point = [pos+vec for pos, vec in zip(self.pos, rotated_vect)]
    def MoveFerry(self, value):
        current_vect = [wy-ps for wy, ps in zip(self.way_point, self.pos)]
        self.pos = [pos+x*value for pos, x in zip(self.pos, current_vect)]
        self.way_point = [pos+x*value for pos, x in zip(self.way_point, current_vect)]
ferry = ActualFerry()
for line in lines_list:
    ferry.ReadInstruction(line)
print("Part 2", ferry.GetManhattanDistance())