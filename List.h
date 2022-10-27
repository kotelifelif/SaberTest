#pragma once
#include <string>
#include <map>
#include <vector>

struct ListNode {
	ListNode* prev = nullptr;
	ListNode* next = nullptr;
	ListNode* rand = nullptr; // указатель на произвольный элемент данного списка, либо NULL
	std::string data;
};

class List
{
public:
	List() = default;
	~List();
	void serialize(FILE* file); // сохранение в файл (открыт с помощью fopen(path, "wb"))
	void deserialize(FILE* file); // загрузка из файла (открыт с помощью fopen(path, "rb"))
	
	void push_back(ListNode& node);
	void push_front(ListNode& node);

	void pop_back();
	void pop_front();
	
	void change_looping(const bool is_ring);
	
	ListNode* get_head() const;	
	void set_head(ListNode& head);

	ListNode* get_tail() const;
	void set_tail(ListNode& tail);

	int size() const;
private:
	ListNode* head;
	ListNode* tail;
	bool is_ring;

	std::map<std::string, ListNode*> node_map;
	std::vector<std::string> keys;
	int count;
};

