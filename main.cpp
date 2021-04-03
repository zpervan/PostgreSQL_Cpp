#include <iostream>
#include <libpq-fe.h>
#include <sstream>

int main() {
    const char conninfo[] = "postgresql://postgres@localhost?port=5432&dbname=postgres&user=postgres&password=root";

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cout << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 1;
    } else {
        std::cout << "Connection to database succeed." << std::endl;
    }

    PGresult *res = nullptr;
    res = PQexec(conn, "SELECT * FROM pc;");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "%s[%d]: Select failed: %s\n",
                __FILE__, __LINE__, PQresultErrorMessage(res));
    } else {
        printf("Get %d has %d fields\n", PQntuples(res), PQnfields(res));
        /* print column name */
        for (int i = 0; i < PQnfields(res); i++) {
            printf("%s    ", PQfname(res, i));
        }
        putchar('\n');
        /* print column values */
        for (int i = 0; i < PQntuples(res); i++) {
            for (int j = 0; j < PQnfields(res); j++) {
                printf("%s    ", PQgetvalue(res, i, j));
            }
            putchar('\n');
        }
    }
    PQclear(res);
    return 0;
}
