#include "Book.h"
#include <string>
#include <iostream>

// инициализаци€ объекта значени€ми по умолчанию
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
// обновление и возврат статуса издани€ в зависимости от заполненности полей
enum Book::EditionStatus Book::getEditionStatus() {
	if (this->edition_info.year != 0 &&
        this->edition_info.publisher != "" &&
        this->edition_info.isbn != "" ) { // если информаци€ об издании заполнена, книга считаетс€ выпущенной
		this->edition_info.edition_status = PUBLISHED;
		return PUBLISHED;
	}
	if (this->author.name != "" &&
	    this->author.surname != "" &&
	    this->author.patronymic != "" &&
		this->title != "" &&
		this->content_data.chapters != 0 &&
		this->content_data.pages != 0 &&
		this->cover_type != NONE) { // если ни одно поле не имеет значение по умолчанию, книга считаетс€ готовой к изданию
		this->edition_info.edition_status = READY;
		return READY;
	}
	this->edition_info.edition_status = UNREADY; // в противном случае книга считаетс€ не готовой
	return UNREADY;
}
// проверка информации об издании
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

// валидаци€ идентификатора ISBN (дл€ "издающих" методов)
bool Book::isValidIsbn() const {
    const std::string& isbn = edition_info.isbn;

    // ”дал€ем все дефисы и пробелы
    std::string cleanIsbn;
    for (char c : isbn) {
        if (c != '-' && !std::isspace(c)) {
            cleanIsbn += std::toupper(c); // X в ISBN-10 должен быть в верхнем регистре
        }
    }

    // ѕровер€ем длину
    if (cleanIsbn.length() == 10) {
        return isValidIsbn10(cleanIsbn);
    }
    else if (cleanIsbn.length() == 13) {
        return isValidIsbn13(cleanIsbn);
    }

    return false;
}
// валидаци€ идентификатора ISBN-10
bool isValidIsbn10(const std::string& isbn) {
    // ISBN-10 должен содержать 9 цифр + 1 цифру или X
    if (isbn.length() != 10) return false;

    int sum = 0;
    for (int i = 0; i < 9; ++i) {
        if (!std::isdigit(isbn[i])) return false;
        sum += (10 - i) * (isbn[i] - '0');
    }

    // ќбработка контрольной цифры (может быть X дл€ 10)
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
// валидаци€ идентификатора ISBN-13
bool isValidIsbn13(const std::string& isbn) {
    // ISBN-13 должен содержать 13 цифр и начинатьс€ с 978 или 979
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

    // ѕроверка контрольной цифры
    int checkDigit = isbn[12] - '0';
    if (checkDigit < 0 || checkDigit > 9) return false;

    int calculatedCheck = (10 - (sum % 10)) % 10;
    return (checkDigit == calculatedCheck);
}

// конструктор без параметров, создает объект с значени€ми по умолчанию
Book::Book() {
    this->init();
}
// конструктор с параметрами дл€ книги готовой к изданию (нет только информации об издании)
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
// конструктор с параметрами дл€ изданной книги (есть все значени€) +++издающий
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

// установить значение автора книги
void Book::setAuthor(struct Person) {

}
// установить значение название книги
void Book::setTitle(std::string){}
// установить значение информации о содержании
void Book::setContentData(struct Metadata){}
// установить значение типа обложки
void Book::setCoverType(enum CoverType){}
// установить значение информации об издании +++издающий
void Book::publishBook(enum EditionStatus) {

}

// ¬ывод информации о книге в консоль
void Book::print() const {}
// ¬озврат среднего количества страниц на главу
double Book::pagesPerChapter() const {}
// получить значение автора книги
struct Book::Person Book::getAuthor() const {}
// получить значение название книги
std::string Book::getTitle() const {}
// получить значение типа обложки
enum Book::CoverType Book::getCoverType() const {}