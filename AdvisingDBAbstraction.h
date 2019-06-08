#pragma once
#include <vector>
#include "DBAbstraction.h"

class AdvisingDBAbstraction : DBAbstraction
{

public:
	AdvisingDBAbstraction(string path);

	//menu 
	void createMenu();
	void createStudentMenu();
	void createAdvisorMenu();
	void createAdministratorMenu();


	//insert functions
	void insertStudent(string firstName, string lastName);
	void insertAdvisor(string firstName, string lastName);
	void insertCourse(string courseNumber, string name, int numberCredits, string required);
	void insertPlans(string planName, int advisorID, int studentID, string semester, int year);
	void insertStudentTakesCourse(int studentID, int courseID, string semester, int year);
	void insertStudentHasAdvisor(int studentID, int advisorID);
	void insertCourseHasPrerequisite(int courseID, int prerequisiteID);
	void insertPlanHasCourse(int courseID, int planID);

private:
	
	//data
	vector <string> courses = { "CSC-1100 CS1 Required", "CSC-1810 CS2 Required", "CSC-1820 CS3 Required" , "CSC-2030 CS4 NotRequired" , "CSC-3210 CS5 NotRequired" , "CSC-3510 CS6 NotRequired" , "CSC-3530 CS7 NotRequired" };
	vector <string> advisorNames = { "Mark Mahoney", "Perry Kivolowitz", "Bill Schroeder", "Erlan Wheeler", "Sarah Jensen" };
	vector <string> studentNames = {"Celestine Ananda", "Nicholas Bartel", "Adam Biewer", 
		"Paul Fischer", "Dimitrije Kastratovic", "Oliver Keller", "Jordan Keller", "Chase Lange", 
		"Marisa Mortellaro", "Olivia Pratt", "Andrew Senkbeil", "Thomas Shannon", "Jaxon Stout", "Scotland White"};

	void insertData();

	//create table functions
	void createStudentsTable();
	void createAdvisorsTable();
	void createPlansTable();
	void createCoursesTable();
	void createCourseHasPrerequisiteTable();
	void createStudentTakesCourseTable();
	void createPlanHasCourseTable();
	void createPlansSemesterYearIndexTable();
	void createStudentHasAdvisorsTable();

	//General queries
	void listAllStudents();
	void listAllAdvisors();
	void listAllCourses();
	void listAllPlans();


	//Advisor queries
	void listStudentsQuery(int advisorID);
	void listPlansQuery(int advisorID);
	void makePlanQuery(int advisorID);
	void deletePlanQuery(int planID);
	void planToCourseQuery(int studentID, int planID);

	//Student queries
	void listCurrentCourses(int studentID);
	void totalNumOfReqCredits(int studentID);
	void totalNumOfNonReqCredits(int studentID);
	void coursesStudentCanTake(int studentID);
	void coursesStudentCannotTake(int studentID);
};
