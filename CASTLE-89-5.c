#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>


int validate_id(const char *id) {
    for (int i = 0; id[i] != '\0'; i++) {
        if (id[i] == '\'') {
            return 0;
        }
    }
    return 1;
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Credentials
    const char *server = getenv("DB_ADDRESS");
    const char *user = getenv("DB_USERNAME");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_DATABASE");
    if (server == NULL || user == NULL || password == NULL || database == NULL) {
        printf("Missing database credentials\n");
        return 1;
    }

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Failed to allocate memory.\n");
        return 1; // Indicate error and exit
    }

    // Connect to database
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(conn));
        return 1;
    }
    printf("Connection successful!\n");

    char id[32];
    printf("ID: ");
    fgets(id, sizeof(id), stdin);

    // Validate input
    if (!validate_id(id)) {
        printf("Invalid ID\n");
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT * FROM tokens WHERE id = %s", id);

    // Send SQL query
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        return 1;
    }

    // Store the result
    res = mysql_store_result(conn);

    // Output the result row by row
    int num_fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}