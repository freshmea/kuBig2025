-- 데이터베이스 생성
create database mydb;
grant all privileges on mydb.* to 'myuser' @'%';
-- 테이블 생성
use mydb;
create table Book (
    bookid integer primary key,
    bookname varchar(40),
    publisher varchar(40),
    price integer
);