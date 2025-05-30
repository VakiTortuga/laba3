#pragma once

#include <string>

class Book
{
private:
	struct Person { 
		std::string name, surname, patronymic; // имя, фамилия, отчество
	} author;                                  // поле для первого автора
	std::string title;                         // название книги
	struct Metadata {
		unsigned short pages, chapters;        // страницы, главы
	} content_data;                            // информация о содержании
	enum CoverType {
		none, soft, hard, ebook                // не определена, мягкая, твердая, электронная
	} cover_type;                              // тип обложки
	enum EditionStatus {
		unready, ready, published              // не готово, готово, издано
	} edition_status;                          // статус издания
	struct EditionInfo {
		unsigned short year;                   // год
		std::string publisher, isbn;           // издатель, ISBN
	} edition_info;                            // информация об издании

	void set_author(struct Person);
	void set_title(std::string);
	void set_content_data(struct );

	struct Person get_author();
	std::string get_title();

	void set_author(struct Person person);
	struct Person get_author();
	void set_author(struct Person person);
	struct Person get_author();
	void set_author(struct Person person);
	struct Person get_author();
	void set_author(struct Person person);
	struct Person get_author();

public:



};