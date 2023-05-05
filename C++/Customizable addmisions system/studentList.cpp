
#include <iostream>
#include <cmath>
#include <cfloat>
#include "studentList.hpp"

// STUDENT LINKED LIST ---------------------------------------------------------------------------------------------

StuLinkedList::StuLinkedList(){
    head = NULL;
}
StuLinkedList::StuLinkedList(const StuLinkedList& LL){
    StudentPtr temp = LL.head;
    while (temp != NULL)
    {
        Student temp1;
        temp1.setFirstName(LL.head->getFirstName());
        temp1.setLastName(LL.head->getLastName());
        temp1.setCGPA(LL.head->getCGPA());
        temp1.setResearchScore(LL.head->getResearchScore());
        temp1.setApplicationID(LL.head->getApplicationID());
    
        tail_insert(temp1);
        temp = temp->getLink();
    }
}
StuLinkedList::~StuLinkedList(){
    StudentPtr temp;
    //cout << "Deleting with DomStu Destructor" << endl;
    while (head != NULL)
    {
        temp = head;
        head = head->getLink();
        delete temp;
    }
}
StuLinkedList& StuLinkedList::operator= (const StuLinkedList& LL){
    if (this == &LL)
        return *this;
    else{
        this->~StuLinkedList();
        StudentPtr temp = LL.head;
        while (temp != NULL){
            Student temp1;
            temp1.setFirstName(LL.head->getFirstName());
            temp1.setLastName(LL.head->getLastName());
            temp1.setCGPA(LL.head->getCGPA());
            temp1.setResearchScore(LL.head->getResearchScore());
            temp1.setApplicationID(LL.head->getApplicationID());

            tail_insert(temp1);
            temp = temp->getLink();
        }
    }
    return *this;
}
void StuLinkedList::head_insert(const Student& stu){
    try {
        StudentPtr n = new Student(stu.getFirstName(), stu.getLastName(), stu.getCGPA(), stu.getResearchScore(), stu.getApplicationID());
        n->setLink(head);
        head = n;
    }
    catch (exception e) {
        cout << "exception thrown! Memory could not be allocated!" << endl;
        cout << e.what() << endl;
        exit(1);
    }
}
StudentPtr StuLinkedList::search_node(const Student& stu) const{
    StudentPtr temp = head;
    while (temp != NULL)
    {
        if (temp->getFirstName() == stu.getFirstName() && temp->getLastName() == stu.getLastName() && temp->getCGPA() == stu.getCGPA() && temp->getResearchScore() == stu.getResearchScore() && temp->getApplicationID() == stu.getApplicationID())
            return temp;
        else
            temp = temp->getLink();
    }
    return NULL;
}
void StuLinkedList::insert_after(const StudentPtr& n, const Student& stu) const{
    if (n == NULL)
        return;
    else{
        try {
            StudentPtr temp = new Student(stu.getFirstName(), stu.getLastName(), stu.getCGPA(), stu.getResearchScore(), stu.getApplicationID());
            temp->setLink(n->getLink());
            n->setLink(temp);
        }
        catch (exception e) {
            cout << "exception thrown! Memory could not be allocated!" << endl;
            cout << e.what() << endl;
            exit(1);
        }
        
    }
}
void StuLinkedList::insert_overallSorted(const Student& stu){
    if (head == NULL){
        head_insert(stu);
        //cout << "I was here" << endl;
        return;
    }
    else{
        StudentPtr temp = head;
        while (temp != NULL)
        {
            if (temp->getResearchScore() < stu.getResearchScore())
                break;
            else if((temp->getResearchScore() == stu.getResearchScore()) && temp->getCGPA() < stu.getCGPA())
                break;
            else
                temp = temp->getLink();
        }
        insert_before(temp, stu);
    }
}
void StuLinkedList::insert_ptrObj(const StudentPtr& stuPtr){
    // insert student object at head given its pointer
    // StudentPtr temp = head;
    // while (temp->getLink() != NULL){
    //     temp = temp->getLink();
    // }
    // temp->setLink(stuPtr);
    // temp = temp->getLink();
    // temp->setLink(NULL);
    stuPtr->setLink(head);
    head = stuPtr;
}

void StuLinkedList::remove_node(const StudentPtr& stuPtr){
    if (head == NULL || stuPtr == NULL)
        return;
    else if (head == stuPtr){
        head = head->getLink();
        delete stuPtr;
        return;
    }
    else{
        StudentPtr temp = head;
        while(temp != NULL){
            if (temp->getLink() == stuPtr){
                temp->setLink(stuPtr->getLink());
                delete stuPtr;
                return;
            }
            temp = temp->getLink();
        }
    }
}
void StuLinkedList::remove_node(const Student& stu){
    StudentPtr temp = search_node(stu);
    remove_node(temp);
}
void StuLinkedList::remove_all(const Student& stu){
    StudentPtr temp;
    do
    {
        temp = search_node(stu);
        remove_node(temp);
    } while (temp != NULL);
}
void StuLinkedList::tail_insert(const Student& stu){
    if (head == NULL)
    {
        head_insert(stu);
        return;
    }
    else
    {
        StudentPtr temp = head;
        while (temp->getLink() != NULL)
            temp = temp->getLink();
        insert_after(temp, stu);
    }
}
void StuLinkedList::insert_before(const StudentPtr& stuPtr, const Student& stu){
    if (head == NULL){
        if (stuPtr == NULL)
            head_insert(stu);
        else
            cout << "Warning: Insertion failed. Wrong node argument." << endl;
        return;
    }
    else if(head != NULL){
        if (stuPtr == NULL)
            tail_insert(stu);
        else if(head == stuPtr)
            head_insert(stu);
        else if(search_node(*stuPtr) == NULL)
            cout << "Warning: Insertion failed. Wrong node argument." << endl;
        else{
            StudentPtr temp = head;
            while (temp->getLink() != stuPtr)
                temp = temp->getLink();
            insert_after(temp, stu);
        }
    }
}
void StuLinkedList::selectionSort(){
    StudentPtr a, b, c, d, r;
 
    a = b = head;
 
    // While b is not the last node
    while (b->getLink() != NULL) {
 
        c = d = b->getLink();
 
        // While d is pointing to a valid node
        while (d != NULL) {
 
            if (b->getResearchScore() < d->getResearchScore()) {
 
                // If d appears immediately after b
                if (b->getLink() == d) {
 
                    // Case 1: b is the head of the linked list
                    if (b == head) {
 
                        // Move d before b
                        b->setLink(d->getLink());
                        d->setLink(b);
 
                        // Swap b and d pointers
                        r = b;
                        b = d;
                        d = r;
 
                        c = d;
 
                        // Update the head
                        head = b;
 
                        // Skip to the next element
                        // as it is already in order
                        d = d->getLink();
                    }
 
                    // Case 2: b is not the head of the linked list
                    else {
 
                        // Move d before b
                        b->setLink(d->getLink());
                        d->setLink(b);
                        a->setLink(d);
 
                        // Swap b and d pointers
                        r = b;
                        b = d;
                        d = r;
 
                        c = d;
 
                        // Skip to the next element
                        // as it is already in order
                        d = d->getLink();
                    }
                }
 
                // If b and d have some non-zero
                // number of nodes in between them
                else {
 
                    // Case 3: b is the head of the linked list
                    if (b == head) {
 
                        // Swap b->next and d->next
                        r = b->getLink();
                        b->setLink(d->getLink());
                        d->setLink(r);
                        c->setLink(b);
 
                        // Swap b and d pointers
                        r = b;
                        b = d;
                        d = r;
 
                        c = d;
 
                        // Skip to the next element
                        // as it is already in order
                        d = d->getLink();
 
                        // Update the head
                        head = b;
                    }
 
                    // Case 4: b is not the head of the linked list
                    else {
 
                        // Swap b->next and d->next
                        r = b->getLink();
                        b->setLink(d->getLink());
                        d->setLink(r);
                        c->setLink(b);
                        a->setLink(d);
 
                        // Swap b and d pointers
                        r = b;
                        b = d;
                        d = r;
 
                        c = d;
 
                        // Skip to the next element
                        // as it is already in order
                        d = d->getLink();
                    }
                }
            }
            else {
 
                // Update c and skip to the next element
                // as it is already in order
                c = d;
                d = d->getLink();
            }
            
        }
        a = b;
        b = b->getLink();
    }

    a = b = head;
 
    // While b is not the last node
    while (b->getLink() != NULL) {
 
        c = d = b->getLink();
 
        // While d is pointing to a valid node
        while (d != NULL) {
 
            if ((b->getCGPA() < d->getCGPA()) && (b->getResearchScore() == d->getResearchScore())) {
 
                // If d appears immediately after b
                if (b->getLink() == d) {
 
                    // Case 1: b is the head of the linked list
                    if (b == head) {
 
                        // Move d before b
                        b->setLink(d->getLink());
                        d->setLink(b);
 
                        // Swap b and d pointers
                        r = b;
                        b = d;
                        d = r;
 
                        c = d;
 
                        // Update the head
                        head = b;
 
                        // Skip to the next element
                        // as it is already in order
                        d = d->getLink();
                    }
 
                    // Case 2: b is not the head of the linked list
                    else {
 
                        // Move d before b
                        b->setLink(d->getLink());
                        d->setLink(b);
                        a->setLink(d);
 
                        // Swap b and d pointers
                        r = b;
                        b = d;
                        d = r;
 
                        c = d;
 
                        // Skip to the next element
                        // as it is already in order
                        d = d->getLink();
                    }
                }
 
                // If b and d have some non-zero
                // number of nodes in between them
                else {
 
                    // Case 3: b is the head of the linked list
                    if (b == head) {
 
                        // Swap b->next and d->next
                        r = b->getLink();
                        b->setLink(d->getLink());
                        d->setLink(r);
                        c->setLink(b);
 
                        // Swap b and d pointers
                        r = b;
                        b = d;
                        d = r;
 
                        c = d;
 
                        // Skip to the next element
                        // as it is already in order
                        d = d->getLink();
 
                        // Update the head
                        head = b;
                    }
 
                    // Case 4: b is not the head of the linked list
                    else {
 
                        // Swap b->next and d->next
                        r = b->getLink();
                        b->setLink(d->getLink());
                        d->setLink(r);
                        c->setLink(b);
                        a->setLink(d);
 
                        // Swap b and d pointers
                        r = b;
                        b = d;
                        d = r;
 
                        c = d;
 
                        // Skip to the next element
                        // as it is already in order
                        d = d->getLink();
                    }
                }
            }
            else {
 
                // Update c and skip to the next element
                // as it is already in order
                c = d;
                d = d->getLink();
            }
            
        }
        a = b;
        b = b->getLink();
    }
}
void StuLinkedList::printThreshold(int resScore, float cgpa) const{
    StudentPtr temp = head;
    bool noMatch = true;
    while (temp != NULL)
    {
        if (temp->getResearchScore() >= resScore && temp->getCGPA() >= cgpa){
            cout << *temp;
            noMatch = false;
        }
        temp = temp->getLink();
    }
    if (noMatch) {
        cout << "There is no match!" << endl;
        return;
    }
}

ostream& operator<< (ostream& out, const StuLinkedList& LL){
    StudentPtr temp = LL.head;
    while(temp != NULL){
        out << *temp;
        temp = temp->getLink();
    }
    return out;
}
// END OF STUDENT LINKED LIST -------------------------------------------------------------------------

// DOMESTIC STUDENT LINKED LIST -----------------------------------------------------------------------

void DomStuLinkedList::updateTail(){
    if (head != NULL){
        DomesticStudentPtr temporary = head;
        while (temporary->getLink() != NULL){
            temporary = temporary->getLink();
        }
        tail = temporary;
    }
    else{
        tail = NULL;
    }
}
ostream& operator<< (ostream& out, const DomStuLinkedList& LL){
    DomesticStudentPtr temp = LL.head;
    while(temp != NULL){
        out << *temp;
        temp = temp->getLink();
    }
    return out;
}
DomStuLinkedList::DomStuLinkedList(){
    head = NULL;
    tail = NULL;
}
DomStuLinkedList::DomStuLinkedList(const DomStuLinkedList &LL){
    DomesticStudentPtr temp = LL.head;
    while (temp != NULL)
    {
        DomesticStudent temp1;
        temp1.setFirstName(LL.head->getFirstName());
        temp1.setLastName(LL.head->getLastName());
        temp1.setCGPA(LL.head->getCGPA());
        temp1.setResearchScore(LL.head->getResearchScore());
        temp1.setApplicationID(LL.head->getApplicationID());
        temp1.setHomeProvince(LL.head->getHomeProvince());
    
        tail_insert(temp1);
        temp = temp->getLink();
    }
    updateTail();
}
DomStuLinkedList::~DomStuLinkedList(){
    DomesticStudentPtr temp;
    //cout << "Deleting with DomStu Destructor" << endl;
    while (head != NULL)
    {
        temp = head;
        head = head->getLink();
        delete temp;
    }
}
DomesticStudentPtr DomStuLinkedList::getHead() const{
    DomesticStudentPtr temp = head;
    return temp;
}
void DomStuLinkedList::setHead(DomesticStudentPtr& stuPtr){
    head = stuPtr;
}
DomStuLinkedList& DomStuLinkedList::operator=(const DomStuLinkedList &LL){
    if (this == &LL)
        return *this;
    else{
        this->~DomStuLinkedList();
        DomesticStudentPtr temp = LL.head;
        while (temp != NULL){
            DomesticStudent temp1;
            temp1.setFirstName(LL.head->getFirstName());
            temp1.setLastName(LL.head->getLastName());
            temp1.setCGPA(LL.head->getCGPA());
            temp1.setResearchScore(LL.head->getResearchScore());
            temp1.setApplicationID(LL.head->getApplicationID());
            temp1.setHomeProvince(LL.head->getHomeProvince());

            tail_insert(temp1);
            temp = temp->getLink();
        }
        updateTail();
    }

    return *this;
}
void DomStuLinkedList::head_insert(const DomesticStudent &stu){
    try {
        // purposeful error by bad_alloc
        //int *reallyBigArray = new int[1000000000];
        
        DomesticStudentPtr n = new DomesticStudent(stu.getFirstName(), stu.getLastName(), stu.getCGPA(), stu.getResearchScore(), stu.getApplicationID(), stu.getHomeProvince());
        n->setLink(head);
        head = n;
        updateTail();
    }
    catch (exception e) {
        cout << "exception thrown! Memory could not be allocated!" << endl;
        cout << e.what() << endl;
        exit(1);
    }
}
void DomStuLinkedList::insert_after(const DomesticStudentPtr& n, const DomesticStudent& stu)
{
    if (n == NULL)
        return;
    else{
        try {
            DomesticStudentPtr temp = new DomesticStudent(stu.getFirstName(), stu.getLastName(), stu.getCGPA(), stu.getResearchScore(), stu.getApplicationID(), stu.getHomeProvince());
            temp->setLink(n->getLink());
            n->setLink(temp);
            updateTail();
        }
        catch (exception e) {
            cout << "exception thrown! Memory could not be allocated!" << endl;
            cout << e.what() << endl;
            exit(1);
        }
        
    }
}
DomesticStudentPtr DomStuLinkedList::search_node(const DomesticStudent& stu) const{
    DomesticStudentPtr temp = head;
    while (temp != NULL)
    {
        if (temp->getFirstName() == stu.getFirstName() && temp->getLastName() == stu.getLastName() && temp->getCGPA() == stu.getCGPA() && temp->getResearchScore() == stu.getResearchScore() && temp->getApplicationID() == stu.getApplicationID() && temp->getHomeProvince() == stu.getHomeProvince())
            return temp;
        else
            temp = temp->getLink();
    }
    return NULL;
}
void DomStuLinkedList::remove_node(const DomesticStudentPtr& stuPtr){
    if (head == NULL || stuPtr == NULL)
        return;
    else if (head == stuPtr){
        head = head->getLink();
        delete stuPtr;
        return;
    }
    else{
        DomesticStudentPtr temp = head;
        while(temp != NULL){
            if (temp->getLink() == stuPtr){
                temp->setLink(stuPtr->getLink());
                delete stuPtr;
                return;
            }
            temp = temp->getLink();
        }
        updateTail();
    }
}
void DomStuLinkedList::remove_node(const DomesticStudent& stu){
    DomesticStudentPtr temp = search_node(stu);
    remove_node(temp);
}
void DomStuLinkedList::remove_all(const DomesticStudent& stu){
    DomesticStudentPtr temp;
    do
    {
        temp = search_node(stu);
        remove_node(temp);
    } while (temp != NULL);
}
void DomStuLinkedList::tail_insert(const DomesticStudent& stu){
    if (head == NULL)
    {
        head_insert(stu);
        return;
    }
    else
    {
        DomesticStudentPtr temp = head;
        while (temp->getLink() != NULL)
            temp = temp->getLink();
        insert_after(temp, stu);
    }
}
void DomStuLinkedList::insert_before(const DomesticStudentPtr& stuPtr, const DomesticStudent& stu){
    if (head == NULL){
        if (stuPtr == NULL)
            head_insert(stu);
        else
            cout << "Warning: Insertion failed. Wrong node argument." << endl;
        return;
    }
    else if(head != NULL){
        if (stuPtr == NULL)
            tail_insert(stu);
        else if(head == stuPtr)
            head_insert(stu);
        else if(search_node(*stuPtr) == NULL)
            cout << "Warning: Insertion failed. Wrong node argument." << endl;
        else{
            DomesticStudentPtr temp = head;
            while (temp->getLink() != stuPtr)
                temp = temp->getLink();
            insert_after(temp, stu);
        }
    }
} 
DomesticStudentPtr DomStuLinkedList::getTail() const{
    return tail;
}

void DomStuLinkedList::deleteHeadAndTail() {
    remove_node(head);
    remove_node(tail);
}

void DomStuLinkedList::insert_overallSorted(const DomesticStudent& stu){
    if (head == NULL){
        head_insert(stu);
        //cout << "I was here" << endl;
        return;
    }
    else{
        DomesticStudentPtr temp = head;
        while (temp != NULL)
        {
            if (temp->getResearchScore() < stu.getResearchScore())
                break;
            else if((temp->getResearchScore() == stu.getResearchScore()) && temp->getCGPA() < stu.getCGPA())
                break;
            else if((temp->getResearchScore() == stu.getResearchScore()) && (temp->getCGPA() == stu.getCGPA()) && (temp->getHomeProvince() > stu.getHomeProvince()))
                break;
            else
                temp = temp->getLink();
        }
        insert_before(temp, stu);
    }
}

void DomStuLinkedList::searchByName(string firstName, string lastName) {
    // Precondition: requires a first name and a last name to search the linked list for a matching object with that name
    // Post-condition: if a match is found, all matches are printed out. If no match is found, this information will also be printed out

    //cout << "searchByName has been called for " << firstName << " " << lastName << endl;

    // input checking/control
    try {
        toTitleCase(firstName);
        toTitleCase(lastName);
    }
    catch (...) {
        cout << "Please try again with correct input" << endl;
        return;
    }

    // go through the links to search for the name and print out each node that satisfies the name
    cout << "Searching..." << endl << endl;
    bool found = false;
    DomesticStudentPtr currentDomStuPtr = this->head;
    while (currentDomStuPtr != NULL) {
        if ((currentDomStuPtr->getFirstName() == firstName) && (currentDomStuPtr->getLastName() == lastName)) {
            cout << *currentDomStuPtr << endl;
            currentDomStuPtr = currentDomStuPtr->getLink();
            found = true;
        }
        else {
            currentDomStuPtr = currentDomStuPtr->getLink();
        }
    }

    // if no match is found, output this information
    if (!found) {
        cout << "No match found!" << endl;
    }
}
  
void DomStuLinkedList::searchByApplicationID(int applicationID){
    // Pre-condition: requires an application ID that is 8 digits and starts at 20210000
    // Post-condition: if a match is found, all matches are printed out. IF no match is found, this information is printed out

    // cout << "searchByApplicationID has been called for " << applicationID << endl;

    bool found = false;
    // go through the links to search for the application ID, print out each node that satisfies the ID
    cout << "Searching..." << endl << endl;
    DomesticStudentPtr currentDomStuPtr = this->head;
    while (currentDomStuPtr != NULL) {
        if ( (currentDomStuPtr->getApplicationID() == applicationID) ) {
            // a match was found
            cout << *currentDomStuPtr << endl;
            currentDomStuPtr = currentDomStuPtr->getLink();
            found = true;
        }
        else {
            currentDomStuPtr = currentDomStuPtr->getLink();
        }
    }
    
    // if found is still false, no match has been found
    if (!found) {
        cout << "No match found!" << endl;
    }
}
void DomStuLinkedList::searchByCGPA(float CGPA){
    // Pre-condition: requires a float CGPA rounded to a single digit
    // Post-condition: if a match is found, all matches are printed out. If no match is found, this information is printed out

    //cout << "searchByCGPA has been called for " << CGPA << endl;

    bool found = false;
    // go through the links to search for the CGPA, print out each node that satisfies the CGPA
    cout << "Searching..." << endl << endl;
    DomesticStudentPtr currentDomStuPtr = this->head;
    while (currentDomStuPtr != NULL) {
        if ( fabs(currentDomStuPtr->getCGPA()-CGPA) < FLT_EPSILON ) { // floating point arithmetic is almost never exact!
            // a match was found
            cout << *currentDomStuPtr << endl;
            currentDomStuPtr = currentDomStuPtr->getLink();
            found = true;
        }
        else {
            currentDomStuPtr = currentDomStuPtr->getLink();
        }
    }
    
    // if found is still false, no match has been found
    if (!found) {
        cout << "No match found!" << endl;
    }

}
void DomStuLinkedList::searchByResearchScore(int researchScore){
    // Pre-condition: requires an int research Score
    // Post-condition: if a match is found, all matches are printed out. If no match is found, this information is printed out

    //cout << "searchByResearchScore has been called for " << researchScore << endl;

    bool found = false;
    // go through the links to search for the research score, print out each node that satisfies the score
    cout << "Searching..." << endl << endl;
    DomesticStudentPtr currentDomStuPtr = this->head;
    while (currentDomStuPtr != NULL) {
        if ( currentDomStuPtr->getResearchScore() == researchScore ) {
            // a match was found
            cout << *currentDomStuPtr << endl;
            currentDomStuPtr = currentDomStuPtr->getLink();
            found = true;
        }
        else {
            currentDomStuPtr = currentDomStuPtr->getLink();
        }
    }
    
    // if found is still false, no match has been found
    if (!found) {
        cout << "No match found!" << endl;
    }    
}

void DomStuLinkedList::deleteByName(string& firstName, string& lastName) {
    // Pre-condition: requires a first name and a last name to search the linked list and delete a matching object with that name
    // Post-condition: If a match is found, all matches are deleted. If no match is found, this information is printed out

    // input checking/control
    try {
        toTitleCase(firstName);
        toTitleCase(lastName);
    }
    catch (...) {
        cout << "Please try again with correct input" << endl;
        return;
    }

    // go through the links to search for the name and remove each node that satisfies the name
    bool found = false;
    DomesticStudentPtr currentDomStuPtr = this->head;
    while (currentDomStuPtr != NULL) {
        if ((currentDomStuPtr->getFirstName() == firstName) && (currentDomStuPtr->getLastName() == lastName)) {
            remove_node(currentDomStuPtr);
            currentDomStuPtr = currentDomStuPtr->getLink();
            found = true;
        }
        else {
            currentDomStuPtr = currentDomStuPtr->getLink();
        }
    }

    // if no match is found, output this information
    if (found) {
        cout << "All matching students have been deleted" << endl;
    }
    else {
        cout << "No match found!" << endl;
    }
}

// END OF DOMESTIC STUDENT LINKED LIST -------------------------------------------------------------------


// INTERNATIONAL STUDENT LINKED LIST ---------------------------------------------------------------------

InternationalStudentPtr IntStuLinkedList::getTail() const{
    return tail;
}
void IntStuLinkedList::updateTail(){
    if (head != NULL){
        InternationalStudentPtr temporary = head;
        while (temporary->getLink() != NULL){
            temporary = temporary->getLink();
        }
        tail = temporary;
    }
    else{
        tail = NULL;
    }
}
IntStuLinkedList::IntStuLinkedList(){
    head = NULL;
    tail = NULL;
}
IntStuLinkedList::IntStuLinkedList(const IntStuLinkedList& LL){
    InternationalStudentPtr temp = LL.head;
    while (temp != NULL)
    {
        InternationalStudent temp1;
        temp1.setFirstName(LL.head->getFirstName());
        temp1.setLastName(LL.head->getLastName());
        temp1.setCGPA(LL.head->getCGPA());
        temp1.setResearchScore(LL.head->getResearchScore());
        temp1.setApplicationID(LL.head->getApplicationID());
        temp1.setHomeCountry(LL.head->getHomeCountry());
        temp1.setTOEFL(LL.head->getTOEFL().getReadingScore(), LL.head->getTOEFL().getListeningScore(), LL.head->getTOEFL().getSpeakingScore(), LL.head->getTOEFL().getWritingScore());
     
        tail_insert(temp1);
        temp = temp->getLink();
    }
    updateTail();
}
IntStuLinkedList::~IntStuLinkedList(){
    InternationalStudentPtr temp;
    //cout << "Deleting with IntStuLinkedList's Destructor" << endl;
    while (head != NULL)
    {
        temp = head;
        head = head->getLink();
        delete temp;
    }
}

InternationalStudentPtr IntStuLinkedList::getHead() const{
    InternationalStudentPtr temp = head;
    return temp;
}
void IntStuLinkedList::setHead(InternationalStudentPtr& stuPtr){
    head = stuPtr;
}

IntStuLinkedList& IntStuLinkedList::operator= (const IntStuLinkedList& LL){
    if (this == &LL)
        return *this;
    else{
        this->~IntStuLinkedList();
        InternationalStudentPtr temp = LL.head;
        while (temp != NULL){
            InternationalStudent temp1;
            temp1.setFirstName(LL.head->getFirstName());
            temp1.setLastName(LL.head->getLastName());
            temp1.setCGPA(LL.head->getCGPA());
            temp1.setResearchScore(LL.head->getResearchScore());
            temp1.setApplicationID(LL.head->getApplicationID());
            temp1.setHomeCountry(LL.head->getHomeCountry());
            temp1.setTOEFL(LL.head->getTOEFL().getReadingScore(), LL.head->getTOEFL().getListeningScore(), LL.head->getTOEFL().getSpeakingScore(), LL.head->getTOEFL().getWritingScore());
     
            tail_insert(temp1);
            temp = temp->getLink();
        }
        updateTail();
    }
    return *this;
}
void IntStuLinkedList::head_insert(const InternationalStudent& stu){
    try {
        InternationalStudentPtr n = new InternationalStudent(stu.getFirstName(), stu.getLastName(), stu.getCGPA(), stu.getResearchScore(), stu.getApplicationID(), stu.getHomeCountry(), stu.getTOEFL());
        n->setLink(head);
        head = n;
        updateTail();
    }
    catch(exception e) {
        cout << "exception thrown! Memory could not be allocated!" << endl;
        cout << e.what() << endl;
        exit(1);
    }
    
}
InternationalStudentPtr IntStuLinkedList::search_node(const InternationalStudent& stu) const{
    InternationalStudentPtr temp = head;
    while (temp != NULL)
    {
        if (temp->getFirstName() == stu.getFirstName() && temp->getLastName() == stu.getLastName() && temp->getCGPA() == stu.getCGPA() && temp->getResearchScore() == stu.getResearchScore() && temp->getApplicationID() == stu.getApplicationID() && temp->getHomeCountry() == stu.getHomeCountry())
            return temp;
        else
            temp = temp->getLink();
    }
    return NULL;
}
void IntStuLinkedList::insert_after(const InternationalStudentPtr& n, const InternationalStudent& stu){
    if (n == NULL)
        return;
    else{
        try{
            InternationalStudentPtr temp = new InternationalStudent(stu.getFirstName(), stu.getLastName(), stu.getCGPA(), stu.getResearchScore(), stu.getApplicationID(), stu.getHomeCountry(), stu.getTOEFL());
            temp->setLink(n->getLink());
            n->setLink(temp);
            updateTail();
        }
        catch (exception e) {
            cout << "exception thrown! Memory could not be allocated!" << endl;
            cout << e.what() << endl;
            exit(1);
        }
    }
}
void IntStuLinkedList::remove_node(const InternationalStudentPtr& stuPtr){
    if (head == NULL || stuPtr == NULL)
        return;
    else if (head == stuPtr){
        head = head->getLink();
        delete stuPtr;
        return;
    }
    else{
        InternationalStudentPtr temp = head;
        while(temp != NULL){
            if (temp->getLink() == stuPtr){
                temp->setLink(stuPtr->getLink());
                delete stuPtr;
                return;
            }
            temp = temp->getLink();
        }
        updateTail();
    }
}
void IntStuLinkedList::remove_node(const InternationalStudent& stu){
    InternationalStudentPtr temp = search_node(stu);
    remove_node(temp);
}
void IntStuLinkedList::remove_all(const InternationalStudent& stu){
    InternationalStudentPtr temp;
    do
    {
        temp = search_node(stu);
        remove_node(temp);
    } while (temp != NULL);
}
void IntStuLinkedList::tail_insert(const InternationalStudent& stu){
    if (head == NULL)
    {
        head_insert(stu);
        return;
    }
    else
    {
        InternationalStudentPtr temp = head;
        while (temp->getLink() != NULL)
            temp = temp->getLink();
        insert_after(temp, stu);
    }
}
void IntStuLinkedList::insert_before(const InternationalStudentPtr& stuPtr, const InternationalStudent& stu){
        if (head == NULL){
        if (stuPtr == NULL)
            head_insert(stu);
        else
            cout << "Warning: Insertion failed. Wrong node argument." << endl;
        return;
    }
    else if(head != NULL){
        if (stuPtr == NULL)
            tail_insert(stu);
        else if(head == stuPtr)
            head_insert(stu);
        else if(search_node(*stuPtr) == NULL)
            cout << "Warning: Insertion failed. Wrong node argument." << endl;
        else{
            InternationalStudentPtr temp = head;
            while (temp->getLink() != stuPtr)
                temp = temp->getLink();
            insert_after(temp, stu);
        }
    }
}
ostream& operator<< (ostream& out, const IntStuLinkedList& LL){
    InternationalStudentPtr temp = LL.head;
    while(temp != NULL){
        out << *temp;
        temp = temp->getLink();
    }
    return out;
}
void IntStuLinkedList::insert_overallSorted(const InternationalStudent& stu){
    if (head == NULL){
        head_insert(stu);
        //cout << "I was here" << endl;
        return;
    }
    else{
        InternationalStudentPtr temp = head;
        while (temp != NULL)
        {
            if (temp->getResearchScore() < stu.getResearchScore())
                break;
            else if((temp->getResearchScore() == stu.getResearchScore()) && temp->getCGPA() < stu.getCGPA())
                break;
            else if((temp->getResearchScore() == stu.getResearchScore()) && (temp->getCGPA() == stu.getCGPA()) && (temp->getHomeCountry() > stu.getHomeCountry()))
                break;
            else
                temp = temp->getLink();
        }
        insert_before(temp, stu);
    }
}

void IntStuLinkedList::searchByName(string firstName, string lastName) {
    // Precondition: requires a first name and a last name to search the linked list for a matching object with that name
    // Post-condition: if a match is found, all matches are printed out. If no match is found, this information will also be printed out

    //cout << "searchByName has been called for " << firstName << lastName << endl;
    
    // input checking/control
    try {
        toTitleCase(firstName);
        toTitleCase(lastName);
    }
    catch (...) {
        throw invalid_argument( "Error! Cannot use the name input! Please try the program again");
    }

    // go through the links to search for the name and print out each node that satisfies the name
    InternationalStudentPtr currentIntStuPtr = this->head;
    bool found = false;
    cout << "Searching..." << endl << endl;
    while (currentIntStuPtr != NULL) {
        if ((currentIntStuPtr->getFirstName() == firstName) && (currentIntStuPtr->getLastName() == lastName)) {
            cout << *currentIntStuPtr << endl;
            currentIntStuPtr = currentIntStuPtr->getLink();
            found = true;
        }
        else {
            currentIntStuPtr = currentIntStuPtr->getLink();
        }
    }

    // if no match is found, print out this information
    if (!found) {
        cout << "No match was found!" << endl;
    }

}

void IntStuLinkedList::searchByApplicationID(int applicationID) {
    // Pre-condition: requires an application ID that is 8 digits and starts at 20210000
    // Post-condition: if a match is found, all matches are printed out. IF no match is found, this information is printed out

    // cout << "searchByApplicationID has been called for " << applicationID << endl;

    bool found = false;
    // go through the links to search for the application ID, print out each node that satisfies the ID
    cout << "Searching..." << endl << endl;
    InternationalStudentPtr currentIntStuPtr = this->head;
    while (currentIntStuPtr != NULL) {
        if ( (currentIntStuPtr->getApplicationID() == applicationID) ) {
            // a match was found
            cout << *currentIntStuPtr << endl;
            currentIntStuPtr = currentIntStuPtr->getLink();
            found = true;
        }
        else {
            currentIntStuPtr = currentIntStuPtr->getLink();
        }
    }
    
    // if found is still false, no match has been found
    if (!found) {
        cout << "No match found!" << endl;
    }
}

void IntStuLinkedList::searchByCGPA(float CGPA) {
    // Pre-condition: requires a float CGPA rounded to a single digit
    // Post-condition: if a match is found, all matches are printed out. If no match is found, this information is printed out

    //cout << "searchByCGPA has been called for " << CGPA << endl;

    bool found = false;
    // go through the links to search for the CGPA, print out each node that satisfies the CGPA
    cout << "Searching..." << endl << endl;
    InternationalStudentPtr currentIntStuPtr = this->head;
    while (currentIntStuPtr != NULL) {
        if ( fabs(currentIntStuPtr->getCGPA()-CGPA) < FLT_EPSILON ) { // floating point arithmetic is almost never exact!
            // a match was found
            cout << *currentIntStuPtr << endl;
            currentIntStuPtr = currentIntStuPtr->getLink();
            found = true;
        }
        else {
            currentIntStuPtr = currentIntStuPtr->getLink();
        }
    }
    
    // if found is still false, no match has been found
    if (!found) {
        cout << "No match found!" << endl;
    }
}

void IntStuLinkedList::searchByResearchScore(int researchScore) {
    // Pre-condition: requires an int research Score
    // Post-condition: if a match is found, all matches are printed out. If no match is found, this information is printed out

    //cout << "searchByResearchScore has been called for " << researchScore << endl;

    bool found = false;
    // go through the links to search for the research score, print out each node that satisfies the score
    cout << "Searching..." << endl << endl;
    InternationalStudentPtr currentIntStuPtr = this->head;
    while (currentIntStuPtr != NULL) {
        if ( currentIntStuPtr->getResearchScore() == researchScore ) {
            // a match was found
            cout << *currentIntStuPtr << endl;
            currentIntStuPtr = currentIntStuPtr->getLink();
            found = true;
        }
        else {
            currentIntStuPtr = currentIntStuPtr->getLink();
        }
    }
    
    // if found is still false, no match has been found
    if (!found) {
        cout << "No match found!" << endl;
    }
}

void IntStuLinkedList::deleteByName(string firstName, string lastName) {
    // Pre-condition: requires a first name and a last name to search the linked list and delete a matching object with that name
    // Post-condition: If a match is found, all matches are deleted. If no match is found, this information is printed out
    
    // input checking/control
    try {
        toTitleCase(firstName);
        toTitleCase(lastName);
    }
    catch (...) {
        cout << "Please try again with correct input" << endl;
        return;
    }

    // go through the links to search for the name and remove each node that satisfies the name
    bool found = false;
    InternationalStudentPtr currentIntStuPtr = this->head;
    while (currentIntStuPtr != NULL) {
        if ((currentIntStuPtr->getFirstName() == firstName) && (currentIntStuPtr->getLastName() == lastName)) {
            remove_node(currentIntStuPtr);
            currentIntStuPtr = currentIntStuPtr->getLink();
            found = true;
        }
        else {
            currentIntStuPtr = currentIntStuPtr->getLink();
        }
    }

    // if no match is found, output this information
    if (found) {
        cout << "All matching students have been deleted" << endl;
    }
    else {
        cout << "No match found!" << endl;
    }
}

void IntStuLinkedList::deleteHeadAndTail() {
    remove_node(head);
    remove_node(tail);
}

// END OF INTERNATIONAL STUDENT LINKED LIST ----------------------------------------------------------------------

// EXTERNAL HELPER FUNCTIONS ----------------------------------------------------------------------------

StuLinkedList mergeStuLinkedList(DomStuLinkedList& oldDomStu, IntStuLinkedList& oldIntStu) {
    // Precondition: takes in a domestic student linked list and an international student linked list
    // Postcondition: returns a merged student linked list

    StuLinkedList stuLL;
    DomesticStudentPtr temp1 = oldDomStu.getHead();
    InternationalStudentPtr temp2 = oldIntStu.getHead();
    int countstudent = 0;
    while (temp1 != NULL)
    {
        stuLL.insert_ptrObj(temp1);
        temp1 = temp1->getLink();
        countstudent++;
    }
    while (temp2 != NULL)
    {
        stuLL.insert_ptrObj(temp2);
        temp2 = temp2->getLink();
        countstudent++;
    }
    stuLL.selectionSort();
    return stuLL;
}