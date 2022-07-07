#include "local.h"

int recv_result(result** result_head, char* receive) {
	result* cur;
	char* recv = (char*)malloc(strlen(receive) + 1);
	char* column_remain;
	int result_count;
	if (recv == NULL) {
		strcpy(err_msg, "Memory Allocaiton Failed");

		return -1;
	}
	strcpy(recv, receive);
	{
		char* result_count_str;
		result_count_str = strtok(recv, pad_seprator);
		column_remain = result_count_str + strlen(result_count_str) + 1;
		result_count = atoi(result_count_str);
	}

	if ((*result_head = (result*)malloc(sizeof(result))) == NULL) {
		strcpy(err_msg, "Memory Allocaiton Failed");

		free(recv);
		return -1;
	}
	(*result_head)->name = 0;
	(*result_head)->_int_data = 0;
	(*result_head)->_float_data = 0;
	(*result_head)->_double_data = 0;
	(*result_head)->_char_data = 0;
	(*result_head)->_string_data = 0;
	(*result_head)->next = 0;


	{
		char* column_line, * column_token;
		result* new_column;
		column_line = strtok(column_remain, pad_seprator);
		column_remain = column_line + strlen(column_line) + 1;
		cur = *result_head;
		column_token = strtok(column_line, ",");
		if ((cur->name = (char*)malloc(strlen(column_token) + 1)) == NULL) {
			strcpy(err_msg, "Memory Allocaiton Failed");

			free(recv);
			result_free(*result_head, result_count);
			return -1;
		}
		strcpy(cur->name, column_token);
		column_token = strtok(NULL, ",");
		cur->type = atoi(column_token);

		switch (cur->type) {
		case _INT:
			if ((cur->_int_data = (int*)malloc(sizeof(int) * result_count)) == NULL) {
				strcpy(err_msg, "Memory Allocaiton Failed");

				free(recv);
				result_free(*result_head, result_count);
				return -1;
			}
			break;
		case _FLOAT:
			if ((cur->_float_data = (float*)malloc(sizeof(float) * result_count)) == NULL) {
				strcpy(err_msg, "Memory Allocaiton Failed");

				free(recv);
				result_free(*result_head, result_count);
				return -1;
			}
			break;
		case _DOUBLE:
			if ((cur->_double_data = (double*)malloc(sizeof(double) * result_count)) == NULL) {
				strcpy(err_msg, "Memory Allocaiton Failed");

				free(recv);
				result_free(*result_head, result_count);
				return -1;
			}
			break;
		case _CHAR:
			if ((cur->_char_data = (char*)malloc(sizeof(char) * result_count)) == NULL) {
				strcpy(err_msg, "Memory Allocaiton Failed");

				free(recv);
				result_free(*result_head, result_count);
				return -1;
			}
			break;
		case _VARCHAR:
			if ((cur->_string_data = (char**)malloc(sizeof(char*) * result_count)) == NULL) {
				strcpy(err_msg, "Memory Allocaiton Failed");

				free(recv);
				result_free(*result_head, result_count);
				return -1;
			}
			for (int i = 0; i < result_count; i++)
				cur->_string_data[i] = 0;
			break;
		}

		while ((column_token = strtok(NULL, ",")) != NULL) {
			if ((new_column = (result*)malloc(sizeof(result))) == NULL) {
				strcpy(err_msg, "Memory Allocaiton Failed");

				free(recv);
				result_free(*result_head, result_count);
				return -1;
			}
			new_column->name = 0;
			new_column->_int_data = 0;
			new_column->_float_data = 0;
			new_column->_double_data = 0;
			new_column->_char_data = 0;
			new_column->_string_data = 0;
			new_column->next = 0;
			cur->next = new_column;

			cur = new_column;
			if ((cur->name = (char*)malloc(strlen(column_token) + 1)) == NULL) {
				strcpy(err_msg, "Memory Allocaiton Failed");

				free(recv);
				result_free(*result_head, result_count);
				return -1;
			}
			strcpy(cur->name, column_token);
			column_token = strtok(NULL, ",");
			cur->type = atoi(column_token);

			switch (cur->type) {
			case _INT:
				if ((cur->_int_data = (int*)malloc(sizeof(int) * result_count)) == NULL) {
					strcpy(err_msg, "Memory Allocaiton Failed");

					free(recv);
					result_free(*result_head, result_count);
					return -1;
				}
				break;
			case _FLOAT:
				if ((cur->_float_data = (float*)malloc(sizeof(float) * result_count)) == NULL) {
					strcpy(err_msg, "Memory Allocaiton Failed");

					free(recv);
					result_free(*result_head, result_count);
					return -1;
				}
				break;
			case _DOUBLE:
				if ((cur->_double_data = (double*)malloc(sizeof(double) * result_count)) == NULL) {
					strcpy(err_msg, "Memory Allocaiton Failed");

					free(recv);
					result_free(*result_head, result_count);
					return -1;
				}
				break;
			case _CHAR:
				if ((cur->_char_data = (char*)malloc(sizeof(char) * result_count)) == NULL) {
					strcpy(err_msg, "Memory Allocaiton Failed");

					free(recv);
					result_free(*result_head, result_count);
					return -1;
				}
				break;
			case _VARCHAR:
				if ((cur->_string_data = (char**)malloc(sizeof(char*) * result_count)) == NULL) {
					strcpy(err_msg, "Memory Allocaiton Failed");

					free(recv);
					result_free(*result_head, result_count);
					return -1;
				}
				for (int i = 0; i < result_count; i++)
					cur->_string_data[i] = 0;
				break;
			}
		}
	}

	{
		char* data_token;
		cur = *result_head;
		data_token = strtok(column_remain, pad_seprator);
		if (!strcmp(data_token, "NULL")) {
			switch (cur->type) {
			case _INT:
				cur->_int_data[0] = INT_MAX;
				break;
			case _FLOAT:
				cur->_float_data[0] = FLT_MAX;
				break;
			case _DOUBLE:
				cur->_double_data[0] = DBL_MAX;
				break;
			case _CHAR:
				cur->_char_data[0] = pad;
				break;
			case _VARCHAR:
				if ((cur->_string_data[0] = (char*)malloc(2)) == NULL) {
					strcpy(err_msg, "Memory Allocaiton Failed");

					free(recv);
					result_free(*result_head, result_count);

					return -1;
				}
				strcpy(cur->_string_data[0], pad_seprator);
				break;
			}
		}
		else {
			switch (cur->type) {
			case _INT:
				cur->_int_data[0] = atoi(data_token);
				break;

			case _FLOAT:
			{
				char* pos = NULL;
				cur->_float_data[0] = strtof(data_token, &pos);

				break;
			}
			case _DOUBLE:
			{
				char* pos = NULL;
				cur->_double_data[0] = strtod(data_token, &pos);

				break;
			}
			case _CHAR:
				cur->_char_data[0] = data_token[0];
				break;

			case _VARCHAR:
				if ((cur->_string_data[0] = (char*)malloc(strlen(data_token) + 1)) == NULL) {
					strcpy(err_msg, "Memory Allocaiton Failed");

					free(recv);
					result_free(*result_head, result_count);

					return -1;
				}
				strcpy(cur->_string_data[0], data_token);
				break;

			}
		}
		{
			int i = 0;
			while ((data_token = strtok(NULL, pad_seprator)) != NULL) {
				if (cur->next == 0) {
					cur = *result_head;
					i++;
				}
				else
					cur = cur->next;

				if (!strcmp(data_token, "NULL")) {
					switch (cur->type) {
					case _INT:
						cur->_int_data[i] = INT_MAX;
						break;
					case _FLOAT:
						cur->_float_data[i] = FLT_MAX;
						break;
					case _DOUBLE:
						cur->_double_data[i] = DBL_MAX;
						break;
					case _CHAR:
						cur->_char_data[i] = pad;
						break;
					case _VARCHAR:
						if ((cur->_string_data[i] = (char*)malloc(2)) == NULL) {
							strcpy(err_msg, "Memory Allocaiton Failed");

							free(recv);
							result_free(*result_head, result_count);

							return -1;
						}
						strcpy(cur->_string_data[i], pad_seprator);
						break;
					}
				}
				else {
					switch (cur->type) {
					case _INT:
						cur->_int_data[i] = atoi(data_token);
						break;

					case _FLOAT:
					{
						char* pos = NULL;
						cur->_float_data[i] = strtof(data_token, &pos);

						break;
					}
					case _DOUBLE:
					{
						char* pos = NULL;
						cur->_double_data[i] = strtod(data_token, &pos);

						break;
					}
					case _CHAR:
						cur->_char_data[i] = data_token[0];
						break;

					case _VARCHAR:
						if ((cur->_string_data[i] = (char*)malloc(strlen(data_token) + 1)) == NULL) {
							strcpy(err_msg, "Memory Allocaiton Failed");

							free(recv);
							result_free(*result_head, result_count);

							return -1;
						}
						strcpy(cur->_string_data[i], data_token);
						break;

					}
				}
			}
		}
	}

	free(recv);

	return result_count;
}
result* find_result(result* result_head, char* column_name) {
	result* find;
	find = result_head;
	while (1) {
		if (!strcmp(find->name, column_name))
			return find;
		else {
			if (find->next == 0) {
				strcpy(err_msg, "Find Column Not Found");
				
				return -1;
			}
			else
				find = find->next;
		}
	}
}
void result_print(result* result_head, int result_count) {
	result* cur;
	cur = result_head;
	while (1) {
		printf("     %s", cur->name);
		if (cur->next == 0)
			break;
		else
			cur = cur->next;
	}
	printf("\n=========================================\n");
	for (int i = 0; i < result_count; i++) {
		cur = result_head;
		while (1) {
			switch (cur->type) {
			case _INT:
				if (int_is_null(cur->_int_data[i]))
					printf("     (NULL)");
				else
					printf("     %d", cur->_int_data[i]);
				break;
			case _FLOAT:
				if (float_is_null(cur->_float_data[i]))
					printf("     (NULL)");
				else
					printf("     %.5f", cur->_float_data[i]);
				break;
			case _DOUBLE:
				if (double_is_null(cur->_double_data[i]))
					printf("     (NULL)");
				else
					printf("     %.12lf", cur->_double_data[i]);
				break;
			case _CHAR:
				if (char_is_null(cur->_char_data[i]))
					printf("     (NULL)");
				else
					printf("     %c", cur->_char_data[i]);
				break;
			case _VARCHAR:
				if (string_is_null(cur->_string_data[i]))
					printf("     (NULL)");
				else
					printf("     %s", cur->_string_data[i]);
				break;
			}
			if (cur->next == 0)
				break;
			else
				cur = cur->next;
		}
		printf("\n");
	}
}
int int_is_null(int _int_data) {
	if (_int_data == INT_MAX)
		return 1;
	else
		return 0;
}
int float_is_null(float _float_data) {
	if (fabsf(_float_data - FLT_MAX) <= FLT_EPSILON)
		return 1;
	else
		return 0;
}
int double_is_null(double _double_data) {
	if (fabs(_double_data - DBL_MAX) <= DBL_EPSILON)
		return 1;
	else
		return 0;
}
int char_is_null(char _char_data) {
	if (_char_data == pad)
		return 1;
	else
		return 0;
}
int string_is_null(char* _string_data) {
	if (_string_data[0] == pad)
		return 1;
	else
		return 0;
}
void result_free(result* node, int result_count) {
	if (node == 0);
	else {
		if (node->next != 0)
			result_free(node->next, result_count);
		if (node->name != 0)
			free(node->name);
		switch (node->type) {
		case _INT:
			if (node->_int_data != 0)
				free(node->_int_data);
			break;
		case _FLOAT:
			if (node->_float_data != 0)
				free(node->_float_data);
			break;
		case _DOUBLE:
			if (node->_double_data != 0)
				free(node->_double_data);
			break;
		case _CHAR:
			if (node->_char_data != 0)
				free(node->_char_data);
			break;
		case _VARCHAR:
			if (node->_string_data != 0) {
				for (int i = 0; i < result_count; i++) {
					if (node->_string_data[i] == 0)
						break;
					free(node->_string_data[i]);
				}
				free(node->_string_data);
			}
		}
		free(node);
	}
}