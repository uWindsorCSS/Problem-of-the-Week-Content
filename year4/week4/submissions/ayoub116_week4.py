class CourseCycleDetector():

    def __init__(self, c, list):
        self.c = c
        self.list = list
        self.prereq_map = {}
        self.unique_courses = set()
        self.states = {}

    def map_prereqs(self):
        for prereq in self.list:
            A = prereq[0]
            B = prereq[1]
            self.unique_courses.add(A)
            self.unique_courses.add(B)

            if A in self.prereq_map:
                self.prereq_map[A].append(B)
            else:
                self.prereq_map[A] = [B]
        self.states = {course:0 for course in self.unique_courses}

    def dfs(self):
        if self.c != len(self.unique_courses):
            return 'Bad'

        for course in self.prereq_map:
            if self.states[course] == 0:
                if self.is_cycle(course, False):
                    return 'Bad'

        return 'Good'

    def is_cycle(self, course, cycle):
        if cycle or not course in self.prereq_map: return cycle
        self.states[course] = 1
        for prereq in self.prereq_map[course]:
            if self.states[prereq] == 1:
                return True
            cycle = (self.is_cycle(prereq, cycle) or cycle)

        self.states[course] = 2
        return cycle

def main():
    c = int(input())
    n = int(input())
    prereqs = [[int(course) for course in input().split()] for i in range(n)]

    cd = CourseCycleDetector(c,prereqs)
    cd.map_prereqs()
    print(cd.dfs())

if __name__ == '__main__': main()
