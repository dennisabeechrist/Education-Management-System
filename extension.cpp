#include <iostream>
#include <vector>
#include <string>
using namespace std;

class CourseC {
	public:
		string courseName;
	    string courseID;
	    
	    CourseC() {
	        courseName = "";
	        courseID = "";
	    }
	
	    CourseC(string name, string id) {
	        courseName = name;
	        courseID = id;
	    }
	
	    virtual void displayDetails() {
	        cout << "Course: " << courseName << " (ID: " << courseID << ")" << endl;
	    }
	
	    virtual ~CourseC() {} 
	    
};
	
class TheoryCourse : public CourseC {
	private:
	    int theoryHours;
	public:
	    TheoryCourse() {
	        theoryHours = 0;
	    }
	
	    TheoryCourse(string name, string id, int hours) : CourseC(name, id) {
	        theoryHours = hours;
	    }
	
	    void displayDetails() {
	        cout << "Theory Course: " << courseName 
	             << " (ID: " << courseID << ") - Hours: " << theoryHours << endl;
	    }
	    
	    virtual int calculateTotalHours(int practicalHours) {
	    	return theoryHours + practicalHours;
		}
		
		int getTheoryHours() {
			return theoryHours;
		}
	};
	
class PracticalCourse : public CourseC {
	private:
	    int labSessions;
	public:
	    PracticalCourse() {
	        labSessions = 0;
	    }
	
	    PracticalCourse(string name, string id, int sessions) : CourseC(name, id) {
	        labSessions = sessions;
	    }
	
	    void displayDetails()  {
	        cout << "Practical Course: " << courseName 
	             << " (ID: " << courseID << ") - Lab Sessions: " << labSessions << endl;
	    }
	    
	    int getLabSessions() {
	    	return labSessions;
		}
};
	
void showMenuC() {
	    cout << "----------------- Course Menu: -----------------" << endl;
	    cout << "1. Enter Theory Class" << endl;
	    cout << "2. Enter Practical Class" << endl;
	    cout << "3. Calculate Total Hours" << endl;
	    cout << "4. Exit" << endl;
	    cout << "------------------------------------------------" << endl;
	    cout << "Enter your choice: ";
}
	
CourseC* createCourse(int choice) {
    string name, id;
    int hoursOrSessions;

    cout << "Enter course name: ";
    cin >> name;
    cout << "Enter course ID: ";
    cin >> id;

    if (choice == 1) { 
        cout << "Enter number of theory hours: ";
        cin >> hoursOrSessions;
        return new TheoryCourse(name, id, hoursOrSessions);
    } else { 
        cout << "Enter number of lab sessions: ";
        cin >> hoursOrSessions;
        return new PracticalCourse(name, id, hoursOrSessions);
    }
}

class Person {
public:
    string personType;

    void setType() {
        cout << "Enter person type (e.g., student, athlete): ";
        cin >> personType;
    }

    void displayType() {
        cout << "Person Type: " << personType << endl;
    }
};

class StudentS : public Person {
public:
    int studentID;
    string studentName;

    void setDetails() {
        cout << "Enter student ID: ";
        cin >> studentID;
        cout << "Enter student name: ";
        cin >> studentName;
    }

    void displayDetails() {
        displayType();
        cout << "Student ID: " << studentID << ", Name: " << studentName << endl;
    }
};

class Marks {
public:
    float academicScore;

    void setMarks() {
        cout << "Enter academic score (out of 100): ";
        cin >> academicScore;
        while (academicScore < 0 || academicScore > 100) {
            cout << "Invalid score. Please enter a score between 0 and 100: ";
            cin >> academicScore;
        }
    }

    void displayMarks() {
        cout << "Academic Score: " << academicScore << "/100" << endl;
    }
};

class Sports {
public:
    float sportsScore;

    void setScore() {
        cout << "Enter sports score (out of 50): ";
        cin >> sportsScore;
        while (sportsScore < 0 || sportsScore > 50) {
            cout << "Invalid score. Please enter a score between 0 and 50: ";
            cin >> sportsScore;
        }
    }

    void displayScore() {
        cout << "Sports Score: " << sportsScore << "/50" << endl;
    }
};

class Scholarship : public StudentS, public Marks, public Sports {
public:
    void calculateEligibility() {
        float totalScore = academicScore + sportsScore;
        cout << "Total Score: " << totalScore << endl;

        if (totalScore >= 130) {
            cout << "Scholarship Eligibility: Eligible" << endl;
        } else {
            cout << "Scholarship Eligibility: Not Eligible" << endl;
        }
    }

    void displayAllDetails() {
        displayDetails();
        displayMarks();
        displayScore();
    }
};


class StudentF {
private:
    string studentId;
    string studentName;
    double totalFees;
    double paidFees;

public:
    StudentF(string id, string name, double fees) {
        studentId = id;
        studentName = name;
        totalFees = fees;
        paidFees = 0;
    }

    StudentF() {
        totalFees = 0; 
        paidFees = 0;
    }

    string getStudentId() {
        return studentId;
    }

    void payFees(double amount) {
        if (amount + paidFees > totalFees) {
            cout << "Payment exceeds total fees. Please enter a valid amount.\n";
        } else {
            paidFees += amount;
            cout << "Payment of " << amount << " processed successfully for " << studentName << ".\n";
        }
    }

    void displayDetails()  {
        cout << "Student ID: " << studentId
             << ", Name: " << studentName
             << ", Total Fees: " << totalFees
             << ", Paid Fees: " << paidFees
             << ", Outstanding Dues: " << (totalFees - paidFees) << endl;
    }

    bool isIdEqual(const string& id) {
        return studentId == id;
    }
};

class Fee {
private:
    StudentF* students; 
    int studentCount;
    int capacity; 

public:
    Fee() {
        capacity = 100; 
        studentCount = 0;
        students = new StudentF[capacity]; 
    }

    ~Fee() {
        delete[] students;
    }

    void addStudent(string id, string name, double fees) {
        if (studentCount < capacity) {
            students[studentCount] = StudentF(id, name, fees);
            studentCount++;
            cout << "Student added successfully.\n";
        } else {
            cout << "Cannot add more students, limit reached.\n";
        }
    }

    void payStudentFees(const string& studentId, double amount) {
        for (int i = 0; i < studentCount; i++) {
            if (students[i].isIdEqual(studentId)) {
                students[i].payFees(amount);
                return;
            }
        }
        cout << "No student found with ID: " << studentId << endl;
    }

    void displayStudents() {
        if (studentCount == 0) {
            cout << "No students available.\n";
            return;
        }
        cout << "Student Details:\n";
        for (int i = 0; i < studentCount; i++) {
            students[i].displayDetails();
        }
    }
};

class Feedback {
    vector<int> ratings;
    int size;

public:
    Feedback(int numStudents) {
        size = numStudents;
        ratings.resize(size, 0);
    }

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index! Exiting..." << endl;
            exit(1);
        }
        return ratings[index];
    }

    void display() {
        cout << "\nCurrent Feedback Ratings:\n";
        for (int i = 0; i < size; ++i) {
            cout << "Student " << i + 1 << ": " << ratings[i] << endl;
        }
    }

    double calculateAverage() {
        double sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += ratings[i];
        }
        return (size > 0) ? sum / size : 0;
    }
};

class Education {
public:
    int Roll_no;
    string Name;
    float Student_marks;

    void Details(int roll, string name, float marks) {
        Roll_no = roll;
        Name = name;
        Student_marks = marks;
    }
    void Educ() {
        cout << "\n-------------| STUDENT DATABASE |-------------\n";
        cout << "Enter the roll number: ";
        cin >> Roll_no;
        cout << "Enter the name: ";
        cin >> Name;
        cout << "Enter the marks: ";
        cin >> Student_marks;

        cout << "\nThe outputs will be printed below.\n";
        cout << "The student's roll number is: " << Roll_no << "\n";
        cout << "The student's name is: " << Name << "\n";
        cout << "The student's mark is: " << Student_marks << "\n";
        cout << "-----------------------------------------------\n";
    }
};

class Student {
private:
    int marks1, marks2, marks3, attendance;
    char grade;

public:
    Student(int m1 = 0, int m2 = 0, int m3 = 0, int att = 0) {
        marks1 = m1;
        marks2 = m2;
        marks3 = m3;
        attendance = att;
        grade = 'F';
    }

    void calculateTotalMarks(int total) {
        total = marks1 + marks2 + marks3;
        cout << "Inside calculateTotalMarks, Total Marks = " << total << endl;
    }

    void updateGrade(int total, char &gradeRef) {
        if (total >= 250) {
            gradeRef = 'A';
        } else if (total >= 200) {
            gradeRef = 'B';
        } else {
            gradeRef = 'C';
        }
        grade = gradeRef;
        cout << "Inside updateGrade, Grade = " << gradeRef << endl;
    }

    int& modifyAttd() {
        attendance += 5;
        return attendance;
    }

    int getTotalMarks() {
        return marks1 + marks2 + marks3;
    }

    void displayStudentInfo() {
        cout << "\nMarks: " << marks1 << ", " << marks2 << ", " << marks3 << endl;
        cout << "Total Marks: " << getTotalMarks() << endl;
        cout << "Grade: " << grade << endl;
        cout << "Attendance: " << attendance << endl;
    }

    // Average Calculator function
    float avg(float a = 0, float b = 0, float c = 0, float d = 0, float e = 0) {
        return (e == 0) ? (a + b + c + d) / 4 : (a + b + c + d + e) / 5;
    }
};

class Book {
private:
    int bookID;
    int pages;
    string title;

public:
    Book() {
        bookID = 0;
        pages = 0;
        title = "Unknown";
    }

    Book(int id) {
        bookID = id;
        pages = 0;
        title = "Unknown";
    }

    Book(int id, string bookTitle) {
        bookID = id;
        pages = 0;
        title = bookTitle;
    }

    Book(int id, string bookTitle, int bookPages) {
        bookID = id;
        title = bookTitle;
        pages = bookPages;
    }

    void print() const {
        cout << "Book ID: " << bookID << ", Title: " << title << ", Pages: " << pages << endl;
    }
};

class Course {
    static int totalEnrollment;
    int courseCode;
    int enrolledStudents;

public:
    Course(int code = 0) {
        courseCode = code;
        enrolledStudents = 0;
    }

    void enrollStudents(int num) {
        enrolledStudents += num;
        totalEnrollment += num;
    }

    static int getTotalEnrollment() {
        return totalEnrollment;
    }

    void displayCourseInfo() const {
        cout << "Course Code: " << courseCode 
             << ", Enrolled Students: " << enrolledStudents << endl;
    }
};

int Course::totalEnrollment = 0;

class Attendance {
    int daysPresent;

public:
    Attendance(int days = 0) {
        daysPresent = days;
    }

    void operator++() {
        daysPresent++;
    }

    void operator--() {
        daysPresent--;
    }

    void operator!() {
        daysPresent = 0;
    }

    void display() const {
        cout << "Days Present: " << daysPresent << endl;
    }
};

class StudentG {
private:
    string name;
    int id;

public:
    void getInfo() {
        cout << "Enter student name: ";
        cin >> name;
        cout << "Enter student ID: ";
        cin >> id;
    }

    void displayInfo() {
        cout << "Student Name: " << name << endl;
        cout << "Student ID: " << id << endl;
    }
};

class Undergraduate : public StudentG {
private:
    string major;

public:
    void getUgInfo() {
        getInfo();
        cout << "Enter major: ";
        cin >> major;
    }

    void displayUgInfo() {
        displayInfo();
        cout << "Major: " << major << endl;
    }
};

class Postgraduate : public Undergraduate {
private:
    string researchTopic;

public:
    void getPgInfo() {
        getUgInfo();
        cout << "Enter research topic: ";
        cin >> researchTopic;
    }

    void displayPgInfo() {
        displayUgInfo();
        cout << "Research Topic: " << researchTopic << endl;
    }
};

void showMenu() {
    cout << "\nAdd information to the Database:\n";
    cout << "\nSelect the type of students: \n";
    cout << "1. Undergraduate Student\n";
    cout << "2. Postgraduate Student\n";
    cout << "3. Exit\n";
}

int main() {
    int choice;
    Education Edu;
    Student student;
    Book books[100];
    Attendance attendance;
    Fee fee;
    Scholarship s1;

    do {
        cout << "\n----------| Education Domain Management |----------\n";
        cout << "1.  Enter the student's marks: \n";
        cout << "2.  Student Academic Data Operations\n";
        cout << "3.  Average Calculator\n";
        cout << "4.  Book Details\n";
        cout << "5.  Course Enrollment\n"; 
        cout << "6.  Attendance Manager\n"; 
        cout << "7.  Feedback Manager\n"; 
        cout << "8.  Fee Manager\n";
        cout << "9.  Scholarship Eligibility\n";
        cout << "10. Theory & Practical Classes\n";
        cout << "11. Exit\n";
        cout << "---------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Edu.Educ();
                break;
            }
            
            case 2: {
                int subchoice, marks1, marks2, marks3, attendance;
                int totalMarks = 0;
                char grade = 'F';
                do {
                    cout << "\n---------------Menu:---------------\n";
                    cout << "1. Enter Student Data\n";
                    cout << "2. Display Student Info\n";
                    cout << "3. Calculate Total Marks\n";
                    cout << "4. Update Grade\n";
                    cout << "5. Modify Attendance\n";
                    cout << "6. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> subchoice;
                    cout << "-----------------------------------\n";

                    switch (subchoice) {
                        case 1: {
                            cout << "Enter the first mark: ";
                            cin >> marks1;
                            cout << "Enter the second mark: ";
                            cin >> marks2;
                            cout << "Enter the third mark: ";
                            cin >> marks3;
                            cout << "Enter the attendance percentage: ";
                            cin >> attendance;
                            student = Student(marks1, marks2, marks3, attendance);
                            break;
                        }
                        case 2: {
                            student.displayStudentInfo();
                            break;
                        }
                        case 3: {
                            student.calculateTotalMarks(totalMarks);
                            cout << "Total Marks: " << totalMarks << " (in main)\n";
                            break;
                        }
                        case 4: {
                            totalMarks = student.getTotalMarks();
                            student.updateGrade(totalMarks, grade);
                            cout << "Grade: " << grade << " (in main)\n";
                            break;
                        }
                        case 5: {
                            int &attendanceRef = student.modifyAttd();
                            cout << "Modified Attendance: " << attendanceRef << endl;
                            attendanceRef += 3;
                            cout << "Further modified Attendance: " << attendanceRef << endl;
                            break;
                        }
                        case 6: {
                            cout << "Exiting Academic Data Operations.\n";
                            break;
                        }
                        default: {
                            cout << "Invalid choice! Please try again.\n";
                            break;
                        }
                    }
                } while (subchoice != 6);
                break;
            }
            
            case 3: {
                float a, b, c, d, e;
                char opt;
                cout << "\n---------------Average Calculator---------------\n";
                cout << "Enter the first mark: ";
                cin >> a;
                cout << "Enter the second mark: ";
                cin >> b;
                cout << "Enter the third mark: ";
                cin >> c;
                cout << "Enter the fourth mark: ";
                cin >> d;
                
                cout << "Do you have a fifth subject? (y/n): ";
                cin >> opt;
                
                if (opt == 'y' || opt == 'Y') {
                    cout << "Enter the fifth mark: ";
                    cin >> e;
                } else {
                    e = 0;
                }
                cout << "-------------------------------------------------\n";
                cout << "The average of the marks is " << student.avg(a, b, c, d, e) << endl;
                break;
            }
            
            case 4: {
                int bookID, pages;
                string title;

                cout << "Enter Book ID: ";
                cin >> bookID;
                cout << "Enter Book Title: ";
                cin >> title;
                cout << "Enter Number of Pages: ";
                cin >> pages;

                Book book(bookID, title, pages);
                book.print();
                break;
            }
            
            case 5: {
                int courseCode, numStudents;
                cout << "Enter Course Code: ";
                cin >> courseCode;
                cout << "Enter number of students to enroll: ";
                cin >> numStudents;

                Course course(courseCode);
                course.enrollStudents(numStudents);
                cout << "Total Enrollment: " << Course::getTotalEnrollment() << endl;
                break;
            }
            
            case 6: {
                int attChoice;
                do {
                    cout << "\n----------| Attendance Manager |----------\n"
                         << "1. Add a Day to Attendance\n"
                         << "2. Remove a Day from Attendance\n"
                         << "3. Reset Attendance\n"
                         << "4. Display Attendance\n"
                         << "5. Exit\n"
                         << "------------------------------------------\n"
                         << "Enter your choice: ";
                    cin >> attChoice;

                    switch (attChoice) {
                        case 1:
                            ++attendance;
                            cout << "Added a day to attendance.\n";
                            break;
                        case 2:
                            --attendance;
                            cout << "Removed a day from attendance.\n";
                            break;
                        case 3:
                            !attendance;
                            cout << "Attendance reset.\n";
                            break;
                        case 4:
                            attendance.display();
                            break;
                        case 5:
                            cout << "Exiting Attendance Manager.\n";
                            break;
                        default:
                            cout << "Invalid choice, please try again.\n";
                    }
                } while (attChoice != 5);
                break;
            }
            
            case 7: {
                int numStudents;
                cout << "Enter the number of students: ";
                cin >> numStudents;

                Feedback feedback(numStudents);

                for (int i = 0; i < numStudents; ++i) {
                    cout << "Enter rating for Student " << i + 1 << ": ";
                    cin >> feedback[i];
                }

                feedback.display();
                cout << "Average Feedback Rating: " << feedback.calculateAverage() << endl;
                break;
            }
            
            case 8: {
			    int choice;
			    do {
			        cout << "\n-------| Fee Management System Menu: |-------\n";
			        cout << "1. Register Student\n";
			        cout << "2. Pay Fees\n";
			        cout << "3. Display Student Details\n";
			        cout << "4. Exit\n";
			        cout << "---------------------------------------------\n";
			        cout << "Enter your choice: ";
			        
			        cin >> choice;
			
			        switch (choice) {
			            case 1: {
			                string id, name;
			                double fees;
			                cout << "\nEnter Student ID: ";
			                cin >> id;
			                cout << "Enter Student Name: ";
			                cin >> name;
			                cout << "Enter Total Fees: ";
			                cin >> fees;
			                fee.addStudent(id, name, fees);
			                break;
			            }
			            case 2: {
			                string id;
			                double amount;
			                cout << "Enter Student ID for fee payment: ";
			                cin >> id;
			                cout << "Enter Payment Amount: ";
			                cin >> amount;
			                fee.payStudentFees(id, amount);
			                break;
			            }
			            case 3:
			                fee.displayStudents();
			                break;
			            case 4:
			                cout << "Exited.\n";
			                break;
			            default:
			                cout << "Invalid choice. Please try again.\n";
			        }
			    } while (choice != 4);
			
			    return 0;
                break;
            }
            
            case 9: {
			    int choice;
			    s1.setType();
			    s1.setDetails();
			    s1.setMarks();
			    s1.setScore();
			
			    do {
			        cout << "\n----------| Scholarship Program Menu |----------\n";
			        cout << "1. Display All Details\n";
			        cout << "2. Calculate Scholarship Eligibility\n";
			        cout << "3. Update Academic Score\n";
			        cout << "4. Update Sports Score\n";
			        cout << "5. Exit\n";
			        cout << "-------------------------------------------------\n";
			        cout << "Enter your choice: ";
			        cin >> choice;
			
			        switch (choice) {
			        case 1:
			            cout << "\nDisplaying All Details (without Eligibility):\n";
			            s1.displayAllDetails();
			            break;
			        case 2:
			            cout << "\nCalculating Scholarship Eligibility:\n";
			            s1.calculateEligibility();
			            break;
			        case 3:
			            s1.setMarks();
			            break;
			        case 4:
			            s1.setScore();
			            break;
			        case 5:
			            cout << "Exiting program. Goodbye!\n";
			            break;
			        default:
			            cout << "Invalid choice, please try again.\n";
			        }
			
			    } while (choice != 5);
			    return 0;
                break;
            }
            
            case 10: {
                int choice;
			    CourseC* coursePtr; 
			    TheoryCourse theoryCourse;
				PracticalCourse practicalCourse;
				bool theoryEntered = false, practicalEntered = false;
			
			    do {
			        showMenu();
			        cin >> choice;
			
			        switch (choice) {
			        case 1: {
			        string name, id;
			        int hours;
			        cout << "Enter course name: ";
			        cin >> name;
			        cout << "Enter course ID: ";
			        cin >> id;
			        cout << "Enter number of theory hours: ";
			        cin >> hours;
			        theoryCourse = TheoryCourse(name, id, hours);
			        theoryCourse.displayDetails();
			        theoryEntered = true;
			        break;
			    }
			
			    case 2: {
			        string name, id;
			        int sessions;
			        cout << "Enter course name: ";
			        cin >> name;
			        cout << "Enter course ID: ";
			        cin >> id;
			        cout << "Enter number of lab sessions: ";
			        cin >> sessions;
			        practicalCourse = PracticalCourse(name, id, sessions);
			        practicalCourse.displayDetails();
			        practicalEntered = true;
			        break;
			    }
			
			    case 3:
			        if (theoryEntered && practicalEntered) {
			            int totalHours = theoryCourse.calculateTotalHours(practicalCourse.getLabSessions());
			            cout << "Total Combined Hours: " << totalHours << endl;
			        } else {
			            cout << "Both theory and practical courses must be entered to calculate total hours." << endl;
			        }
			        break;
			        
			    case 4:
			        cout << "Exiting..." << endl;
			        break;
			
			    default:
			        cout << "Invalid choice! Please try again." << endl;
				    }
				} while (choice != 3);
				return 0;
                break;
            }
            
            case 11: {
                cout << "Exiting the program.\n";
                break;
            }
            
            default: {
                cout << "Invalid choice! Please try again.\n";
                break;
            }
        }
    } while (choice != 8);

    return 0;
}

