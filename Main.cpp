#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

// The Date class was created to hold the date of birth and appointment of employees.
class Date {
private:
    string date;
public:
    string getDate() { return date; };
    void setDate(string date) { this->date = date; };
    // Parsing the Date for obtaining Day
    int getDay(){
        size_t start;
        size_t end = 0;
        vector <string> tokens;
        string delim = "-";
        while ((start = date.find_first_not_of(delim, end)) != string::npos){
            end = date.find(delim, start);
            tokens.push_back(date.substr(start, end - start));
        }
        return stoi(tokens[0]);
    }
    // Parsing the Date for obtaining Month
    int getMonth(){
        size_t start;
        size_t end = 0;
        vector <string> tokens;
        string delim = "-";
        while ((start = date.find_first_not_of(delim, end)) != string::npos){
            end = date.find(delim, start);
            tokens.push_back(date.substr(start, end - start));
        }
        return stoi(tokens[1]);
    }
    // Parsing the Date for obtaining Year
    int getYear(){
        size_t start;
        size_t end = 0;
        vector <string> tokens;
        string delim = "-";
        while ((start = date.find_first_not_of(delim, end)) != string::npos){
            end = date.find(delim, start);
            tokens.push_back(date.substr(start, end - start));
        }
        return stoi(tokens[2]);
    }
};

// The Employee class was created to hold all employees.
class Employee {
    // Attributes of employee
protected:
    int employeeNumber;
    int employeeType;
    string name;
    string surname;
    string title;
    float salaryCoefficient;
    Date dateOfBirth;
    Date dateOfAppointment;
    int lengthOfService;
    // Getter-Setter functions
public:
    int getEmployeeNumber() { return employeeNumber; };
    void setEmployeeNumber(int employeeNumber) { this->employeeNumber = employeeNumber; };

    int getEmployeeType() { return employeeType; };
    void setEmployeeType(int employeeType) { this->employeeType = employeeType; };

    string getName() { return name; };
    void setName(string name) { this->name = name; };

    string getSurname() { return surname; };
    void setSurname(string surname) { this->surname = surname; };

    string getTitle() { return title; };
    void setTitle(string title) { this->title = title; };

    float getSalaryCoefficient() { return salaryCoefficient; };
    void setSalaryCoefficient(float salaryCoefficient) { this->salaryCoefficient = salaryCoefficient; };

    Date getDateOfBirth() { return dateOfBirth; };
    void setDateOfBirth(Date dateOfBirth) { this->dateOfBirth = dateOfBirth; };

    Date getDateOfAppointment() { return dateOfAppointment; };
    void setDateOfAppointment(Date dateOfAppointment) { this->dateOfAppointment = dateOfAppointment; };

    int getLengthOfService() { return lengthOfService; };
    void setLengthOfService(int lengthOfService) { this->lengthOfService = lengthOfService; };
};

// Subclass of Employee - Only employeeType set on 0
class TemporaryEmployee : public Employee {
public:
    TemporaryEmployee(int employeeNumber, string name, string surname, string title,
             float salaryCoefficient, Date dateOfBirth, Date dateOfAppointment, int lengthOfService) {
        this->employeeNumber = employeeNumber;
        this->employeeType = 0;
        this->name = name;
        this->surname = surname;
        this->title = title;
        this->salaryCoefficient = salaryCoefficient;
        this->dateOfBirth = dateOfBirth;
        this->dateOfAppointment = dateOfAppointment;
        this->lengthOfService = lengthOfService;
    };
};

// Subclass of Employee - Only employeeType set on 1
class PermanentEmployee : public Employee {
public:
    PermanentEmployee(int employeeNumber, string name, string surname, string title,
                      float salaryCoefficient, Date dateOfBirth, Date dateOfAppointment, int lengthOfService){
        this->employeeNumber = employeeNumber;
        this->employeeType = 1;
        this->name = name;
        this->surname = surname;
        this->title = title;
        this->salaryCoefficient = salaryCoefficient;
        this->dateOfBirth = dateOfBirth;
        this->dateOfAppointment = dateOfAppointment;
        this->lengthOfService = lengthOfService;
    };
};

// CIRCULAR SINGLE LINKED LIST INITIALIZATION
struct CircularLL {
    TemporaryEmployee *TE;
    struct CircularLL *next;
};
struct CircularLL *head = NULL;
struct CircularLL *last = NULL;

// CIRCULAR LINKED LIST - INSERT (IF EMPTY)
struct CircularLL *insertCircularLL(struct CircularLL *last, TemporaryEmployee *newTE) {
    if (last != NULL) return last;
    struct CircularLL *temp = (struct CircularLL *) malloc (sizeof(struct CircularLL));
    temp->TE = newTE;
    last = temp;
    last->next = last;
    return last;
}

// CIRCULAR LINKED LIST - INSERT (IF CONTAINS EMPLOYEE)
struct CircularLL  *insertEndCircularLL(struct CircularLL *last, TemporaryEmployee *newTE){
    if (last == NULL) return insertCircularLL(last, newTE);
    struct CircularLL *temp = (struct CircularLL *) malloc(sizeof (struct CircularLL));
    temp->TE = newTE;
    temp->next = last->next;
    last->next = temp;
    last = temp;
    return last;
}

// DISPLAY ALL TEMPORARY EMPLOYEES
void displayCircularLL() {
    struct CircularLL *ptr;
    ptr = last->next;
    do {
        cout << "******************************" << "\n"
             << "Employee Number: " << ptr->TE->getEmployeeNumber()
             << "\n" << "Employee Type: " << ptr->TE->getEmployeeType() << " (Temporary)"
             << "\n" << "Name: " << ptr->TE->getName()
             << "\n" << "Surname: " << ptr->TE->getSurname()
             << "\n" << "Title: " << ptr->TE->getTitle()
             << "\n" << "Salary Coefficient: " << ptr->TE->getSalaryCoefficient()
             << "\n" << "Birth Date: " << ptr->TE->getDateOfBirth().getDate()
             << "\n" << "Appointment Date: " << ptr->TE->getDateOfAppointment().getDate()
             << "\n" << "Length of service: " << ptr->TE->getLengthOfService()
             << "\n" << "******************************"
             << endl;
        ptr = ptr->next;
    } while (ptr != last->next);
}

// SEARCH AN EMPLOYEE
void searchCLL(int en) {
    struct CircularLL *search;
    search = last->next;

    while (search != last) {
        if ( search->TE->getEmployeeNumber() == en) {
            cout << "******************************" << "\n"
                 << "Employee Number: " << search->TE->getEmployeeNumber()
                 << "\n" << "Employee Type: " << search->TE->getEmployeeType() << " (Temporary)"
                 << "\n" << "Name: " << search->TE->getName()
                 << "\n" << "Surname: " << search->TE->getSurname()
                 << "\n" << "Title: " << search->TE->getTitle()
                 << "\n" << "Salary Coefficient: " << search->TE->getSalaryCoefficient()
                 << "\n" << "Birth Date: " << search->TE->getDateOfBirth().getDate()
                 << "\n" << "Appointment Date: " << search->TE->getDateOfAppointment().getDate()
                 << "\n" << "Length of service: " << search->TE->getLengthOfService()
                 << "\n" << "******************************"
                 << endl;
        }
        search = search->next;
    }
    if (search->TE->getEmployeeNumber() == en) {
        cout << "******************************" << "\n"
             << "Employee Number: " << search->TE->getEmployeeNumber()
             << "\n" << "Employee Type: " << search->TE->getEmployeeType() << " (Temporary)"
             << "\n" << "Name: " << search->TE->getName()
             << "\n" << "Surname: " << search->TE->getSurname()
             << "\n" << "Title: " << search->TE->getTitle()
             << "\n" << "Salary Coefficient: " << search->TE->getSalaryCoefficient()
             << "\n" << "Birth Date: " << search->TE->getDateOfBirth().getDate()
             << "\n" << "Appointment Date: " << search->TE->getDateOfAppointment().getDate()
             << "\n" << "Length of service: " << search->TE->getLengthOfService()
             << "\n" << "******************************"
             << endl;
    }
}

// UPDATE AN EMPLOYEE'S TITLE AND SALARY COEFFICIENT
void updateCLL(int en){
    struct CircularLL *search;
    search = last->next;

    string title;
    float salaryCoefficient;

    while (search != last) {
        if ( search->TE->getEmployeeNumber() == en) {
            cout << "Please type the title" << endl;
            cin >> title;
            search->TE->setTitle(title);
            cout << "Please type the salary coefficient" << endl;
            cin >> salaryCoefficient;
            search->TE->setSalaryCoefficient(salaryCoefficient);
        }
        search = search->next;
    }

    if (search->TE->getEmployeeNumber() == en) {
        cout << "Please type the title" << endl;
        cin >> title;
        search->TE->setTitle(title);
        cout << "Please type the salary coefficient" << endl;
        cin >> salaryCoefficient;
        search->TE->setSalaryCoefficient(salaryCoefficient);
    }
}

// SEARCH AN EMPLOYEE ACCORDING TO APPOINTMENT YEAR
void searchYearCLL(int year){
    struct CircularLL *search;
    search = last->next;

    while (search != last) {
        if ( search->TE->getDateOfAppointment().getYear() == year) {
            cout << "******************************" << "\n"
                 << "Employee Number: " << search->TE->getEmployeeNumber()
                 << "\n" << "Employee Type: " << search->TE->getEmployeeType() << " (Temporary)"
                 << "\n" << "Name: " << search->TE->getName()
                 << "\n" << "Surname: " << search->TE->getSurname()
                 << "\n" << "Title: " << search->TE->getTitle()
                 << "\n" << "Salary Coefficient: " << search->TE->getSalaryCoefficient()
                 << "\n" << "Birth Date: " << search->TE->getDateOfBirth().getDate()
                 << "\n" << "Appointment Date: " << search->TE->getDateOfAppointment().getDate()
                 << "\n" << "Length of service: " << search->TE->getLengthOfService()
                 << "\n" << "******************************"
                 << endl;
        }
        search = search->next;
    }
    if (search->TE->getDateOfAppointment().getYear() == year) {
        cout << "******************************" << "\n"
             << "Employee Number: " << search->TE->getEmployeeNumber()
             << "\n" << "Employee Type: " << search->TE->getEmployeeType() << " (Temporary)"
             << "\n" << "Name: " << search->TE->getName()
             << "\n" << "Surname: " << search->TE->getSurname()
             << "\n" << "Title: " << search->TE->getTitle()
             << "\n" << "Salary Coefficient: " << search->TE->getSalaryCoefficient()
             << "\n" << "Birth Date: " << search->TE->getDateOfBirth().getDate()
             << "\n" << "Appointment Date: " << search->TE->getDateOfAppointment().getDate()
             << "\n" << "Length of service: " << search->TE->getLengthOfService()
             << "\n" << "******************************"
             << endl;
    }
}

// SEARCH AN EMPLOYEE THAT APPOINTED AFTER A GIVEN YEAR
void searchAfterDateCLL(string appDate){
    size_t start;
    size_t end = 0;
    vector <string> tokens;
    string delim = "-";
    while ((start = appDate.find_first_not_of(delim, end)) != string::npos){
        end = appDate.find(delim, start);
        tokens.push_back(appDate.substr(start, end - start));
    }

    struct CircularLL *search;
    search = last->next;

    while (search != last) {
        if ( search->TE->getDateOfAppointment().getYear() > stoi(tokens[2])
        ||
        ( search->TE->getDateOfAppointment().getYear() == stoi(tokens[2])
        && search->TE->getDateOfAppointment().getMonth() > stoi(tokens[1]))
        ||
        ( search->TE->getDateOfAppointment().getYear() == stoi(tokens[2])
        && search->TE->getDateOfAppointment().getMonth() == stoi(tokens[1])
        && search->TE->getDateOfAppointment().getDay() > stoi(tokens[0]))) {
            cout << "******************************" << "\n"
                 << "Employee Number: " << search->TE->getEmployeeNumber()
                 << "\n" << "Employee Type: " << search->TE->getEmployeeType() << " (Temporary)"
                 << "\n" << "Name: " << search->TE->getName()
                 << "\n" << "Surname: " << search->TE->getSurname()
                 << "\n" << "Title: " << search->TE->getTitle()
                 << "\n" << "Salary Coefficient: " << search->TE->getSalaryCoefficient()
                 << "\n" << "Birth Date: " << search->TE->getDateOfBirth().getDate()
                 << "\n" << "Appointment Date: " << search->TE->getDateOfAppointment().getDate()
                 << "\n" << "Length of service: " << search->TE->getLengthOfService()
                 << "\n" << "******************************"
                 << endl;
        }
        search = search->next;
    }
    if ( search->TE->getDateOfAppointment().getYear() > stoi(tokens[2])
         ||
         ( search->TE->getDateOfAppointment().getYear() == stoi(tokens[2])
           && search->TE->getDateOfAppointment().getMonth() > stoi(tokens[1]))
         ||
         ( search->TE->getDateOfAppointment().getYear() == stoi(tokens[2])
           && search->TE->getDateOfAppointment().getMonth() == stoi(tokens[1])
           && search->TE->getDateOfAppointment().getDay() > stoi(tokens[0]))) {
        cout << "******************************" << "\n"
             << "Employee Number: " << search->TE->getEmployeeNumber()
             << "\n" << "Employee Type: " << search->TE->getEmployeeType() << " (Temporary)"
             << "\n" << "Name: " << search->TE->getName()
             << "\n" << "Surname: " << search->TE->getSurname()
             << "\n" << "Title: " << search->TE->getTitle()
             << "\n" << "Salary Coefficient: " << search->TE->getSalaryCoefficient()
             << "\n" << "Birth Date: " << search->TE->getDateOfBirth().getDate()
             << "\n" << "Appointment Date: " << search->TE->getDateOfAppointment().getDate()
             << "\n" << "Length of service: " << search->TE->getLengthOfService()
             << "\n" << "******************************"
             << endl;
    }
}

// SEARCH AN EMPLOYEE THAT BORN BEFORE A GIVEN DATE
void searchBeforeCLL(string birthDate){
    size_t start;
    size_t end = 0;
    vector <string> tokens;
    string delim = "-";
    while ((start = birthDate.find_first_not_of(delim, end)) != string::npos){
        end = birthDate.find(delim, start);
        tokens.push_back(birthDate.substr(start, end - start));
    }

    struct CircularLL *search;
    search = last->next;

    while (search != last) {
        if ( search->TE->getDateOfBirth().getYear() < stoi(tokens[2])
             ||
             ( search->TE->getDateOfBirth().getYear() == stoi(tokens[2])
               && search->TE->getDateOfBirth().getMonth() < stoi(tokens[1]))
             ||
             ( search->TE->getDateOfBirth().getYear() == stoi(tokens[2])
               && search->TE->getDateOfBirth().getMonth() == stoi(tokens[1])
               && search->TE->getDateOfBirth().getDay() < stoi(tokens[0]))) {
            cout << "******************************" << "\n"
                 << "Employee Number: " << search->TE->getEmployeeNumber()
                 << "\n" << "Employee Type: " << search->TE->getEmployeeType() << " (Temporary)"
                 << "\n" << "Name: " << search->TE->getName()
                 << "\n" << "Surname: " << search->TE->getSurname()
                 << "\n" << "Title: " << search->TE->getTitle()
                 << "\n" << "Salary Coefficient: " << search->TE->getSalaryCoefficient()
                 << "\n" << "Birth Date: " << search->TE->getDateOfBirth().getDate()
                 << "\n" << "Appointment Date: " << search->TE->getDateOfAppointment().getDate()
                 << "\n" << "Length of service: " << search->TE->getLengthOfService()
                 << "\n" << "******************************"
                 << endl;
        }
        search = search->next;
    }
    if ( search->TE->getDateOfBirth().getYear() < stoi(tokens[2])
         ||
         ( search->TE->getDateOfBirth().getYear() == stoi(tokens[2])
           && search->TE->getDateOfBirth().getMonth() < stoi(tokens[1]))
         ||
         ( search->TE->getDateOfBirth().getYear() == stoi(tokens[2])
           && search->TE->getDateOfBirth().getMonth() == stoi(tokens[1])
           && search->TE->getDateOfBirth().getDay() < stoi(tokens[0]))) {
        cout << "******************************" << "\n"
             << "Employee Number: " << search->TE->getEmployeeNumber()
             << "\n" << "Employee Type: " << search->TE->getEmployeeType() << " (Temporary)"
             << "\n" << "Name: " << search->TE->getName()
             << "\n" << "Surname: " << search->TE->getSurname()
             << "\n" << "Title: " << search->TE->getTitle()
             << "\n" << "Salary Coefficient: " << search->TE->getSalaryCoefficient()
             << "\n" << "Birth Date: " << search->TE->getDateOfBirth().getDate()
             << "\n" << "Appointment Date: " << search->TE->getDateOfAppointment().getDate()
             << "\n" << "Length of service: " << search->TE->getLengthOfService()
             << "\n" << "******************************"
             << endl;
    }
}

// SEARCH AN EMPLOYEE THAT BORN IN A GIVEN MONTH
void searchMonthCLL(int month){
    struct CircularLL *search;
    search = last->next;

    while (search != last) {
        if ( search->TE->getDateOfBirth().getMonth() == month) {
            cout << "******************************" << "\n"
                 << "Employee Number: " << search->TE->getEmployeeNumber()
                 << "\n" << "Employee Type: " << search->TE->getEmployeeType() << " (Temporary)"
                 << "\n" << "Name: " << search->TE->getName()
                 << "\n" << "Surname: " << search->TE->getSurname()
                 << "\n" << "Title: " << search->TE->getTitle()
                 << "\n" << "Salary Coefficient: " << search->TE->getSalaryCoefficient()
                 << "\n" << "Birth Date: " << search->TE->getDateOfBirth().getDate()
                 << "\n" << "Appointment Date: " << search->TE->getDateOfAppointment().getDate()
                 << "\n" << "Length of service: " << search->TE->getLengthOfService()
                 << "\n" << "******************************"
                 << endl;
        }
        search = search->next;
    }
    if (search->TE->getDateOfBirth().getMonth() == month) {
        cout << "******************************" << "\n"
             << "Employee Number: " << search->TE->getEmployeeNumber()
             << "\n" << "Employee Type: " << search->TE->getEmployeeType() << " (Temporary)"
             << "\n" << "Name: " << search->TE->getName()
             << "\n" << "Surname: " << search->TE->getSurname()
             << "\n" << "Title: " << search->TE->getTitle()
             << "\n" << "Salary Coefficient: " << search->TE->getSalaryCoefficient()
             << "\n" << "Birth Date: " << search->TE->getDateOfBirth().getDate()
             << "\n" << "Appointment Date: " << search->TE->getDateOfAppointment().getDate()
             << "\n" << "Length of service: " << search->TE->getLengthOfService()
             << "\n" << "******************************"
             << endl;
    }
}

// SEARCH AN EMPLOYEE WITH GIVEN TITLE - This function returns an object. So we can find last assigned employee with
// given title.
CircularLL *searchTitleCLL(string title){
    struct CircularLL *search;
    struct CircularLL *temp;
    bool flag = true;
    search = last->next;

    while (search != last) {
        if ( search->TE->getTitle() == title && flag ) {
            temp = search;
            flag = false;
        }
        else if ( search->TE->getTitle() == title ) {
            if ( search->TE->getDateOfAppointment().getYear() > temp->TE->getDateOfAppointment().getYear()
            ||
            (search->TE->getDateOfAppointment().getYear() == temp->TE->getDateOfAppointment().getYear() &&
                    search->TE->getDateOfAppointment().getMonth() > temp->TE->getDateOfAppointment().getMonth())
            ||
            (search->TE->getDateOfAppointment().getYear() == temp->TE->getDateOfAppointment().getYear() &&
                    search->TE->getDateOfAppointment().getMonth() == temp->TE->getDateOfAppointment().getMonth() &&
                    search->TE->getDateOfAppointment().getDay() > temp->TE->getDateOfAppointment().getDay())
            ) {
                temp = search;
            }
        }
        search = search->next;
    }
    if (search->TE->getTitle() == title) {
        temp = search;
    }

    return temp;
}


// DOUBLE LINKED LIST INITIALIZATION
class DoubleLL {
public:
    PermanentEmployee *PE;
    DoubleLL *next;
    DoubleLL *prev;
};
DoubleLL *headDLL = NULL;

// INSERT AN EMPLOYEE TO LINKED LIST ( IF LINKED LIST IS EMPTY )
void insertDoubleLL(DoubleLL **head_ref, PermanentEmployee *newPE){
    DoubleLL *newNode = new DoubleLL();
    newNode->PE = newPE;
    newNode->next = (*head_ref);
    newNode->prev = NULL;

    if ((*head_ref) != NULL) (*head_ref)->prev = newNode;
    (*head_ref) = newNode;
}

// INSERT AN EMPLOYEE TO LINKED LIST ( IF CONTAINS EMPLOYEE )
void insertEndDoubleLL(DoubleLL **head_ref, PermanentEmployee *newPE){
    DoubleLL *newNode = new DoubleLL();
    DoubleLL *last = *head_ref;
    newNode->PE = newPE;
    newNode->next = NULL;

    if (*head_ref == NULL) {
        newNode->prev = NULL;
        *head_ref = newNode;
    }
    while ( last->next != NULL ) last = last->next;

    last->next = newNode;
    newNode->prev = last;
}

// DISPLAY ALL PERMANENT EMPLOYEES
void displayDoubleLL(DoubleLL *d){
    DoubleLL *last;
    while (d != NULL) {
        cout << "******************************" << "\n"
             << "Employee Number: " << d->PE->getEmployeeNumber()
             << "\n" << "Employee Type: " << d->PE->getEmployeeType() << " (Permanent)"
             << "\n" << "Name: " << d->PE->getName()
             << "\n" << "Surname: " << d->PE->getSurname()
             << "\n" << "Title: " << d->PE->getTitle()
             << "\n" << "Salary Coefficient: " << d->PE->getSalaryCoefficient()
             << "\n" << "Birth Date: " << d->PE->getDateOfBirth().getDate()
             << "\n" << "Appointment Date: " << d->PE->getDateOfAppointment().getDate()
             << "\n" << "Length of service: " << d->PE->getLengthOfService()
             << "\n" << "******************************"
             << endl;
        last = d;
        d = d->next;
    }
}

// SEARCH AN EMPLOYEE WITH GIVEN EMPLOYEE NUMBER IN DOUBLE LINKED LIST
void searchDLL(int en){
    if ( headDLL == NULL ) cout << "Linked list is empty!" << endl;

    DoubleLL *current = headDLL;
    while ( current != NULL ){
        if ( current->PE->getEmployeeNumber() == en ) {
            cout << "******************************" << "\n"
                 << "Employee Number: " << current->PE->getEmployeeNumber()
                 << "\n" << "Employee Type: " << current->PE->getEmployeeType() << " (Permanent)"
                 << "\n" << "Name: " << current->PE->getName()
                 << "\n" << "Surname: " << current->PE->getSurname()
                 << "\n" << "Title: " << current->PE->getTitle()
                 << "\n" << "Salary Coefficient: " << current->PE->getSalaryCoefficient()
                 << "\n" << "Birth Date: " << current->PE->getDateOfBirth().getDate()
                 << "\n" << "Appointment Date: " << current->PE->getDateOfAppointment().getDate()
                 << "\n" << "Length of service: " << current->PE->getLengthOfService()
                 << "\n" << "******************************"
                 << endl;
        }
        if ( current->next != NULL ){
            current = current->next;
        }
        else break;
    }
}

// UPDATE AN EMPLOYEE'S TITLE AND SALARY COEFFICIENT
void updateDLL(int en){
    if ( headDLL == NULL ) cout << "Linked list is empty!" << endl;

    string title;
    float salaryCoefficient;

    DoubleLL *current = headDLL;
    while ( current != NULL ){
        if ( current->PE->getEmployeeNumber() == en ) {
            cout << "Please type the title" << endl;
            cin >> title;
            current->PE->setTitle(title);
            cout << "Please type the salary coefficient" << endl;
            cin >> salaryCoefficient;
            current->PE->setSalaryCoefficient(salaryCoefficient);
        }
        if ( current->next != NULL ){
            current = current->next;
        }
        else break;
    }
}

// SEARCH AN EMPLOYEE THAT ASSIGNED IN A GIVEN YEAR
void searchYearDLL(int year){
    if ( headDLL == NULL ) cout << "Linked list is empty!" << endl;

    DoubleLL *current = headDLL;
    while ( current != NULL ){
        if ( current->PE->getDateOfAppointment().getYear() == year ) {
            cout << "******************************" << "\n"
                 << "Employee Number: " << current->PE->getEmployeeNumber()
                 << "\n" << "Employee Type: " << current->PE->getEmployeeType() << " (Permanent)"
                 << "\n" << "Name: " << current->PE->getName()
                 << "\n" << "Surname: " << current->PE->getSurname()
                 << "\n" << "Title: " << current->PE->getTitle()
                 << "\n" << "Salary Coefficient: " << current->PE->getSalaryCoefficient()
                 << "\n" << "Birth Date: " << current->PE->getDateOfBirth().getDate()
                 << "\n" << "Appointment Date: " << current->PE->getDateOfAppointment().getDate()
                 << "\n" << "Length of service: " << current->PE->getLengthOfService()
                 << "\n" << "******************************"
                 << endl;
        }
        if ( current->next != NULL ){
            current = current->next;
        }
        else break;
    }
}

// SEARCH AN EMPLOYEE THAT ASSIGNED AFTER GIVEN YEAR
void searchAfterDateDLL(string appDate){
    size_t start;
    size_t end = 0;
    vector <string> tokens;
    string delim = "-";
    while ((start = appDate.find_first_not_of(delim, end)) != string::npos){
        end = appDate.find(delim, start);
        tokens.push_back(appDate.substr(start, end - start));
    }

    if ( headDLL == NULL ) cout << "Linked list is empty!" << endl;

    DoubleLL *current = headDLL;
    while ( current != NULL ){
        if ( current->PE->getDateOfAppointment().getYear() > stoi(tokens[2])
             ||
             ( current->PE->getDateOfAppointment().getYear() == stoi(tokens[2])
               && current->PE->getDateOfAppointment().getMonth() > stoi(tokens[1]))
             ||
             ( current->PE->getDateOfAppointment().getYear() == stoi(tokens[2])
               && current->PE->getDateOfAppointment().getMonth() == stoi(tokens[1])
               && current->PE->getDateOfAppointment().getDay() > stoi(tokens[0])) ) {
            cout << "******************************" << "\n"
                 << "Employee Number: " << current->PE->getEmployeeNumber()
                 << "\n" << "Employee Type: " << current->PE->getEmployeeType() << " (Permanent)"
                 << "\n" << "Name: " << current->PE->getName()
                 << "\n" << "Surname: " << current->PE->getSurname()
                 << "\n" << "Title: " << current->PE->getTitle()
                 << "\n" << "Salary Coefficient: " << current->PE->getSalaryCoefficient()
                 << "\n" << "Birth Date: " << current->PE->getDateOfBirth().getDate()
                 << "\n" << "Appointment Date: " << current->PE->getDateOfAppointment().getDate()
                 << "\n" << "Length of service: " << current->PE->getLengthOfService()
                 << "\n" << "******************************"
                 << endl;
        }
        if ( current->next != NULL ){
            current = current->next;
        }
        else break;
    }
}

// SEARCH AN EMPLOYEE THAT BORN BEFORE GIVEN DATE
void searchBeforeDLL(string birthDate){
    size_t start;
    size_t end = 0;
    vector <string> tokens;
    string delim = "-";
    while ((start = birthDate.find_first_not_of(delim, end)) != string::npos){
        end = birthDate.find(delim, start);
        tokens.push_back(birthDate.substr(start, end - start));
    }

    if ( headDLL == NULL ) cout << "Linked list is empty!" << endl;

    DoubleLL *current = headDLL;
    while ( current != NULL ){
        if ( current->PE->getDateOfBirth().getYear() < stoi(tokens[2])
             ||
             ( current->PE->getDateOfBirth().getYear() == stoi(tokens[2])
               && current->PE->getDateOfBirth().getMonth() < stoi(tokens[1]))
             ||
             ( current->PE->getDateOfBirth().getYear() == stoi(tokens[2])
               && current->PE->getDateOfBirth().getMonth() == stoi(tokens[1])
               && current->PE->getDateOfBirth().getDay() < stoi(tokens[0])) ) {
            cout << "******************************" << "\n"
                 << "Employee Number: " << current->PE->getEmployeeNumber()
                 << "\n" << "Employee Type: " << current->PE->getEmployeeType() << " (Permanent)"
                 << "\n" << "Name: " << current->PE->getName()
                 << "\n" << "Surname: " << current->PE->getSurname()
                 << "\n" << "Title: " << current->PE->getTitle()
                 << "\n" << "Salary Coefficient: " << current->PE->getSalaryCoefficient()
                 << "\n" << "Birth Date: " << current->PE->getDateOfBirth().getDate()
                 << "\n" << "Appointment Date: " << current->PE->getDateOfAppointment().getDate()
                 << "\n" << "Length of service: " << current->PE->getLengthOfService()
                 << "\n" << "******************************"
                 << endl;
        }
        if ( current->next != NULL ){
            current = current->next;
        }
        else break;
    }
}

// SEARCH AN EMPLOYEE THAT BORN IN GIVEN MONTH
void searchMonthDLL(int month){
    if ( headDLL == NULL ) cout << "Linked list is empty!" << endl;

    DoubleLL *current = headDLL;
    while ( current != NULL ){
        if ( current->PE->getDateOfBirth().getMonth() == month ) {
            cout << "******************************" << "\n"
                 << "Employee Number: " << current->PE->getEmployeeNumber()
                 << "\n" << "Employee Type: " << current->PE->getEmployeeType() << " (Permanent)"
                 << "\n" << "Name: " << current->PE->getName()
                 << "\n" << "Surname: " << current->PE->getSurname()
                 << "\n" << "Title: " << current->PE->getTitle()
                 << "\n" << "Salary Coefficient: " << current->PE->getSalaryCoefficient()
                 << "\n" << "Birth Date: " << current->PE->getDateOfBirth().getDate()
                 << "\n" << "Appointment Date: " << current->PE->getDateOfAppointment().getDate()
                 << "\n" << "Length of service: " << current->PE->getLengthOfService()
                 << "\n" << "******************************"
                 << endl;
        }
        if ( current->next != NULL ){
            current = current->next;
        }
        else break;
    }
}

// SEARCH AN EMPLOYEE WITH GIVEN TITLE - This function returns an object. So we can find last assigned employee with
// given title.
DoubleLL *searchTitleDLL(string title){
    if ( headDLL == NULL ) cout << "Linked list is empty!" << endl;
    struct DoubleLL *temp;
    DoubleLL *current = headDLL;
    bool flag = true;

    while ( current != NULL ){
        if ( current->PE->getTitle() == title && flag ) {
            temp = current;
            flag = false;
        }
        else if ( current->PE->getTitle() == title ){
            if (current->PE->getDateOfAppointment().getYear() > temp->PE->getDateOfAppointment().getYear()
                ||
                (current->PE->getDateOfAppointment().getYear() == temp->PE->getDateOfAppointment().getYear() &&
                 current->PE->getDateOfAppointment().getMonth() > temp->PE->getDateOfAppointment().getMonth())
                ||
                (current->PE->getDateOfAppointment().getYear() == temp->PE->getDateOfAppointment().getYear() &&
                 current->PE->getDateOfAppointment().getMonth() == temp->PE->getDateOfAppointment().getMonth() &&
                 current->PE->getDateOfAppointment().getDay() > temp->PE->getDateOfAppointment().getDay()))
            {
                temp = current;
            }
        }
        current = current->next;
    }

    return temp;
}

// FUNCTION WHERE ALL WORK IS PERFORMED
void Program() {

    cout << "____ Employee Recording System ____"
    << "\n" << "Please select for the following Menu Operation:"
    << "\n" << "1) Appointment of a new employee"
    << "\n" << "2) Appointment of a transferred employee"
    << "\n" << "3) Updating the title and salary coefficient of an employee"
    << "\n" << "4) Deletion of an employee"
    << "\n" << "5) Listing the information of an employee"
    << "\n" << "6) Listing employees ordered by employee number"
    << "\n" << "7) Listing employees ordered by appointment date"
    << "\n" << "8) Listing employees appointed after a certain date"
    << "\n" << "9) Listing employees assigned in a given year"
    << "\n" << "10) Listing employees born before a certain date"
    << "\n" << "11) Listing employees born in a particular month"
    << "\n" << "12) Listing the information of the last assigned employee with a given title" << endl;

    int choice;
    cin >> choice;

    // ADD EMPLOYEE WITHOUT LENGTH OF SERVICE
    if (choice == 1) {
        int employeeNumber;
        int employeeType;
        string name;
        string surname;
        string title;
        float salaryCoefficient;
        Date dateOfBirth = Date();
        Date dateOfAppointment = Date();

        cout << "Please type the employee number" << endl;
        cin >> employeeNumber;
        cout << "Type the employee type" << endl;
        cin >> employeeType;
        cout << "Type the Name" << endl;
        cin >> name;
        cout << "Type surname" << endl;
        cin >> surname;
        cout << "Type title" << endl;
        cin >> title;
        cout << "Type salary coefficient" << endl;
        cin >> salaryCoefficient;
        cout << "Type birth date" << endl;
        string birthDate;
        cin >> birthDate;
        dateOfBirth.setDate(birthDate);
        cout << "Type appointment date" << endl;
        string appointDate;
        cin >> appointDate;
        dateOfAppointment.setDate(appointDate);

        if ( employeeType == 0 ) {
            if (last == NULL) {
                last = insertCircularLL(last, new TemporaryEmployee(employeeNumber, name, surname, title, salaryCoefficient, dateOfBirth,
                                                       dateOfAppointment, 0));
            }
            else {
                last = insertEndCircularLL(last, new TemporaryEmployee(employeeNumber, name, surname, title, salaryCoefficient, dateOfBirth,
                                                                       dateOfAppointment, 0));
            }

        }
        else if ( employeeType == 1 ) {
            if ( headDLL == NULL ) {
                insertDoubleLL(&headDLL, new PermanentEmployee(employeeNumber, name, surname,
                                                               title, salaryCoefficient, dateOfBirth,dateOfAppointment, 0));
            }
            else {
                insertEndDoubleLL(&headDLL, new PermanentEmployee(employeeNumber, name, surname,
                                                               title, salaryCoefficient, dateOfBirth,dateOfAppointment, 0));
            }
        }
        Program();
    }

    // ADD EMPLOYEE WITH LENGTH OF SERVICE
    else if (choice == 2) {
        int employeeNumber;
        int employeeType;
        string name;
        string surname;
        string title;
        float salaryCoefficient;
        Date dateOfBirth = Date();
        Date dateOfAppointment = Date();
        int lengthOfService;

        cout << "Please type the employee number" << endl;
        cin >> employeeNumber;
        cout << "Type the employee type" << endl;
        cin >> employeeType;
        cout << "Type the Name" << endl;
        cin >> name;
        cout << "Type surname" << endl;
        cin >> surname;
        cout << "Type title" << endl;
        cin >> title;
        cout << "Type salary coefficient" << endl;
        cin >> salaryCoefficient;
        cout << "Type birth date" << endl;
        string birthDate;
        cin >> birthDate;
        dateOfBirth.setDate(birthDate);
        cout << "Type appointment date" << endl;
        string appointDate;
        cin >> appointDate;
        dateOfAppointment.setDate(appointDate);
        cout << "Type length of service days" << endl;
        cin >> lengthOfService;

        if (employeeType == 0) {
            if (last == NULL) {
                last = insertCircularLL(last,
                                        new TemporaryEmployee(employeeNumber, name, surname, title, salaryCoefficient,
                                                              dateOfBirth,
                                                              dateOfAppointment, lengthOfService));
            } else {
                last = insertEndCircularLL(last, new TemporaryEmployee(employeeNumber, name, surname, title,
                                                                       salaryCoefficient, dateOfBirth,
                                                                       dateOfAppointment, lengthOfService));
            }
        } else if (employeeType == 1) {
            if (headDLL == NULL) {
                insertDoubleLL(&headDLL, new PermanentEmployee(employeeNumber, name, surname,
                                                               title, salaryCoefficient, dateOfBirth, dateOfAppointment,
                                                               lengthOfService));
            } else {
                insertEndDoubleLL(&headDLL, new PermanentEmployee(employeeNumber, name, surname,
                                                                  title, salaryCoefficient, dateOfBirth,
                                                                  dateOfAppointment, lengthOfService));
            }
        }
        Program();
    }

    // UPDATE INFORMATION OF AN EMPLOYEE
    else if (choice == 3) {
        int en;
        cout << "Please type the employee number" << endl;
        cin >> en;
        if ( last != NULL && headDLL != NULL ){
            updateCLL(en);
            updateDLL(en);
        }
        else if ( last == NULL && headDLL != NULL ){
            updateDLL(en);
        }
        else if ( last != NULL && headDLL == NULL ){
            updateCLL(en);
        }
        Program();
    }

    // I COULD NOT DO THIS PART - SO DELETION IS NOT WORKING.
    else if (choice == 4) {
        cout << "I could not do this part!" << endl;
        Program();
    }

    // SEARCH AN EMPLOYEE
    else if (choice == 5) {
        int en;
        cout << "Please type the employee number" << endl;
        cin >> en;
        if ( last != NULL && headDLL != NULL ){
            searchCLL(en);
            searchDLL(en);
        }
        else if ( last == NULL && headDLL != NULL ){
            searchDLL(en);
        }
        else if ( last != NULL && headDLL == NULL ){
            searchCLL(en);
        }
        else {
            cout << "No employee to show!" << endl;
        }
        Program();
    }

    // DISPLAY ALL EMPLOYEES
    else if (choice == 6) {
        if ( last != NULL && headDLL != NULL) {
            displayCircularLL();
            displayDoubleLL(headDLL);
        }
        else if ( last == NULL &&  headDLL != NULL) {
            displayDoubleLL(headDLL);
        }
        else if ( headDLL == NULL && last != NULL) {
            displayCircularLL();
        }
        else {
            cout << "No employee to show!" << endl;
        }
        Program();
    }

    // DISPLAY ALL EMPLOYEES
    else if (choice == 7) {
        if ( last != NULL && headDLL != NULL) {
            displayCircularLL();
            displayDoubleLL(headDLL);
        }
        else if ( last == NULL &&  headDLL != NULL) {
            displayDoubleLL(headDLL);
        }
        else if ( headDLL == NULL && last != NULL) {
            displayCircularLL();
        }
        else {
            cout << "No employee to show!" << endl;
        }
        Program();
    }

    // SEARCH THE EMPLOYEES THAT APPOINTED AFTER GIVEN DATE
    else if (choice == 8) {
        cout << "Please type a appointment date" << endl;
        string appDate;
        cin >> appDate;
        if ( last != NULL && headDLL != NULL ){
            searchAfterDateCLL(appDate);
            searchAfterDateDLL(appDate);
        }
        else if ( last == NULL && headDLL != NULL ){
            searchAfterDateDLL(appDate);
        }
        else if ( last != NULL && headDLL == NULL ){
            searchAfterDateCLL(appDate);
        }
        else {
            cout << "No employee to show!" << endl;
        }
        Program();
    }

    // SEARCH THE EMPLOYEES THAT ASSIGNED A GIVEN YEAR
    else if (choice == 9) {
        cout << "Please type a year" << endl;
        int year;
        cin >> year;
        if ( last != NULL && headDLL != NULL ){
            searchYearCLL(year);
            searchYearDLL(year);
        }
        else if ( last == NULL && headDLL != NULL ){
            searchYearDLL(year);
        }
        else if ( last != NULL && headDLL == NULL ){
            searchYearCLL(year);
        }
        else {
            cout << "No employee to show!" << endl;
        }
        Program();
    }

    // SEARCH THE EMPLOYEES THAT BORN BEFORE GIVEN DATE
    else if (choice == 10) {
        cout << "Please type a birth date" << endl;
        string birthDate;
        cin >> birthDate;
        if ( last != NULL && headDLL != NULL ){
            searchBeforeCLL(birthDate);
            searchBeforeDLL(birthDate);
        }
        else if ( last == NULL && headDLL != NULL ){
            searchBeforeDLL(birthDate);
        }
        else if ( last != NULL && headDLL == NULL ){
            searchBeforeCLL(birthDate);
        }
        else {
            cout << "No employee to show!" << endl;
        }
        Program();
    }

    // SEARCH THE EMPLOYEES THAT BORN GIVEN MONTH
    else if (choice == 11) {
        cout << "Please type a month" << endl;
        int month;
        cin >> month;
        if ( last != NULL && headDLL != NULL ){
            searchMonthCLL(month);
            searchMonthDLL(month);
        }
        else if ( last == NULL && headDLL != NULL ){
            searchMonthDLL(month);
        }
        else if ( last != NULL && headDLL == NULL ){
            searchMonthCLL(month);
        }
        else {
            cout << "No employee to show!" << endl;
        }
        Program();
    }

    // SEARCH THE EMPLOYEE THAT LAST ASSIGNED WITH GIVEN TITLE
    else if (choice == 12) {
        cout << "Please type a title" << endl;
        string title;
        cin >> title;
        CircularLL *searchCLL;
        DoubleLL *searchDLL;

        if ( last != NULL && headDLL != NULL ){
            searchCLL = searchTitleCLL(title);
            searchDLL = searchTitleDLL(title);

            if ( searchCLL->TE->getDateOfAppointment().getYear() > searchDLL->PE->getDateOfAppointment().getYear() ||
            (searchCLL->TE->getDateOfAppointment().getYear() == searchDLL->PE->getDateOfAppointment().getYear() &&
            searchCLL->TE->getDateOfAppointment().getMonth() > searchDLL->PE->getDateOfAppointment().getMonth()) ||
            (searchCLL->TE->getDateOfAppointment().getYear() == searchDLL->PE->getDateOfAppointment().getYear() &&
             searchCLL->TE->getDateOfAppointment().getMonth() == searchDLL->PE->getDateOfAppointment().getMonth() &&
             searchCLL->TE->getDateOfAppointment().getDay() > searchDLL->PE->getDateOfAppointment().getDay())
             ) {
                cout << "******************************" << "\n"
                     << "Employee Number: " << searchCLL->TE->getEmployeeNumber()
                     << "\n" << "Employee Type: " << searchCLL->TE->getEmployeeType() << " (Permanent)"
                     << "\n" << "Name: " << searchCLL->TE->getName()
                     << "\n" << "Surname: " << searchCLL->TE->getSurname()
                     << "\n" << "Title: " << searchCLL->TE->getTitle()
                     << "\n" << "Salary Coefficient: " << searchCLL->TE->getSalaryCoefficient()
                     << "\n" << "Birth Date: " << searchCLL->TE->getDateOfBirth().getDate()
                     << "\n" << "Appointment Date: " << searchCLL->TE->getDateOfAppointment().getDate()
                     << "\n" << "Length of service: " << searchCLL->TE->getLengthOfService()
                     << "\n" << "******************************"
                     << endl;
            }
            else {
                cout << "******************************" << "\n"
                     << "Employee Number: " << searchDLL->PE->getEmployeeNumber()
                     << "\n" << "Employee Type: " << searchDLL->PE->getEmployeeType() << " (Permanent)"
                     << "\n" << "Name: " << searchDLL->PE->getName()
                     << "\n" << "Surname: " << searchDLL->PE->getSurname()
                     << "\n" << "Title: " << searchDLL->PE->getTitle()
                     << "\n" << "Salary Coefficient: " << searchDLL->PE->getSalaryCoefficient()
                     << "\n" << "Birth Date: " << searchDLL->PE->getDateOfBirth().getDate()
                     << "\n" << "Appointment Date: " << searchDLL->PE->getDateOfAppointment().getDate()
                     << "\n" << "Length of service: " << searchDLL->PE->getLengthOfService()
                     << "\n" << "******************************"
                     << endl;
            }
        }
        else if ( last == NULL && headDLL != NULL ){
            searchDLL = searchTitleDLL(title);
            cout << "******************************" << "\n"
                 << "Employee Number: " << searchDLL->PE->getEmployeeNumber()
                 << "\n" << "Employee Type: " << searchDLL->PE->getEmployeeType() << " (Permanent)"
                 << "\n" << "Name: " << searchDLL->PE->getName()
                 << "\n" << "Surname: " << searchDLL->PE->getSurname()
                 << "\n" << "Title: " << searchDLL->PE->getTitle()
                 << "\n" << "Salary Coefficient: " << searchDLL->PE->getSalaryCoefficient()
                 << "\n" << "Birth Date: " << searchDLL->PE->getDateOfBirth().getDate()
                 << "\n" << "Appointment Date: " << searchDLL->PE->getDateOfAppointment().getDate()
                 << "\n" << "Length of service: " << searchDLL->PE->getLengthOfService()
                 << "\n" << "******************************"
                 << endl;
        }
        else if ( last != NULL && headDLL == NULL ){
            searchCLL = searchTitleCLL(title);
            cout << "******************************" << "\n"
                 << "Employee Number: " << searchCLL->TE->getEmployeeNumber()
                 << "\n" << "Employee Type: " << searchCLL->TE->getEmployeeType() << " (Permanent)"
                 << "\n" << "Name: " << searchCLL->TE->getName()
                 << "\n" << "Surname: " << searchCLL->TE->getSurname()
                 << "\n" << "Title: " << searchCLL->TE->getTitle()
                 << "\n" << "Salary Coefficient: " << searchCLL->TE->getSalaryCoefficient()
                 << "\n" << "Birth Date: " << searchCLL->TE->getDateOfBirth().getDate()
                 << "\n" << "Appointment Date: " << searchCLL->TE->getDateOfAppointment().getDate()
                 << "\n" << "Length of service: " << searchCLL->TE->getLengthOfService()
                 << "\n" << "******************************"
                 << endl;
        }
        else {
            cout << "No employee to show!" << endl;
        }
        Program();
    }
};

// MAIN FUNCTION THAT CALL Program FUNCTION
int main() {

    Program();

    return 0;
}
