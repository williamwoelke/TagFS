/**
 * General functions that are neither tagfs callbacks nor database functions.
 *
 * @file tagfs_common.h
 * @author Keith Woelke
 * @date 30/07/2010
 */

#ifndef TAGFS_COMMON_H
#define TAGFS_COMMON_H

#include <semaphore.h>
#include <stdbool.h>

sem_t sem;

/**
 * Counts the number if digits in an integer.
 *
 * @param num The number from which to count digits.
 * @return The number of digits in num.
 */
int num_digits(unsigned int num);

/**
 * Get the directory of where the TagFS is being executed from (assuming it is 
 * passed argv[0]). The returned path must be free'd by the caller. Logging 
 * functions such as DEBUG, INFO, and WARN should not be called in this 
 * function.
 *
 * @param exec_name The path to the executable given from argv[0].
 * @return The path to the executable.
 */
char *get_exec_dir(const char *exec_name);

/**
 * Retrieves the file name of the file associated with a file ID. The returned
 * file name must be free'd by the caller.
 *
 * @param file_id The ID of the file.
 * @return The name of the file corresponding to the file ID.
 */
char *file_name_from_id(int file_id);

/**
 * Checks whether or not a given path is valid. This is specifically done by 
 * checking that every component of the path is valid and that every component 
 * is unique. Essentially, this is done with calls to valid_tags_in_path() and 
 * unique_path().
 *
 * @param path A string representing a path in the filesystem.
 * @return True, if the path is valid. False, if the path is not.
 */
bool valid_path_to_folder(const char *path);

/**
 * Converts a path into an array of tokens. The path is delimated using the "/" 
 * character and each token is inserted into an array. The number of elements in
 * the array is returned and the pointer passed in by the user will be allocated
 * for the array of elements. The caller is responsible for freeing both the 
 * array pointer, and the pointers of each token in the array. The function 
 * free_double_ptr() can be used for this purpose.
 *
 * @param path A string representing a path in the filesystem.
 * @param array A pointer to an array of strings (char pointers).
 * @return The number of elements in the path array.
 */
int path_to_array(const char *path, char ***array);

/**
 * Counts the number of tags in a path. Uses the standand path delimiter "/" to 
 * calculate the total. Function uses strtok_r, but does not modify the path 
 * that is passed in as a parameter.
 *
 * @param path A string representing a path in the filesystem.
 * @return The number of path elements delimited by the "/" character.
 */
int num_tags_in_path(const char *path);

/**
 * Checks if a string is contained within an array. Expects a count parameter 
 * to be passed in representing the length of the array.
 * 
 * @param array The array the check.
 * @param string The string to check the array for.
 * @return True, if the string is in the array. False, if the string is not.
 */
bool array_contains_string(const char **array, const char *string, int count);

/**
 * Responsible for freeing the memory of a single pointer. The main added 
 * benefit is that it will automatically assign the pointer to NULL once it is 
 * done.
 *
 * @param ptr The pointer to free.
 */
void free_single_ptr(void **ptr);

/**
 * Responsible for freeing the memory in an array of objects that have been
 * alloc'd. Also frees the array pointer.
 *
 * @param array A pointer to the array of pointers to be free'd.
 * @param count The number of elements in the array to be free'd.
 */
void free_double_ptr(void ***array, int count);

/**
 * Returns a list of the folders at the specified location in the filesystem. This based on the files which are at the same location.
 *
 * @param path A string representing a path in the filesystem.
 * @param files The files at the specified filesystem location.
 * @param num_files The number of files in the specified filesystem location.
 * @param folders The array of folders will be populated based on the tags on the specified files.
 * @return The number of folders at the specified location.
 */
int folders_at_location(const char *path, int *files, int num_files, int **folders);

/**
 * Counts the number of tags in a path. Uses the standand path delimiter "/" to calculate the total. Function uses strtok, but does not modify the path that is passed in as a parameter.
 *
 * @param path A string representing a path in the filesystem.
const int num_tags_in_path(const char* path);
 * @return The number of path elements delimited by the "/" character.
 */
int num_tags_in_path(const char *path);

/*
 * Finds the overlap between two arrays. Namely, it will return an array with the elements both arrays have in common. Both arrays are assumed to contain sorted array of unique values. Caller is responsible for freeing the memory for returned folder array.
 *
 * @param a The first array to compare.
 * @param a_size The size of the first array.
 * @param b The second array to compare.
 * @param b_size The size of the second array.
 * @param folders An array of items which exist in both arrays.
 * @return The number of items in the intersection.
 */
int array_intersection(int *a, int a_size, int *b, int b_size, int **intersection);

/**
 * Returns a collection of the tags at a location, attempting to remove superfluous paths for reaching files.
 *
 * @param path A string representing a path in the filesystem.
 * @param files An array containing the files IDs of the files location at the specified path.
 * @param num_files The number of file IDs.
 * @param tags The array of tags to display at the location.
 * @return The number of folders at the specified location.
 */
int smart_tags_from_files(const char *path, int *files, int num_files, int **tags);

/**
 * Returns a collection of the files at the specified path in the filesystem.
 *
 * @param path A string representing a path in the filesystem.
 * @param file_array A collection containing the files in the specified path.
 * @return The number of files at the specified location.
 */
int files_at_location(const char *path, int **file_array);

/**
 * Returns the tag name that corresponds with the specified tag ID.
 *
 * @param file_id The file ID to match to a tag name.
 * @return The tag name that corresponds to the specified file ID.
 */
char *tag_name_from_tag_id(int file_id);

/**
 * Returns the directory for a given path. Specifically, a string will be returned which is the specified path minus everything after the last '/' character.
 *
 * @param path A string representing a path in the filesystem.
 * @return The directory of the specified path.
 */
char *dirname(const char *path);

/**
 * Returns the base name for a given path. specifically, a string will be returned which is the everything following the last '/' character.
 *
 * @param path A string representing a path in the filesystem.
 * @return The base name of the specified path.
 */
char *basename(const char *path);

/**
 * Checks if a file is valid. This is done with a call to file_id_from_path. If a file has a file ID, then the file is assumed to be valid.
 *
 * @param path A string representing a path in the filesystem.
 * @return True, if the file is valid. False, if the file is not valid.
 */
bool valid_path_to_file(const char *path);

/**
 * Retrieves the file ID for a file specified by path. File is identified by determining which files belong at the given location and retrieving the file ID for the file at the specified location.

 *
 * @param path A string representing a path in the filesystem.
 * @return The file ID corresponding to the file specified by path.
 */
int file_id_from_path(const char *path);

/**
 * Wrapper for db_get_file_location. Returns the location of a file on the physical filesystem.
 *
 * @param file_id The file ID in the database to match against.
 * @return The physical location on the filesystem.
 */
char *get_file_location(int file_id);

/**
 * Delete a file from the TagFS by its corresponding file ID.
 *
 * @param file_id The ID of the file to delete.
 */
void delete_file(int file_id);

/**
 * Remove all tags from a file.
 *
 * @param file_id The ID of the file to remove all tags from.
 */
void remove_tags(int file_id);

/**
 * Retrieve all tags on a file.
 *
 * @param file_id The ID of the file to retrieve.
 * @param tags The collection of tags on the specified file.
 * @return The number of tags on the specified file.
 */
int tags_from_file(int file_id, int **tags);

/**
 * Given a path and a collection of files at that location, calculate which tag is used the most among all files.
 *
 * @param path A directory path.
 * @param files An array of file IDs.
 * @param num_files The number of files.
 * @param exclude_tags An array of tag IDs to exclude from consideration.
 * @param exclude_tags_count The number tags to exclude.
 */
int most_popular_tag_on_files_at_location(const char *path, int *files, int num_files, int **exclude_tags, int *exclude_tags_count);

/**
 * Remove a file from the filesystem.
 *
 * @param file_id The ID of the file to be removed from the filesystem.
 */
void remove_file(int file_id);

/**
 * Add a tag to a file.
 *
 * @param tag_id The tag to add to the file.
 * @param file_id The file to which to add the tag.
 */
void add_tag_to_file(int tag_id, int file_id);

/**
 * Retrieve the tag ID which corresponds with a tag name.
 *
 * @param tag The tag for which to return an ID.
 */
int tag_id_from_tag_name(char *tag_name);

#endif
