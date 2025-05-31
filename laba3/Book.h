#pragma once

#include <string>

// валидация идентификатора ISBN-10
bool isValidIsbn10(const std::string&);
// валидация идентификатора ISBN-13
bool isValidIsbn13(const std::string&);

class Book
{
private:

	/* ИНФОРМАЦИЯ О ПОЛЯХ КЛАССА
	Поля объекта могут иметь только корректные значения
	Поля объекта могут иметь значения "по умолчанию", но объект нельзя издать
	Структуры объекта имеют корректные значения во всех полях, либо значения "по умолчанию" во всех полях
	Объект является изданным, если у него присутствует информация об издании
	Изданный объект нельзя редактировать (см. статус издания)
	Объект нельзя издать, если объект не готов к изданию (см. статус издания)
	*/

	struct Person {                                 // поле (структура) ФИО первого автора
		std::string name = "";                      // имя
		std::string surname = "";                   // фамилия
		std::string patronymic = "";                // отчество
	} author;

	std::string title = "";                         // название книги

	struct Metadata {                               // информация о содержании
		unsigned short pages = 0;                   // страницы
		unsigned short chapters = 0;                // главы
	} content_data;

	enum CoverType {                                // тип обложки
		NONE, SOFT, HARD, EBOOK
	} cover_type = NONE;

	enum EditionStatus {                            // статус издания
		UNREADY, READY, PUBLISHED
	};

	struct EditionInfo {                                 // информация об издании
		enum EditionStatus edition_status = UNREADY;     // статус издания
		unsigned short year = 0;                         // год
		std::string publisher = "";                      // издатель
		std::string isbn = "";                           // ISBN
	} edition_info;

	// инициализация объекта значениями по умолчанию
	void init();
	// обновление и возврат статуса издания в зависимости от заполненности полей
	enum EditionStatus getEditionStatus();
	// валидация идентификатора ISBN (для "издающих" методов)
	bool isValidIsbn() const;
	// проверка информации об издании
	bool checkEditionInfo();

public:

	/*ИНФОРМАЦИЯ О КОНСТРУКТОРАХ
	Конструкторы не могут оставить часть значений "по умолчанию" у полей, за которые они отвечают
	При передач некорректных значений конструктору, все поля получат значения по умолчанию

	+++ обновляют значение статуса издания
	*/

	// конструктор без параметров, создает объект с значениями по умолчанию
	Book();
	// конструктор с параметрами для книги готовой к изданию (нет только информации об издании)
	Book(struct Person, std::string, struct Metadata, enum CoverType);
	// конструктор с параметрами для изданной книги (есть все значения) +++издающий
	Book(struct Person, std::string, struct Metadata, enum CoverType, struct EditionInfo);

	/* ИНФОРМАЦИЯ О СЕТТЕРАХ
	выбрасывают исключения в случае передачи некорректных значений, оставляют значения полей которые были до вызова функции
	сеттеры работают только для невыпущенных книг

	+++ обновляют значение статуса издания
	*/

	// установить значение автора книги
	void setAuthor(struct Person);
	// установить значение название книги
	void setTitle(std::string);
	// установить значение информации о содержании
	void setContentData(struct Metadata);
	// установить значение типа обложки
	void setCoverType(enum CoverType);
	// установить значение информации об издании +++издающий
	void publishBook(enum EditionStatus);

	/* ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ */

	// Вывод информации о книге в консоль
	void print() const;
	// Возврат среднего количества страниц на главу
	double pagesPerChapter() const;
	// получить значение автора книги
	struct Person getAuthor() const;
	// получить значение название книги
	std::string getTitle() const;
	// получить значение типа обложки
	enum CoverType getCoverType() const;

};