/*
 * Chapter 18 - list Example: Determining Enrollment
 *
 * Builds a duplicate-free, sorted master roster from a vector of per-course
 * student lists (containers can be nested), minus a list of dropped students.
 * Showcases the list-specific algorithms sort(), unique(), and remove(), plus
 * C++23 append_range() to concatenate lists.
 *
 * Key notes:
 *   - Reads roster data from course1.txt, course2.txt, ... and dropped.txt in
 *     the working directory; without those files it prints "Failed to open"
 *     and produces an empty result.
 */

#include <print>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <format>

using namespace std;

// courseStudents is a vector of lists, one for each course. The lists
// contain the students enrolled in those courses. They are not sorted.
//
// droppedStudents is a list of students who failed to pay their
// tuition and so were dropped from their courses.
//
// The function returns a list of every enrolled (non-dropped) student in
// all the courses.
list<string> getTotalEnrollment(const vector<list<string>>& courseStudents,
								const list<string>& droppedStudents)
{
	list<string> allStudents;

	// Concatenate all the course lists onto the master list
	for (auto& lst : courseStudents) {
		allStudents.append_range(lst); // C++23
		//allStudents.insert(cend(allStudents), cbegin(lst), cend(lst)); // Pre-C++23
	}

	// Sort the master list
	allStudents.sort();

	// Remove duplicate student names (those who are in multiple courses).
	allStudents.unique();

	// Remove students who are on the dropped list.
	// Iterate through the dropped list, calling remove on the
	// master list for each student in the dropped list.
	for (auto& str : droppedStudents) {
		allStudents.remove(str);
	}

	// done!
	return allStudents;
}

list<string> readStudentList(ifstream& istr)
{
	list<string> students;
	string name;
	while (getline(istr, name)) {
		println("Read name {}.", name);
		students.push_back(name);
	}
	return students;
}

vector<list<string>> readCourseLists()
{
	vector<list<string>> lists;
	// Read all course files. Course files are named as
	// course1.txt, course2.txt, ...
	// The loop stops once a file cannot be found.
	for (int i{ 1 };; ++i) {
		auto fileName{ format("course{}.txt", i) };
		ifstream istr{ fileName };
		if (!istr) {
			println("Failed to open {}.", fileName);
			break;
		}
		lists.push_back(readStudentList(istr));
	}
	return lists;
}

list<string> readDroppedStudents()
{
	ifstream istr{ "dropped.txt" };
	return readStudentList(istr);
}

int main()
{
	auto courseStudents{ readCourseLists() };
	auto droppedStudents{ readDroppedStudents() };

	auto finalList{ getTotalEnrollment(courseStudents, droppedStudents) };

	for (const auto& name : finalList) {
		println("{}", name);
	}
}
