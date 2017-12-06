class Course:
	global courses
	def __init__(self, courseCode):
		self.courseCode = courseCode
		self.prereqs = []
		self.nextCourses = []
		self.nextDepth = 0
		self.visits = 0
		self.visited = False
	def addPrereq(self, prereq):
		self.prereqs.append(prereq)
		prereq.addNext(self)
	def addNext(self, nextCourse):
		self.nextCourses.append(nextCourse)
	def getDepth(self):
		self.visited = True
		self.visits += 1
		if len(self.nextCourses) == 0:
			return 0
		if self.nextDepth != 0:
			return self.nextDepth
		maxDepth = 0
		for c in self.nextCourses:
			course = courses[c]
			if(course.visits) > len(course.prereqs):
				print("Bad")
				exit()
			course.nextDepth = course.getDepth()
			maxDepth = max(maxDepth, course.nextDepth)
		self.nextDepth = maxDepth + 1
		return self.nextDepth

C = int(input())
N = int(input())
courses = {}
for i in range(N):
	A, B = [int(x) for x in input().split()]
	if A not in courses:
		courses[A] = Course(A)
	if B not in courses:
		courses[B] = Course(B)
	if B not in courses[A].prereqs:
		courses[A].prereqs.append(B)
	if A not in courses[B].nextCourses:
		courses[B].nextCourses.append(A)
for c in courses:
	if len(courses[c].prereqs) == 0:
		courses[c].getDepth()
for c in courses:
	if courses[c].visits == 0:
		print("Bad")
		exit()
if len(courses) > C:
	print("Bad")
else:
	print("Good")