#include "local.h"

column* head;
column* tail;
int data_start_index = 0;
int data_end_index = 0;
int data_line_length = 0;
FILE* F;

int initalizing(char* file_name) {
	column tmp;
	column* cur;
	int column_line_length = 0;
	char* column_list;
	char* buff;
	char* token;
	int count = 0;
	if ((head = (column*)malloc(sizeof(column))) == NULL) {
		strcpy(err_msg, "Memory Allocation Failed");

		return -1;
	}
	head->length = 0; head->start_index = 0; head->type = 0; head->next = 0; head->name = 0;
	tail = head;
	if ((_file_location = (char*)malloc(strlen(file_name) + 5)) == NULL) {
		strcpy(err_msg, "Memory Allocation Failed");

		return -1;
	}
	strcpy(_file_location, file_name);
	strcat(_file_location, ".dat");
	F = fopen(_file_location, "rb");
	if (F == NULL) {
		strcpy(err_msg, "File Not Exist");
		return -1;
	}
	while (1) {
		char a = fgetc(F);
		column_line_length++;
		if (a == '\n')
			break;
	}
	fseek(F, 0, SEEK_SET);
	buff = (char*)malloc(column_line_length + 1);
	if (buff == NULL) {
		strcpy(err_msg, "Memory Allocation Failed");

		return -1;
	}
	column_list = fgets(buff, column_line_length + 1, F);
	token = strtok(column_list, " ");
	while (1) {
		switch (count % 3) {
		case 0:
			tmp.name = (char*)malloc(strlen(token) + 1);
			if (tmp.name == 0) {
				strcpy(err_msg, "Memory Allocation Failed");
				fclose(F);

				return -1;
			}
			strcpy(tmp.name, token);
			break;
		case 1:
			tmp.type = atoi(token);
			break;
		case 2:
			tmp.length = atoi(token);
			if (add_column(tmp) == -1) {
				fclose(F);
				free(tmp.name);
				return -1;
			}
			free(tmp.name);
			break;
		}
		count++;
		token = strtok(NULL, " ");
		if (token == NULL)
			break;
	}
	cur = head->next;
	while (1) {
		data_line_length += cur->length;
		if (cur->next != 0)
			cur = cur->next;
		else
			break;
	}
	{
		char tmp = ' ';
		int count = 0;
		fseek(F, 0, SEEK_SET);
		while (tmp != '\n') {
			tmp = fgetc(F);
			count++;
		}
		data_start_index = count;
	}
	fseek(F, 0, SEEK_END);
	data_end_index = ftell(F);
	fclose(F);
	free(buff);
	return 0;
}
int add_column(column tmp) {
	column* new_column = (column*)malloc(sizeof(column));
	if (new_column == 0) {
		strcpy(err_msg, "Memory Allocation Failed");
		return -1;
	}
	new_column->name = (char*)malloc(strlen(tmp.name) + 1);
	if (new_column->name == 0) {
		strcpy(err_msg, "Memory Allocation Failed");
		return -1;
	}
	strcpy(new_column->name, tmp.name);
	new_column->type = tmp.type;
	new_column->length = tmp.length;
	new_column->start_index = (tail->start_index + tail->length);
	new_column->next = 0;
	tail->next = new_column;
	tail = new_column;

	return 0;
}
int _create(char* file_name, char* column_list) {
	char* _file_name;
	char* _column_list;
	char* token;
	if ((_file_name = (char*)malloc(strlen(file_name) + 5)) == NULL) {
		strcpy(err_msg, "Memory Allocation Failed");

		return -1;
	}
	strcpy(_file_name, file_name);
	strcat(_file_name, ".dat");
	if ((_column_list = (char*)malloc(strlen(column_list) + 1)) == NULL) {
		strcpy(err_msg, "Memory Allocation Failed");

		free(_file_name);
		return -1;
	}
	strcpy(_column_list, column_list);
	if ((F = fopen(_file_name, "wb")) == NULL) {
		strcpy(err_msg, "File Can't Open");

		free(_file_name);
		free(_column_list);
		return -1;
	}

	token = strtok(_column_list, " ()");
	fputs(token, F); fputc(' ', F);
	token = strtok(NULL, " ()");
	if (token == NULL) {
		strcpy(err_msg, "Data Type Error");

		fclose(F);
		remove(_file_name);
		free(_file_name);
		free(_column_list);
		return -1;
	}
	if (!strcmp(token, "INT") || !strcmp(token, "int"))
		fputs("1 4", F);
	else if (!strcmp(token, "FLOAT") || !strcmp(token, "float"))
		fputs("2 4", F);
	else if (!strcmp(token, "DOUBLE") || !strcmp(token, "double"))
		fputs("3 8", F);
	else if (!strcmp(token, "CHAR") || !strcmp(token, "char"))
		fputs("4 1", F);
	else if (!strcmp(token, "VARCHAR") || !strcmp(token, "varchar")) {
		fputs("5 ", F);
		token = strtok(NULL, " ()");
		fputs(token, F);
	}
	else {
		strcpy(err_msg, "Data Type Error");

		fclose(F);
		remove(_file_name);
		free(_file_name);
		free(_column_list);
		return -1;
	}
	while ((token = strtok(NULL, " ()")) != NULL) {
		fputc(' ', F); fputs(token, F); fputc(' ', F);
		token = strtok(NULL, " ()");
		if (token == NULL) {
			strcpy(err_msg, "Data Type Error");

			fclose(F);
			remove(_file_name);
			free(_file_name);
			free(_column_list);
			return -1;
		}
		if (!strcmp(token, "INT") || !strcmp(token, "int"))
			fputs("1 4", F);
		else if (!strcmp(token, "FLOAT") || !strcmp(token, "float"))
			fputs("2 4", F);
		else if (!strcmp(token, "DOUBLE") || !strcmp(token, "double"))
			fputs("3 8", F);
		else if (!strcmp(token, "CHAR") || !strcmp(token, "char"))
			fputs("4 1", F);
		else if (!strcmp(token, "VARCHAR") || !strcmp(token, "varchar")) {
			fputs("5 ", F);
			token = strtok(NULL, " ()");
			fputs(token, F);
		}
		else {
			strcpy(err_msg, "Data Type Error");

			fclose(F);
			remove(_file_name);
			free(_file_name);
			free(_column_list);
			return -1;
		}
	}
	fputc('\n', F);

	free(_file_name);
	free(_column_list);
	fclose(F);

	return 0;
}
int _insert(char* values) {

	char* _values = (char*)malloc(strlen(values) + 1);
	char* ptr = _values;
	column* cur = head->next;
	int index = 0;
	int IS_STRING = 0;

	strcpy(_values, values);
	F = fopen(_file_location, "ab");
	while (1) {
		if (ptr[index] == 39)
			IS_STRING++;
		if (ptr[index] == ',' && IS_STRING % 2 == 0) {
			char* tmp = (char*)malloc(index + 1);
			char* token;
			strncpy(tmp, ptr, index);
			tmp[index] = '\0';
			if (IS_STRING == 2) {
				token = strtok(tmp, "'");
				if (token[0] == ' ')
					token = strtok(NULL, "'");
			}
			else if (tmp[0] == ' ' || tmp[strlen(tmp) - 1] == ' ') {
				token = strtok(tmp, " ");
			}
			else
				token = tmp;
			ptr = ptr + index + 1;
			if (!strcmp(token, "NULL")) {
				switch (cur->type) {
				case _INT:
				case _FLOAT:
					fputc('N', F); fputc('U', F); fputc('L', F); fputc('L', F);
					break;
				case _DOUBLE:
					fputc('N', F); fputc('U', F); fputc('L', F); fputc('L', F);
					for (unsigned int i = 0; i < (cur->length) - 4; i++)
						fputc(pad, F);
					break;
				case _CHAR:
				case _VARCHAR:
					for (unsigned int i = 0; i < cur->length; i++)
						fputc(pad, F);
					break;
				}
			}
			else {
				switch (cur->type) {
				case _CHAR:
				case _VARCHAR:
					if (strlen(token) > cur->length) {
						strcpy(err_msg, "Value Length Over");
						free(_values);
						free(tmp);
						fclose(F);
						return -1;
					}
				}

				switch (cur->type) {
				case _INT:
				{
					int i_token = atoi(token);
					fwrite(&i_token, sizeof(int), 1, F);

					break;
				}
				case _DOUBLE:
				{
					char* pos = NULL;
					double d_token = strtod(token, &pos);
					fwrite(&d_token, sizeof(double), 1, F);

					break;
				}
				case _FLOAT:
				{
					char* pos = NULL;
					float f_token = strtof(token, &pos);
					fwrite(&f_token, sizeof(float), 1, F);

					break;
				}
				case _CHAR:
				{
					char c_token = token[0];
					fputc(c_token, F);
					break;
				}
				case _VARCHAR:
				{
					int padding;
					fputs(token, F);
					if (strlen(token) != cur->length) {
						padding = cur->length - strlen(token);
						for (int i = 0; i < padding; i++)
							fputc(pad, F);
					}
					break;
				}
				}
			}
			cur = cur->next;
			index = 0;
			IS_STRING = 0;
			free(tmp);
			continue;
		}
		if (ptr[index] == '\0') {
			ptr = strtok(ptr, "' ");
			if (IS_STRING == 2) {
				if (ptr[0] == ' ')
					ptr = strtok(NULL, "'");
			}
			if (!strcmp(ptr, "NULL")) {
				switch (cur->type) {
				case _INT:
				case _FLOAT:
					fputc('N', F); fputc('U', F); fputc('L', F); fputc('L', F);
					break;
				case _DOUBLE:
					fputc('N', F); fputc('U', F); fputc('L', F); fputc('L', F);
					for (unsigned int i = 0; i < (cur->length) - 4; i++)
						fputc(pad, F);
					break;
				case _CHAR:
				case _VARCHAR:
					for (unsigned int i = 0; i < cur->length; i++)
						fputc(pad, F);
					break;
				}
			}
			else {
				switch (cur->type) {
				case _CHAR:
				case _VARCHAR:
					if (strlen(ptr) > cur->length) {
						strcpy(err_msg, "Value Length Over");
						free(_values);
						fclose(F);
						return -1;
					}
				}

				switch (cur->type) {
				case _INT:
				{
					int i_token = atoi(ptr);
					fwrite(&i_token, sizeof(int), 1, F);

					break;
				}
				case _DOUBLE:
				{
					char* pos = NULL;
					double d_token = strtod(ptr, &pos);
					fwrite(&d_token, sizeof(double), 1, F);

					break;
				}
				case _FLOAT:
				{
					char* pos = NULL;
					float f_token = strtof(ptr, &pos);
					fwrite(&f_token, sizeof(float), 1, F);

					break;
				}
				case _CHAR:
				{
					char c_token = ptr[0];
					fputc(c_token, F);
					break;
				}
				case _VARCHAR:
				{
					int padding;
					fputs(ptr, F);
					if (strlen(ptr) != cur->length) {
						padding = cur->length - strlen(ptr);
						for (int i = 0; i < padding; i++)
							fputc(pad, F);
					}

					break;
				}

				}

			}
			if (cur->next == 0)
				break;
			else {
				while (cur->next != 0) {
					cur = cur->next;
					switch (cur->type) {
					case _INT:
					case _FLOAT:
						fputc('N', F); fputc('U', F); fputc('L', F); fputc('L', F);
						break;
					case _DOUBLE:
						fputc('N', F); fputc('U', F); fputc('L', F); fputc('L', F);
						for (unsigned int i = 0; i < (cur->length) - 4; i++)
							fputc(pad, F);
						break;
					case _CHAR:
					case _VARCHAR:
						for (unsigned int i = 0; i < cur->length; i++)
							fputc(pad, F);
						break;
					}
				}
				break;
			}
		}

		index++;
	}
	fseek(F, 0, SEEK_END);
	data_end_index = ftell(F);
	free(_values);
	fclose(F);
	return 0;
}
int _delete(char* conditional) {
	FILE* tmp_file;
	char* _conditional = (char*)malloc(strlen(conditional) + 1);
	char* conditional_name, * conditional_value;
	int conditional_search_success = -1;
	int column_found = 1;
	int search_start_index;
	column* cur = head->next;

	strcpy(_conditional, conditional);
	conditional_name = strtok(_conditional, "= ");
	conditional_value = strtok(NULL, "= \0");
	while (1) {
		if (!strcmp(cur->name, conditional_name)) {
			if (cur->type == _CHAR || cur->type == _VARCHAR) {
				if (cur->length < strlen(conditional_value) - 2 && strcmp(conditional_value, "NULL")) {
					free(_conditional);
					strcpy(err_msg, "Conditional Length Over");
					return -1;
				}
				else {
					if (strcmp(conditional_value, "NULL"))
						conditional_value = strtok(conditional_value, "'");
				}
			}
			column_found = 0;
			break;
		}
		if (cur->next != 0)
			cur = cur->next;
		else
			break;
	}
	if (column_found) {
		free(_conditional);
		strcpy(err_msg, "Conditional Column Not Found");
		return -1;
	}

	tmp_file = fopen("tmp.dat", "wb");
	F = fopen(_file_location, "rb");

	{
		char* column_buff;
		char tmp = ' ';
		int count = 0;
		while (tmp != '\n') {
			tmp = fgetc(F);
			count++;
		}
		column_buff = (char*)malloc(count + 2);
		fseek(F, 0, SEEK_SET);
		fputs(fgets(column_buff, count + 2, F), tmp_file);
		free(column_buff);
	}

	search_start_index = data_start_index;
	while (search_start_index < data_end_index) {
		char IS_NULL[5];
		fseek(F, search_start_index + (cur->start_index), SEEK_SET);
		switch (cur->type) {
		case _INT:
		{
			int i_token;
			if (!strcmp(conditional_value, "NULL")) {
				fread(IS_NULL, 4, 1, F);
				IS_NULL[4] = '\0';
				if (!strcmp(IS_NULL, "NULL"))
					conditional_search_success = 1;
				break;
			}
			fread(&i_token, sizeof(int), 1, F);
			if (i_token == atoi(conditional_value))
				conditional_search_success = 1;
			break;
		}
		case _FLOAT:
		{
			float f_token;
			char* pos;
			if (!strcmp(conditional_value, "NULL")) {
				fread(IS_NULL, 4, 1, F);
				IS_NULL[4] = '\0';
				if (!strcmp(IS_NULL, "NULL"))
					conditional_search_success = 1;
				break;
			}
			fread(&f_token, sizeof(float), 1, F);
			if (fabsf(strtof(conditional_value, &pos) - f_token) <= FLT_EPSILON)
				conditional_search_success = 1;
			break;
		}
		case _DOUBLE:
		{
			double d_token;
			char* pos;
			if (!strcmp(conditional_value, "NULL")) {
				fread(IS_NULL, 4, 1, F);
				IS_NULL[4] = '\0';
				if (!strcmp(IS_NULL, "NULL"))
					conditional_search_success = 1;
				break;
			}
			fread(&d_token, sizeof(double), 1, F);
			if (fabs(strtod(conditional_value, &pos) - d_token) <= DBL_EPSILON)
				conditional_search_success = 1;
			break;
		}
		case _CHAR:
		{
			char c_token;
			if (!strcmp(conditional_value, "NULL")) {
				c_token = fgetc(F);
				if (c_token == pad)
					conditional_search_success = 1;
				break;
			}
			c_token = fgetc(F);
			if (c_token == conditional_value[0])
				conditional_search_success = 1;
			break;
		}
		case _VARCHAR:
		{
			char* s_token;
			char c_token;
			if (!strcmp(conditional_value, "NULL")) {
				c_token = fgetc(F);
				if (c_token == pad)
					conditional_search_success = 1;
				break;
			}
			s_token = (char*)malloc(cur->length + 1);
			fread(s_token, cur->length, 1, F);
			s_token = strtok(s_token, pad_seprator);
			if (!strcmp(s_token, conditional_value))
				conditional_search_success = 1;
			free(s_token);
			break;
		}
		}
		if (conditional_search_success == 0 || conditional_search_success == -1) {
			void* copy_line = malloc(data_line_length);
			if (copy_line == 0) {
				free(_conditional);
				fclose(F);
				fclose(tmp_file);
				remove("tmp.dat");
				strcpy(err_msg, "Memory Allocation Failed");
				return -1;
			}
			fseek(F, search_start_index, SEEK_SET);
			fread(copy_line, data_line_length, 1, F);
			fwrite(copy_line, data_line_length, 1, tmp_file);
			free(copy_line);
		}
		else
			conditional_search_success = 0;

		search_start_index += data_line_length;
	}
	if (conditional_search_success == -1) {
		free(_conditional);
		fclose(F);
		fclose(tmp_file);
		remove("tmp.dat");
		strcpy(err_msg, "Conditional Value Not Found");
		return -1;
	}
	fseek(tmp_file, 0, SEEK_END);
	data_end_index = ftell(tmp_file);
	free(_conditional);
	fclose(F);
	fclose(tmp_file);
	remove(_file_location);
	if (rename("tmp.dat", _file_location) != 0) {
		strcpy(err_msg, "File Rename Error");
		return -1;
	}
	return 0;
}
int _update(char* conditional, char* set) {
	char* _conditional = (char*)malloc(strlen(conditional) + 1);
	char* conditional_name, * conditional_value;
	column* conditional_column = 0;
	char* _set = (char*)malloc(strlen(set) + 1);
	char* set_name, * set_value;
	column* set_column = 0;

	int padding = 0;
	int search_start_index;
	int conditional_search_success = -1;

	column* cur;
	strcpy(_conditional, conditional);
	strcpy(_set, set);

	conditional_name = strtok(_conditional, "= ");
	conditional_value = strtok(NULL, "= \0");
	set_name = strtok(_set, "= ");
	set_value = strtok(NULL, "= \0");

	cur = head->next;
	while (1) {
		if (!strcmp(cur->name, conditional_name)) {
			if (cur->type == _CHAR || cur->type == _VARCHAR) {
				if (cur->length < strlen(conditional_value) - 2 && strcmp(conditional_value, "NULL")) {
					strcpy(err_msg, "Conditional Length Over");
					free(_conditional);
					free(_set);
					return -1;
				}
			}
			if (strcmp(conditional_value, "NULL"))
				conditional_value = strtok(conditional_value, "'");
			conditional_column = cur;
		}
		if (!strcmp(cur->name, set_name)) {
			if (cur->type == _CHAR || cur->type == _VARCHAR) {
				if (cur->length < strlen(set_value) - 2 && strcmp(set_value, "NULL")) {
					strcpy(err_msg, "Set Length Over");
					free(_conditional);
					free(_set);
					return -1;
				}
			}
			set_column = cur;
		}
		if (cur->next != 0)
			cur = cur->next;
		else
			break;
	}
	if (conditional_column == 0) {
		strcpy(err_msg, "Conditional Column Not Found");
		free(_conditional);
		free(_set);
		return -1;
	}
	else if (set_column == 0) {
		strcpy(err_msg, "Set Column Not Found");
		free(_conditional);
		free(_set);
		return -1;
	}
	F = fopen(_file_location, "rb+");

	search_start_index = data_start_index;
	while (search_start_index < data_end_index) {
		char IS_NULL[5];
		fseek(F, search_start_index + conditional_column->start_index, SEEK_SET);
		switch (conditional_column->type) {
		case _INT:
		{
			int i_token;
			if (!strcmp(conditional_value, "NULL")) {
				fread(IS_NULL, 4, 1, F);
				IS_NULL[4] = '\0';
				if (!strcmp(IS_NULL, "NULL"))
					conditional_search_success = 1;
				break;
			}
			fread(&i_token, sizeof(int), 1, F);
			if (i_token == atoi(conditional_value))
				conditional_search_success = 1;
			break;
		}
		case _FLOAT:
		{
			float f_token;
			char* pos;
			if (!strcmp(conditional_value, "NULL")) {
				fread(IS_NULL, 4, 1, F);
				IS_NULL[4] = '\0';
				if (!strcmp(IS_NULL, "NULL"))
					conditional_search_success = 1;
				break;
			}
			fread(&f_token, sizeof(float), 1, F);
			if (fabsf(strtof(conditional_value, &pos) - f_token) <= FLT_EPSILON)
				conditional_search_success = 1;
			break;
		}
		case _DOUBLE:
		{
			double d_token;
			char* pos;
			if (!strcmp(conditional_value, "NULL")) {
				fread(IS_NULL, 4, 1, F);
				IS_NULL[4] = '\0';
				if (!strcmp(IS_NULL, "NULL"))
					conditional_search_success = 1;
				break;
			}
			fread(&d_token, sizeof(double), 1, F);
			if (fabs(strtod(conditional_value, &pos) - d_token) <= DBL_EPSILON)
				conditional_search_success = 1;
			break;
		}
		case _CHAR:
		{
			char c_token;
			if (!strcmp(conditional_value, "NULL")) {
				c_token = fgetc(F);
				if (c_token == pad) {
					conditional_search_success = 1;
				}
				break;
			}
			c_token = fgetc(F);
			if (c_token == conditional_value[0])
				conditional_search_success = 1;
			break;
		}
		case _VARCHAR:
		{
			char* s_token;
			char c_token;
			if (!strcmp(conditional_value, "NULL")) {
				c_token = fgetc(F);
				if (c_token == pad)
					conditional_search_success = 1;
				break;
			}
			s_token = (char*)malloc(conditional_column->length + 1);
			fread(s_token, conditional_column->length, 1, F);
			s_token = strtok(s_token, pad_seprator);
			if (!strcmp(s_token, conditional_value))
				conditional_search_success = 1;
			free(s_token);
			break;
		}
		}

		if (conditional_search_success == 1) {
			fseek(F, search_start_index + (set_column->start_index), SEEK_SET);
			if (!strcmp(set_value, "NULL")) {
				switch (set_column->type) {
				case _INT:
				case _FLOAT:
					fputc('N', F); fputc('U', F); fputc('L', F); fputc('L', F);
					break;
				case _DOUBLE:
					fputc('N', F); fputc('U', F); fputc('L', F); fputc('L', F);
					for (unsigned int i = 0; i < (set_column->length) - 4; i++)
						fputc(pad, F);
					break;
				case _CHAR:
				case _VARCHAR:
					for (unsigned int i = 0; i < set_column->length; i++)
						fputc(pad, F);
					break;
				}
			}
			else {
				switch (set_column->type) {
				case _INT:
				{
					int i_token = atoi(set_value);
					fwrite(&i_token, sizeof(int), 1, F);

					break;
				}
				case _DOUBLE:
				{
					char* pos = NULL;
					double d_token = strtod(set_value, &pos);
					fwrite(&d_token, sizeof(double), 1, F);

					break;
				}
				case _FLOAT:
				{
					char* pos = NULL;
					float f_token = strtof(set_value, &pos);
					fwrite(&f_token, sizeof(float), 1, F);

					break;
				}
				case _CHAR:
				{
					char c_token = set_value[1];
					fputc(c_token, F);
					break;
				}
				case _VARCHAR:
				{
					char* s_token = (char*)malloc(strlen(set_value) - 1);
					unsigned int destination_index;
					int padding;

					for (destination_index = 1; destination_index < strlen(set_value) - 1; destination_index++)
						s_token[destination_index - 1] = set_value[destination_index];
					s_token[destination_index - 1] = '\0';
					fputs(s_token, F);
					if (strlen(s_token) != set_column->length) {
						padding = set_column->length - strlen(s_token);
						for (int i = 0; i < padding; i++)
							fputc(pad, F);
					}
					free(s_token);
					break;
				}
				}
			}
			conditional_search_success = 0;
		}
		search_start_index += data_line_length;
	}
	if (conditional_search_success == -1) {
		strcpy(err_msg, "Conditional Value Not Found");
		free(_conditional);
		free(_set);
		fclose(F);
		return -1;
	}
	free(_conditional);
	free(_set);
	fclose(F);
	return 0;
}
int _select(char* conditional, char* select, char** result) {
	char* _conditional = (char*)malloc(strlen(conditional) + 1);
	char* conditional_name, * conditional_value=0;
	int conditional_index = -1;
	column* conditional_column = 0;
	char* _select = (char*)malloc(strlen(select) + 1);
	int select_count = 0;
	column** select_column;
	column* cur = head->next;
	sdts* sdts_head;
	sdts* sdts_tail;
	int result_count = 0;

	strcpy(_conditional, conditional);
	strcpy(_select, select);


	if (strcmp(conditional, "*") != 0) {
		conditional_name = strtok(_conditional, "= ");
		conditional_value = strtok(NULL, "= \0");

		while (1) {
			if (!strcmp(cur->name, conditional_name)) {
				if (cur->type == _CHAR || cur->type == _VARCHAR) {
					if (cur->length < strlen(conditional_value) - 2 && strcmp(conditional_value, "NULL")) {
						free(_conditional);
						free(_select);
						strcpy(err_msg, "Conditional Length Over");
						return -1;
					}
					else {
						if (strcmp(conditional_value, "NULL"))
							conditional_value = strtok(conditional_value, "'");
					}
				}
				conditional_column = cur;
				break;
			}
			if (cur->next != 0)
				cur = cur->next;
			else
				break;
		}
		if (conditional_column == 0) {
			free(_conditional);
			free(_select);
			strcpy(err_msg, "Conditional Column Not Found");
			return -1;
		}
	}

	for (unsigned int i = 0; i < strlen(_select); i++) {
		if (_select[i] == ',')
			select_count++;
	}
	select_count++;
	select_column = (column**)malloc(sizeof(column*) * select_count);

	{
		char* select_token;
		cur = head->next;
		select_token = strtok(_select, ", ");
		while (1) {
			if (!strcmp(cur->name, select_token)) {
				select_column[0] = cur;
				break;
			}
			if (cur->next == 0) {
				strcpy(err_msg, "Select Column Not Exist");
				free(_conditional);
				free(_select);
				free(select_column);
				return -1;
			}
			cur = cur->next;
		}

		for (int i = 1; i < select_count; i++) {
			cur = head->next;
			select_token = strtok(NULL, ", ");
			while (1) {
				if (!strcmp(cur->name, select_token)) {
					select_column[i] = cur;
					break;
				}
				if (cur->next == 0) {
					strcpy(err_msg, "Select Column Not Exist");
					free(_conditional);
					free(_select);
					free(select_column);
					return -1;
				}
				cur = cur->next;
			}
		}
	}
	if (strcmp(conditional, "*") != 0)	{
		int search_index = data_start_index;
		int conditional_search_success = -1;
		sdts_head = (sdts*)malloc(sizeof(sdts));
		sdts_head->str = 0;
		sdts_head->next = 0;
		sdts_tail = sdts_head;
		F = fopen(_file_location, "r");
		while (search_index < data_end_index) {
			char IS_NULL[5];
			fseek(F, search_index + (conditional_column->start_index), SEEK_SET);
			switch (conditional_column->type) {
			case _INT:
			{
				int i_token;
				if (!strcmp(conditional_value, "NULL")) {
					fread(IS_NULL, 4, 1, F);
					IS_NULL[4] = '\0';
					if (!strcmp(IS_NULL, "NULL"))
						conditional_search_success = 1;
					break;
				}
				fread(&i_token, sizeof(int), 1, F);
				if (i_token == atoi(conditional_value))
					conditional_search_success = 1;
				break;
			}
			case _FLOAT:
			{
				float f_token;
				char* pos;
				if (!strcmp(conditional_value, "NULL")) {
					fread(IS_NULL, 4, 1, F);
					IS_NULL[4] = '\0';
					if (!strcmp(IS_NULL, "NULL"))
						conditional_search_success = 1;
					break;
				}
				fread(&f_token, sizeof(float), 1, F);
				if (fabsf(strtof(conditional_value, &pos) - f_token) <= FLT_EPSILON)
					conditional_search_success = 1;
				break;
			}
			case _DOUBLE:
			{
				double d_token;
				char* pos;
				if (!strcmp(conditional_value, "NULL")) {
					fread(IS_NULL, 4, 1, F);
					IS_NULL[4] = '\0';
					if (!strcmp(IS_NULL, "NULL"))
						conditional_search_success = 1;
					break;
				}
				fread(&d_token, sizeof(double), 1, F);
				if (fabs(strtod(conditional_value, &pos) - d_token) <= DBL_EPSILON)
					conditional_search_success = 1;
				break;
			}
			case _CHAR:
			{
				char c_token;
				if (!strcmp(conditional_value, "NULL")) {
					c_token = fgetc(F);
					if (c_token == pad)
						conditional_search_success = 1;
					break;
				}
				c_token = fgetc(F);
				if (c_token == conditional_value[0])
					conditional_search_success = 1;
				break;
			}
			case _VARCHAR:
			{
				char* s_token;
				char c_token;
				if (!strcmp(conditional_value, "NULL")) {
					c_token = fgetc(F);
					if (c_token == pad)
						conditional_search_success = 1;
					break;
				}
				s_token = (char*)malloc(conditional_column->length + 1);
				if (s_token == 0) {
					strcpy(err_msg, "Memory Allocation Failed");
					free(_conditional);
					free(_select);
					free(select_column);
					sdts_free(sdts_head);
					fclose(F);
					return -1;
				}
				fread(s_token, conditional_column->length, 1, F);
				s_token = strtok(s_token, pad_seprator);
				if (!strcmp(s_token, conditional_value))
					conditional_search_success = 1;
				free(s_token);
				break;
			}
			}

			if (conditional_search_success == 1) {
				sdts* new_sdts;
				result_count++;
				conditional_search_success = 0;
				for (int i = 0; i < select_count; i++) {
					strcpy(IS_NULL, "\0");
					new_sdts = (sdts*)malloc(sizeof(sdts));
					if (new_sdts == 0) {
						free(_conditional);
						free(_select);
						free(select_column);
						sdts_free(sdts_head);
						fclose(F);
						strcpy(err_msg, "Memory Allocaiton Failed");
						return -1;
					}
					new_sdts->next = 0;
					fseek(F, search_index + select_column[i]->start_index, SEEK_SET);
					switch (select_column[i]->type) {
					case _INT:
					{
						int i_token;
						fread(IS_NULL, 4, 1, F);
						IS_NULL[4] = '\0';
						if (!strcmp(IS_NULL, "NULL")) {
							new_sdts->str = (char*)malloc(5);
							strcpy(new_sdts->str, "NULL");
						}
						else {
							fseek(F, search_index + select_column[i]->start_index, SEEK_SET);
							fread(&i_token, sizeof(int), 1, F);
							new_sdts->str = (char*)malloc(11);
							sprintf(new_sdts->str, "%d", i_token);
						}
						break;
					}
					case _FLOAT:
					{
						float f_token;
						fread(IS_NULL, 4, 1, F);
						IS_NULL[4] = '\0';
						if (!strcmp(IS_NULL, "NULL")) {
							new_sdts->str = (char*)malloc(5);
							strcpy(new_sdts->str, "NULL");
						}
						else {
							fseek(F, search_index + select_column[i]->start_index, SEEK_SET);
							fread(&f_token, sizeof(float), 1, F);
							new_sdts->str = (char*)malloc(31);
							sprintf(new_sdts->str, "%.5f", f_token);

						}
						break;
					}
					case _DOUBLE:
					{
						double d_token;
						fread(IS_NULL, 4, 1, F);
						IS_NULL[4] = '\0';
						if (!strcmp(IS_NULL, "NULL")) {
							new_sdts->str = (char*)malloc(5);
							strcpy(new_sdts->str, "NULL");
						}
						else {
							fseek(F, search_index + select_column[i]->start_index, SEEK_SET);
							fread(&d_token, sizeof(double), 1, F);
							new_sdts->str = (char*)malloc(31);
							sprintf(new_sdts->str, "%.12lf", d_token);
						}
						break;
					}
					case _CHAR:
					{
						IS_NULL[0] = fgetc(F);
						if (IS_NULL[0] == pad) {
							new_sdts->str = (char*)malloc(5);
							strcpy(new_sdts->str, "NULL");
						}
						else {
							fseek(F, search_index + select_column[i]->start_index, SEEK_SET);
							new_sdts->str = (char*)malloc(2);
							new_sdts->str[0] = fgetc(F);
							new_sdts->str[1] = '\0';
						}
						break;

					}
					case _VARCHAR:
					{
						char* s_token;
						IS_NULL[0] = fgetc(F);
						if (IS_NULL[0] == pad) {
							new_sdts->str = (char*)malloc(5);
							strcpy(new_sdts->str, "NULL");
						}
						else {
							fseek(F, search_index + select_column[i]->start_index, SEEK_SET);
							s_token = (char*)malloc((select_column[i]->length) + 1);
							fread(s_token, select_column[i]->length, 1, F);
							s_token = strtok(s_token, pad_seprator);
							new_sdts->str = (char*)malloc(strlen(s_token) + 1);
							strcpy(new_sdts->str, s_token);
						}
						break;
					}
					}
					sdts_tail->next = new_sdts;
					sdts_tail = new_sdts;
				}
			}

			search_index += data_line_length;
		}

		if (conditional_search_success == -1) {
			free(_conditional);
			free(_select);
			free(select_column);
			free(sdts_head);
			fclose(F);
			strcpy(err_msg, "Conditional Value Not Found");
			return -1;
		}
	}

	else {
		int search_index = data_start_index;
		char IS_NULL[5];
		sdts* new_sdts;
		sdts_head = (sdts*)malloc(sizeof(sdts));
		sdts_head->str = 0;
		sdts_head->next = 0;
		sdts_tail = sdts_head;
		F = fopen(_file_location, "r");
		while (search_index < data_end_index) {
			result_count++;
			for (int i = 0; i < select_count; i++) {
				strcpy(IS_NULL, "\0");
				new_sdts = (sdts*)malloc(sizeof(sdts));
				if (new_sdts == 0) {
					free(_conditional);
					free(_select);
					free(select_column);
					sdts_free(sdts_head);
					fclose(F);
					strcpy(err_msg, "Memory Allocaiton Failed");
					return -1;
				}
				new_sdts->next = 0;
				fseek(F, search_index + select_column[i]->start_index, SEEK_SET);
				switch (select_column[i]->type) {
				case _INT:
				{
					int i_token;
					fread(IS_NULL, 4, 1, F);
					IS_NULL[4] = '\0';
					if (!strcmp(IS_NULL, "NULL")) {
						new_sdts->str = (char*)malloc(5);
						strcpy(new_sdts->str, "NULL");
					}
					else {
						fseek(F, search_index + select_column[i]->start_index, SEEK_SET);
						fread(&i_token, sizeof(int), 1, F);
						new_sdts->str = (char*)malloc(11);
						sprintf(new_sdts->str, "%d", i_token);
					}
					break;
				}
				case _FLOAT:
				{
					float f_token;
					fread(IS_NULL, 4, 1, F);
					IS_NULL[4] = '\0';
					if (!strcmp(IS_NULL, "NULL")) {
						new_sdts->str = (char*)malloc(5);
						strcpy(new_sdts->str, "NULL");
					}
					else {
						fseek(F, search_index + select_column[i]->start_index, SEEK_SET);
						fread(&f_token, sizeof(float), 1, F);
						new_sdts->str = (char*)malloc(31);
						sprintf(new_sdts->str, "%.5f", f_token);

					}
					break;
				}
				case _DOUBLE:
				{
					double d_token;
					fread(IS_NULL, 4, 1, F);
					IS_NULL[4] = '\0';
					if (!strcmp(IS_NULL, "NULL")) {
						new_sdts->str = (char*)malloc(5);
						strcpy(new_sdts->str, "NULL");
					}
					else {
						fseek(F, search_index + select_column[i]->start_index, SEEK_SET);
						fread(&d_token, sizeof(double), 1, F);
						new_sdts->str = (char*)malloc(31);
						sprintf(new_sdts->str, "%.12lf", d_token);
					}
					break;
				}
				case _CHAR:
				{
					IS_NULL[0] = fgetc(F);
					if (IS_NULL[0] == pad) {
						new_sdts->str = (char*)malloc(5);
						strcpy(new_sdts->str, "NULL");
					}
					else {
						fseek(F, search_index + select_column[i]->start_index, SEEK_SET);
						new_sdts->str = (char*)malloc(2);
						new_sdts->str[0] = fgetc(F);
						new_sdts->str[1] = '\0';
					}
					break;

				}
				case _VARCHAR:
				{
					char* s_token;
					IS_NULL[0] = fgetc(F);
					if (IS_NULL[0] == pad) {
						new_sdts->str = (char*)malloc(5);
						strcpy(new_sdts->str, "NULL");
					}
					else {
						fseek(F, search_index + select_column[i]->start_index, SEEK_SET);
						s_token = (char*)malloc((select_column[i]->length) + 1);
						fread(s_token, select_column[i]->length, 1, F);
						s_token = strtok(s_token, pad_seprator);
						new_sdts->str = (char*)malloc(strlen(s_token) + 1);
						strcpy(new_sdts->str, s_token);
					}
					break;
				}
				}
				sdts_tail->next = new_sdts;
				sdts_tail = new_sdts;
			}
			search_index += data_line_length;
		}

	}

	{
		int result_size = 0;
		sdts* sdts_cur = sdts_head;
		for (int i = 0; i < select_count; i++)
			result_size += (strlen(select_column[i]->name) + 3);
		while (sdts_cur->next != 0) {
			sdts_cur = sdts_cur->next;
			result_size += (strlen(sdts_cur->str) + 1);
		}
		*result = (char*)malloc(result_size + 12);
		*result[0] = '\0';
		{
			char buf[11] = "\0";
			sprintf(buf, "%d", result_count);
			strcat(*result, buf);
			strcat(*result, pad_seprator);
		}
		for (int i = 0; i < select_count; i++) {
			char buf[2] = "\0";
			strcat(*result, select_column[i]->name);
			strcat(*result, ",");
			sprintf(buf, "%d", select_column[i]->type);
			strcat(*result, buf);
			if (i == select_count - 1)
				strcat(*result, pad_seprator);
			else
				strcat(*result, ",");
		}
		sdts_cur = sdts_head;
		while (sdts_cur->next != 0) {
			sdts_cur = sdts_cur->next;
			strcat(*result, sdts_cur->str);
			strcat(*result, pad_seprator);
		}
	}

	sdts_free(sdts_head);
	free(_conditional);
	free(_select);
	free(select_column);
	fclose(F);
	return 0;
}

void print_column() {
	column* cur = head->next;
	while (1) {
		printf("컬럼명 : %s\n", cur->name);
		printf("컬럼타입 : ");
		switch (cur->type) {
		case _CHAR:
			printf("char\n");
			break;
		case _VARCHAR:
			printf("varchar\n");
			printf("길이제한 : %d\n", cur->length);
			break;
		case _INT:
			printf("int\n");
			break;
		case _FLOAT:
			printf("float\n");
			break;
		case _DOUBLE:
			printf("double\n");
			break;
		}
		printf("\n");
		if (cur->next != 0)
			cur = cur->next;
		else
			break;
	}
}
int print_data() {

	column* cur;
	int searching = data_start_index;

	cur = head;
	while (cur->next != 0) {
		cur = cur->next;
		printf("    %s", cur->name);
	}
	printf("\n=================================================================================================================================================================\n");
	F = fopen(_file_location, "rb");
	while (searching < data_end_index) {
		fseek(F, searching, SEEK_SET);
		cur = head;
		while (cur->next != 0) {
			char IS_NULL[5] = "    \0";
			cur = cur->next;
			switch (cur->type) {
			case _INT:
			{
				int i_token;
				fread(IS_NULL, sizeof(char), 4, F);
				fseek(F, -4, SEEK_CUR);
				if (!strcmp(IS_NULL, "NULL")) {
					printf("    (NULL)");
					fseek(F, sizeof(int), SEEK_CUR);
				}
				else {
					fread(&i_token, sizeof(int), 1, F);
					printf("    %8d", i_token);
				}

				break;
			}
			case _FLOAT:
			{
				float f_token;
				fread(IS_NULL, sizeof(char), 4, F);
				fseek(F, -4, SEEK_CUR);
				if (!strcmp(IS_NULL, "NULL")) {
					printf("    (NULL)");
					fseek(F, sizeof(float), SEEK_CUR);
				}
				else {
					fread(&f_token, sizeof(float), 1, F);
					printf("    %.5f", f_token);
				}
				break;
			}
			case _DOUBLE:
			{
				double d_token;
				fread(IS_NULL, sizeof(char), 4, F);
				fseek(F, -4, SEEK_CUR);
				if (!strcmp(IS_NULL, "NULL")) {
					printf("    (NULL)");
					fseek(F, sizeof(double), SEEK_CUR);
				}
				else {
					fread(&d_token, sizeof(double), 1, F);
					printf("    %.12lf", d_token);
				}
				break;
			}
			case _CHAR:
			{
				char c_token;
				c_token = fgetc(F);
				if (c_token == pad)
					printf("    (NULL)");
				else
					printf("    %4c", c_token);
				break;
			}
			case _VARCHAR:
			{
				char* s_token;
				char* string;
				if ((s_token = (char*)malloc((cur->length) + 1)) == NULL) {
					strcpy(err_msg, "Memory Allocation Failed");

					return -1;
				}
				fread(s_token, cur->length, 1, F);
				s_token[cur->length] = '\0';
				if (s_token[0] == pad) {
					printf("    (NULL)");
				}
				else {
					string = strtok(s_token, pad_seprator);
					printf("    %12s", string);
				}
				break;
			}
			}
		}
		printf("\n");
		searching += data_line_length;
	}

	fclose(F);
	return 0;
}

void sdts_free(sdts* node) {
	if (node == 0);
	else {
		if (node->next != 0)
			sdts_free(node->next);
		if (node->str != 0)
			free(node->str);
		free(node);
	}
}
void recursive_column_free_function(column* node) {
	if (node == 0);
	else {
		if (node->next != 0)
			recursive_column_free_function(node->next);
		if (node->name != 0)
			free(node->name);
		free(node);
	}
}
void file_column_free() {
	column* node = head;
	recursive_column_free_function(head);
	if (select_result_str != NULL|| select_result_str !=0)
		free(select_result_str);
	free(_file_location);
	head = 0;
	tail = 0;
	data_start_index = 0;
	data_end_index = 0;
	data_line_length = 0;
	select_result_str = 0;
}
int print_ITEM() {

	column* cur;
	int searching = data_start_index;

	cur = head;
	while (cur->next != 0) {
		cur = cur->next;
		printf("     %s", cur->name);
	}
	printf("\n=================================================================================================================================================================\n");
	F = fopen(_file_location, "rb");
	while (searching < data_end_index) {
		fseek(F, searching, SEEK_SET);
		cur = head;
		while (cur->next != 0) {
			char IS_NULL[5] = "    \0";
			cur = cur->next;
			switch (cur->type) {
			case _INT:
			{
				int i_token;
				fread(IS_NULL, sizeof(char), 4, F);
				fseek(F, -4, SEEK_CUR);
				if (!strcmp(IS_NULL, "NULL")) {
					printf("    (NULL)");
					fseek(F, sizeof(int), SEEK_CUR);
				}
				else {
					fread(&i_token, sizeof(int), 1, F);
					printf("  %6d    ", i_token);
				}

				break;
			}
			case _FLOAT:
			{
				float f_token;
				fread(IS_NULL, sizeof(char), 4, F);
				fseek(F, -4, SEEK_CUR);
				if (!strcmp(IS_NULL, "NULL")) {
					printf("    (NULL)");
					fseek(F, sizeof(float), SEEK_CUR);
				}
				else {
					fread(&f_token, sizeof(float), 1, F);
					printf("    %9.3f", f_token);
				}
				break;
			}
			case _DOUBLE:
			{
				double d_token;
				fread(IS_NULL, sizeof(char), 4, F);
				fseek(F, -4, SEEK_CUR);
				if (!strcmp(IS_NULL, "NULL")) {
					printf("    (NULL)");
					fseek(F, sizeof(double), SEEK_CUR);
				}
				else {
					fread(&d_token, sizeof(double), 1, F);
					printf("    %9.3lf", d_token);
				}
				break;
			}
			case _CHAR:
			{
				char c_token;
				c_token = fgetc(F);
				if (c_token == pad)
					printf("    (NULL)");
				else
					printf("    %9c", c_token);
				break;
			}
			case _VARCHAR:
			{
				char* s_token;
				char* string;
				if ((s_token = (char*)malloc((cur->length) + 1)) == NULL) {
					strcpy(err_msg, "Memory Allocation Failed");

					return -1;
				}
				fread(s_token, cur->length, 1, F);
				s_token[cur->length] = '\0';
				if (s_token[0] == pad) {
					printf("    (NULL)");
				}
				else {
					string = strtok(s_token, pad_seprator);
					printf("  %11s   ", string);
				}
				break;
			}
			}
		}

		printf("\n");
		searching += data_line_length;
	}
	printf("\n=============================================================================================\n");
	fclose(F);
	return 0;
}
int print_BOM() {

	column* cur;
	int searching = data_start_index;

	cur = head;
	while (cur->next != 0) {
		cur = cur->next;
		printf("    %s", cur->name);
	}
	printf("\n=========================================================\n");
	F = fopen(_file_location, "rb");
	while (searching < data_end_index) {
		fseek(F, searching, SEEK_SET);
		cur = head;
		while (cur->next != 0) {
			char IS_NULL[5] = "    \0";
			cur = cur->next;
			switch (cur->type) {
			case _INT:
			{
				int i_token;
				fread(IS_NULL, sizeof(char), 4, F);
				fseek(F, -4, SEEK_CUR);
				if (!strcmp(IS_NULL, "NULL")) {
					printf("    (NULL)");
					fseek(F, sizeof(int), SEEK_CUR);
				}
				else {
					fread(&i_token, sizeof(int), 1, F);
					printf("    %6d", i_token);
				}

				break;
			}
			case _FLOAT:
			{
				float f_token;
				fread(IS_NULL, sizeof(char), 4, F);
				fseek(F, -4, SEEK_CUR);
				if (!strcmp(IS_NULL, "NULL")) {
					printf("    (NULL)");
					fseek(F, sizeof(float), SEEK_CUR);
				}
				else {
					fread(&f_token, sizeof(float), 1, F);
					printf("    %9.3f", f_token);
				}
				break;
			}
			case _DOUBLE:
			{
				double d_token;
				fread(IS_NULL, sizeof(char), 4, F);
				fseek(F, -4, SEEK_CUR);
				if (!strcmp(IS_NULL, "NULL")) {
					printf("    (NULL)");
					fseek(F, sizeof(double), SEEK_CUR);
				}
				else {
					fread(&d_token, sizeof(double), 1, F);
					printf("    %9.3lf", d_token);
				}
				break;
			}
			case _CHAR:
			{
				char c_token;
				c_token = fgetc(F);
				if (c_token == pad)
					printf("    (NULL)");
				else
					printf("    %9c", c_token);
				break;
			}
			case _VARCHAR:
			{
				char* s_token;
				char* string;
				if ((s_token = (char*)malloc((cur->length) + 1)) == NULL) {
					strcpy(err_msg, "Memory Allocation Failed");

					return -1;
				}
				fread(s_token, cur->length, 1, F);
				s_token[cur->length] = '\0';
				if (s_token[0] == pad) {
					printf("    (NULL)");
				}
				else {
					string = strtok(s_token, pad_seprator);
					printf("    %9s", string);
				}
				break;
			}
			}
		}
		printf("\n");
		searching += data_line_length;
	}

	fclose(F);
	return 0;
}
float print_BOM_Total() {

	column* cur;
	int searching = data_start_index;
	float Total = 0;

	cur = head;
	while (cur->next != 0) {
		cur = cur->next;
		printf("    %s", cur->name);
	}
	printf("\n=========================================================\n");
	F = fopen(_file_location, "rb");
	while (searching < data_end_index) {
		fseek(F, searching, SEEK_SET);
		cur = head;
		while (cur->next != 0) {
			char IS_NULL[5] = "    \0";
			cur = cur->next;
			switch (cur->type) {
			case _INT:
			{
				int i_token;
				fread(IS_NULL, sizeof(char), 4, F);
				fseek(F, -4, SEEK_CUR);
				if (!strcmp(IS_NULL, "NULL")) {
					printf("    (NULL)");
					fseek(F, sizeof(int), SEEK_CUR);
				}
				else {
					fread(&i_token, sizeof(int), 1, F);
					printf("    %6d", i_token);
				}

				break;
			}
			case _FLOAT:
			{
				float f_token;
				fread(IS_NULL, sizeof(char), 4, F);
				fseek(F, -4, SEEK_CUR);
				if (!strcmp(IS_NULL, "NULL")) {
					printf("    (NULL)");
					fseek(F, sizeof(float), SEEK_CUR);
				}
				else {
					fread(&f_token, sizeof(float), 1, F);
					printf("    %9.3f", f_token);
					Total = Total + f_token;
				}
				break;
			}
			case _DOUBLE:
			{
				double d_token;
				fread(IS_NULL, sizeof(char), 4, F);
				fseek(F, -4, SEEK_CUR);
				if (!strcmp(IS_NULL, "NULL")) {
					printf("    (NULL)");
					fseek(F, sizeof(double), SEEK_CUR);
				}
				else {
					fread(&d_token, sizeof(double), 1, F);
					printf("    %9.3lf", d_token);
				}
				break;
			}
			case _CHAR:
			{
				char c_token;
				c_token = fgetc(F);
				if (c_token == pad)
					printf("    (NULL)");
				else
					printf("    %9c", c_token);
				break;
			}
			case _VARCHAR:
			{
				char* s_token;
				char* string;
				if ((s_token = (char*)malloc((cur->length) + 1)) == NULL) {
					strcpy(err_msg, "Memory Allocation Failed");

					return -1;
				}
				fread(s_token, cur->length, 1, F);
				s_token[cur->length] = '\0';
				if (s_token[0] == pad) {
					printf("    (NULL)");
				}
				else {
					string = strtok(s_token, pad_seprator);
					printf("    %9s", string);
				}
				break;
			}
			}
		}
		printf("\n");
		searching += data_line_length;
	}

	fclose(F);

	return Total;
}