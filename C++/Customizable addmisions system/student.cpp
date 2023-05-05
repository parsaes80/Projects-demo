//student.cpp to implement your classes
#include "student.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <cfloat>
using namespace std;

// general variables
const int numOfProvinces = 13;
const string homeProvinces[numOfProvinces] = {"NL","PE","NS","NB","QC","ON","MB","SK","AB","BC","YT","NT","NU"};
const int numOfCountries = 5;
const string homeCountries[numOfCountries] = {"Canada","China","India","Iran","Korea"};

/* STUDENT CLASS */
/* constructors */
Student::Student() {
	// default constructor
	string firstName = "";
	string lastName = "";
	float CGPA{0};
	int researchScore{0}; // value initializing to zero as defensive programming
	int applicationID{0};
}

Student::Student(string firstName, string lastName, float CGPA, int researchScore, int applicationID) {
	// parameters have similar names to classes members, this could lead to errors in some compilers
	this->firstName = firstName;
	this->lastName = lastName;
	this->CGPA = CGPA;
	this->researchScore = researchScore;
	this->applicationID = applicationID;
}

/* getter functions */

string Student::getFirstName() const {
	return firstName;
}

string Student::getLastName() const {
	return lastName;
}

float Student::getCGPA() const {
	return CGPA;
}

int Student::getResearchScore() const {
	return researchScore;
}

int Student::getApplicationID() const {
	return applicationID;
}

/* setter functions */

void Student::setFirstName(string newFirstName) {
    toTitleCase(newFirstName);
	firstName = newFirstName;
}

void Student::setLastName(string newLastName) {
    toTitleCase(newLastName);
	lastName = newLastName;
}

void Student::setResearchScore(int newResearchScore) {
	researchScore = newResearchScore;
}

void Student::setApplicationID(int newApplicationID) {
	applicationID = newApplicationID;
}

void Student::setCGPA(float newCGPA) {
	CGPA = newCGPA;
}

StudentPtr Student::getLink() const{
    return link;
}
void Student::setLink(const StudentPtr& stuPtr){
    link = stuPtr;
}
ostream& operator<<(ostream& outs, const Student& currentStudent){
    currentStudent.printInfo(outs);
    outs << endl;
	return outs;
}
void Student::operator= (const Student& copyThis){
    this->setFirstName(copyThis.getFirstName());
    this->setLastName(copyThis.getLastName());
    this->setCGPA(copyThis.getCGPA());
    this->setResearchScore(copyThis.getResearchScore());
    this->setApplicationID(copyThis.getApplicationID());
    this->setLink(copyThis.getLink());
}
bool Student::operator==(const Student& stu){
    if (this->getFirstName() == stu.getFirstName() && this->getLastName() == stu.getLastName() && this->getCGPA() == stu.getCGPA() && this->getResearchScore() == stu.getResearchScore() && this->getApplicationID() == stu.getApplicationID())
            return true;
    else
        return false;
}
void Student::printInfo(ostream& outs) const{
    //outs << "I WAS HERE" << endl;
}

/* DOMESTIC STUDENT CLASS */
/* constructors */
DomesticStudent::DomesticStudent() : Student() {
	// default constructor
	this->homeProvince = ""; // empty string
    link = NULL;
}

DomesticStudent::DomesticStudent(const DomesticStudent& copyThis){
    this->setFirstName(copyThis.getFirstName());
    this->setLastName(copyThis.getLastName());
    this->setCGPA(copyThis.getCGPA());
    this->setResearchScore(copyThis.getResearchScore());
    this->setApplicationID(copyThis.getApplicationID());
    this->setHomeProvince(copyThis.getHomeProvince());
    this->setLink(copyThis.getLink());
}
DomesticStudentPtr DomesticStudent::getLink() const{
    return link;
}
void DomesticStudent::setLink(const DomesticStudentPtr& stuPtr){
    link = stuPtr;
}

DomesticStudent::DomesticStudent(string firstName, string lastName, float CGPA, int researchScore, int applicationID, string homeProvince) : Student( firstName, lastName, CGPA, researchScore, applicationID) {
	this->homeProvince = homeProvince;
    link = NULL;
}

string DomesticStudent::getHomeProvince() const {
	return homeProvince;
}

void DomesticStudent::setHomeProvince(string newProvince) {
	if (isProvince(newProvince)) {
		homeProvince = newProvince;
	}
	else {
		cout << "unable to set province! Please enter a valid province!" << endl;
		return;
	}
}

void DomesticStudent::operator= (const DomesticStudent& copyThis){
    this->setFirstName(copyThis.getFirstName());
    this->setLastName(copyThis.getLastName());
    this->setCGPA(copyThis.getCGPA());
    this->setResearchScore(copyThis.getResearchScore());
    this->setApplicationID(copyThis.getApplicationID());
    this->setHomeProvince(copyThis.getHomeProvince());
    this->setLink(copyThis.getLink());
}

bool DomesticStudent::operator==(const DomesticStudent& stu){
    if (this->getFirstName() == stu.getFirstName() && this->getLastName() == stu.getLastName() && this->getCGPA() == stu.getCGPA() && this->getResearchScore() == stu.getResearchScore() && this->getApplicationID() == stu.getApplicationID() && this->getHomeProvince() == stu.getHomeProvince())
            return true;
    else
        return false;
}
void DomesticStudent::printInfo(ostream& outs) const{
    outs << "Domestic Student: " << getFirstName() << " " << getLastName();
	outs << " Application ID: " << getApplicationID();
	outs << " Home Province: " << getHomeProvince();
	outs << " CGPA: " << getCGPA();
	outs << " Research Score: " << getResearchScore();
}

/* ostream operator overlaod */
ostream& operator <<(ostream& outs, const DomesticStudent& currentStudent) {
	// print out all object information on Domestic Student
	outs << "Domestic Student: " << currentStudent.getFirstName() << " " << currentStudent.getLastName() << " ";
	outs << "Application ID: " << currentStudent.getApplicationID() << " ";
	outs << "Home Province: " << currentStudent.getHomeProvince() << " ";
	outs << "CGPA: " << currentStudent.getCGPA() << " ";
	outs << "Research Score: " << currentStudent.getResearchScore() << endl;
	return outs;
}

/* TOEFL SCORE CLASS */
/* constructors */
ToeflScore::ToeflScore() {
	// default constructor
	// give all values a default value
	readingScore = 0;
	listeningScore = 0;
	speakingScore = 0;
	writingScore = 0;
}

ToeflScore::ToeflScore( int readingScore, int listeningScore, int speakingScore, int writingScore) {
	// user defined values for each individual score
	this->readingScore = readingScore;
	this->listeningScore = listeningScore;
	this->speakingScore = speakingScore;
	this->writingScore = writingScore;

	// add up all individual scores
	this->totalScore = readingScore + listeningScore + speakingScore + writingScore;
}

/* getter functions */
int ToeflScore::getReadingScore() const {
	return readingScore;
}

int ToeflScore::getListeningScore() const {
	return listeningScore;
}

int ToeflScore::getSpeakingScore() const {
	return speakingScore;
}

int ToeflScore::getWritingScore() const {
	return writingScore;
}

int ToeflScore::getTotalScore() {
	return totalScore;
}

/* setter functions */
void ToeflScore::setReadingScore(int newReadingScore) {
	readingScore = newReadingScore;
}

void ToeflScore::setListeningScore(int newListeningScore) {
	listeningScore = newListeningScore;
}

void ToeflScore::setSpeakingScore(int newSpeakingScore) {
	speakingScore = newSpeakingScore;
}

void ToeflScore::setWritingScore(int newWritingScore) {
	writingScore = newWritingScore;
}

/* INTERNATIONAL STUDENT CLASS */
InternationalStudent::InternationalStudent() : Student() {
	// default constructor
	homeCountry = "";
    link = NULL;
}

InternationalStudent::InternationalStudent(string firstName, string lastName, float CGPA, int researchScore, int applicationID, string homeCountry, ToeflScore TOEFL) : Student(firstName, lastName, CGPA, researchScore, applicationID) {
	this->homeCountry = homeCountry;
	this->TOEFL = TOEFL;
    link = NULL;
}

InternationalStudent::InternationalStudent(const InternationalStudent& stu): Student(stu.getFirstName(), stu.getLastName(), stu.getCGPA(), stu.getResearchScore(), stu.getApplicationID()){
    homeCountry = stu.homeCountry;
    TOEFL = stu.TOEFL;
    link = stu.link;
}

/* getter functions */
string InternationalStudent::getHomeCountry() const {
	return homeCountry;
}

ToeflScore InternationalStudent::getTOEFL() const {
	return TOEFL;
}

InternationalStudentPtr InternationalStudent::getLink() const{
    return link;
}

/* setter functions */
void InternationalStudent::setLink(const InternationalStudentPtr& stuPtr){
    link = stuPtr;
}

void InternationalStudent::setHomeCountry(string newHomeCountry) {
	if (isCountry) {
		homeCountry = newHomeCountry;
	}
	else {
		cout << "invalid country information!" << endl;
		return;
	}
}

void InternationalStudent::setTOEFL(int newReadingScore, int newListeningScore, int newSpeakingScore, int newWritingScore) {
	ToeflScore newToefl(newReadingScore, newListeningScore, newSpeakingScore, newWritingScore);
	this->TOEFL = newToefl;
}

void InternationalStudent::operator= (const InternationalStudent& copyThis){
    this->setFirstName(copyThis.getFirstName());
    this->setLastName(copyThis.getLastName());
    this->setCGPA(copyThis.getCGPA());
    this->setResearchScore(copyThis.getResearchScore());
    this->setApplicationID(copyThis.getApplicationID());
    this->setHomeCountry(copyThis.getHomeCountry());
    this->setTOEFL(copyThis.getTOEFL().getReadingScore(), copyThis.getTOEFL().getListeningScore(), copyThis.getTOEFL().getSpeakingScore(), copyThis.getTOEFL().getWritingScore());
    this->setLink(copyThis.getLink());
}
bool InternationalStudent::operator==(const InternationalStudent& stu){
    if (this->getFirstName() == stu.getFirstName() && this->getLastName() == stu.getLastName() && this->getCGPA() == stu.getCGPA() && this->getResearchScore() == stu.getResearchScore() && this->getApplicationID() == stu.getApplicationID() && this->getHomeCountry() == stu.getHomeCountry())
        return true;
    else
        return false;
}
void InternationalStudent::printInfo(ostream& outs) const{
    outs << "International Student: " << getFirstName() << " " << getLastName();
	outs << " Application ID: " << getApplicationID();
	outs << " Home Country: " << getHomeCountry();
	outs << " CGPA: " << getCGPA();
	outs << " Research Score: " << getResearchScore();
	outs << " TOEFL Score: " << getTOEFL().getTotalScore();
}
/* ostream operator overload */
ostream& operator << (ostream& outs, const InternationalStudent& currentStudent) {

	// print out all International Student object information
	outs << "International Student: " << currentStudent.getFirstName() << " " << currentStudent.getLastName();
	outs << " Application ID: " << currentStudent.getApplicationID();
	outs << " Home Country: " << currentStudent.getHomeCountry();
	outs << " CGPA: " << currentStudent.getCGPA();
	outs << " Research Score: " << currentStudent.getResearchScore();
	outs << " TOEFL Score: " << currentStudent.getTOEFL().getTotalScore() << endl;
	return outs;
}

/* EXTERNAL HELPER FUNCTIONS */

void toTitleCase(string& inputString) {
    // capitalize first letter and make other letters lowercase
    for (int i = 0; i < inputString.size(); i++) {
        if (i == 0) {
            inputString[i] = toupper(inputString[i]);
        }
        else {
            inputString[i] = tolower(inputString[i]);
        }
    }
}

void toCapitalCase(string& inputString) {
	// capitalize all letters
	for (int i = 0; i < inputString.size(); i++) {
		inputString[i] = toupper(inputString[i]);
	}
}

bool isProvince(string& userInput) {
	// if user input is a valid province, return true. Otherwise, return false
	// if the string can't be capitalized, it is not a province
	try {
		toCapitalCase(userInput);
	}
	catch (...) {
		return false;
	}

	// see if the string matches one of the valid provinces
	for (int i = 0; i < numOfProvinces; i++) {
		if (userInput == homeProvinces[i]) {
			return true;
		}
	}

	// if no matches, it is not a province
	return false;
}

bool isCountry(string& userInput) {
	// if user input is a valid country, return true, otherwise, return false
	// if the string can't be Title-cased, it is not a country
	try {
		toTitleCase(userInput);
	}
	catch(...) {
		return false;
	}

	// see if the string matches one of the valid countries
	for (int i = 0; i < numOfCountries; i++) {
		if (userInput == homeCountries[i]) {
			return true;
		}
	}

	// if no matches, it is not a country
	return false;
}