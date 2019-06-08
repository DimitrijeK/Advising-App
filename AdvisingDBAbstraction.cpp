#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>

#include"AdvisingDBAbstraction.h"

using namespace std;

AdvisingDBAbstraction::AdvisingDBAbstraction(string path)
	: DBAbstraction(path)
{
		createStudentsTable();
		createAdvisorsTable();
		createPlansTable();
		createCoursesTable();
		createCourseHasPrerequisiteTable();
		createStudentHasAdvisorsTable();
		createStudentTakesCourseTable();
		createPlanHasCourseTable();

		insertData();
}

void AdvisingDBAbstraction::insertStudent(string firstName, string lastName)
{
	//query to insert a student
	string sql = "INSERT INTO Students (firstName, lastName) VALUES (?, ?);";

	//create a statement pointer
	sqlite3_stmt* myStatement;

	//create the statement object using the prepare()
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

	//check to see if the prepared statement was created
	if (statusOfPrep == SQLITE_OK)
	{
		//add parameters
		sqlite3_bind_text(myStatement, 1, firstName.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(myStatement, 2, lastName.c_str(), -1, SQLITE_STATIC);


		//execute the query to insert a new user
		if (!executeQueryNoResultsBack(myStatement))
		{
			cout << "Error inserting into Students" << endl;
		}
	}
}

void AdvisingDBAbstraction::insertAdvisor(string firstName, string lastName)
{
	//query to insert a advisor
	string sql = "INSERT INTO Advisors (firstName, lastName) VALUES (?, ?);";

	//create a statement pointer
	sqlite3_stmt* myStatement;

	//create the statement object using the prepare()
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

	//check to see if the prepared statement was created
	if (statusOfPrep == SQLITE_OK)
	{
		//add parameters
		sqlite3_bind_text(myStatement, 1, firstName.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(myStatement, 2, lastName.c_str(), -1, SQLITE_STATIC);


		//execute the query to insert a new user
		if (!executeQueryNoResultsBack(myStatement))
		{
			cout << "Error inserting into Advisors" << endl;
		}
	}
}


void AdvisingDBAbstraction::insertCourse(string courseNumber, string name, int numberCredits, string required)
{
	//query to insert a course
	string sql = "INSERT INTO Courses (CourseNumber, Name, NumberCredits, Required) VALUES (?, ?, ?, ?);";

	//create a statement pointer
	sqlite3_stmt* myStatement;

	//create the statement object using the prepare()
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

	//check to see if the prepared statement was created
	if (statusOfPrep == SQLITE_OK)
	{
		//add parameters
		sqlite3_bind_text(myStatement, 1, courseNumber.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(myStatement, 2, name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(myStatement, 3, numberCredits);
		sqlite3_bind_text(myStatement, 4, required.c_str(), -1, SQLITE_STATIC);


		//execute the query to insert a new user
		if (!executeQueryNoResultsBack(myStatement))
		{
			cout << "Error inserting into Courses" << endl;
		}
	}
}

void AdvisingDBAbstraction::insertPlans(string planName, int advisorID, int studentID, string semester, int year)
{
	//query to insert plan
	string sql = "INSERT INTO Plans (PlanName, Semester, Year, AdvisorID, StudentID) VALUES (?, ?, ?, ?, ?);";

	//create a statement pointer
	sqlite3_stmt* myStatement;

	//create the statement object using the prepare()
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

	//check to see if the prepared statement was created
	if (statusOfPrep == SQLITE_OK)
	{
		//add parameters
		sqlite3_bind_text(myStatement, 1, planName.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(myStatement, 2, semester.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(myStatement, 3, year);
		sqlite3_bind_int(myStatement, 4, advisorID);
		sqlite3_bind_int(myStatement, 5, studentID);


		//execute the query to insert a new user
		if (!executeQueryNoResultsBack(myStatement))
		{
			cout << "Error inserting into Plans" << endl;
		}
	}
}

void AdvisingDBAbstraction::insertStudentTakesCourse(int studentID, int courseID, string semester, int year)
{
	//query to insert plan
	string sql = "INSERT INTO StudentTakesCourse (StudentID, CourseID, Semester, Year) VALUES (?, ?, ?, ?);";

	//create a statement pointer
	sqlite3_stmt* myStatement;

	//create the statement object using the prepare()
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

	//check to see if the prepared statement was created
	if (statusOfPrep == SQLITE_OK)
	{
		//add parameters
		sqlite3_bind_int(myStatement, 1, studentID);
		sqlite3_bind_int(myStatement, 2, courseID);
		sqlite3_bind_text(myStatement, 3, semester.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(myStatement, 4, year);


		//execute the query to insert a new user
		if (!executeQueryNoResultsBack(myStatement))
		{
			cout << "Error inserting into StudentTakesCourse" << endl;
		}
	}
}

void AdvisingDBAbstraction::insertStudentHasAdvisor(int studentID, int advisorID)
{
	string sql = "INSERT INTO StudentHasAdvisor (StudentID, AdvisorID) VALUES (?,?);";

	sqlite3_stmt* myStatement;

	//create the statement object using the prepare()
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

	//check to see if the prepared statement was created
	if (statusOfPrep == SQLITE_OK)
	{
		//add parameters
		sqlite3_bind_int(myStatement, 1, studentID);
		sqlite3_bind_int(myStatement, 2, advisorID);

		//execute the query to insert a new user
		if (!executeQueryNoResultsBack(myStatement))
		{
			cout << "Error inserting into StudentHasAdvisor" << endl;
		}
	}
}

void AdvisingDBAbstraction::insertCourseHasPrerequisite(int courseID, int prerequisiteID)
{
	string sql = "INSERT INTO CourseHasPrerequisite (CourseID, PrereqID) VALUES (?,?);";

	sqlite3_stmt* myStatement;

	//create the statement object using the prepare()
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

	//check to see if the prepared statement was created
	if (statusOfPrep == SQLITE_OK)
	{
		//add parameters
		sqlite3_bind_int(myStatement, 1, courseID);
		sqlite3_bind_int(myStatement, 2, prerequisiteID);

		//execute the query to insert a new user
		if (!executeQueryNoResultsBack(myStatement))
		{
			cout << "Error inserting into CourseHasPrerequisite" << endl;
		}
	}
}

void AdvisingDBAbstraction::insertPlanHasCourse(int courseID, int planID)
{
	string sql = "INSERT INTO PlanHasCourse (PlanID, CourseID) VALUES (?, ?);";

	//create a statement pointer
	sqlite3_stmt* myStatement;

	//create the statement object using the prepare()
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

	//check to see if the prepared statement was created
	if (statusOfPrep == SQLITE_OK)
	{
		//add parameters
		sqlite3_bind_int(myStatement, 1, planID);
		sqlite3_bind_int(myStatement, 2, courseID);

		//execute the query to insert a new user
		if (!executeQueryNoResultsBack(myStatement))
		{
			cout << "Error inserting into PlanHasCourse" << endl;
		}
	}
}

void AdvisingDBAbstraction::createStudentsTable()
{
	//Students (id, firstName, lastName, AdvisorID)
	string sql = "CREATE TABLE IF NOT EXISTS `Students` (`id`	INTEGER,`firstName`	TEXT,`lastName`	TEXT, PRIMARY KEY(`id`)); ";

	//execute the query to create the table
	if (!executeQueryNoResultsBack(sql))
	{
		cout << "Error creating Students table" << endl;
	}
}

void AdvisingDBAbstraction::createAdvisorsTable()
{
	//Advisors (id, firstName, lastName)
	string sql = "CREATE TABLE IF NOT EXISTS `Advisors` (`id`	INTEGER,`firstName`	INTEGER,`lastName`	INTEGER,PRIMARY KEY(`id`)); ";

	//execute the query to create the table
	if (!executeQueryNoResultsBack(sql))
	{
		cout << "Error creating Advisors table" << endl;
	}
}

void AdvisingDBAbstraction::createPlansTable()
{
	//Plans (id, firstName, lastName)
	string sql = "CREATE TABLE IF NOT EXISTS `Plans` (`id`	INTEGER,`PlanName` TEXT,`Semester`	TEXT,`Year`	INTEGER,`AdvisorID`	INTEGER, `StudentID` INTEGER, PRIMARY KEY(`id`),FOREIGN KEY(`AdvisorID`) REFERENCES `Advisors`(`id`), FOREIGN KEY(`StudentID`) REFERENCES `Students`(`id`)); ";

	//execute the query to create the table
	if (!executeQueryNoResultsBack(sql))
	{
		cout << "Error creating Plans table" << endl;
	}
}

void AdvisingDBAbstraction::createCoursesTable()
{
	//Courses (id, firstName, lastName)
	string sql = "CREATE TABLE IF NOT EXISTS `Courses` (`id`	INTEGER,`CourseNumber`	TEXT,`Name`	TEXT, `NumberCredits`	INTEGER,`Required`	TEXT,PRIMARY KEY(`id`)); ";

	//execute the query to create the table
	if (!executeQueryNoResultsBack(sql))
	{
		cout << "Error creating Courses table" << endl;
	}
}

void AdvisingDBAbstraction::createCourseHasPrerequisiteTable()
{
	string sql = "CREATE TABLE IF NOT EXISTS `CourseHasPrerequisite` (`id` INTEGER, `CourseID` INTEGER, `PrereqID` INTEGER, FOREIGN KEY(`CourseID`) REFERENCES `Courses`(`id`), FOREIGN KEY(`PrereqID`) REFERENCES `Courses`(`id`), PRIMARY KEY(`id`)); ";

	//execute the query to create the table
	if (!executeQueryNoResultsBack(sql))
	{
		cout << "Error creating CourseHasPrerequisite table" << endl;
	}
}

void AdvisingDBAbstraction::createStudentTakesCourseTable()
{
	//StudentTakesCourse (id, firstName, lastName)
	string sql = "CREATE TABLE IF NOT EXISTS `StudentTakesCourse` (`id`	INTEGER,`StudentID`	INTEGER,`CourseID`	INTEGER,`Semester`	TEXT,`Year`	INTEGER,PRIMARY KEY(`id`),FOREIGN KEY(`CourseID`) REFERENCES `Courses`(`id`),FOREIGN KEY(`StudentID`) REFERENCES `Students`(`id`)); ";

	//execute the query to create the table
	if (!executeQueryNoResultsBack(sql))
	{
		cout << "Error creating StudentTakesCourse table" << endl;
	}
}

void AdvisingDBAbstraction::createPlanHasCourseTable()
{
	//PlanHasCourse (id, firstName, lastName)
	string sql = "CREATE TABLE IF NOT EXISTS `PlanHasCourse` (`id`	INTEGER,`PlanID`	INTEGER,`CourseID`	INTEGER,FOREIGN KEY(`CourseID`) REFERENCES `Courses`(`id`),FOREIGN KEY(`PlanID`) REFERENCES `Plans`(`id`),PRIMARY KEY(`id`)); ";

	//execute the query to create the table
	if (!executeQueryNoResultsBack(sql))
	{
		cout << "Error creating PlanHasCourse table" << endl;
	}
}

void AdvisingDBAbstraction::createPlansSemesterYearIndexTable()
{
	string sql = "CREATE INDEX IF NOT EXISTS `SemesterYearIndex` ON `Plans` (`Semester` ASC, `Year` ASC)";

	if (!executeQueryNoResultsBack(sql))
	{
		cout << "Error creating Index table" << endl;
	}
}

void AdvisingDBAbstraction::createStudentHasAdvisorsTable()
{
	string sql = "CREATE TABLE IF NOT EXISTS `StudentHasAdvisor` (`id` INTEGER, `StudentID` INTEGER, `AdvisorID` INTEGER, FOREIGN KEY(`StudentID`) REFERENCES `Students`(`id`), FOREIGN KEY(`AdvisorID`) REFERENCES `Advisors`(`id`), PRIMARY KEY(`id`)); ";

	//execute the query to create the table
	if (!executeQueryNoResultsBack(sql))
	{
		cout << "Error creating StudentHasAdvisor table" << endl;
	}
}

void AdvisingDBAbstraction::listAllStudents()
{
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Students.firstName, Students.lastName FROM Students ;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = 0;
		int counter = 1;
		statusOfStep = sqlite3_step(myStatement);

		while (statusOfStep == SQLITE_ROW)
		{
			string studentFirst = (char*)sqlite3_column_text(myStatement, 0);
			string studentLast = (char*)sqlite3_column_text(myStatement, 1);

			cout << counter << ". " << studentFirst << " " << studentLast << endl;
			statusOfStep = sqlite3_step(myStatement);
			counter++;
		}

		cout << endl;
		sqlite3_finalize(myStatement);
	}

	else
	{
		cout << "Error executing listAllStudents query." << endl;
	}
}

void AdvisingDBAbstraction::listAllAdvisors()
{
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Advisors.firstName, Advisors.lastName FROM Advisors ;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = 0;
		int counter = 1;
		statusOfStep = sqlite3_step(myStatement);

		while (statusOfStep == SQLITE_ROW)
		{
			string advisorFirst = (char*)sqlite3_column_text(myStatement, 0);
			string advisorLast = (char*)sqlite3_column_text(myStatement, 1);

			cout << counter << ". " << advisorFirst << " " << advisorLast << endl;
			statusOfStep = sqlite3_step(myStatement);
			counter++;
		}

		cout << endl;
		sqlite3_finalize(myStatement);
	}

	else
	{
		cout << "Error executing listAllAdvisors query." << endl;
	}
}

void AdvisingDBAbstraction::listAllCourses()
{
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Courses.CourseNumber, Courses.Name, Courses.NumberCredits, Courses.Required FROM Courses ;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = 0;
		int counter = 1;
		statusOfStep = sqlite3_step(myStatement);

		while (statusOfStep == SQLITE_ROW)
		{
			string courseNumber = (char*)sqlite3_column_text(myStatement, 0);
			string courseName = (char*)sqlite3_column_text(myStatement, 1);
			int numberOfCredits = sqlite3_column_int(myStatement, 2);
			string isRequired = (char*)sqlite3_column_text(myStatement, 3);

			cout << counter << ". " << courseNumber << " " << courseName << " " << numberOfCredits << " " << isRequired << endl;
			statusOfStep = sqlite3_step(myStatement);
			counter++;
		}

		cout << endl;
		sqlite3_finalize(myStatement);
	}

	else
	{
		cout << "Error executing listStudents query." << endl;
	}
}

void AdvisingDBAbstraction::listAllPlans()
{
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Plans.PlanName, Plans.semester, Plans.year, Plans.advisorID, Plans.studentID FROM Plans ;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = 0;
		int counter = 1;
		statusOfStep = sqlite3_step(myStatement);

		while (statusOfStep == SQLITE_ROW)
		{
			string planName = (char*)sqlite3_column_text(myStatement, 0);
			string semester = (char*)sqlite3_column_text(myStatement, 1);
			int year = sqlite3_column_int(myStatement, 2);
			int advisorID = sqlite3_column_int(myStatement, 3);
			int studentID = sqlite3_column_int(myStatement, 4);

			cout << counter << ". " << planName << " " << semester << " " << year << " " << advisorID << " " << studentID << endl;
			statusOfStep = sqlite3_step(myStatement);
			counter++;
		}

		cout << endl;
		sqlite3_finalize(myStatement);
	}

	else
	{
		cout << "Error executing listAllPlans query." << endl;
	}
}


void AdvisingDBAbstraction::listStudentsQuery(int advisorID)
{
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Students.id, Students.firstName, Students.lastName FROM Students, StudentHasAdvisor, Advisors WHERE Students.id = StudentHasAdvisor.StudentID AND StudentHasAdvisor.AdvisorID = Advisors.id AND Advisors.id = ? ;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = 0;
		int counter = 1;
		sqlite3_bind_int(myStatement, 1, advisorID);
		statusOfStep = sqlite3_step(myStatement);

		while (statusOfStep == SQLITE_ROW)
		{
			int studentID = sqlite3_column_int(myStatement, 0);
			string studentFirst = (char*)sqlite3_column_text(myStatement,1);
			string studentLast = (char*)sqlite3_column_text(myStatement, 2);

			cout << studentID << ". " << studentFirst << " " << studentLast << endl;
			statusOfStep = sqlite3_step(myStatement);
			counter++;
		}

		cout << endl;
		sqlite3_finalize(myStatement);
	}

	else
	{
		cout << "Error executing listStudents query." << endl;
	}
}

void AdvisingDBAbstraction::listPlansQuery(int advisorID)
{
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Plans.id, Plans.PlanName, Plans.Semester, Plans.Year FROM Plans, Advisors WHERE Plans.AdvisorID = Advisors.id AND Advisors.id = ? ;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = 0;
		int counter = 1;
		sqlite3_bind_int(myStatement, 1, advisorID);
		statusOfStep = sqlite3_step(myStatement);

		while (statusOfStep == SQLITE_ROW)
		{
			int planID = sqlite3_column_int(myStatement, 0);
			string planName = (char*)sqlite3_column_text(myStatement, 1);
			string semester = (char*)sqlite3_column_text(myStatement, 2);
			string year = (char*)sqlite3_column_text(myStatement, 3);

			cout << planID << ". " << planName << " " << semester << " " << year << endl;
			statusOfStep = sqlite3_step(myStatement);
			counter++;
		}

		cout << endl;
		sqlite3_finalize(myStatement);
	}

	else
	{
		cout << "Error executing listPlans query." << endl;
	}
}

void AdvisingDBAbstraction::makePlanQuery(int advisorID)
{
	int studentID;
	string planName;
	string semester;
	int year;
	int courseID;

	listAllStudents();

	cout << "Which student you would like to make a plan with: ";
	cin >> studentID;

	cout << "What is the name of the plan: ";
	cin >> planName;

	cout << "What semester is this plan for (string): ";
	cin >> semester;

	cout << "What year is this plan for (int): ";
	cin >> year;
	cout << endl;

	//insert plan
	insertPlans(planName, advisorID, studentID, semester, year);
}

void AdvisingDBAbstraction::deletePlanQuery(int planID)
{
	
	//1. Delete from PlanHasCourse
	string sql1 = "DELETE FROM PlanHasCourse WHERE Plans.id = ? ;";

	sqlite3_stmt* myStatement1;

	int statusOfPrep1 = sqlite3_prepare_v2(db, sql1.c_str(), -1, &myStatement1, NULL);

	if (statusOfPrep1 == SQLITE_OK)
	{
		sqlite3_bind_int(myStatement1, 1, planID);

		//execute the query to insert a new user
		if (!executeQueryNoResultsBack(myStatement1))
		{
			cout << "Error deleting from Plans" << endl;
		}
	}
	
	
	//2. Delete Plan 
	string sql2 = "DELETE FROM Plans WHERE Plans.id = ? ;";

	sqlite3_stmt* myStatement2;

	int statusOfPrep2 = sqlite3_prepare_v2(db, sql2.c_str(), -1, &myStatement2, NULL);

	if (statusOfPrep2 == SQLITE_OK)
	{
		sqlite3_bind_int(myStatement2, 1, planID);

		//execute the query to insert a new user
		if (!executeQueryNoResultsBack(myStatement2))
		{
			cout << "Error deleting from Plans" << endl;
		}
	}


}

void AdvisingDBAbstraction::planToCourseQuery(int studentID, int planID)
{

	vector<int>courseIDS;
	vector<string>semesters;
	vector<int>years;

	//So in order to turn group of courses to classes that are being taken, we first need to find all courses(and info about them) for particular plan
	string sql = "SELECT PlanHasCourse.CourseID, Plans.Semester, Plans.Year FROM PlanHasCourse, Plans WHERE PlanHasCourse.PlanID = ? AND PlanHasCourse.PlanID = Plans.id ;";

	sqlite3_stmt* myStatement1;
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement1, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		sqlite3_bind_int(myStatement1, 1, planID);
		int statusOfStep = sqlite3_step(myStatement1);

		while (statusOfStep == SQLITE_ROW)
		{
			int courseID = sqlite3_column_int(myStatement1, 0);
			string semester = (char*)sqlite3_column_text(myStatement1, 1);
			int year = sqlite3_column_int(myStatement1, 2);

			courseIDS.push_back(courseID);
			semesters.push_back(semester);
			years.push_back(year);

			statusOfStep = sqlite3_step(myStatement1);
		}
	}


	for (int i = 0; i < courseIDS.size(); i++)
	{
		sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

		insertStudentTakesCourse(studentID,courseIDS[i],semesters[i],years[i]);
		

		sqlite3_exec(db, "END TRANSACTION;", NULL, NULL, NULL);
	}

}

void AdvisingDBAbstraction::listCurrentCourses(int studentID)
{
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Courses.CourseNumber, Courses.Name, Courses.NumberCredits, Courses.Required FROM Courses, StudentTakesCourse, Students WHERE Courses.id = StudentTakesCourse.CourseID AND StudentTakesCourse.StudentID = Students.id AND Students.id = ? ;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = 0;
		int counter = 1;
		sqlite3_bind_int(myStatement, 1, studentID);
		statusOfStep = sqlite3_step(myStatement);

		while (statusOfStep == SQLITE_ROW)
		{
			string courseNumber = (char*)sqlite3_column_text(myStatement, 0);
			string courseName = (char*)sqlite3_column_text(myStatement, 1);
			int numOfCredits = sqlite3_column_int(myStatement, 2);
			string isRequired = (char*)sqlite3_column_text(myStatement, 3);

			cout << counter << ". " << courseNumber << " " << courseName << " " << numOfCredits << " " << isRequired << endl;
			statusOfStep = sqlite3_step(myStatement);
			counter++;
		}

		cout << endl;
		sqlite3_finalize(myStatement);
	}

	else
	{
		cout << "Error executing listCurrentCourses query." << endl;
	}
}

void AdvisingDBAbstraction::totalNumOfReqCredits(int studentID)
{
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT SUM(Courses.NumberCredits) as totalNumOfReqCredits FROM Courses, StudentTakesCourse, Students WHERE Courses.Required = 'Required' AND Courses.id = StudentTakesCourse.CourseID AND StudentTakesCourse.StudentID = Students.id AND Students.id = ? ;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = 0;
		int counter = 1;
		sqlite3_bind_int(myStatement, 1, studentID);
		statusOfStep = sqlite3_step(myStatement);

		while (statusOfStep == SQLITE_ROW)
		{
			int totalNumOfCredits = sqlite3_column_int(myStatement, 0);

			cout << counter << ". " << totalNumOfCredits << endl;
			statusOfStep = sqlite3_step(myStatement);
			counter++;
		}

		cout << endl;
		sqlite3_finalize(myStatement);
	}

	else
	{
		cout << "Error executing totalNumOfReqCredits query." << endl;
	}
}

void AdvisingDBAbstraction::totalNumOfNonReqCredits(int studentID)
{
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT SUM(Courses.NumberCredits) as totalNumOfReqCredits FROM Courses, StudentTakesCourse, Students WHERE Courses.Required = 'NotRequired' AND Courses.id = StudentTakesCourse.CourseID AND StudentTakesCourse.StudentID = Students.id AND Students.id = ? ;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = 0;
		int counter = 1;
		sqlite3_bind_int(myStatement, 1, studentID);
		statusOfStep = sqlite3_step(myStatement);

		while (statusOfStep == SQLITE_ROW)
		{
			int totalNumOfCredits = sqlite3_column_int(myStatement, 0);

			cout << counter << ". " << totalNumOfCredits << endl;
			statusOfStep = sqlite3_step(myStatement);
			counter++;
		}

		cout << endl;
		sqlite3_finalize(myStatement);
	}

	else
	{
		cout << "Error executing totalNumOfNonReqCredits query." << endl;
	}
}

void AdvisingDBAbstraction::coursesStudentCanTake(int studentID)
{
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "WITH coursesStudentDidntTake AS ( SELECT Courses.id, Courses.CourseNumber, Courses.Name, Courses.NumberCredits, Courses.Required, CourseHasPrerequisite.PrereqID"
			" FROM Courses, CourseHasPrerequisite"
			" WHERE Courses.id NOT IN("
			" SELECT Courses.ID"
		" FROM Students, StudentTakesCourse, Courses"
		" WHERE Students.id = ?"
		" AND Students.id = StudentTakesCourse.StudentID"
		" AND StudentTakesCourse.CourseID = Courses.id" 
		" )" 
		" AND Courses.id = CourseHasPrerequisite.CourseID" 
		" )" 

		" SELECT coursesStudentDidntTake.CourseNumber, coursesStudentDidntTake.Name, coursesStudentDidntTake.NumberCredits, coursesStudentDidntTake.Required" 
		" FROM coursesStudentDidntTake" 
		" WHERE coursesStudentDidntTake.PrereqID IN(" 
		" SELECT Courses.id" 
		" FROM Students, StudentTakesCourse, Courses" 
		" WHERE Students.id = ?" 
		" AND Students.id = StudentTakesCourse.StudentID" 
		" AND StudentTakesCourse.CourseID = Courses.id" 
		" )", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int counter = 1;
		sqlite3_bind_int(myStatement, 1, studentID);
		sqlite3_bind_int(myStatement, 2, studentID);
		int statusOfStep = sqlite3_step(myStatement);

		while (statusOfStep == SQLITE_ROW)
		{
			string courseNumber = (char*)sqlite3_column_text(myStatement, 0);
			string courseName = (char*)sqlite3_column_text(myStatement, 1);
			int numOfCredits = sqlite3_column_int(myStatement, 2);
			string isRequired = (char*)sqlite3_column_text(myStatement, 3);

			cout << counter << ". " << courseNumber << " " << courseName << " " << numOfCredits << " " << isRequired << endl;
			statusOfStep = sqlite3_step(myStatement);
			counter++;
		}

		cout << endl;
		sqlite3_finalize(myStatement);
	}

	else
	{
		cout << "Error executing coursesStudentCanTake query." << endl;
	}


}

void AdvisingDBAbstraction::coursesStudentCannotTake(int studentID)
{
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "WITH coursesStudentDidntTake AS ( SELECT Courses.id, Courses.CourseNumber, Courses.Name, Courses.NumberCredits, Courses.Required, CourseHasPrerequisite.PrereqID"
		" FROM Courses, CourseHasPrerequisite"
		" WHERE Courses.id NOT IN("
		" SELECT Courses.ID"
		" FROM Students, StudentTakesCourse, Courses"
		" WHERE Students.id = ?"
		" AND Students.id = StudentTakesCourse.StudentID"
		" AND StudentTakesCourse.CourseID = Courses.id"
		" )"
		" AND Courses.id = CourseHasPrerequisite.CourseID"
		" )"

		" SELECT coursesStudentDidntTake.CourseNumber, coursesStudentDidntTake.Name, coursesStudentDidntTake.NumberCredits, coursesStudentDidntTake.Required"
		" FROM coursesStudentDidntTake"
		" WHERE coursesStudentDidntTake.PrereqID NOT IN("
		" SELECT Courses.id"
		" FROM Students, StudentTakesCourse, Courses"
		" WHERE Students.id = ?"
		" AND Students.id = StudentTakesCourse.StudentID"
		" AND StudentTakesCourse.CourseID = Courses.id"
		" )", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int counter = 1;
		sqlite3_bind_int(myStatement, 1, studentID);
		sqlite3_bind_int(myStatement, 2, studentID);
		int statusOfStep = sqlite3_step(myStatement);

		while (statusOfStep == SQLITE_ROW)
		{
			string courseNumber = (char*)sqlite3_column_text(myStatement, 0);
			string courseName = (char*)sqlite3_column_text(myStatement, 1);
			int numOfCredits = sqlite3_column_int(myStatement, 2);
			string isRequired = (char*)sqlite3_column_text(myStatement, 3);

			cout << counter << ". " << courseNumber << " " << courseName << " " << numOfCredits << " " << isRequired << endl;
			statusOfStep = sqlite3_step(myStatement);
			counter++;
		}

		cout << endl;
		sqlite3_finalize(myStatement);
	}

	else
	{
		cout << "Error executing coursesStudentCannotTake query." << endl;
	}
}


void AdvisingDBAbstraction::insertData()
{

	srand(time(NULL));

	//Advisors
	for (int i = 0; i < advisorNames.size(); i++)
	{
		string firstLastName[2];
		stringstream ssin(advisorNames[i]);

		int j = 0;

		while (ssin.good() && j < 2)
		{
			ssin >> firstLastName[j];
			j++;
		}

		insertAdvisor(firstLastName[0], firstLastName[1]);
	}

	//Students
	for (int i = 0; i < studentNames.size(); i++)
	{
		string firstLastName[2];
		stringstream ssin(studentNames[i]);

		int j = 0;

		while (ssin.good() && j < 2)
		{
			ssin >> firstLastName[j];
			j++;
		}

		//int randomAdvisor = (rand() % 5) + 1;

		insertStudent(firstLastName[0], firstLastName[1]);
	}

	//Courses
	for (int i = 0; i < courses.size(); i++)
	{
		string course[3];
		stringstream ssin(courses[i]);

		int j = 0;

		while (ssin.good() && j < 3)
		{
			ssin >> course[j];
			j++; 
		}

		insertCourse(course[0], course[1], 4, course[2]);
	}

	//Plans
	insertPlans("Dimitri's Plan1", 1, 5, "Spring", 2019);
	insertPlans("Dimitri's Plan2", 1, 5, "Spring", 2019);

	insertPlans("Jordan's Plan1", 3, 7, "Spring", 2019);
	insertPlans("Jordan's Plan2", 3, 7, "Spring", 2019);


	//StudentHasAdvisors
	insertStudentHasAdvisor(5, 1);
	insertStudentHasAdvisor(6, 1);
	insertStudentHasAdvisor(7, 1);
	insertStudentHasAdvisor(8, 1);
	insertStudentHasAdvisor(1, 2);
	insertStudentHasAdvisor(2, 2);
	insertStudentHasAdvisor(3, 2);


	//CourseHasPrerequisite
	insertCourseHasPrerequisite(2, 1);
	insertCourseHasPrerequisite(3, 1);
	insertCourseHasPrerequisite(4, 1);
	insertCourseHasPrerequisite(5, 4);
	insertCourseHasPrerequisite(6, 5);
	insertCourseHasPrerequisite(7, 6);


	//PlanHasCourse
	insertPlanHasCourse(1, 1);
	insertPlanHasCourse(2, 2);

	insertPlanHasCourse(1, 3);
	insertPlanHasCourse(2, 4);


	//StudentTakesCourse
	insertStudentTakesCourse(5, 1, "Fall", 2018);
	insertStudentTakesCourse(5, 2, "Fall", 2018);

	insertStudentTakesCourse(7, 1, "Fall", 2018);
	insertStudentTakesCourse(7, 2, "Fall", 2018);

}

void AdvisingDBAbstraction::createMenu()
{
	cout << "Hello and Welcome to the Advising App!" << endl;
	cout << endl;

	int answer;

	cout << "Who are you?(1/2)" << endl;
	cout << "1. Advisor" << endl;
	cout << "2. Student" << endl;
	cout << "3. Administrator" << endl;
	cin >> answer;

	cout << endl;

	if (answer == 1)
	{
		cout << "-- Advisor --" << endl;
		createAdvisorMenu();
	}
	else if (answer == 2)
	{
		cout << "-- Student --" << endl;
		createStudentMenu();
	}
	else if (answer == 3)
	{
		cout << "-- Administrator --" << endl;
		createAdministratorMenu();
	}
	else
	{
		cout << "Please try again." << endl;
	}

}

void AdvisingDBAbstraction::createStudentMenu()
{
	system("CLS");

	listAllStudents();

	int student;
	cout << "Who are you? (1/2/3...)";
	cin >> student;
	cout << endl;

	//current student's first and last name
	//---
	string firstLastName[2];
	stringstream ssin(studentNames[student - 1]);

	int j = 0;

	while (ssin.good() && j < 2)
	{
		ssin >> firstLastName[j];
		j++;
	}
	//---

	int answer = 1;

	while (answer > 0 && answer < 5)
	{
		cout << "Student Menu: " << endl;
		cout << "1. Current courses" << endl;
		cout << "2. Courses you can take" << endl;
		cout << "3. Courses you cannot take" << endl;
		cout << "4. Total # of credits in required courses" << endl;
		cout << "5. Total # of credits in non-required courses" << endl;
		cout << "6. Go Back" << endl;
		cout << "7. Quit" << endl;

		cin >> answer;

		if (answer == 1)
		{
			cout << endl;
			cout << firstLastName[0] << " " << firstLastName[1] << "'s current courses: " << endl;
			listCurrentCourses(student);
		}

		else if (answer == 2)
		{
			cout << endl;
			cout << "Classes that " << firstLastName[0] << " " << firstLastName[1] << " can take: " << endl;
			coursesStudentCanTake(student);
		}

		else if (answer == 3)
		{
			cout << endl;
			cout << "Classes that " << firstLastName[0] << " " << firstLastName[1] << " cannot take: " << endl;
			coursesStudentCannotTake(student);
		}

		else if (answer == 4)
		{
			cout << endl;
			cout << firstLastName[0] << " " << firstLastName[1] << "'s total number of credits in required courses: " << endl;
			totalNumOfReqCredits(student);
		}

		else if (answer == 5)
		{
			cout << endl;
			cout << firstLastName[0] << " " << firstLastName[1] << "'s total number of credits in non-required courses: " << endl;
			totalNumOfNonReqCredits(student);
		}

		else if (answer == 6)
		{
			system("CLS");
			createMenu();
		}

		else
		{
			//quit
			//go back to first menu
		}
	}


}

void AdvisingDBAbstraction::createAdvisorMenu()
{
	system("CLS");
	
	listAllAdvisors();

	int advisor;
	cout << "Who are you? (1/2/3...) ";
	cin >> advisor;
	cout << endl;

	//current advisor's first and last name
	//---
	string firstLastName[2];
	stringstream ssin(advisorNames[advisor-1]);

	int j = 0;

	while (ssin.good() && j < 2)
	{
		ssin >> firstLastName[j];
		j++;
	}
	//---


	int answer = 1;

	while (answer > 0 && answer < 5)
	{
		cout << "Advisor Menu: " << endl;
		cout << "1. List Students" << endl;
		cout << "2. List Plans" << endl;
		cout << "3. Make a plan" << endl;
		cout << "4. Add a course to a plan (edit plan)" << endl;
		cout << "5. Delete a plan" << endl;
		cout << "6. Covert a plan to a group of courses" << endl; 
		cout << "7. Go back" << endl;
		cout << "8. Quit" << endl;

		cin >> answer;

		if (answer == 1)
		{
			cout << endl;
			cout << firstLastName[0] << " " << firstLastName[1] << "'s students: " << endl;
			listStudentsQuery(advisor);
		}

		else if (answer == 2)
		{
			cout << endl;
			cout << firstLastName[0] << " " << firstLastName[1] << "'s plans: " << endl;
			listPlansQuery(advisor);
		}

		else if (answer == 3)
		{
			cout << endl;
			cout << "Making a Plan: " << endl;
			makePlanQuery(advisor);
		}

		else if (answer == 4)
		{
			cout << endl;
			cout << "Edit a Plan: " << endl;
			listPlansQuery(advisor);

			int planID;
			cout << "What plan would you like to edit: ";
			cin >> planID;

			listAllCourses();

			int courseID;
			cout << endl;
			cout << "What course would you like to add to the plan: ";
			cin >> courseID;

			insertPlanHasCourse(courseID, planID);

		}

		else if (answer == 5)
		{
			cout << endl;
			cout << firstLastName[0] << " " << firstLastName[1] << "'s plans: " << endl;
			listPlansQuery(advisor);

			int planID;
			cout << "Which plan would you like to delete: ";
			cin >> planID;

			deletePlanQuery(planID);

		}

		else if (answer == 6)
		{
			cout << endl;
			cout << firstLastName[0] << " " << firstLastName[1] << "'s students: " << endl;
			listStudentsQuery(advisor);

			int studentID;
			cout << "Which student you would like to do this for: ";
			cin >> studentID;

			//here
			cout << endl;
			cout << firstLastName[0] << " " << firstLastName[1] << "'s plans: " << endl;
			listPlansQuery(advisor);

			int planID;
			cout << "Which plan would you like to turn into a course: ";
			cin >> planID;

			planToCourseQuery(studentID, planID);

		}

		else if (answer == 7)
		{
			//go back
			system("CLS");
			createMenu();
		}

		else
		{
			//quit
		}
	}
}
void AdvisingDBAbstraction::createAdministratorMenu()
{
	system("CLS");

	int answer = 1;

	while (answer > 0 && answer < 6)
	{
		cout << "Administrator Menu: " << endl;
		cout << "1. Add Student" << endl;
		cout << "2. Add Advisor" << endl;
		cout << "3. Add Course" << endl;
		cout << "4. Add Prerequisite" << endl;
		cout << "5. Go back" << endl;
		cout << "6. Quit" << endl;
		
		cin >> answer;

		if (answer == 1)
		{
			string firstName;
			string lastName;

			cout << endl;
			cout << "Please enter students first name: ";
			cin >> firstName;

			cout << "Please enter students last name: ";
			cin >> lastName;

			insertStudent(firstName, lastName);
		}

		else if (answer == 2)
		{
			string firstName;
			string lastName;

			cout << endl;
			cout << "Please enter advisors first name: ";
			cin >> firstName;

			cout << "Please enter advisors last name: ";
			cin >> lastName;

			insertAdvisor(firstName, lastName);
		}

		else if (answer == 3)
		{
			string courseNumber;
			string courseName;
			int numOfCredits;
			string isRequired;

			cout << endl;
			cout << "Please enter course number: ";
			cin >> courseNumber;

			cout << "Please enter course name: ";
			cin >> courseName;

			cout << "Please enter the number of credits for this course: ";
			cin >> numOfCredits;

			cout << "Please enter if this course is required or not (Required/NotRequired): ";
			cin >> isRequired;

			insertCourse(courseNumber, courseName, numOfCredits, isRequired);
		}

		else if (answer == 4)
		{
			int courseID;
			int prereqID;

			cout << endl;
			listAllCourses();

			cout << "For what class would you like to add a prerequisite: ";
			cin >> courseID;

			cout << "What is the prerequisite this course: ";
			cin >> prereqID;

			insertCourseHasPrerequisite(courseID, prereqID);
		}

		else if (answer == 5)
		{
			//go back
			system("CLS");
			createMenu();
		}

		else
		{
			//quit
		}
	}
}


