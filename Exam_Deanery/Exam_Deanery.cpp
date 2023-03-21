#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include "Colors.h"

using namespace std;

class Person
{
private:
	string firstName;
	string lastName;
	int age;
public:
	Person() : firstName(""), lastName(""), age(0) { }
	Person(string f, string l, int a) : firstName(f), lastName(l)
	{
		if (a < 17)
			throw exception("Invalid age");
		else
			age = a;
	}
	virtual void ShowInfo()
	{
		cout << firstName << " " << lastName << " - " << age << " years old." <<endl;
	}
	string GetFirstName()
	{
		return firstName;
	}
	string GetLastName()
	{
		return lastName;
	}
	int GetAge()
	{
		return age;
	}
	void SetFirstName(string f)
	{
		firstName = f;
	}
	void SetLastName(string l)
	{
		lastName = l;
	}
	void SetAge(int a)
	{
		age = a;
	}
	void SetAll(string f, string l, int a)
	{
		firstName = f;
		lastName = l;
		age = a;
	}
};

class Student : public Person
{
private:

public:
	Student() : Person() { }
	Student(string f, string l, int a) : Person(f, l, a) { }
};

class Teacher : public Person
{
private:

public:
	Teacher() : Person() { }
	Teacher(string f, string l, int a) : Person(f, l, a) { }
};
class Marks
{
private:
	vector<int> marks;
public:
	Marks() { }
	Marks(std::initializer_list<int> mark)
	{
		for (const int* ptr = mark.begin(); ptr != mark.end(); ptr++)
		{
			this->marks.push_back(*ptr);
		}
	}
	~Marks()
	{
		marks.clear();
	}
	void AddMarks(std::initializer_list<int> mark)
	{
		for (const int* ptr = mark.begin(); ptr != mark.end(); ptr++)
		{
			this->marks.push_back(*ptr);
		}
	}
	int GetMark(int i)
	{
		return marks[i];
	}
	int NumOfMarks()
	{
		return marks.size();
	}
	void AddMark(int mark)
	{
		this->marks.push_back(mark);
	}
	void ShowMarks()
	{
		for (int i = 0; i < marks.size(); i++)
		{
			cout << marks[i] << ' ';
		}
		cout << endl;
	}
};

class Subject
{
private:
	string subjectName;
	Teacher* teacher;
	vector<Marks>marks;
	vector<Student>student;
public:
	Subject() { }
	Subject(string s) : subjectName(s) { }
	Subject(string s, Teacher* t) : subjectName(s), teacher(t){ }
	~Subject()
	{
		marks.clear();
		student.clear();
	}
	void Show()
	{
		cout << "Subject: " << subjectName << endl;
		if (IsTeacher())
			cout << "Teacher: " << teacher->GetFirstName() << " " << teacher->GetLastName() << endl;
		else
			cout << "Unknown teacher" << endl;
	}
	void AddMarks(Marks* mark)
	{
		this->marks.push_back(*mark);
	}
	void AddStudent(Student* student)
	{
		this->student.push_back(*student);
	}
	void AddTeacher(Teacher* teacher)
	{
		this->teacher = teacher;
	}
	int GetTeacherAge()
	{
		return teacher->GetAge();
	}
	void AddSubjectName(string subName)
	{
		subjectName = subName;
	}
	int* GetMarks(int i)
	{
		int* mark = new int[marks[i].NumOfMarks()];
		for (size_t j = 0; j < marks[i].NumOfMarks(); j++)
		{
			mark[j] = marks[i].GetMark(j);
		}
		return mark;
	}
	int NumOfMarks(int i)
	{
		return marks[i].NumOfMarks();
	}
	string GetSubjectName()
	{
		return subjectName;
	}
	string GetFullName()
	{
		string fullName;
		fullName = teacher->GetFirstName() + " " + teacher->GetLastName();
		return fullName;
	}
	string GetStudentFullName(int i)
	{
		return (student[i].GetFirstName() + " " + student[i].GetLastName());
	}
	int GetStudentAge(int i)
	{
		return student[i].GetAge();
	}
	int NumOfStudent()
	{
		return student.size();
	}
	bool IsTeacher() const
	{
		return teacher != nullptr;
	}
	void ShowGradeLog()
	{
		if (student.size() < marks.size())
			cout << "Add more student, number of marks - " << marks.size() << " number of student - " << student.size() << endl;
		else if(student.size() > marks.size())
			cout << "Add more marks, number of marks - " << marks.size() << " number of student - " << student.size() << endl;
		else
		{
			for (int i = 0; i < marks.size(); i++)
			{
				cout << "Student grades " << student[i].GetFirstName() << " " << student[i].GetLastName() << " is:\t ";
				marks[i].ShowMarks();
			}
		}
	}
	void ShowGradeByIndex(int index)
	{
		if (index == -1)
			return;
		else
		{
			cout << "Student grades " << student[index].GetFirstName() << " " << student[index].GetLastName() << " is:\t ";
			marks[index].ShowMarks();
		}
	}
	int IfIsStudent(string name)
	{
		for (int i = 0; i < student.size(); i++)
		{
			if (student[i].GetFirstName() + student[i].GetLastName() == name)
				return i;
		}
		return -1;
	}
	void DeleteStudent(string firstName, string lastName)
	{
		bool found = false;
		for (int i = 0; i < student.size(); i++)
		{
			if (firstName + lastName == student[i].GetFirstName() + student[i].GetLastName())
			{
				student.erase(student.begin() + i);
				found = true;
			}
		}
		if (!found)
			cout << "Student not found";
	}
};


class Group
{
private:
	string groupName;
	vector<Subject>subject;
	vector<Student>student;
public:
	Group() { }
	Group(string g) : groupName(g) { }
	Group(string g, std::initializer_list<Subject> sub, std::initializer_list<Student> stu) : groupName(g)
	{
		for (const Subject* ptr = sub.begin(); ptr != sub.end(); ptr++)
		{
			this->subject.push_back(*ptr);
		}
		for (const Student* ptr = stu.begin(); ptr != stu.end(); ptr++)
		{
			this->student.push_back(*ptr);
		}
	}
	~Group()
	{
		subject.clear();
		student.clear();
	}
	void AddSubject(Subject* subject)
	{
		this->subject.push_back(*subject);
	}
	void AddStudent(Student* student)
	{
		this->student.push_back(*student);
	}
	void AddGroupName(string groupName)
	{
		this->groupName = groupName;
	}
	void ShowStudentList()
	{
		cout << "Group: " << groupName << endl;
		cout << "\tStudent list\n";
		for (int i = 0; i < student.size(); i++)
		{
			cout << i + 1 << "# ";
			student[i].ShowInfo();
		}
		cout << "==================================================================================\n";
	}
	void ShowSubjects()
	{
		cout << "Group: " << groupName << endl;
		cout << "\tSubject list\n";
		for (int i = 0; i < subject.size(); i++)
		{
			cout << i + 1 << "# ";
			subject[i].Show();
		}
		cout << "==================================================================================\n";
	}
	void ShowGroupName()
	{
		cout << groupName << endl;
	}
	void SetGroupName(string name)
	{
		groupName = name;
	}
	int NumOfSubject()
	{
		return subject.size();
	}
	int NumOfStudent()
	{
		return student.size();
	}
	string GetGroupName()
	{
		return groupName;
	}
	string GetTeacherName(int i)
	{
		return subject[i].GetFullName();
	}
	string GetSubjectName(int i)
	{
		return subject[i].GetSubjectName();
	}
	string GetStudentName(int i)
	{
		return (student[i].GetFirstName() + " " + student[i].GetLastName());
	}
	int GetStudentAge(int i)
	{
		return student[i].GetAge();
	}
	int GetSubjectNum()
	{
		return subject.size();
	}
	void ShowGrades()
	{
		bool found = false;
		for (int i = 0; i < subject.size(); i++)
		{
			cout << "\t\t";
			subject[i].Show();
			for (int j = 0; j < student.size(); j++)
			{
				found = false;
				subject[i].ShowGradeByIndex(subject[i].IfIsStudent(student[j].GetFirstName() + student[j].GetLastName()));
				if (subject[i].IfIsStudent(student[j].GetFirstName() + student[j].GetLastName()) != -1)
					found = true;
				if (!found)
					cout << "Student " << student[j].GetFirstName() << " " << student[j].GetLastName() << " grades is:\t not found" << endl;
			}

		}
		cout << "==================================================================================\n";
	}

	void DeleteStudent(string firstName, string lastName)
	{
		bool found = false;
		for (int i = 0; i < student.size(); i++)
		{
			if (firstName + lastName == student[i].GetFirstName() + student[i].GetLastName())
			{
				student.erase(student.begin() + i);
				found = true;
			}
		}
		if (!found)
			cout << "Student not found";

	}
	void DeleteSubject(string subName)
	{
		bool found = false;
		for (int i = 0; i < subject.size(); i++)
		{
			if (subName == subject[i].GetSubjectName())
			{
				subject.erase(subject.begin() + i);
				found = true;
			}
		}
		if (!found)
			cout << "Subject not found";
	}
};

class Menu
{
private:
	vector<string> items;
	int selectedIndex = 0;

public:
	Menu()
	{
		items.assign({ "Show list of students in group", "Show list of studied subjects",
			"Show students grades", "Add subject", "Add group", "Load subject from file",
			"Load group from file","Exclude student", "Delete subject from group", 
			"Save group to file", "Save subject to file", "Resave all group to file", "Resave all subject to file", "Exit" });
	}
	Menu(initializer_list<string> item)
	{
		for (const string* ptr = item.begin(); ptr != item.end(); ptr++)
		{
			this->items.push_back(*ptr);
		}
	}

	int Show()
	{
		int input = 'q';
		do
		{
			system("cls");
			SetColor(ConsoleColor::BLACK, ConsoleColor::YELLOW);
			cout << "\tMENU\n";
			for (size_t i = 0; i < items.size(); i++)
			{
				if (i == selectedIndex)
					SetColor(ConsoleColor::BLACK, ConsoleColor::WHITE);
				else
					SetColor(ConsoleColor::BLACK, ConsoleColor::GRAY);
				cout << items[i] << endl;
			}
			input = _getch();
			if (input == 224)
			{
				input = _getch();
				switch (input)
				{
				case 80:
					if (selectedIndex < items.size() - 1)
						++selectedIndex;
					break;
				case 72:
					if (selectedIndex > 0)
						--selectedIndex;
					break;
				}
			}
			else if (input == 13)
				return selectedIndex;
		} while (input != 'q');
		SetColor();
		return -1;
	}
};

class Deanery
{
private:
	Marks marks[400];
	Student student[400];
	int studentNum;
	Teacher teacher[50];
	int teacherNum;
	Subject subject[50];
	int subjectNum;
	Group group[10];
	int groupNum;
public:
	Deanery() : studentNum(-1), teacherNum(-1), subjectNum(-1), groupNum(-1) { }
	void LoadSubjectFromFile()
	{
		string something = "";
		string firstName = "";
		string lastName = "";
		int value;
		int number = 0;
		bool found = false;
		ifstream file("SubjectDatabase.txt");
		if (!file.is_open())
		{
			cerr << ">>>>> Error of opening file !>>>>>\n";
		}
		else
		{
			file >> something;
			do {
				if (something != "<SUBJECT>")
					break;
				file >> something;
				file >> firstName;
				file >> lastName;
				file >> value;
				found = false;
				if (subjectNum >= 0)
				{
					for (size_t i = 0; i <= subjectNum; i++)
					{
						if (subject[i].GetFullName() == (firstName + " " + lastName) && subject[i].GetSubjectName() == something)
							found = true;
					}
				}
				if (!found)
				{
					subjectNum++;
					subject[subjectNum].AddSubjectName(something);
					teacherNum++;
					teacher[teacherNum].SetFirstName(firstName);
					teacher[teacherNum].SetLastName(lastName);
					teacher[teacherNum].SetAge(value);
					file >> number;
					subject[subjectNum].AddTeacher(&teacher[teacherNum]);
					for (size_t i = 0; i < number; i++)
					{
						file >> firstName;
						file >> lastName;
						file >> value;
						if (studentNum < 0)
						{
							studentNum++;
							student[studentNum].SetAll(firstName, lastName, value);
							subject[subjectNum].AddStudent(&student[studentNum]);
						}
						else
						{
							found = false;
							for (size_t j = 0; j <= studentNum; j++)
							{
								if (student[j].GetFirstName() + " " + student[j].GetLastName() == firstName + " " + lastName && student[j].GetAge() == value)
								{
									subject[subjectNum].AddStudent(&student[j]);
									found = true;
								}
							}
							if (!found)
							{
								studentNum++;
								student[studentNum].SetAll(firstName, lastName, value);
								subject[subjectNum].AddStudent(&student[studentNum]);
							}
						}
					}
					for (int i = number - 1; i >= 0; i--)
					{
						while (file >> value)
						{
							if (value == -1)
								break;
							marks[studentNum - i + 1].AddMark(value);
						}
						subject[subjectNum].AddMarks(&marks[studentNum - i + 1]);
					}
				}
				else
				{
					file >> number;
					for (size_t i = 0; i < number+1; i++)
					{
						getline(file, something);
					}
					for (size_t i = 0; i < number; i++)
					{
						getline(file, something);
					}
				}
				file >> something;
			} while (true);
			file.close();
		}
	}

	void ShowSubjectGrades()
	{
		for (size_t i = 0; i <= subjectNum; i++)
		{
			subject[i].Show();
			subject[i].ShowGradeLog();
		}
	}

	void ShowSubject()
	{
		for (size_t i = 0; i <= subjectNum; i++)
		{
			cout << "#" << i + 1 << " ";
			subject[i].Show();
		}
	}
	void LoadGroupFromFile()
	{
		string something = "";
		string firstName = "";
		string lastName = "";
		int value = 0;
		int number = 0;
		bool found = false;
		ifstream file("GroupDatabase.txt");
		if (!file.is_open())
		{
			cerr << ">>>>> Error of opening file !>>>>>\n";
		}
		else
		{
			file >> something;
			do{
				if (something != "<GROUP>")
					break;
				groupNum++;
				file >> something;
				group[groupNum].AddGroupName(something);
				file >> number;
				for (size_t i = 0; i < number; i++)
				{
					file >> something;
					file >> firstName;
					file >> lastName;
					for (size_t j = 0; j <= subjectNum; j++)
					{
						if (subject[j].GetSubjectName() == something && subject[j].GetFullName() == (firstName + " " + lastName))
							group[groupNum].AddSubject(&subject[j]);
					}
				}
				file >> number;
				for (size_t i = 0; i < number; i++)
				{
					file >> firstName;
					file >> lastName;
					file >> value;
						if (studentNum < 0)
						{
							studentNum++;
							student[studentNum].SetAll(firstName, lastName, value);
							group[groupNum].AddStudent(&student[studentNum]);
						}
						else
						{
							found = false;
							for (size_t j = 0; j <= studentNum; j++)
							{
								if (student[j].GetFirstName() + " " + student[j].GetLastName() == firstName + " " + lastName && student[j].GetAge() == value)
								{
									group[groupNum].AddStudent(&student[j]);
									found = true;
								}
							}
							if (!found)
							{
								studentNum++;
								student[studentNum].SetAll(firstName, lastName, value);
								group[groupNum].AddStudent(&student[studentNum]);
							}
						}
				}
				file >> something;
			} while (true);
		file.close();
		}
	}
	void AddSubject()
	{
		string something = "";
		string firstName = "";
		string lastName = "";
		int number = 0;
		int value = 0;
		bool found = false;
		cout << "Enter subject name: ";
		cin >> something;
		cout << "Enter firstname of teacher: ";
		cin >> firstName;
		cout << "Enter lastname of teacher: ";
		cin >> lastName;
		cout << "Enter age of teacher: ";
		cin >> value;
		if (subjectNum > 0)
		{
			found = false;
			for (size_t i = 0; i < subjectNum; i++)
			{
				if (subject[i].GetSubjectName() == something && subject[i].GetFullName() == (firstName + " " + lastName))
				{
					found = true;
				}
			}
		}
		if (!found)
		{
			subjectNum++;
			subject[subjectNum].AddSubjectName(something);
			if (teacherNum > 0)
			{
				found = false;
				for (size_t j = 0; j <= teacherNum; j++)
				{
					if (teacher[j].GetFirstName() + " " + teacher[j].GetLastName() == firstName + " " + lastName && teacher[j].GetAge() == value)
					{
						subject[subjectNum].AddTeacher(&teacher[j]);
						found = true;
					}
				}
			}
			if (!found)
			{
				teacherNum++;
				teacher[teacherNum].SetAll(firstName, lastName, value);
				subject[subjectNum].AddTeacher(&teacher[teacherNum]);
			}
			cout << "Enter number of student you want add to the subject: ";
			cin >> number;
			for (size_t j = 0; j < number; j++)
			{
				cout << "Enter firstname of student: ";
				cin >> firstName;
				cout << "Enter lastname of student: ";
				cin >> lastName;
				cout << "Enter age of student: ";
				cin >> value;
				if (studentNum < 0)
				{
					studentNum++;
					student[studentNum].SetAll(firstName, lastName, value);
					subject[subjectNum].AddStudent(&student[studentNum]);
				}
				else
				{
					found = false;
					for (size_t j = 0; j <= studentNum; j++)
					{
						if (student[j].GetFirstName() + " " + student[j].GetLastName() == firstName + " " + lastName && student[j].GetAge() == value)
						{
							subject[subjectNum].AddStudent(&student[j]);
							found = true;
						}
					}
					if (!found)
					{
						studentNum++;
						student[studentNum].SetAll(firstName, lastName, value);
						subject[subjectNum].AddStudent(&student[studentNum]);
					}
				}
			}
			int marksNumber = 0;
			for (int j = number - 1; j >= 0; j--)
			{
				cout << "Enter number of marks for " << number - j << " student: ";
				cin >> marksNumber;
				for (size_t i = 0; i < marksNumber; i++)
				{
					cout << "Enter mark #" << i + 1 << " : ";
					cin >> value;
					marks[studentNum - j + 1].AddMark(value);
				}
				subject[subjectNum].AddMarks(&marks[studentNum - j + 1]);
			}
		}
		else
			cout << "Subject with this name and teacher has already been added" << endl;
	}

	void AddGroup()
	{
		string something = "";
		string firstName = "";
		string lastName = "";
		int number = 0;
		bool found = false;
		cout << "Enter name of group: ";
		cin >> something;
		if (groupNum > 0)
		{
			found = false;
			for (size_t i = 0; i < groupNum; i++)
			{
				if (group[i].GetGroupName() == something)
					found = true;
			}
		}
		if (!found)
		{
			int variant;
			groupNum++;
			group[groupNum].SetGroupName(something);
			do {
				Menu menu1({ "Add subject from database", "Add new subject", "Next" });
				variant = menu1.Show();
				if (variant == 0)
				{
					if (subjectNum < 0)
						cout << "There are no subject in database" << endl;
					else
					{
						ShowSubject();
						do {
							cout << "Enter subject number you want to add the group: ";
							cin >> number;
						} while (number <= 0 || number > subjectNum + 1);
						group[groupNum].AddSubject(&subject[number - 1]);
					}
				}
				else if (variant == 1)
				{
					AddSubject();
					group[groupNum].AddSubject(&subject[subjectNum]);
				}
				else
					break;
			} while (true);
			do {
				number = 0;
				Menu menu2({ "Add student from database", "Add new student", "Next" });
				variant = menu2.Show();
				if (variant == 0)
				{
					if (studentNum < 0)
						cout << "There are no student in database" << endl;
					else
					{
						ShowAllStudent();
						do {
							cout << "Enter subject number you want to add the group: ";
							cin >> number;
						} while (number <= 0 || number > studentNum + 1);
						group[groupNum].AddStudent(&student[number - 1]);
					}
				}
				else if (variant == 1)
				{
					cout << "Enter student first name: ";
					cin >> firstName;
					cout << "Enter student last name: ";
					cin >> lastName;
					cout << "Enter student age: ";
					cin >> number;
					studentNum++;
					student[studentNum].SetAll(firstName, lastName, number);
					group[groupNum].AddStudent(&student[studentNum]);
				}
				else
					break;
			} while (true);
		}
	}

	void ShowGroupStList()
	{
		for (size_t i = 0; i <= groupNum; i++)
		{
			group[i].ShowStudentList();
		}
	}
	void ShowGroupSubject()
	{
		for (size_t i = 0; i <= groupNum; i++)
		{
			group[i].ShowSubjects();
		}
	}
	void ShowGroupGrades()
	{
		for (size_t i = 0; i <= groupNum; i++)
		{
			group[i].ShowGrades();
		}
	}

	void ShowGroup()
	{
		for (size_t i = 0; i <= groupNum; i++)
		{
			group[i].ShowStudentList();
			group[i].ShowSubjects();
			group[i].ShowGrades();
		}
	}

	void SaveGroupToFile()
	{
		ofstream file("GroupDatabase.txt", ios::binary | ios::app);
		if (!file.is_open())
		{
			cerr << ">>>>> Error of opening file !>>>>>\n";
		}
		else
		{
			int variant = -1;
			if(groupNum >= 0 )
				for (size_t i = 0; i <= groupNum; i++)
				{
					group[i].ShowGroupName();
				}
			do {
				cout << "Enter number of group you want to save ";
				cin >> variant;
			} while (variant <= 0 || variant > groupNum + 1);
			variant--;
			file << "\n<GROUP>";
			file << endl <<group[variant].GetGroupName();
			file << endl << group[variant].NumOfSubject();
			for (size_t j = 0; j < group[variant].NumOfSubject(); j++)
			{
				file << endl << group[variant].GetSubjectName(j) << " " << group[variant].GetTeacherName(j);
			}
			file << endl << group[variant].NumOfStudent();
			for (size_t j = 0; j < group[variant].NumOfStudent(); j++)
			{
				file << endl << group[variant].GetStudentName(j) << " " << group[variant].GetStudentAge(j);
			}
			file.close();
		}
	}
	void SaveSubjectToFile()
	{
		ofstream file("SubjectDatabase.txt", ios::binary | ios::app);
		if (!file.is_open())
		{
			cerr << ">>>>> Error of opening file !>>>>>\n";
		}
		else
		{
			int variant = -1;
			if (subjectNum >= 0)
				for (size_t i = 0; i <= subjectNum; i++)
				{
					subject[i].Show();
				}
			do {
				cout << "Enter number of group you want to save ";
				cin >> variant;
			} while (variant <= 0 || variant > subjectNum + 1);
			variant--;
			file << "\n<SUBJECT>";
			file << endl << subject[variant].GetSubjectName();
			file << endl << subject[variant].GetFullName() << " " << subject[variant].GetTeacherAge();

			for (size_t j = 0; j < subject[variant].NumOfStudent(); j++)
			{
				file << endl << subject[variant].GetStudentFullName(j) << " " << subject[variant].GetStudentAge(j);
			}
			for (size_t j = 0; j < subject[variant].NumOfStudent(); j++)
			{
				int* mark = new int[subject[variant].NumOfMarks(j)];
				mark = subject[variant].GetMarks(j);
				file << endl;
				for (size_t k = 0; k < subject[variant].NumOfMarks(j); k++)
				{
					file << mark[k] << " ";
				}
				file << "-1";
			}
			file.close();
		}
	}

	void ReSaveAllGroup()
	{
		fstream clear_file("GroupDatabase.txt", ios::out);
		clear_file.close();
		ofstream file("GroupDatabase.txt");
		if (!file.is_open())
		{
			cerr << ">>>>> Error of opening file !>>>>>\n";
		}
		else
		{
			int variant;
			cout << "WARNING!!!  If you want to resave all groups, all previous data from the file will be deleted" << endl;
			cout << "Do you want to continue?\n1 - Yes\n2 - No" << endl;
			do {
				cout << "Enter your choice: ";
				cin >> variant;
			} while (variant != 1 || variant != 2);
			if (variant == 1)
			{
				if (groupNum >= 0)
				{
					if (groupNum == 0)
						file << "<GROUP>";
					else
						file << "\n<GROUP>";
					for (size_t i = 0; i <= groupNum; i++)
					{
						file << endl << group[i].GetGroupName();
						file << endl << group[i].NumOfSubject();
						for (size_t j = 0; j < group[i].NumOfSubject(); j++)
						{
							file << endl << group[i].GetSubjectName(j) << " " << group[i].GetTeacherName(j);
						}
						file << endl << group[i].NumOfStudent();
						for (size_t j = 0; j < group[i].NumOfStudent(); j++)
						{
							file << endl << group[i].GetStudentName(j) << " " << group[i].GetStudentAge(j);
						}
					}
				}
			}
			file.close();
		}
	}
	void ReSaveAllSubject()
	{
		fstream clear_file("SubjectDatabase.txt", ios::out);
		clear_file.close();
		ofstream file("SubjectDatabase.txt");
		if (!file.is_open())
		{
			cerr << ">>>>> Error of opening file !>>>>>\n";
		}
		else
		{
			int variant;
			cout << "WARNING!!!  If you want to resave all subjects, all previous data from the file will be deleted" << endl;
			cout << "Do you want to continue?\n1 - Yes\n2 - No" << endl;
			do {
				cout << "Enter your choice: ";
				cin >> variant;
			} while (variant != 1 || variant != 2);
			if (variant == 1)
			{
				if (subjectNum >= 0)
				{
					if (subjectNum == 0)
						file << "<SUBJECT>";
					else
						file << "\n<SUBJECT>";
					for (size_t i = 0; i <= subjectNum; i++)
					{
						file << endl << subject[i].GetSubjectName();
						file << endl << subject[i].GetFullName() << " " << subject[i].GetTeacherAge();

						for (size_t j = 0; j < subject[i].NumOfStudent(); j++)
						{
							file << endl << subject[i].GetStudentFullName(j) << " " << subject[i].GetStudentAge(j);
						}
						for (size_t j = 0; j < subject[i].NumOfStudent(); j++)
						{
							int* mark = new int[subject[i].NumOfMarks(j)];
							mark = subject[i].GetMarks(j);
							file << endl;
							for (size_t k = 0; k < subject[i].NumOfMarks(j); k++)
							{
								file << mark[k] << " ";
							}
							file << "-1";
						}
					}
				}
			}
			file.close();
		}
	}
	void ExcludeStudent()
	{
		string firstName, lastName;
		cout << "Enter first name of the student you want to exclude: ";
		cin >> firstName;
		cout << "Enter last name of the student you want to exclude: ";
		cin >> lastName;
		if (groupNum >= 0)
		{
			for (size_t i = 0; i <= groupNum; i++)
			{
				group[i].DeleteStudent(firstName, lastName);
			}
		}
		if (subjectNum >= 0)
		{
			for (size_t i = 0; i < subjectNum; i++)
			{
				subject[i].DeleteStudent(firstName, lastName);
			}
		}
	}
	void DeleteSubjectFromGroup()
	{
		int number;
		int index;
		if (groupNum >= 0)
		{
			for (size_t i = 0; i <= groupNum; i++)
			{
				cout << "#" << i + 1 << " ";
				group[i].ShowGroupName();
			}
			do {
				cout << "Enter number of group from which you want to remove subject from the group: ";
				cin >> index;
			} while (index <= 0 || index > groupNum + 1);
			group[index - 1].ShowSubjects();
			do {
				cout << "Enter number of subject you want to remove from the group: ";
				cin >> number;
			} while (number <= 0 || number > group[index - 1].GetSubjectNum());
			group[index - 1].DeleteSubject(group[index - 1].GetSubjectName(number - 1));
		}
	}
	void ShowAllStudent()
	{
		for (size_t i = 0; i <= studentNum; i++)
		{
			cout << "#" << i + 1 << " ";
			cout << student[i].GetFirstName() << " " << student[i].GetLastName() << " " << student[i].GetAge() << endl;
		}
	}
};

int main()
{
	Deanery deanery;
	Menu menu;
	int variant;
	do {
		variant = menu.Show();
		system("cls");
		if (variant == 0)
			deanery.ShowGroupStList();
		else if (variant == 1)
			deanery.ShowGroupSubject();
		else if (variant == 2)
			deanery.ShowGroupGrades();
		else if (variant == 3)
			deanery.AddSubject();
		else if (variant == 4)
			deanery.AddGroup();
		else if (variant == 5)
			deanery.LoadSubjectFromFile();
		else if (variant == 6)
			deanery.LoadGroupFromFile();
		else if (variant == 7)
			deanery.ExcludeStudent();
		else if (variant == 8)
			deanery.DeleteSubjectFromGroup();
		else if (variant == 9)
			deanery.SaveGroupToFile();
		else if (variant == 10)
			deanery.SaveSubjectToFile();
		else if (variant == 11)
			deanery.ReSaveAllGroup();
		else if (variant == 11)
			deanery.ReSaveAllSubject();
		else
			break;
		_getch();
	} while (true);
}	