#include "List.h"
#include <iostream>

using namespace std;

List::~List()
{
	while (head)
	{
		tail = head->next;
		delete head;
		head = tail;
	}
}

void List::change_looping(const bool is_ring)
{
	this->is_ring = is_ring;
	if (this->is_ring) {
		tail->next = head;
		head->prev = tail;
	}
	else {
		tail->next = nullptr;
		head->prev = nullptr;
	}
}

ListNode* List::get_head() const {
	return head;
}

void List::set_head(ListNode& head) {
	this->head = &head;
}

ListNode* List::get_tail() const {
	return tail;
}

void List::set_tail(ListNode& tail) {
	this->tail = &tail;
}

int List::size() const {
	return count;
}

void List::serialize(FILE* file)
{
	if (file == nullptr) {
		return;
	}
	fwrite(&count, sizeof(count), 1, file);
	fwrite(&is_ring, sizeof(is_ring), 1, file);

	ListNode* current_node = head;
	int count_nodes = count;
	int data_size = 0;
	string data;
	while (count_nodes != 0) {
		data_size = current_node->data.size();
		data = current_node->data;
		fwrite(&data_size, sizeof(int), 1, file);
		fwrite(data.c_str(), data_size, 1, file);
		if (current_node->rand == nullptr) {
			data_size = 0;
			fwrite(&data_size, sizeof(int), 1, file);
		}
		else {
			data_size = current_node->rand->data.size();
			data = current_node->rand->data;
			fwrite(&data_size, sizeof(int), 1, file);
			fwrite(data.c_str(), data_size, 1, file);
		}
		count_nodes--;
		current_node = current_node->next;
	}

	fclose(file);
}

void List::deserialize(FILE* file)
{
	if (file == nullptr) {
		return;
	}
	this->count = 0;
	int count_nodes = 0;
	
	fread(&count_nodes, sizeof(count_nodes), 1, file);
	fread(&is_ring, sizeof(is_ring), 1, file);

	int data_size = 0;
	int rand_data_size = 0;
	string rand_data;
	string data;
	std::vector<char> vector_data;
	for (int index = 0; index < count_nodes; index++) {
		fread(&data_size, sizeof(int), 1, file);
		vector_data.resize(data_size);
		fread(&vector_data[0], 1, data_size, file);

		ListNode* current_node = new ListNode;
		current_node->data = string(vector_data.begin(), vector_data.end());
		push_back(*current_node);
		node_map[current_node->data] = current_node;

		fread(&data_size, sizeof(int), 1, file);
		if (data_size == 0) {
			keys.push_back("");
			continue;
		}

		vector_data.resize(data_size);
		fread(&vector_data[0], 1, data_size, file);
		keys.push_back(string(vector_data.begin(), vector_data.end()));
	}

	ListNode* current_node = head;
	int index = 0;
	for (int index = 0; index < count; index++) {
		if (!keys[index].empty()) {
			current_node->rand = node_map[keys[index]];
			current_node = current_node->next;
		}
		index++;
	}

	fclose(file);
}

void List::push_back(ListNode& node)
{
	if (count == 0) {
		count++;
		node.next = nullptr;
		node.prev = nullptr;
		head = &node;
		tail = &node;
		if (is_ring) {
			head->prev = tail;
			tail->next = head;
		}
		return;
	}
	count++;
	node.prev = tail;
	tail->next = &node;
	tail = &node;
}

void List::push_front(ListNode& node)
{
	if (count == 0) {
		count++;
		node.next = nullptr;
		node.prev = nullptr;
		head = &node;
		tail = &node;
		if (is_ring) {
			head->prev = tail;
			tail->next = head;
		}
		return;
	}
	count++;
	node.next = head;
	head->prev = &node;
	head = &node;
}

void List::pop_back() {
	if (count == 0) {
		return;
	}
	count--;
	tail = tail->prev;
	if (!is_ring && count != 0) {
		tail->next = nullptr;
	}
	else if (count != 0) {
		tail->next = head;
	}
}

void List::pop_front() {
	if (count == 0) {
		return;
	}
	count--;
	head = head->next;
	if (!is_ring && count != 0) {
		head->prev = nullptr;
	}
	else if (count != 0) {
		head->prev = tail;
	}
}


