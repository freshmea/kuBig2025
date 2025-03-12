#include <mysql.h>
#include <stdio.h>
#include <string.h>
// sudo apt install libmysql++*
// dpkg -L libmysqlclient-dev | grep mysql.h
// cc -o bookSql bookSql.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
// libmysqlclient.so libmysqlclient.a
typedef struct
{
    int bookid;
    char bookname[40];
    char publisher[40];
    int price;
} Book;

int main(void)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *host = "localhost";
    char *user = "myuser";
    char *pass = "0000";
    char *db = "mydb";
    char query[255];
    int port = 3306;

    strcpy(query, "select * from Book");

    // 연결
    conn = mysql_init(NULL); // DB 연결 요청 준비
    if (mysql_real_connect(conn, host, user, pass, db, port, NULL, 0))
        printf("MySQL 연결 성공\n");
    else
    {
        printf("MySQL 연결 실패\n");
        return 1;
    }

    // 쿼리 요청
    if (mysql_query(conn, query))
    {
        printf("쿼리 실패");
        return 1;
    }
    res = mysql_store_result(conn);
    Book book[100]; // 동적 할당이 좋지만 일단... 스택에 만들자.
    int i = 0;
    // 데이터 베이스의 정보를 구조체에 저장 - ORM
    while (row = mysql_fetch_row(res))
    {
        book[i].bookid = atoi(row[0]);
        strcpy(book[i].bookname, row[1]);
        strcpy(book[i].publisher, row[2]);
        book[i].price = atoi(row[3]);
        ++i;
    };
    for (int j = 0; j < i; ++j)
    {
        printf("%d \t%s \t%s \t%d \n",
               book[j].bookid, book[j].bookname,
               book[j].publisher, book[j].price);
    }
    mysql_close(conn);

    return 0;
}