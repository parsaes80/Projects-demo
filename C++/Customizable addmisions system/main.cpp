//main.cpp, put your driver code here, 
//you can manipulate your class objects here
#include <iostream> //cin and cout
#include <fstream> //file processing
#include <sstream> //formatted string processing
#include <cstdlib> //atof and atoi
#include <string>
#include "student.hpp"
#include "studentList.hpp"

using namespace std;


// menu for domestic
void domestic_sort_menu(DomStuLinkedList& domStuLinkedList) {
    cout << "\n\t\t---Please select one of the following options to search the data---" << endl;
    cout << "1. Search by Name" << endl;
    cout << "2. Search by Application ID" << endl;
    cout << "3. Search by CGPA" << endl;
    cout << "4. Search by Research Score" << endl;
    cout << "5. Create new Domestic Student" << endl;
    cout << "6. Delete a Domestic Student from the list" << endl;
    cout << "7. Delete Head and Tail pointer" << endl;

    string inputFirstName,  inputLastName;
    int inputApplicationID;
    float inputCGPA;
    int inputResearchScore;

    int opt = 0;
    cin >> opt;
    switch (opt) {
    case 1: {
        // search by name
        cout << "Please enter the full name of who you'd like to search for: " << endl;
        cin >> inputFirstName >> inputLastName;

        try {
            toTitleCase(inputFirstName);
            toTitleCase(inputLastName);
        }
        catch (std::exception e) {
            std::cout << "uh oh! please enter a valid name" << endl;
            std::cout << e.what() << endl;
        }
        cout << "---------------------------------------" << endl;
        domStuLinkedList.searchByName(inputFirstName,inputLastName);
        cout << "---------------------------------------" << endl;
        break;
    }
    case 2: {
        // search by application ID
        cout << "Please enter the application ID you'd like to search for: " << endl;
        try {
            cin >> inputApplicationID;
        }
        catch (...) {
            cout << "Please try again with an 8 digit application ID, starting at 20210000" << endl;
            break;
        }
        cout << "---------------------------------------" << endl;
        domStuLinkedList.searchByApplicationID(inputApplicationID);
        cout << "---------------------------------------" << endl;
        break;
    }
    case 3: {
        // search by CGPA
        cout << "Please enter the CGPA you'd like to search for: " << endl;

        try {
            cin >> inputCGPA;
        }
        catch (...) {
            cout << "Please try again with a proper input for CGPA" << endl;
            break;
        }
        cout << "---------------------------------------" << endl;
        domStuLinkedList.searchByCGPA(inputCGPA);
        cout << "---------------------------------------" << endl;
        break;
    }
    case 4: {
        // search by research score
        cout << "Please enter the research score you'd like to search based off of: " << endl;
        try {
            cin >> inputResearchScore;
        }
        catch (...) {
            cout << "Please try again with proper research score input" << endl;
            break;
        }
        cout << "---------------------------------------" << endl;
        domStuLinkedList.searchByResearchScore(inputResearchScore);
        cout << "---------------------------------------" << endl;
        break;
    }
    case 5: {
        // create new domestic student and add this to domestic student linked list
        cout << "Please enter the first name of the new student: ";
        string firstName,lastName;
        try {
            cin >> firstName;
        }
        catch (exception e) {
            cout << "please enter a valid string" << endl;
            cout << e.what() << endl;
            break;
        }
        cout << "Please enter the last name of the new student: ";
        try {
            cin >> lastName;
        }
        catch (exception e) {
            cout << "Please enter a valid string" << endl;
            cout << e.what() << endl;
            break;
        }

        // make first and last names Titlecase
        try {
            toTitleCase(firstName);
            toTitleCase(lastName);
        }
        catch (exception e) {
            cout << "Invalid input!" << endl;
            cout << e.what() << endl;
            break;
        }

        // get CGPA information
        cout << "What is this student's CGPA? (0.0-4.3) ";
        float CGPA;
        try {
            cin >> CGPA;
        }
        catch (exception e) {
            cout << "Please enter a valid CGPA" << endl;
            cout << e.what() << endl;
            break;
        }
        
        // get research Score information
        int researchScore;
        cout << "What is this student's research Score? (0-100) ";
        try {
            cin >> researchScore;
        }
        catch(exception e) {
            cout << "only integers are allowed for research score" << endl;
            cout << e.what() << endl;
            break;
        }

        // get application ID information
        long unsigned int applicationID; 
        cout << "What is this student's application ID? (8 digit number starting at 20210000) ";
        try {
            cin >> applicationID;
        }
        catch (exception e) {
            cout << "Please enter a valid ID" << endl;
            cout << e.what() << endl;
            break;
        }

        // get home province information
        string homeProvince;
        cout << "What is this student's home province? ";
        try {
            cin >> homeProvince;
        }
        catch (exception e) {
            cout << "invalid string, please try again with valid input" << endl;
            cout << e.what() << endl;
            break;
        }

        // check if proper province input
        if (isProvince(homeProvince)) {
            // do nothing
        }
        else {
            cout << "Error! this province input is invalid! Returning to beginning..." << endl;
            break;
        }

        // make student object and insert into linked list 
        DomesticStudent newDomStu(firstName,lastName,CGPA,researchScore,applicationID,homeProvince);
        domStuLinkedList.insert_overallSorted(newDomStu);
        break;
    }
    case 6: {
        // delete a student based on firstName and lastName

        // get name
        string firstName, lastName;
        cout << "Please enter the first name of the student you'd like to delete from the list: ";
        try {
            cin >> firstName;
        }
        catch (exception e) {
            cout << "error! please enter a valid first name!" << endl;
            cout << e.what() << endl;
            break;
        }
        cout << "Now please enter the last name: ";
        try {
            cin >> lastName;
        }
        catch (exception e) {
            cout << "error! Please enter a valid last name!" << endl;
            cout << e.what() << endl;
            break;
        }

        domStuLinkedList.deleteByName(firstName,lastName);
        break;
    }
    case 7: {
        // delete head and tail pointer
        domStuLinkedList.deleteHeadAndTail();
        cout << "The linked list head and tail have been deleted" << endl;
        break;
    }
    default: {
        cout << "\a\aInvalid choice\n";
        break;
    }
  }
}

// menu for international
void international_sort_menu(IntStuLinkedList& intStuLinkedList) {
    cout << "\n\t---Please select one of the following options---" << endl;
    cout << "1. Search by Name " << endl;
    cout << "2. Search by Application ID" << endl;
    cout << "3. Search by CGPA" << endl;
    cout << "4. Search by Research Score" << endl;
    cout << "5. Create new International student" << endl;
    cout << "6. Delete an international student from the list" << endl;
    cout << "7. Delete Head and Tail Pointer" << endl;

    string inputFirstName, inputLastName;
    int inputApplicationID;
    float inputCGPA;
    int inputResearchScore;

    int opt = 0;
    cin >> opt;
    switch (opt) {
    case 1: {
        // search by name
        cout << "Please enter the full name of who you'd like to search for: " << endl;
        cin >> inputFirstName >> inputLastName;

        try {
            toTitleCase(inputFirstName);
            toTitleCase(inputLastName);
        }
        catch (std::exception e) {
            std::cerr << "uh oh! please enter a valid name" << endl;
            std::cerr << e.what() << endl;
            break;
        }
        cout << "---------------------------------------" << endl;
        intStuLinkedList.searchByName(inputFirstName,inputLastName);
        cout << "---------------------------------------" << endl;
        break;
    }
    case 2: {
        // search by application ID
        cout << "Please enter the application ID you'd like to search for: " << endl;
        try {
            cin >> inputApplicationID;
        }
        catch (...) {
            cout << "Please try again with an 8 digit application ID, starting at 20210000" << endl;
            break;
        }
        cout << "---------------------------------------" << endl;
        intStuLinkedList.searchByApplicationID(inputApplicationID);
        cout << "---------------------------------------" << endl;
        break;
    }
    case 3: {
        // search by CGPA
        cout << "Please enter the CGPA you'd like to search for: " << endl;

        try {
            cin >> inputCGPA;
        }
        catch (...) {
            cout << "Please try again with a proper input for CGPA" << endl;
            break;
        }
        cout << "---------------------------------------" << endl;
        intStuLinkedList.searchByCGPA(inputCGPA);
        cout << "---------------------------------------" << endl;

        break;
    }
    case 4: {
        // search by research score
        cout << "Please enter the research score you'd like to search based off of: " << endl;
        try {
            cin >> inputResearchScore;
        }
        catch (...) {
            cout << "Please try again with proper research score input" << endl;
            break;
        }
        cout << "---------------------------------------" << endl;
        intStuLinkedList.searchByResearchScore(inputResearchScore);
        cout << "---------------------------------------" << endl;
        break;
    }
    case 5: {
        // create a new international student and put this into the international student linked list
        cout << "Please enter the first name of the new student: ";
        string firstName,lastName;
        try {
            cin >> firstName;
        }
        catch (exception e) {
            cout << "please enter a valid string" << endl;
            cout << e.what() << endl;
            break;
        }
        cout << "Please enter the last name of the new student: ";
        try {
            cin >> lastName;
        }
        catch (exception e) {
            cout << "Please enter a valid string" << endl;
            cout << e.what() << endl;
            break;
        }

        // make first and last names Titlecase
        try {
            toTitleCase(firstName);
            toTitleCase(lastName);
        }
        catch (exception e) {
            cout << "Invalid input!" << endl;
            cout << e.what() << endl;
            break;
        }

        // get CGPA information
        cout << "What is this student's CGPA? (0.0-4.3) ";
        float CGPA;
        try {
            cin >> CGPA;
        }
        catch (exception e) {
            cout << "Please enter a valid CGPA" << endl;
            cout << e.what() << endl;
            break;
        }
        
        // get research Score information
        int researchScore;
        cout << "What is this student's research Score? (0-100) ";
        try {
            cin >> researchScore;
        }
        catch(exception e) {
            cout << "only integers are allowed for research score" << endl;
            cout << e.what() << endl;
            break;
        }

        // get application ID information
        long unsigned int applicationID; 
        cout << "What is this student's application ID? (8 digit number starting at 20210000) ";
        try {
            cin >> applicationID;
        }
        catch (exception e) {
            cout << "Please enter a valid ID" << endl;
            cout << e.what() << endl;
            break;
        }

        // get home Country information
        string homeCountry;
        cout << "What is this student's home country? ";
        try {
            cin >> homeCountry;
        }
        catch (exception e) {
            cout << "invalid string, please try again with valid input" << endl;
            cout << e.what() << endl;
            break;
        }
        
        // check if country field is valid
        if (isCountry(homeCountry)) {
            // do nothing
        }
        else {
            cout << "This country entry is invalid! Please try again with proper country entry! Returning to beginning..." << endl;
            break;
        }

        // get TOEFL information
        int readingScore, listeningScore, speakingScore, writingScore;
        cout << "Now for collecting TOEFL information:" << endl;
        cout << "please student's reading Score, listening score, speaking score, and writing score, in that order, separated by a space: ";
        try {
            cin >> readingScore >> listeningScore >> speakingScore >> writingScore;
        }
        catch(exception e) {
            cout << "Error! Please put in proper input next time!" << endl;
            cout << e.what() << endl;
            break;
        }
        ToeflScore TOEFL(readingScore,listeningScore,speakingScore,writingScore);

        // make student object and insert into linked list 
        InternationalStudent newIntStu(firstName,lastName,CGPA,researchScore,applicationID,homeCountry,TOEFL);
        intStuLinkedList.insert_overallSorted(newIntStu);
        break;
    }
    case 6: {
        // delete a student based on firstName and lastName

        // get name
        string firstName, lastName;
        cout << "Please enter the first name of the student you'd like to delete from the list: ";
        try {
            cin >> firstName;
        }
        catch (exception e) {
            cout << "error! please enter a valid first name!" << endl;
            cout << e.what() << endl;
            break;
        }
        cout << "Now please enter the last name: ";
        try {
            cin >> lastName;
        }
        catch (exception e) {
            cout << "error! Please enter a valid last name!" << endl;
            cout << e.what() << endl;
            break;
        }

        intStuLinkedList.deleteByName(firstName,lastName);

        break;
    }
    case 7: {
        // delete head and tail pointer
        intStuLinkedList.deleteHeadAndTail();
        cout << "The linked list head and tail have been deleted" << endl;
        break;
    }
    default: {
        cout << "\a\aInvalid choice\n";
        break;
    }
  }
}

// main menu
void sort_menu( DomStuLinkedList& domStuLinkedList, IntStuLinkedList& intStuLinkedList){
    cout << "\n\n\t\t****Please select one of the following option to manipulate and view the data****" << endl;
    cout << "1. Domestic Student" << endl;
    cout << "2. International Student" << endl;
    cout << "3. Merge Domestic Student Linked List and International Student Linked List" << endl;
    cout << "4. Search student objects in merged linked list based on CGPA and research threshold" << endl;

    int opt = 0;
    try {
        cin >> opt;
    }
    catch (std::exception e) {
        cerr << "Invalid choice, please try again with proper input" << endl;
        cerr << e.what() << endl;
        return;
    }
    switch (opt) {
    case 1: {
        domestic_sort_menu(domStuLinkedList);
        break;
    }
    case 2: {
        international_sort_menu(intStuLinkedList);
        break;
    }
    case 3: {
        // Merge Domestic Student linked list and international student linked list
        StuLinkedList newStuLL = mergeStuLinkedList(domStuLinkedList,intStuLinkedList);
        cout << "List has been successfully merged: " << endl;
        cout << "---------------------------------------" << endl;
        cout << newStuLL << endl;
        cout << "---------------------------------------" << endl;
        break;
    }
    case 4: {
        // merge linked lists first
        StuLinkedList newStuLL = mergeStuLinkedList(domStuLinkedList,intStuLinkedList);

        // search student objects in merged linked list based on CGPA and research threshold
        float CGPA;
        int researchScore;

        cout << "Please enter the CGPA threshold you'd like for your search (0.0-4.3): ";
        try {
            cin >> CGPA;
        }
        catch (...) {
            cout << "Please enter proper input for CGPA! returning to beginning..." << endl;
            break;
        }
        cout << "Please enter the research Score threshold you'd like for your search (0-100): ";
        try {
            cin >> researchScore;
        }
        catch (...) {
            cout << "Please enter proper input for research score! Returning to beginning..." << endl;
            break;
        }
        cout << "Printing all matches: " << endl;
        cout << "---------------------------------------------------" << endl;
        newStuLL.printThreshold(researchScore,CGPA);
        cout << "---------------------------------------------------" << endl;
        break;
    }
    default: {
        cout << "\a\aInvalid choice, please try again.\n";
        break;
    }
    }
}

// driver program
int main() {
    IntStuLinkedList myIntStu;
    IntStuLinkedList myIntDropStu;
    DomStuLinkedList myDomStu;

    int APPLICATION_ID_BASE = 20210000;
    cout.precision(2); // for all CGPA results

    //Read the domestic-stu.txt file and exit if failed
    string line;

    ifstream domesticFile("domestic-stu.txt");
    if (!domesticFile.is_open()) {
        cout << "Unable to open file domestic-stu.txt" << endl;
        return -1;
    }

    //Read the first line of domestic-stu.txt, which specifies
    //the file format. And then print it out to the screen
    getline(domesticFile, line);
    cout << "File format: " << line << endl;

    /*Keep reading the rest of the lines in domestic-stu.txt.
     *In the example code here, I will read each data separated
     *by a comma, and then print it out to the screen.
     *In your lab assignment 1, you should use these read data
     *to initialize your DomesticStudent object. Then you can
     *use get and set functions to manipulate your object, and
     *print the object content to the screen
     */
    int stu_count = 0;
    while (getline(domesticFile, line)) {
        /*process each line, get each field separated by a comma.
         *We use istringstream to handle it.
         *Note in this example code here, we assume the file format
         *is perfect and do NOT handle error cases. We will leave the
         *error and exception handling of file format to Lab Assignment 4
         */
        istringstream ss(line);

        string firstName, lastName, province, s_cgpa, s_researchScore;
        double cgpa;
        int researchScore;

        // make sure all fields are read from file
        try {
            //get firstName separated by comma
            getline(ss, firstName, ',');

            //get lastName separated by comma
            getline(ss, lastName, ',');

            //get province separated by comma
            getline(ss, province, ',');

            // confirm proper province input
            if (isProvince(province)) {
                // do nothing
            }
            else {
                cout << "Error! Please the province field is invalid! Exiting program..." << endl;
                exit(1);
            }

            //get cpga separated by comma, and convert string to double
            getline(ss, s_cgpa, ',');
            cgpa = atof(s_cgpa.c_str());

            //get researchScore separated by comma, and convert it to int
            getline(ss, s_researchScore, ',');
            researchScore = atoi(s_researchScore.c_str());
        }
        catch (exception e) {
            cout << "Error! A field is missing from the text file" << endl;
            cout << e.what() << endl;
            exit(1);
        }

        DomesticStudent myTempStu;
        myTempStu.setFirstName(firstName);
        myTempStu.setLastName(lastName);
        myTempStu.setHomeProvince(province);
        myTempStu.setCGPA(cgpa);
        myTempStu.setResearchScore(researchScore);
        myTempStu.setApplicationID(APPLICATION_ID_BASE + stu_count);
        myDomStu.insert_overallSorted(myTempStu);

        stu_count++;
    }

    //close your file
    domesticFile.close();
    
    //Read the domestic-stu.txt file and exit if failed

    //string line;
    ifstream internationalFile("international-stu.txt");
    if (!internationalFile.is_open()) {
        cout << "Unable to open file international-stu.txt" << endl;
        return -1;
    }

    getline(internationalFile, line);
    cout << "File format: " << line << endl;

    int stu_count2 = 0;
    int dropStu_count2 = 0;
    int intstu_count2 = 0;
    while (getline(internationalFile, line)) {
        istringstream ss(line);

        string firstName, lastName, country, s_cgpa, s_researchScore, s_reading, s_listening, s_speaking, s_writing;
        double cgpa;
        int researchScore, reading, listening, speaking, writing;

        // make sure all fields are present in file
        try {
            //get firstName separated by comma
            getline(ss, firstName, ',');

            //get lastName separated by comma
            getline(ss, lastName, ',');

            //get country separated by comma
            getline(ss, country, ',');

            // "idia" typo from pdf requirement
            if (country == "Idian") {
                cout << "Warning! A typo has been found spelling 'Idian' instead of 'India', now correcting to proper spelling.." << endl;
                country = "India";
            }
            else {
                // do nothing
            }
            // check if proper country
            if (isCountry(country)) {
                // do nothing
            }
            else {
                cout << "invalid country data in the text file! exiting program..." << endl;
                exit(1);
            }

            //get cpga separated by comma, and convert string to double
            getline(ss, s_cgpa, ',');
            cgpa = atof(s_cgpa.c_str());

            //get researchScore separated by comma, and convert it to int
            getline(ss, s_researchScore, ',');
            researchScore = atoi(s_researchScore.c_str());

            getline(ss, s_reading, ',');
            reading = atoi(s_reading.c_str());

            getline(ss, s_listening, ',');
            listening = atoi(s_listening.c_str());

            getline(ss, s_speaking, ',');
            speaking = atoi(s_speaking.c_str());

            getline(ss, s_writing, ',');
            writing = atoi(s_writing.c_str());
        }
        catch (exception e) {
            cout << "Error! A field is missing!" << endl;
            cout << e.what() << endl;
            exit(1);
        }

        InternationalStudent myTempStu;
        myTempStu.setFirstName(firstName);
        myTempStu.setLastName(lastName);
        myTempStu.setHomeCountry(country);
        myTempStu.setCGPA(cgpa);
        myTempStu.setResearchScore(researchScore);
        myTempStu.setTOEFL(reading, listening, speaking, writing);
        myTempStu.setApplicationID(APPLICATION_ID_BASE + stu_count + stu_count2);

        if (myTempStu.getTOEFL().getTotalScore() < 93 || myTempStu.getTOEFL().getWritingScore() < 20 || myTempStu.getTOEFL().getReadingScore() < 20 || myTempStu.getTOEFL().getSpeakingScore() < 20 || myTempStu.getTOEFL().getListeningScore() < 20)
            {
                myIntDropStu.insert_overallSorted(myTempStu);
                dropStu_count2++;
            }
        else{
            myIntStu.insert_overallSorted(myTempStu);
            intstu_count2++;
        }
        stu_count2++;
    }
    //close your file
    internationalFile.close();

    // after reading and storing file data, let's go to menu
    bool active = true;
    while (active) {
        try {
            sort_menu(myDomStu, myIntStu);
        }
        catch (...) {
            cout << "Invalid user input, please run program again" << endl;
            break;
        }

        // clear input buffer
        cin.ignore(1000,'\n');
        // get user feedback on whether program should continue
        cout << "Would you like to go again? (Y/N)" << endl;
        string userInput;
        cin >> userInput;
        if (userInput == "Y" || userInput == "y") {
            active = true;
        }
        else if (userInput == "N" || userInput == "n") {
            cout << "Now exiting program..." << endl;
            active = false;
        }
        else {
            cout << "Invalid user input, please run program again" << endl;
            active = false;
        }
    }

    /*
    // print out linked lists as tests
    cout << myDomStu << endl;
    //cout << *(myDomStu.getHead()) << endl << *(myDomStu.getTail()) << endl;
    cout << myIntStu << endl;
    //cout << *(myIntStu.getHead()) << endl << *(myIntStu.getTail()) << endl;
    //cout << myIntDropStu << endl;
    */

    
    return 0;
}

