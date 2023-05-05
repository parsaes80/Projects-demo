#ifndef STUDENTLIST_HPP
#define STUDENTLIST_HPP

#include "student.hpp"

using namespace std;

class StuLinkedList
{
private:
    StudentPtr head;
public:
    StuLinkedList();
    StuLinkedList(const StuLinkedList&);
    ~StuLinkedList();
    StuLinkedList& operator= (const StuLinkedList&);
    void head_insert(const Student&);
    StudentPtr search_node(const Student&) const;
    void insert_after(const StudentPtr&, const Student&) const;
    void insert_overallSorted(const Student&);
    void insert_ptrObj(const StudentPtr&); // insert student object at head given its pointer
    void remove_node(const StudentPtr&);
    void remove_node(const Student&);
    void remove_all(const Student&);
    void tail_insert(const Student&);
    void insert_before(const StudentPtr&, const Student&);
    void printThreshold(int resScore, float cgpa) const; // prints out all matches that meet the threshold, otherwise, prints that no match was found
    void selectionSort();

    friend ostream& operator<< (ostream&, const StuLinkedList&);
};

class DomStuLinkedList
{
private:
    DomesticStudentPtr head;
    DomesticStudentPtr tail;
public:
    DomStuLinkedList();
    DomStuLinkedList(const DomStuLinkedList&);
    ~DomStuLinkedList();

    DomesticStudentPtr getHead() const;
    void setHead(DomesticStudentPtr&);

    DomesticStudentPtr getTail() const;
    void updateTail();

    void deleteHeadAndTail();

    DomStuLinkedList& operator= (const DomStuLinkedList&);
    void head_insert(const DomesticStudent&);
    DomesticStudentPtr search_node(const DomesticStudent&) const;
    void insert_after(const DomesticStudentPtr&, const DomesticStudent&);
    void insert_overallSorted(const DomesticStudent&);
    void remove_node(const DomesticStudentPtr&);
    void remove_node(const DomesticStudent&);
    void remove_all(const DomesticStudent&);
    void tail_insert(const DomesticStudent&);
    void insert_before(const DomesticStudentPtr&, const DomesticStudent&);

    void searchByName(string firstName, string lastName);
    // Precondition: requires a first name and a last name to search the linked list for a matching object with that name
    // Post-condition: if a match is found, all matches are printed out. If no match is found, this information will also be printed out

    void searchByApplicationID(int applicationID);
    // Pre-condition: requires an application ID that is 8 digits and starts at 20210000
    // Post-condition: if a match is found, all matches are printed out. IF no match is found, this information is printed out

    void searchByCGPA(float CGPA);
    // Pre-condition: requires a float CGPA rounded to a single digit
    // Post-condition: if a match is found, all matches are printed out. If no match is found, this information is printed out

    void searchByResearchScore(int researchScore);
    // Pre-condition: requires an int research Score
    // Post-condition: if a match is found, all matches are printed out. If no match is found, this information is printed out

    void deleteByName(string& firstName, string& lastName);
    // Pre-condition: requires a first name and a last name to search the linked list and delete a matching object with that name
    // Post-condition: If a match is found, all matches are deleted. If no match is found, this information is printed out

    //friend void overallSortLL(DomStuLinkedList&);//Not Implemented and questionable if we need it.
    friend ostream& operator<< (ostream&, const DomStuLinkedList&);
};

class IntStuLinkedList
{
private:
    InternationalStudentPtr head;
    InternationalStudentPtr tail;
public:
    IntStuLinkedList();
    IntStuLinkedList(const IntStuLinkedList&);
    ~IntStuLinkedList();

    InternationalStudentPtr getHead() const;
    void setHead(InternationalStudentPtr&);

    InternationalStudentPtr getTail() const;
    void updateTail();

    void deleteHeadAndTail();

    IntStuLinkedList& operator= (const IntStuLinkedList&);
    void head_insert(const InternationalStudent&);
    InternationalStudentPtr search_node(const InternationalStudent&) const;
    void insert_after(const InternationalStudentPtr&, const InternationalStudent&);
    void remove_node(const InternationalStudentPtr&);
    void remove_node(const InternationalStudent&);
    void remove_all(const InternationalStudent&);
    void tail_insert(const InternationalStudent&);
    void insert_before(const InternationalStudentPtr&, const InternationalStudent&);
    void insert_overallSorted(const InternationalStudent&);

    void searchByName(string firstName, string lastName);
    // Precondition: requires a first name and a last name to search the linked list for a matching object with that name
    // Post-condition: if a match is found, all matches are printed out. If no match is found, this information will also be printed out

    void searchByApplicationID(int applicationID);
    // Pre-condition: requires an application ID that is 8 digits and starts at 20210000
    // Post-condition: if a match is found, all matches are printed out. IF no match is found, this information is printed out

    void searchByCGPA(float CGPA);
    // Pre-condition: requires a float CGPA rounded to a single digit
    // Post-condition: if a match is found, all matches are printed out. If no match is found, this information is printed out

    void searchByResearchScore(int researchScore);
    // Pre-condition: requires an int research Score
    // Post-condition: if a match is found, all matches are printed out. If no match is found, this information is printed out

    void deleteByName(string firstName, string lastName);
    // Pre-condition: requires a first name and a last name to search the linked list and delete a matching object with that name
    // Post-condition: If a match is found, all matches are deleted. If no match is found, this information is printed out

    //friend void overallSortLL(IntStuLinkedList&);//Not Implemented and questionable if we need it.
    friend ostream& operator<< (ostream&, const IntStuLinkedList&);
};

/* EXTERNAL HELPER FUNCTIONS */

StuLinkedList mergeStuLinkedList(DomStuLinkedList&,IntStuLinkedList&);
// Precondition: takes in a domestic student linked list and an international student linked list
// Postcondition: returns a merged student linked list

#endif //STUDENTLIST_HPP