#include "tagfs_common.h"
#include "tagfs_debug.h"
#include "tagfs_db.h"

#include <assert.h>
#include <string.h>

/**
 * Checks whether or not a given tag is valid.
 *
 * @param tag The tag to check.
 * @return true, if the tag is valid. false, if the tag is not valid.
 */
static bool valid_tag(const char *tag) {
	DEBUG(ENTRY);
	bool valid = false;
	char *query = NULL;
	const char select_from[] = "SELECT * FROM tags WHERE tag_name = \"\"";
	int length = 0;
	int written = 0; /* characters written by snprintf */
	int count = 0; /* number of results returned by query */

	/* get length of query */
	length = strlen(select_from) + strlen(tag);
	DEBUG("Length of query to select matching tags is %d", length);

	/* build query */
	query = malloc(length * sizeof(*query) + 1);
	assert(query != NULL);
	written = snprintf(query, length + 1, "SELECT * FROM tags WHERE tag_name = \"%s\"", tag);
	assert(written == length);
	DEBUG("Query to check if tag \"%s\" is valid: %s", tag, query);

	/* check query count */
	count = db_count_from_query(query);
	assert(count == 0 || count == 1);
	DEBUG("%d results returned from query", count);

	if(count == 1) { valid = true; }

	DEBUG("Tag \"%s\" is %s", tag, valid == true ? "valid" : "not valid");
	DEBUG(EXIT);
	return valid;
} /* db_valid_tag */

/**
 * Checks whether or not a path is made up of valid tags.
 *
 * @param path The path to check.
 * @return true, if the path is valid. false, if the path is not valid.
 */
static bool valid_tags_in_path(const char *path) {
	DEBUG(ENTRY);
	bool valid = true;
	char **tag_array = NULL;
	int i = 0;
	int num_tags = 0;

	assert(path != NULL);

	num_tags = tags_from_query(path, &tag_array, "directory_contents");
	DEBUG("%d tags in %s", num_tags, path);

	for(i = 0; i < num_tags; i++) {
		if(!valid_tag(tag_array[i])) { valid = false; }
	}

	free_char_ptr_array(&tag_array, num_tags);

	DEBUG(EXIT);
	return valid;
} /* valid_tags_in_path */

/* TODO: Check source */
/* TODO: Add info */
static bool unique_tags_in_path(const char *path) {
	bool unique = true;
	char **tag_array = NULL;
	char **tags_checked = NULL;
	int i = 0;
	int num_tokens = 0;

	DEBUG(ENTRY);

	assert(path != NULL);

	DEBUG("Checking uniqueness of tags in %s", path);
	num_tokens = path_to_array(path, &tag_array);
	DEBUG("Number of tokens: %d", num_tokens);
	tags_checked = malloc(num_tokens * sizeof(*tags_checked));
	assert(tags_checked != NULL);

	for(i = 0; i < num_tokens; i++) {
		assert(tag_array != NULL);
		if(array_contains_string(tags_checked, tag_array[i], i)) {
			unique = false;
			break;
		}

		tags_checked[i] = malloc(strlen(tag_array[i]) + 1);
		assert(tags_checked[i] != NULL);
		strcpy(tags_checked[i], tag_array[i]);
	}

	free_char_ptr_array(&tag_array, num_tokens);
	free_char_ptr_array(&tags_checked, i);

	DEBUG("Tags in path are %sunique", unique ? "" : "not ");
	DEBUG("unique_tags_in_path");
	return unique;
} /* unique_tags_in_path */

int num_digits(unsigned int num) {
	DEBUG(ENTRY);
	int count = 0;

	DEBUG("Counting number of digits in %u", num);

	do {
		num /= 10;
		count++;
	} while(num != 0);

	DEBUG("Number of digits in %u: %d", num, count);
	DEBUG(EXIT);
	return count;
} /* num_digits */

int path_to_array(const char *path, char ***array) {
	DEBUG(ENTRY);
	char *tmp_path = NULL;
	char *tok_ptr = NULL;
	char *token = NULL;
	int i = 0;
	int num_tokens = 0;

	assert(path != NULL);
	assert(array != NULL);
	assert(*array == NULL);

	DEBUG("Converting %s to array", path);

	if(strcmp(path, "/") != 0) {
		/* calculate the number of tags in the path */
		num_tokens = num_tags_in_path(path);
		DEBUG("Number of tokens in path: %d", num_tokens);

		/* make a copy of the path that can be modified */
		tmp_path = malloc(strlen(path) * sizeof(*tmp_path) + 1);
		assert(tmp_path != NULL);

		*array = malloc(num_tokens * sizeof(**array));
		assert(*array != NULL);

		strcpy(tmp_path, path);
		assert(strcmp(path, tmp_path) == 0);

		/* copy tags from path into an array */
		token = strtok_r(tmp_path, "/", &tok_ptr);
		DEBUG("Array contents:");
		for(i = 0; token != NULL; i++) {
			(*array)[i] = malloc(strlen(token) * sizeof((**array)[i]) + 1);
			assert((*array)[i] != NULL);
			strncpy((*array)[i], token, strlen(token) + 1);
			assert(strcmp((*array)[i], token) == 0);
			DEBUG("array[%d] = %s, at address %p.", i, (*array)[i], (*array)[i]);
			token = strtok_r(NULL, "/", &tok_ptr);
		}

		assert(tmp_path);
		free(tmp_path);
		tmp_path = NULL;

		DEBUG("Returning array from %s with %d element(s).", path, num_tokens);
	}

	DEBUG(EXIT);
	return num_tokens;
} /* path_to_array */

void free_char_ptr_array(char ***array, int count) {
	DEBUG(ENTRY);
	int i = 0;

	DEBUG("Attempting to free array of %d pointer(s) plus the main pointer.", count);

	assert(array != NULL);
	assert(count >= 0);

	/* array is empty */
	if(*array == NULL) { DEBUG("Array is NULL. Nothing to free."); }
	/* array is not empty */
	else {
		assert(*array != NULL);

		/* free each element */
		for(i = 0; i < count; i++) {
			DEBUG("Freeing array[%d] = %s", i, (*array)[i]);
			free((*array)[i]);
			(*array)[i] = NULL;
		}

		DEBUG("Free'd %d element(s).", i);

		assert(*array != NULL);
		free(*array);
		*array = NULL;

		DEBUG("Free'd main array pointer.");
	}

	DEBUG(EXIT);
} /* free_char_ptr_array */

int num_tags_in_path(const char *path) {
	DEBUG(ENTRY);
	char *tmp_path = NULL;
	char *tok_ptr = NULL;
	char *token = NULL;
	int i = 0;

	assert(path != NULL);

	DEBUG("Calculating number of tags in %s", path);

	/* make copy of path for tokenization */
	tmp_path = malloc(strlen(path) * sizeof(*tmp_path) + 1);
	assert(tmp_path != NULL);

	strcpy(tmp_path, path);
	assert(strcmp(path, tmp_path) == 0);
	token = strtok_r(tmp_path, "/", &tok_ptr);

	/* count tokens */
	for(i = 0; token != NULL; i++) { token = strtok_r(NULL, "/", &tok_ptr); }

	assert(tmp_path != NULL);
	free(tmp_path);
	tmp_path = NULL;

	DEBUG("%d tags in %s", i, path);
	DEBUG(EXIT);
	return i;
} /* num_tags_in_path */

char *get_query_files_with_tag(const char *tag) {
	DEBUG(ENTRY);
	char *query = NULL;
	const char select_from_outline[] = "SELECT file_id FROM all_tables where tag_name == \"\"";
	int length = 0; /* length of sqlite3 query */
	int written = 0; /* characters written by snprintf */

	assert(tag != NULL);

	DEBUG("Building query to select all files with tag \"%s\"", tag);

	/* calculating length */
	length = strlen(select_from_outline) + strlen(tag);
	DEBUG("Length of query to select files with tag \"%s\" is %d", tag, length);

	/* building query */
	query = malloc(length * sizeof(*query) + 1);
	assert(query != NULL);
	written = snprintf(query, length + 1, "SELECT file_id FROM all_tables where tag_name == \"%s\"", tag);
	assert(written == length);

	DEBUG("Query to select files with tag \"%s\": %s", tag, query);
	DEBUG(EXIT);
	return query;
} /* get_query_files_with_tag */

void set_directory_contents(const char *path, const char *table) {
	DEBUG(ENTRY);
	int num_tags = 0; /* number of tags in the path */
	char **tag_array = NULL; /* array of path elements */
	int i = 0;

	assert(path != NULL);
	assert(table != NULL);

	DEBUG("Loading the contents of %s into table \"%s\"", path, table);

	/* turn path into array and get count */
	num_tags = path_to_array(path, &tag_array);
	DEBUG("%s has %d tags", path, num_tags);

	/* truncate the table */
	db_truncate_table(table);

	if(strcmp(path, "/") != 0) {
		/* load first tag into table */
		assert(tag_array != NULL);
		assert(tag_array[0] != NULL);
		db_load_table(tag_array[0], table);

		/* filter the rest out that do not have subsequent tags */
		for(i = 1; i < num_tags; i++) {
			db_filter_table(tag_array[i], table);
		}

		free_char_ptr_array(&tag_array, num_tags);
	}

	DEBUG(EXIT);
} /* set_directory_contents */

int tags_from_query(const char *path, char ***tag_array, const char *table) {
	DEBUG(ENTRY);
	char **path_tag_array = NULL;
	char *query = NULL; /* sqlite3 query to select tags that match the files in the given table */
	const char and_not[] = " AND tag_name != '";
	const char select_distinct[] = "SELECT DISTINCT tag_name FROM all_tables WHERE file_id IN (SELECT file_id FROM )";
	const char select_root[] = "SELECT tag_name FROM tags";
	int i = 0;
	int length = 0; /* length of sqlite3 query to select tags */
	int num_path_tags = 0; /* number of tags in the path */
	int num_tags = 0; /* number of tags at the directory location */
	int written = 0; /* characters written by snprintf */

	assert(path != NULL);
	assert(tag_array != NULL);
	assert(*tag_array == NULL);
	assert(table != NULL);

	DEBUG("Getting tags in path %s and using result table \"%s\"", path, table);

	/* if at root directory */
	if(strcmp(path, "/") == 0) {
		/* get results from root level query */
		num_tags = db_array_from_query("tag_name", select_root, tag_array);
	}
	else {
		/* get number of tags in path, array of tags in path, and length of query */
		num_path_tags = path_to_array(path, &path_tag_array);
		DEBUG("%d tags in path %s", num_path_tags, path);
		length = strlen(select_distinct) + strlen(table);
		DEBUG("Length of initial portion of query %s: %d", path, length);

		/* build inital portion of query */
		query = calloc(strlen(select_distinct) + (num_tags * (strlen(and_not) + 1) + strlen(path) - num_path_tags + 1), sizeof(query));
		assert(query != NULL);
		written = snprintf(query, length + 1, "SELECT DISTINCT tag_name FROM all_tables WHERE file_id IN (SELECT file_id FROM %s)", table);
		assert(written == length);
		DEBUG("Initial portion of query: %s", query);

		/* add tags to exclude from query */
		for(i = 0; i < num_path_tags; i++) {
			strcat(strcat(strcat(query, and_not), path_tag_array[i]), "'");
		}
		free_char_ptr_array(&path_tag_array, num_path_tags);
		DEBUG("Full query of length %d is: %s", length, query);

		/* get results from query */
		num_tags = db_array_from_query("tag_name", query, tag_array);

		assert(query != NULL);
		free(query);
		query = NULL;
	}	

	DEBUG("%d tags at location %s", num_tags, path);
	DEBUG(EXIT);
	return num_tags;
} /* tags_from_query */

int files_from_query(const char *path, char ***file_array, const char *table) {
	DEBUG(ENTRY);
	char *query = NULL; /* sqlite3 query to select tags that match the files in the given table */
	const char select_from[] = "SELECT file_name FROM files JOIN  USING(file_id)";
	int length = 0; /* length of sqlite3 query to select tags */
	int num_files = 0; /* number of files at the directory location */
	int written = 0; /* characters written by snprintf */

	assert(path != NULL);
	assert(file_array != NULL);
	assert(*file_array == NULL);
	assert(table != NULL);

	DEBUG("Getting files in path %s and using result table \"%s\"", path, table);

	/* get length of query */
	length = strlen(select_from) + strlen(table);
	DEBUG("Length of query is %d", length);

	/* build query */
	query = malloc(length * sizeof(*query) + 1);
	assert(query != NULL);
	written = snprintf(query, length + 1, "SELECT file_name FROM files JOIN %s USING(file_id)", table);
	assert(written == length);

	/* get results from root level query */
	num_files = db_array_from_query("file_name", query, file_array);

	assert(query != NULL);
	free(query);
	query = NULL;

	DEBUG("%d tags at location %s", num_files, path);
	DEBUG(EXIT);
	return num_files;
} /* tags_from_query */

bool valid_path_to_tag(const char *path) {
	DEBUG(ENTRY);
	bool valid = false;

	assert(path != NULL);

	DEBUG("Checking that %s is a valid path to a tag", path);

	if(strcmp(path, "/") == 0) { valid = true; }
	else {
		if(!unique_tags_in_path(path) || !valid_tags_in_path(path)) { valid = false; }
		else { valid = true; }
	}

	DEBUG("%s is %sa valid path to a tag", path, valid ? "" : "not a ");
	DEBUG(EXIT);
	return valid;
} /* valid_path_to_tag */
