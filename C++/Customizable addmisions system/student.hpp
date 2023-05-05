//header file student.hpp to declare your classes
#ifndef STUDENT_H
#define STUDENT_H
using namespace std; //use namespace std

#include <string> //you will have to use string in C++
#include <vector>
class Student {
    typedef Student* StudentPtr;
public:
    // Constructors
    Student();
    Student( string firstName, string lastName, float CGPA, int researchScore, int applicationID );
    Student(const Student& copyThis);//copy constructor

    // get and set functions
    string getFirstName() const;
    string getLastName() const;
    float getCGPA()const ;
    int getResearchScore() const;
    int getApplicationID() const ;

    void setFirstName(string newFirstName);
    void setLastName(string newLastName);
    void setResearchScore(int newResearchScore);
    void setApplicationID(int newApplicationID);
    void setCGPA(float newCGPA);

    Student* getLink() const;
    void setLink(const StudentPtr& stuPtr);
    friend ostream& operator <<(ostream& outs, const Student& stu);
    void operator= (const Student&);
    bool operator==(const Student&);
    virtual void printInfo(ostream&) const; 

private:

    string firstName, lastName;
    float CGPA; // output must always be to 1 decimal place
    int researchScore; // from 0-100
    long unsigned int applicationID; // 8-digit ID starting at 20210000
    Student *link;
};
typedef Student* StudentPtr;

class DomesticStudent : public Student {
    typedef DomesticStudent* DomesticStudentPtr;
public:
    // Constructors
    DomesticStudent();
    DomesticStudent( string firstName, string lastName, float CGPA, int researchScore, int applicationID, string homeProvince );
    DomesticStudent(const DomesticStudent& copyThis);//copy constructor

    // get and set functions
    string getHomeProvince() const;
    virtual void setHomeProvince(string newProvince);

    DomesticStudent* getLink() const;
    void setLink(const DomesticStudentPtr& stuPtr);

    // overloaded insertion operator
    virtual void printInfo(ostream&) const;
    friend ostream& operator <<(ostream& outs, const DomesticStudent& stu);

    void operator= (const DomesticStudent&);
    bool operator==(const DomesticStudent&);
private:
    string homeProvince;
    DomesticStudent *link;
};
typedef DomesticStudent* DomesticStudentPtr;

class ToeflScore {
public:
    // constructors
    ToeflScore();
    ToeflScore( int readingScore, int listeningScore, int speakingScore, int writingScore );

    // get and set functions
    int getReadingScore() const;
    int getListeningScore() const;
    int getSpeakingScore() const;
    int getWritingScore() const;
    int getTotalScore();

    void setReadingScore( int newReadingScore );
    void setListeningScore( int newListeningScore );
    void setSpeakingScore( int newSpeakingScore );
    void setWritingScore( int newWritingScore );

private:
    // all individual scores of type int 0-30
    int readingScore;
    int listeningScore;
    int speakingScore;
    int writingScore;

    // sum of all individual scores
    int totalScore;
};

class InternationalStudent : public Student {
    typedef InternationalStudent* InternationalStudentPtr;
public:
    // Constructors
    InternationalStudent();
    InternationalStudent( string firstName, string lastName, float CGPA, int researchScore, int applicationID, string homeCountry, ToeflScore TOEFL );
    InternationalStudent(const InternationalStudent& copyThis);

    // get and set functions
    string getHomeCountry() const;
    ToeflScore getTOEFL() const;

    void setHomeCountry(string newHomeCountry);
    void setTOEFL( int newReadingScore, int newListeningScore, int newSpeakingScore, int newWritingScore );

    InternationalStudentPtr getLink() const;
    void setLink(const InternationalStudentPtr& stuPtr);

    void operator= (const InternationalStudent&);
    bool operator==(const InternationalStudent&);

    // overloaded insertion operator
    friend ostream& operator <<(ostream& outs, const InternationalStudent& stu);
    virtual void printInfo(ostream&) const;
    
private:
    string homeCountry;
    ToeflScore TOEFL;
    InternationalStudent* link;
};
typedef InternationalStudent* InternationalStudentPtr;

/* EXTERNAL HELPER FUNCTIONS */

void toTitleCase(string& inputString); // make all letters except first lowercase
void toCapitalCase(string& inputString); // make all letters capital

bool isProvince(string& userInput); // if the string provided is a valid province, returns true
bool isCountry(string& userInput); // if the string provided is a valid country, returns true


#endif // !STUDENT_H
