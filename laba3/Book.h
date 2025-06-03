#pragma once

#include <string>

class Book
{
private:

	/* ���������� � ����� ������
	���� ������� ����� ����� ������ ���������� ��������
	���� ������� ����� ����� �������� "�� ���������", �� ������ ������ ������
	��������� ������� ����� ���������� �������� �� ���� �����, ���� �������� "�� ���������" �� ���� �����
	������ �������� ��������, ���� � ���� ������������ ���������� �� �������
	�������� ������ ������ ������������� (��. ������ �������)
	������ ������ ������, ���� ������ �� ����� � ������� (��. ������ �������)
	*/

	struct Person {                                 // ���� (���������) ��� ������� ������
		std::string name = "";                      // ���
		std::string surname = "";                   // �������
		std::string patronymic = "";                // ��������
	} author;

	std::string title = "";                         // �������� �����

	struct Metadata {                               // ���������� � ����������
		unsigned short pages = 0;                   // ��������
		unsigned short chapters = 0;                // �����
	} content_data;

	enum CoverType {                                // ��� �������
		NONE, SOFT, HARD, EBOOK
	} cover_type = NONE;

	enum EditionStatus {                            // ������ �������
		UNREADY, READY, PUBLISHED
	};

	struct EditionInfo {                                 // ���������� �� �������
		enum EditionStatus status = UNREADY;     // ������ �������
		unsigned short year = 0;                         // ���
		std::string publisher = "";                      // ��������
		std::string isbn = "";                           // ISBN
	} edition_info;

	// ������������� ������� ���������� �� ���������
	void init();
	// ���������� � ������� ������� ������� � ����������� �� ������������� �����
	enum EditionStatus getEditionStatus();
	// ��������� �������������� ISBN (��� "��������" �������)
	bool isValidIsbn() const;
	// ��������� �������������� ISBN-10
	static bool isValidIsbn10(const std::string&);
	// ��������� �������������� ISBN-13
	static bool isValidIsbn13(const std::string&);

public:

	/*���������� � �������������
	������������ �� ����� �������� ����� �������� "�� ���������" � �����, �� ������� ��� ��������
	��� ������� ������������ �������� ������������, ��� ���� ������� �������� �� ���������

	+++ ��������� �������� ������� �������
	*/

	// ����������� ��� ����������, ������� ������ � ���������� �� ���������
	Book();
	// ����������� � ����������� ��� ����� ������� � ������� (��� ������ ���������� �� �������)
	Book(struct Person, std::string, struct Metadata, enum CoverType);
	// ����������� � ����������� ��� �������� ����� (���� ��� ��������) +++��������
	Book(struct Person, std::string, struct Metadata, enum CoverType, struct EditionInfo);

	/* ���������� � ��������
	����������� ���������� � ������ �������� ������������ ��������, ��������� �������� ����� ������� ���� �� ������ �������
	������� �������� ������ ��� ������������ ����

	+++ ��������� �������� ������� �������
	*/

	// ���������� �������� ������ �����
	void setAuthor(struct Person);
	// ���������� �������� �������� �����
	void setTitle(std::string);
	// ���������� �������� ���������� � ����������
	void setContentData(struct Metadata);
	// ���������� �������� ���� �������
	void setCoverType(enum CoverType);
	// ���������� �������� ���������� �� ������� +++��������
	void publishBook(struct EditionInfo);

	/* ���������������� ������� */

	// ����� ���������� � ����� � �������
	void print() const;
	// ������� �������� ���������� ������� �� �����
	double pagesPerChapter() const;
	// �������� �������� ������ �����
	struct Person getAuthor() const;
	// �������� �������� �������� �����
	std::string getTitle() const;
	// �������� �������� ���� �������
	enum CoverType getCoverType() const;

};