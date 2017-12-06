/* UWindsor CS POTW 2017
 * Week 4 - The Blackboard API
 * Adam Vandolder
 * github.com/avandolder */

#include <deque>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Course
{
    std::unordered_set<Course*> children; // Courses that require this one.
    std::unordered_set<Course*> parents; // Courses this one requires.

public:
    bool has_parents();
    void add_parent(Course *c);
    void remove_parent(Course *c);
    void add_child(Course *c);
    std::unordered_set<Course*>& get_children();
};

bool Course::has_parents()
{
    return !parents.empty();
}

void Course::add_parent(Course *c)
{
    parents.insert(c);
}

void Course::remove_parent(Course *c)
{
    parents.erase(c);
}

void Course::add_child(Course *c)
{
    children.insert(c);
}

std::unordered_set<Course*>& Course::get_children()
{
    return children;
}

int can_graduate(std::unordered_map<int, Course*>& courses, int required)
{
    std::deque<Course*> satisfied; // Keep track of courses for which the
                                   // requirements have been satisfied.
    int taken = 0; // Keep track of the number of courses that can be taken.

    // Find courses with no requirements.
    for (auto c : courses)
        if (!c.second->has_parents())
            satisfied.push_back(c.second);

    while (!satisfied.empty())
    {
        // Get the top course from the satisfied list.
        auto parent = satisfied.front();
        satisfied.pop_front();

        // Increase the amount of courses taken, returning if surpasses or
        // equals the required amount.
        if (++taken >= required)
            return true;

        for (auto c : parent->get_children())
        {
            c->remove_parent(parent);

            // If c's requirements have been satisfied, add it to satisfied.
            if (!c->has_parents())
                satisfied.push_back(c);
        }
    }

    return taken >= required;
}

int main(int argc, char *argv[])
{
    std::unordered_map<int, Course*> courses;

    int c, n;
    std::cin >> c >> n;

    for (int i = 0; i < n; i++)
    {
        int parent, child;
        std::cin >> parent >> child;

        // If the parent or child don't already exist, create them.
        if (courses.find(parent) == courses.end())
            courses[parent] = new Course();
        if (courses.find(child) == courses.end())
            courses[child] = new Course();

        courses[child]->add_parent(courses[parent]);
        courses[parent]->add_child(courses[child]);
    }

    if (can_graduate(courses, c))
        std::cout << "Good" << std::endl;
    else
        std::cout << "Bad" << std::endl;

    for (int i = 0; i < courses.size(); i++)
        delete courses[i];

    return 0;
}
