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
    this->edition_info.status = UNREADY;
    this->edition_info.publisher = "";
    this->edition_info.isbn = "";
    this->edition_info.year = 0;

}

// обновление и возврат статуса издани€ в зависимости от заполненности полей
enum Book::EditionStatus Book::getEditionStatus() {
    if (this->edition_info.year > 2000 &&
        this->edition_info.year < 3000 &&
        this->edition_info.publisher != "" &&
        this->isValidIsbn()) { // если информаци€ об издании заполнена, книга считаетс€ выпущенной
        this->edition_info.status = PUBLISHED;
        return PUBLISHED;
    }
    if (this->author.name != "" &&
        this->author.surname != "" &&
        this->author.patronymic != "" &&
        this->title != "" &&
        this->content_data.chapters != 0 &&
        this->content_data.pages != 0 &&
        this->cover_type != NONE) { // если ни одно поле не имеет значение по умолчанию, книга считаетс€ готовой к изданию
        this->edition_info.status = READY;
        return READY;
    }
    this->edition_info.status = UNREADY; // в противном случае книга считаетс€ не готовой
    return UNREADY;
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
        return this->Book::isValidIsbn10(cleanIsbn);
    }
    else if (cleanIsbn.length() == 13) {
        return this->Book::isValidIsbn13(cleanIsbn);
    }

    return false;
}

// валидаци€ идентификатора ISBN-10
bool Book::isValidIsbn10(const std::string& isbn){
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
bool Book::isValidIsbn13(const std::string& isbn) {
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
    if (this->getEditionStatus() != PUBLISHED) {
        this->init();
        throw std::invalid_argument("Error, invalid edition info.");
    }
}

// установить значение автора книги
void Book::setAuthor(struct Person _author) {
    if (this->edition_info.status == PUBLISHED) {
        throw std::logic_error("Error. You can't change the fields of a published book.");
    }
    if (_author.name == "" ||
        _author.surname == "" ||
        _author.patronymic == "") throw std::invalid_argument("Error, you cant set empty author info.");

    this->author = _author;
    this->getEditionStatus();
}

// установить значение название книги
void Book::setTitle(std::string _title) {
    if (this->edition_info.status == PUBLISHED) {
        throw std::logic_error("Error. You can't change the fields of a published book.");
    }
    if (_title == "") throw std::invalid_argument("Error, you cant set empty title.");
    else {
        this->title = _title;
        this->getEditionStatus();
    }
}

// установить значение информации о содержании
void Book::setContentData(struct Metadata _content_data) {
    if (this->edition_info.status == PUBLISHED) {
        throw std::logic_error("Error. You can't change the fields of a published book.");
    }
    if (_content_data.pages == 0 && _content_data.chapters == 0) {
        // ƒопустимо (например, книга ещЄ не готова)
    } 
    else if (_content_data.pages == 0 || _content_data.chapters == 0) {
        throw std::invalid_argument("Error: pages and chapters must both be zero or both non-zero.");
    }

    this->content_data = _content_data;
    this->getEditionStatus();
}

// установить значение типа обложки
void Book::setCoverType(enum CoverType _cover_type) {
    if (this->edition_info.status == PUBLISHED) {
        throw std::logic_error("Error. You can't change the fields of a published book.");
    }
    if (_cover_type == NONE) {
        throw std::invalid_argument("Error: cover type cannot be NONE for a ready book.");
    }
    else {
        this->cover_type = _cover_type;
        this->getEditionStatus();
    }
}

// установить значение информации об издании +++издающий
void Book::publishBook(struct EditionInfo _edition_info) {
    if (this->edition_info.status == PUBLISHED) {
        throw std::logic_error("Error. You can't change the fields of a published book.");
    }
    if (this->getEditionStatus() != READY) {
        throw std::logic_error("Error. The book is not ready for publishing.");
    }

    EditionInfo old_info = this->edition_info; // —охран€ем предыдущее состо€ние
    this->edition_info = _edition_info;

    if (this->getEditionStatus() != PUBLISHED) {
        this->edition_info = old_info; // ¬осстанавливаем, если валидаци€ не прошла
        throw std::invalid_argument("Error, invalid edition info.");
    }
}

// ¬ывод информации о книге в консоль
void Book::print() const {
    std::cout << "Title: " << title << std::endl;

    std::cout << "Author: ";
    if (author.name == "") std::cout << "Not stated yet" << std::endl;
    else std::cout  << author.name << " " << author.patronymic << " " << author.surname << std::endl;

    std::cout << "Content: " << content_data.chapters << " chapters, " << content_data.pages << " pages" << std::endl;
    std::cout << "Book type: ";
    switch (cover_type) {
    case NONE:
    {
        std::cout << "not stated";
        break;
    }
    case SOFT:
    {
        std::cout << "soft cover";
        break;
    }
    case HARD:
    {
        std::cout << "hard cover";
        break;
    }
    case EBOOK:
    {
        std::cout << "e-book";
        break;
    }
    }
    std::cout << std::endl;
    if (edition_info.status == PUBLISHED) {
        std::cout << "Published in " << edition_info.year << " by " << edition_info.publisher << ". ISBN: " << edition_info.isbn << std::endl;
    }
}

// ¬озврат среднего количества страниц на главу
double Book::pagesPerChapter() const {
    if (content_data.pages == 0 || content_data.chapters == 0) {
        return 0.0;
    }
    return (double)content_data.pages / content_data.chapters;
}

// получить значение автора книги
struct Book::Person Book::getAuthor() const {
    return this->author;
}

// получить значение название книги
std::string Book::getTitle() const {
    return this->title;
}

// получить значение типа обложки
enum Book::CoverType Book::getCoverType() const {
    return this->cover_type;
}