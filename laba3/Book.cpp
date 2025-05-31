#include "Book.h"
#include <string>
#include <iostream>

// ������������� ������� ���������� �� ���������
void Book::init() {
    this->author.name = "";
    this->author.surname = "";
    this->author.patronymic = "";
    this->title = "";
    this->content_data.chapters = 0;
    this->content_data.pages = 0;
    this->cover_type = NONE;
    this->edition_info.edition_status = UNREADY;
    this->edition_info.publisher = "";
    this->edition_info.isbn = "";
    this->edition_info.year = 0;

}
// ���������� � ������� ������� ������� � ����������� �� ������������� �����
enum Book::EditionStatus Book::getEditionStatus() {
	if (this->edition_info.year != 0 &&
        this->edition_info.publisher != "" &&
        this->edition_info.isbn != "" ) { // ���� ���������� �� ������� ���������, ����� ��������� ����������
		this->edition_info.edition_status = PUBLISHED;
		return PUBLISHED;
	}
	if (this->author.name != "" &&
	    this->author.surname != "" &&
	    this->author.patronymic != "" &&
		this->title != "" &&
		this->content_data.chapters != 0 &&
		this->content_data.pages != 0 &&
		this->cover_type != NONE) { // ���� �� ���� ���� �� ����� �������� �� ���������, ����� ��������� ������� � �������
		this->edition_info.edition_status = READY;
		return READY;
	}
	this->edition_info.edition_status = UNREADY; // � ��������� ������ ����� ��������� �� �������
	return UNREADY;
}
// �������� ���������� �� �������
bool Book::checkEditionInfo() {
    if (this->edition_info.edition_status == READY && 
        this->edition_info.year > 2000 &&
        this->edition_info.year < 3000 &&
        this->edition_info.publisher != "" &&
        this->isValidIsbn()) {
        this->edition_info.edition_status = PUBLISHED;
        return true;
    }
    return false;
}

// ��������� �������������� ISBN (��� "��������" �������)
bool Book::isValidIsbn() const {
    const std::string& isbn = edition_info.isbn;

    // ������� ��� ������ � �������
    std::string cleanIsbn;
    for (char c : isbn) {
        if (c != '-' && !std::isspace(c)) {
            cleanIsbn += std::toupper(c); // X � ISBN-10 ������ ���� � ������� ��������
        }
    }

    // ��������� �����
    if (cleanIsbn.length() == 10) {
        return isValidIsbn10(cleanIsbn);
    }
    else if (cleanIsbn.length() == 13) {
        return isValidIsbn13(cleanIsbn);
    }

    return false;
}
// ��������� �������������� ISBN-10
bool isValidIsbn10(const std::string& isbn) {
    // ISBN-10 ������ ��������� 9 ���� + 1 ����� ��� X
    if (isbn.length() != 10) return false;

    int sum = 0;
    for (int i = 0; i < 9; ++i) {
        if (!std::isdigit(isbn[i])) return false;
        sum += (10 - i) * (isbn[i] - '0');
    }

    // ��������� ����������� ����� (����� ���� X ��� 10)
    char lastChar = isbn[9];
    if (lastChar == 'X') {
        sum += 10;
    }
    else if (std::isdigit(lastChar)) {
        sum += (lastChar - '0');
    }
    else {
        return false;
    }

    return (sum % 11 == 0);
}
// ��������� �������������� ISBN-13
bool isValidIsbn13(const std::string& isbn) {
    // ISBN-13 ������ ��������� 13 ���� � ���������� � 978 ��� 979
    if (isbn.length() != 13) return false;
    if (isbn.substr(0, 3) != "978" && isbn.substr(0, 3) != "979") {
        return false;
    }

    int sum = 0;
    for (int i = 0; i < 12; ++i) {
        if (!std::isdigit(isbn[i])) return false;
        int digit = isbn[i] - '0';
        sum += (i % 2 == 0) ? digit : digit * 3;
    }

    // �������� ����������� �����
    int checkDigit = isbn[12] - '0';
    if (checkDigit < 0 || checkDigit > 9) return false;

    int calculatedCheck = (10 - (sum % 10)) % 10;
    return (checkDigit == calculatedCheck);
}

// ����������� ��� ����������, ������� ������ � ���������� �� ���������
Book::Book() {
    this->init();
}
// ����������� � ����������� ��� ����� ������� � ������� (��� ������ ���������� �� �������)
Book::Book(struct Person _author, std::string _title, struct Metadata _content_data, enum CoverType _cover_type) {
    this->author = _author;
    this->title = _title;
    this->content_data = _content_data;
    this->cover_type = _cover_type;
    if (this->getEditionStatus() != READY)
    {
        this->init();
        throw std::invalid_argument("Error, values are incorrect.");
    }
}
// ����������� � ����������� ��� �������� ����� (���� ��� ��������) +++��������
Book::Book(struct Person _author, std::string _title, struct Metadata _content_data, enum CoverType _cover_type, struct EditionInfo _edition_status) {
    this->author = _author;
    this->title = _title;
    this->content_data = _content_data;
    this->cover_type = _cover_type;
    if (this->getEditionStatus() != READY)
    {
        this->init();
        throw std::invalid_argument("Error, mandatory values are empty.");
    }
    this->edition_info = _edition_status;
    if (this->checkEditionInfo() == false) {
        this->init();
        throw std::invalid_argument("Error, invalid edition info.");
    }
}

// ���������� �������� ������ �����
void Book::setAuthor(struct Person) {

}
// ���������� �������� �������� �����
void Book::setTitle(std::string){}
// ���������� �������� ���������� � ����������
void Book::setContentData(struct Metadata){}
// ���������� �������� ���� �������
void Book::setCoverType(enum CoverType){}
// ���������� �������� ���������� �� ������� +++��������
void Book::publishBook(enum EditionStatus) {

}

// ����� ���������� � ����� � �������
void Book::print() const {}
// ������� �������� ���������� ������� �� �����
double Book::pagesPerChapter() const {}
// �������� �������� ������ �����
struct Book::Person Book::getAuthor() const {}
// �������� �������� �������� �����
std::string Book::getTitle() const {}
// �������� �������� ���� �������
enum Book::CoverType Book::getCoverType() const {}