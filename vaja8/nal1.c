#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

// Deklaracije spremenljivk
MYSQL *conn;              // Povezava
MYSQL_RES *res;           // Rezultat
MYSQL_ROW row;            // Vrstica
const char *server = "localhost";
const char *user = "root";
const char *password = "";
const char *database = "vaja";

// Vzpostavimo povezavo z podatkovno bazo
int main() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    // Povezava z bazo
    if (mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    if(mysql_query(conn, "INSERT INTO Pors (portid, opis) VALUES (10, 'Demo')")) {
        fprintf(stderr, "SELECT query failed\n");
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    

    // Izvedba poizvedbe
    if (mysql_query(conn, "SELECT * FROM Pors")) {
        fprintf(stderr, "SELECT * FROM Pors. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Prikaz rezultatov
    int num_fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for(int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }  

    // Čiščenje in zapiranje povezave
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}