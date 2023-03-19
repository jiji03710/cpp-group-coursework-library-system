#include "book.h"

using namespace std;

// Variables
vector<Book> books; // Dynamic array (Vector) of Book class objects
vector<Reader> readers; // Dynamic array (Vector) of Reader class objects
map<int, int> borrow_status; // Map variable to correlate bID with sID and to show the borrow status of each book in the system
// Const strings for file paths
const string book_filepath = "book.txt";
const string reader_filepath = "reader.txt";
const string borrow_filepath = "borrow.txt";

// Constructor for Book object
Book::Book(int input_bID, string input_title, string input_author, double input_price, int input_year, string input_publisher):
bID(input_bID),
title(input_title),
author(input_author),
price(input_price),
year(input_year),
publisher(input_publisher){}

// Get functions for private data fields
int Book::get_bID(){
    return bID;
}
string Book::get_title(){
    return title;
}
string Book::get_author(){
    return author;
}
double Book::get_price(){
    return price;
}
int Book::get_year(){
    return year;
}
string Book::get_publisher(){
    return publisher;
}

// Constructor for Reader object
Reader::Reader(int input_sID, string input_name, string input_gender, string input_email, string input_college):
sID(input_sID),
name(input_name),
gender(input_gender),
email(input_email),
college(input_college){}

// Get functions for private data fields
int Reader::get_sID(){
    return sID;
}
string Reader::get_name(){
    return name;
}
string Reader::get_gender(){
    return gender;
}
string Reader::get_email(){
    return email;
}
string Reader::get_college(){
    return college;
}

// Main functions
void BookEntry(){
    ofstream fout;
    fout.open(book_filepath, ios::app);    //open file
    if (!fout)
    {
        cout << "OPEN FILE FAILED" << endl;
        exit(1);
    }

    cout << "STARTING THE BOOKENTRY FUNCTION" << endl;
    string input_bID, input_title, input_author, input_year, input_publisher, input_price;

    cout << "PLEASE ENTER THE BOOK ID:" << endl;
    getline(cin, input_bID);

    // If the invalid ID is entered, it outputs the error and gets another input
    while(true){
        if(!consist_of_num(input_bID)){
            cout << "ERROR INVALID INPUT\nPlease enter a numerical value:\n";
            getline(cin, input_bID);
            continue;
        }
        int num_input_bID = stoi(input_bID);
        if(borrow_status.find(num_input_bID) != borrow_status.end()){
            cout << "ERROR BOOK ID ALREADY EXISTS\nPlease enter a non-existent ID:\n";
            getline(cin, input_bID);
            continue;
        }

        // Creates a key in borrow_status map with bID and sets the value to be equal to -1 (default value which states that the book is not borrowed)
        borrow_status[num_input_bID] = -1;
        break;
    }

    cout << "PLEASE ENTER THE BOOK NAME:" << endl;
    getline(cin, input_title);

    cout << "PLEASE ENTER THE AUTHOR:" << endl;
    getline(cin, input_author);

    cout << "PLEASE ENTER THE PRICE:" << endl;
    getline(cin, input_price);

    // If the invalid price is entered, it outputs the error and gets another input
    while(!is_price(input_price)){
        cout << "ERROR INVALID INPUT\nPlease enter a numerical value:\n";
        getline(cin, input_price);
    }

    // If the invalid year is entered, it outputs the error and gets another input
    cout << "PLEASE ENTER THE YEAR:" << endl;
    getline(cin, input_year);
    while(!consist_of_num(input_year)){
        cout << "ERROR INVALID INPUT\nPlease enter a numerical value:\n";
        getline(cin, input_year);
    }

    cout << "PLEASE ENTER THE PUBLISHER:" << endl;
    getline(cin, input_publisher);

    fout << left << setw(15) << input_bID << setw(15) << input_title << setw(15) << input_author << setw(15) << input_price << setw(15) << input_year << setw(15) << input_publisher << setw(15) << endl;

    // Creates a temporal Book object and then puts in into books vector
    Book temp_book(stoi(input_bID), input_title, input_author, stod(input_price), stoi(input_year), input_publisher);
    books.push_back(temp_book);

    print_success();

    fout.close();
}
void BookMessage(){
    cout << "STARTING THE BOOKMESSAGE FUNCTION" << endl;
    ifstream fin(book_filepath);
    if (fin)
    {
        string str;
        while (getline(fin, str))
        {
            cout << str << endl;
        }
    }
    else
    {
        cout << "OPEN FILE FAILED" << endl;
        exit(1);
    }

    print_success();

    fin.close();
}
void DeleteBook(){
    ofstream fout;
    fout.open(book_filepath, ios::app);    //open file
    if (!fout)
    {
        cout << "OPEN FILE FAILED" << endl;
        exit(1);
    }

    cout << "STARTING THE DELETEBOOK FUNCTION" << endl;

    // If there are no books in the library, it outputs the error message
    if(borrow_status.empty()){
        print_error("THERE ARE NO BOOKS IN THE LIBRARY", 1);
        return;
    }

    string input_bID;

    cout << "PLEASE ENTER THE BOOK ID THAT YOU WISH TO DELETE:" << endl;
    getline(cin, input_bID);

    // If the invalid ID is entered, it outputs the error and gets another input
    while(true){
        if(!consist_of_num(input_bID)){
            cout << "ERROR INVALID INPUT\nPlease enter a numerical value:\n";
            getline(cin, input_bID);
            continue;
        }
        int num_input_bID = stoi(input_bID);
        if(borrow_status.find(num_input_bID) == borrow_status.end()){
            cout << "ERROR BOOK ID DOES NOT EXIST\nPlease enter an existent ID:\n";
            getline(cin, input_bID);
            continue;
        }

        // Erases the book info for corresponding book ID from books vector and borrow_status map
        borrow_status.erase(num_input_bID);
        delete_ID(books, num_input_bID);
        break;
    }

    update_file();
    print_success();

}
void ReaderEntry(){
    ofstream fout;
    fout.open(reader_filepath, ios::app);    //open file
    if (!fout)
    {
        cout << "OPEN FILE FAILED" << endl;
        exit(1);
    }

    cout << "STARTING THE READERENTRY FUNCTION" << endl;
    string input_sID, input_name, input_gender, input_email, input_college;

    cout << "PLEASE ENTER THE STUDENT ID:" << endl;
    getline(cin, input_sID);

    // If the invalid ID is entered, it outputs the error and gets another input
    while(true){
        if(!consist_of_num(input_sID)){
            cout << "ERROR INVALID INPUT\nPlease enter a numerical value:\n";
            getline(cin, input_sID);
            continue;
        }
        int num_input_sID = stoi(input_sID);
        if(is_sID_existent(num_input_sID)){
            cout << "ERROR STUDENT ID ALREADY EXISTS\nPlease enter a non-existent ID:\n";
            getline(cin, input_sID);
            continue;
        }
        break;
    }

    cout << "PLEASE ENTER THE NAME:" << endl;
    getline(cin, input_name);

    cout << "PLEASE ENTER THE GENDER:\n 1 for Male, 2 for Female" << endl;
    getline(cin, input_gender);

    // If the invalid number is entered, it outputs the error and gets another input
    while(input_gender != "1" && input_gender != "2"){
        cout << "ERROR INVALID INPUT\nPlease enter 1 for Male or 2 for Female:\n";
        getline(cin, input_gender);
    }
    input_gender == "1" ? input_gender = "Male" : input_gender = "Female";

    // If the invalid email is entered, it outputs the error and gets another input
    cout << "PLEASE ENTER THE EMAIL:" << endl;
    getline(cin, input_email);
    while(!is_email(input_email)){
        cout << "ERROR INVALID INPUT\nPlease enter a valid email address:\n";
        getline(cin, input_email);
    }

    cout << "PLEASE ENTER THE COLLEGE:" << endl;
    getline(cin, input_college);

    fout << left << setw(15) << input_sID << setw(15) << input_name << setw(15) << input_gender << setw(15) << input_email << setw(15) << input_college << setw(15) << endl;

    // Creates a temporal Reader object and then puts in into readers vector
    Reader temp_reader(stoi(input_sID), input_name, input_gender, input_email, input_college);
    readers.push_back(temp_reader);

    print_success();

    fout.close();
}

// Overloaded ReaderEntry function which has the student ID as an input parameter
void ReaderEntry(int input_sID){
    ofstream fout;
    fout.open(reader_filepath, ios::app);    //open file
    if (!fout)
    {
        cout << "OPEN FILE FAILED" << endl;
        exit(1);
    }

    cout << "STARTING THE REGISTRATION FUNCTION FOR STUDENT ID: " << input_sID << endl;
    string input_name, input_gender, input_email, input_college;

    cout << "PLEASE ENTER THE NAME:" << endl;
    getline(cin, input_name);

    cout << "PLEASE ENTER THE GENDER:\n 1 for Male, 2 for Female" << endl;
    getline(cin, input_gender);

    // If the invalid number is entered, it outputs the error and gets another input
    while(input_gender != "1" && input_gender != "2"){
        cout << "ERROR INVALID INPUT\nPlease enter 1 for Male or 2 for Female:\n";
        getline(cin, input_gender);
    }
    input_gender == "1" ? input_gender = "Male" : input_gender = "Female";

    cout << "PLEASE ENTER THE EMAIL:" << endl;
    getline(cin, input_email);

    // If the invalid email is entered, it outputs the error and gets another input
    while(!is_email(input_email)){
        cout << "ERROR INVALID INPUT\nPlease enter a valid email address:\n";
        getline(cin, input_email);
    }

    cout << "PLEASE ENTER THE COLLEGE:" << endl;
    getline(cin, input_college);

    fout << left << setw(15) << input_sID << setw(15) << input_name << setw(15) << input_gender << setw(15) << input_email << setw(15) << input_college << setw(15) << endl;

    // Creates a temporal Reader object and then puts in into readers vector
    Reader temp_reader(input_sID, input_name, input_gender, input_email, input_college);
    readers.push_back(temp_reader);

    fout.close();
}
void ReaderMessage(){
    cout << "STARTING THE READERMESSAGE FUNCTION" << endl;
    ifstream fin(reader_filepath);
    if (fin)
    {
        string str;
        while (getline(fin, str))
        {
            cout << str << endl;
        }
    }
    else
    {
        cout << "OPEN FILE FAILED" << endl;
        exit(1);
    }

    print_success();

    fin.close();
}
void BorrowBook(){
    cout << "STARTING THE BORROWBOOK FUNCTION" << endl;

    // Display an error if there are no books in the library or all books are currently borrowed
    if(borrow_status.empty()){
        print_error("THERE ARE NO BOOKS IN THE LIBRARY", 1);
        return;
    }
    if(books_in_library() == 0){
        print_error("ALL BOOKS ARE BORROWED", 1);
        return;
    }

    string input_bID;
    cout << "PLEASE ENTER THE BOOK ID THAT YOU WISH TO BORROW:" << endl;
    getline(cin, input_bID);
    int temp_input_bID;

    // Display errors for incorrect inputted book ID
    while(true){
        if(!consist_of_num(input_bID)){
            cout << "ERROR INVALID INPUT\nPlease enter a numerical value:\n";
            getline(cin, input_bID);
            continue;
        }
        int num_input_bID = stoi(input_bID);
        if(borrow_status.find(num_input_bID) == borrow_status.end()){
            cout << "ERROR BOOK ID DOES NOT EXIST\nPlease enter an existent ID:\n";
            getline(cin, input_bID);
            continue;
        }
        if(borrow_status[num_input_bID] != -1){
            cout << "ERROR BOOK IS ALREADY BORROWED\nPlease enter another book ID:\n";
            getline(cin, input_bID);
            continue;
        }
        temp_input_bID = num_input_bID;
        break;
    }

    string input_sID;
    cout << "PLEASE ENTER THE STUDENT ID:" << endl;
    getline(cin, input_sID);
    int temp_input_sID;

    // If the invalid ID is entered, it outputs the error and gets another input
    while(true){
        if(!consist_of_num(input_sID)){
            cout << "ERROR INVALID INPUT\nPlease enter a numerical value:\n";
            getline(cin, input_sID);
            continue;
        }
        int num_input_sID = stoi(input_sID);

        // If student ID does not exist, user can choose to register a new student or to input another student ID
        if(!is_sID_existent(num_input_sID)){
            cout << "ERROR STUDENT ID DOES NOT EXIST\nPlease enter 1 to input an existent ID or 2 to register new reader:\n";
            string temp_num;
            getline(cin, temp_num);
            while(temp_num != "1" && temp_num != "2"){
                cout << "ERROR INVALID INPUT\nPlease enter 1 to input an existent ID or 2 to register new reader:\n";
                getline(cin, temp_num);
            }
            if(temp_num == "2"){
                ReaderEntry(num_input_sID);
                temp_input_sID = num_input_sID;
                break;
            }
            getline(cin, input_sID);
            continue;
        }
        temp_input_sID = num_input_sID;
        break;
    }

    // Sets the value to be equal to Student ID for the key of borrowed book ID in borrow_status map
    borrow_status[temp_input_bID] = temp_input_sID;

    print_success();
}
void ReturnBook(){
    cout << "STARTING THE RETURNBOOK FUNCTION" << endl;

    // Display an error if there are no books borrowed or all books are currently in library
    if(borrow_status.empty()){
        print_error("THERE ARE NO BOOKS IN THE LIBRARY", 1);
        return;
    }
    if((borrow_status.size() - books_in_library()) == 0){
        print_error("THERE ARE NO BOOKS TO BE RETURNED", 1);
        return;
    }

    string input_bID;
    cout << "PLEASE ENTER THE BOOK ID THAT YOU WISH TO RETURN:" << endl;
    getline(cin, input_bID);
    int temp_input_bID;

    // If the invalid ID is entered, it outputs the error and gets another input
    while(true){
        if(!consist_of_num(input_bID)){
            cout << "ERROR INVALID INPUT\nPlease enter a numerical value:\n";
            getline(cin, input_bID);
            continue;
        }
        int num_input_bID = stoi(input_bID);
        if(borrow_status.find(num_input_bID) == borrow_status.end()){
            cout << "ERROR BOOK ID DOES NOT EXIST\nPlease enter an existent ID:\n";
            getline(cin, input_bID);
            continue;
        }
        if(borrow_status[num_input_bID] == -1){
            cout << "ERROR BOOK IS NOT BORROWED\nPlease enter another book ID:\n";
            getline(cin, input_bID);
            continue;
        }
        temp_input_bID = num_input_bID;
        break;
    }

    // Sets the value to be equal to -1 (default value for non-borrowed book) for the key of borrowed book ID in borrow_status map
    borrow_status[temp_input_bID] = -1;

    print_success();
}
void BorrowMessage(){
    cout << "STARTING THE BORROWMESSAGE FUNCTION" << endl;

    cout << left << setw(30) << "BOOK ID" << setw(30) << "BORROW STATUS" << endl;

    for(auto it = borrow_status.begin(); it != borrow_status.end(); it++){
        if(it->second == -1){
            cout << left << setw(30) << it->first << setw(30) << "is not borrowed" << endl;
            continue;
        }
        cout << left << setw(30) << it->first << setw(0) << "borrowed by " << it->second <<endl;
    }

    print_success();

}
void CountBook(){
    cout << "STARTING THE COUNTBOOK FUNCTION" << endl;

    cout << left << setw(20) << "BOOKS IN LIBRARY" << setw(20) << "BORROWED BOOKS" << setw(20) << "TOTAl AMOUNT" << endl;
    int total = borrow_status.size(), in_library = books_in_library();
    cout << left << setw(20) << in_library << setw(20) << total - in_library << setw(20) << total << endl;

    print_success();
}

// Secondary functions

// Checks if the string consists of numbers using regular expression
inline bool consist_of_num(string str){
    return regex_match(str, regex("[0-9]+") );
}

// Checks if the string is an email of the form "xxx@xxx.xxx" (here the part before @ may contain "." or "_") using regular expression
inline bool is_email(string str){
    return regex_match(str, regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)") );
}

// Checks if the string consists of numbers and may contain a decimal part with "." using regular expression
inline bool is_price(string str){
    return regex_match(str, regex("([0-9]+)(\\.?)([0-9]*)") );
}

// Checks if student ID exists in the System by going through the readers vector
bool is_sID_existent(int ID){
    for(auto it = readers.begin(); it != readers.end(); it++){
        if(it -> get_sID() == ID) return true;
    }
    return false;
}

// This function updates the book info in book.txt file
void update_file(){
    ofstream fout;
    fout.open(book_filepath, ios::out);    //open file
    if (!fout)
    {
        cout << "OPEN FILE FAILED" << endl;
        exit(1);
    }

    fout << left << setw(15) << "bID" << setw(15) << "title" << setw(15) << "author" << setw(15) << "price" << setw(15) << "year" << setw(15) << "publisher" << endl;

    for(auto it = books.begin(); it != books.end(); it++){
        fout << left << setw(15) << it -> get_bID() << setw(15) << it -> get_title() << setw(15) << it -> get_author() << setw(15) << it -> get_price() << setw(15) << it -> get_year() << setw(15) << it -> get_publisher() << setw(15) << endl;
    }

    fout.close();

}

// This function prints the graphical user interface of the book system
void print_GUI(){
    cout << "|--------------------BOOK SYSTEM---------------------|" << endl;
    cout << "|----------------------------------------------------|" << endl;
    cout << "|  1.BOOK ENTRY    2.BOOK MESSAGE    3.BOOK DELETE   |" << endl;
    cout << "|  4.READER ENTRY  5.READER MESSAGE  6.BOOK BORROW   |" << endl;
    cout << "|  7.BOOK RETURN   8.BORROW MESSAGE  9.BOOK COUNT    |" << endl;
    cout << "|                                    0.QUIT          |" << endl;
    cout << "|----------------------------------------------------|" << endl;
    cout << "PLEASE ENTER OPERATION ID:\n";
}

// This function prints success message and the next one prints error message
void print_success(){
    cout << "OPERATION SUCCESSFULLY COMPLETED\n";
}
void print_error(string error_message, bool terminate_message){
    cout << "ERROR OCCURRED" << endl << error_message;
    if(terminate_message) {
        cout << endl << "OPERATION PROCESS TERMINATED" << endl;
        return;
    }
    cout << endl;
}

// This function deletes the book info with correlates with given book ID
void delete_ID(vector<Book> &books_info, int ID){
    for(auto it = books_info.begin(); it != books_info.end(); it++){
        if(it -> get_bID() == ID){
            books_info.erase(it);
            return;
        }
    }
}

// This function starts one of the main functions by given operation ID
void start_operation(int ID){
    switch (ID) {
        case 1: {
            BookEntry();
            break;
        }
        case 2: {
            BookMessage();
            break;
        }
        case 3: {
            DeleteBook();
            break;
        }
        case 4: {
            ReaderEntry();
            break;
        }
        case 5: {
            ReaderMessage();
            break;
        }
        case 6: {
            BorrowBook();
            break;
        }
        case 7: {
            ReturnBook();
            break;
        }
        case 8: {
            BorrowMessage();
            break;
        }
        case 9: {
            CountBook();
            break;
        }
    }
}

// This function checks whether the file with given file path is empty
bool is_file_empty(string FilePath){
    ifstream file(FilePath);
    if(!file) {
        file.close();
        return true;
    }
    if(file && file.peek() == file.eof()){
        file.close();
        return true;
    }
    file.close();
    return false;
}

// This function returns the amount of books in the library
int books_in_library(){
    int in_library = 0;
    for(auto it = borrow_status.begin(); it != borrow_status.end(); it++){
        if(it->second == -1){
            in_library++;
            continue;
        }
    }
    return in_library;
}

// This functions sets the initial states of book and readers vectors, and borrow_status map if the files with data exist
void initialize_variables(){
    ifstream book_fin;
    ifstream reader_fin;
    ifstream borrow_fin;

    book_fin.open(book_filepath);
    reader_fin.open(reader_filepath);
    borrow_fin.open(borrow_filepath);

    if(!book_fin || !reader_fin || !borrow_fin) return;

    string temp;

    // Getting the first line from book.txt and reader.txt because it contains the names of the data fields
    getline(book_fin, temp);
    getline(reader_fin, temp);

    // Getting book object info from the file and using string stream for inputting them into temporal variables in order to create object instance and putting it in vector books
    while(true){
        getline(book_fin, temp);
        if(book_fin.eof()) break;
        stringstream ss(temp);
        string input_title, input_author, input_publisher;
        int input_bID, input_year;
        double input_price;
        ss >> input_bID >> input_title >> input_author >> input_price >> input_year >> input_publisher;
        Book temp_book(input_bID, input_title, input_author, input_price, input_year, input_publisher);
        books.push_back(temp_book);
    }

    // Getting reader object info from the file and using string stream for inputting them into temporal variables in order to create object instance and putting it in vector readers
    while(true){
        getline(reader_fin, temp);
        if(reader_fin.eof()) break;
        stringstream ss(temp);
        string input_name, input_gender, input_email, input_college;
        int input_sID;
        ss >> input_sID >> input_name >> input_gender >> input_email >> input_college;
        Reader temp_reader(input_sID, input_name, input_gender, input_email, input_college);
        readers.push_back(temp_reader);
    }

    // Getting the info of borrow status of each book from borrow.txt and putting them into borrow_status map
    while(true){
        int temp_bID, temp_sID;
        borrow_fin >> temp_bID >> temp_sID;
        if(borrow_fin.eof()) break;
        borrow_status[temp_bID] = temp_sID;
    }

    book_fin.close();
    reader_fin.close();
    borrow_fin.close();
}

// This function saves the borrow status info of each book into the borrow.txt
void save_BorrowInfo(){
    ofstream borrow_fout;
    borrow_fout.open(borrow_filepath);  //open file
    if (!borrow_fout)
    {
        cout << "OPEN FILE FAILED" << endl;
        exit(1);
    }
    for(auto it = borrow_status.begin(); it != borrow_status.end(); it++){
        borrow_fout << it->first << " " << it->second << endl;
    }
}

// This function prepares the system for the start and then starts it
void start_BookSystem(){
    initialize_variables();
    const bool book_empty = is_file_empty(book_filepath);
    const bool reader_empty = is_file_empty(reader_filepath);
    ofstream book_fout;
    book_fout.open(book_filepath, ios::app);  //open file
    if (!book_fout)
    {
        cout << "OPEN FILE FAILED" << endl;
        exit(1);
    }
    if(book_empty) book_fout << left << setw(15) << "bID" << setw(15) << "title" << setw(15) << "author" << setw(15) << "price" << setw(15) << "year" << setw(15) << "publisher" << endl;

    ofstream reader_fout;
    reader_fout.open(reader_filepath, ios::app);  //open file
    if (!reader_fout)
    {
        cout << "OPEN FILE FAILED" << endl;
        exit(1);
    }
    if(reader_empty) reader_fout << left << setw(15) << "sID" << setw(15) << "name" << setw(15) << "gender" << setw(15) << "email" << setw(15) << "college" << endl;

    int operation_ID = 1;
    string operation_ID_str;
    while (operation_ID)
    {
        print_GUI();
        getline(cin, operation_ID_str);
        // If the input operation ID is not just a number from 0 to 9, it outputs the error
        while(operation_ID_str.length() - 1 || operation_ID_str.find_first_of("0123456789") != 0)
        {
            cout << "ERROR INVALID INPUT\nPlease enter a valid operation ID:\n";
            cin >> operation_ID_str;
        }
        operation_ID = stoi(operation_ID_str);
        start_operation(operation_ID);
    }

    cout << "SYSTEM CLOSED" << endl;

    save_BorrowInfo();
    reader_fout.close();
    book_fout.close();
}

int main(){
    start_BookSystem();
    return 0;
}
