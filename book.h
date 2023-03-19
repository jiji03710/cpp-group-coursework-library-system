#ifndef BOOK_H
#define BOOK_H

// Importing needed libraries
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
#include <iomanip>
#include <sstream>

using namespace std;

// Creating a Book class
class Book{
private:
    int bID;
    string title;
    string author;
    double price;
    int year;
    string publisher;
public:
    Book(int input_bID, string input_title, string input_author, double input_price, int input_year, string input_publisher);
    int get_bID();
    string get_title();
    string get_author();
    double get_price();
    int get_year();
    string get_publisher();
};

// Creating a Reader class
class Reader{
private:
    int sID;
    string name;
    string gender;
    string email;
    string college;
public:
    Reader(int input_sID, string input_name, string input_gender, string input_email, string input_college);
    int get_sID();
    string get_name();
    string get_gender();
    string get_email();
    string get_college();
};

// Main functions
void BookEntry();
void BookMessage();
void DeleteBook();
void ReaderEntry();
void ReaderEntry(int input_sID);
void ReaderMessage();
void BorrowBook();
void ReturnBook();
void BorrowMessage();
void CountBook();


// Secondary functions
inline bool consist_of_num(string str);
inline bool is_email(string str);
inline bool is_price(string str);
bool is_sID_existent(int ID);
void update_file();
void delete_ID(vector<Book> &books_info, int ID);
void print_GUI();
void print_success();
void print_error(string error_message, bool terminate_message = false);
void start_operation(int ID);
bool is_file_empty(string FilePath);
int books_in_library();
void initialize_variables();
void save_BorrowInfo();
void start_BookSystem();

#endif
