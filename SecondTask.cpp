void remove_dups(char* str) {
	if (!str)
		return;

	size_t index = 0;
	size_t temp_index = 0;

	char* temp_str = str;
	while (str[index] != '\0') {
		if (str[index] != str[index + 1]) {
			temp_str[temp_index] = str[index];
			temp_index++;
		}
		index++;
	}

	for (int index = 0; index < temp_index; index++) {
		str[index] = temp_str[index];
	}
	str[temp_index] = '\0';
}
