/**
 * Handles interaction with the sqlite3 database.
 *
 * @file tagfs_db.h
 * @author Keith Woelke
 * @date 07/25/2010
 */

#ifndef TAGFS_DB_H
#define TAGFS_DB_H

/**
 * Returns a physical file system location corresponding to a location in the 
 * TagFS.
 *
 * @param file_id The file ID for which to return the full physical path.
 *
 * @return The path to the physical location in the file system corresponding 
 * to the file ID in the TagFS.
 */
char *db_get_file_location(int file_id);

/**
 * Retrieve a set of unique tags associated with a collection of file IDs
 *
 * @param files Array of file IDs.
 * @param num_files Number of file IDs in the array.
 * @param folders The collection of tags associated with the file IDs.
 *
 * @return The number of unique tags associated with the file IDs.
 */
int db_get_tags_from_files(const int *files, int num_files, int **folders);




int db_get_all_tags(int **folders);

#endif
