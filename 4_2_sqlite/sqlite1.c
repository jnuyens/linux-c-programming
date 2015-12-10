#include <sqlite3.h>
#include <stdio.h>

int main(void) {
    
    sqlite3 *database; 	/*a database handle: pointer to a pointer */
    char *err_msg = 0;
    
    int return_code = sqlite3_open("test.db", &database);

/* This opens a database connection
It returns SQLITE_OK if the connection was opened successfully*/
    
    if (return_code != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(database));
        sqlite3_close(database);

 /* even if the connection fails to the database, we still need to release the 
connection handle with sqlite3_close */

        return 1;
    }
    
    char *sql_statement = "DROP TABLE IF EXISTS Students;" 
                "CREATE TABLE Students(Id INT, Name TEXT, Number INT);" 
                "INSERT INTO Students VALUES(1, 'Linus', 42);" 
                "INSERT INTO Students VALUES(2, 'Richard', 1);" 
                "INSERT INTO Students VALUES(3, 'Greg', 666);" 
                "INSERT INTO Students VALUES(4, 'Andrew', 4242);";

    return_code = sqlite3_exec(database, sql_statement, 0, 0, &err_msg);
/*we provide the obtained database handle, the sql statement string, the third 
* parameter is a callback function invoked for each result row, the 4th parameter 
is the first parameter passed to the callback function and err_msg can be used 
to see what the error message waws with sqlite3_free(err_msg). */
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQLite error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(database);
        return 1;
    } 
    
    sqlite3_close(database);
    return 0;
}
