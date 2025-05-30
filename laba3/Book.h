#pragma once

#include <string>

class Book
{
private:
	struct Person { 
		std::string name, surname, patronymic; // ���, �������, ��������
	} author;                                  // ���� ��� ������� ������
	std::string title;                         // �������� �����
	struct Metadata {
		unsigned short pages, chapters;        // ��������, �����
	} content_data;                            // ���������� � ����������
	enum CoverType {
		none, soft, hard, ebook                // �� ����������, ������, �������, �����������
	} cover_type;                              // ��� �������
	enum EditionStatus {
		unready, ready, published              // �� ������, ������, ������
	} edition_status;                          // ������ �������
	struct EditionInfo {
		unsigned short year;                   // ���
		std::string publisher, isbn;           // ��������, ISBN
	} edition_info;                            // ���������� �� �������

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