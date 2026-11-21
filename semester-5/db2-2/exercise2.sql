# ερωτημα 2
show databases;
drop database if exists personnel;
create database personnel;

# ερωτημα 3
use personnel;

# ερωτημα 4
show tables;
drop table if exists DEPT;
drop table if exists JOB;
drop table if exists EMP;

# ερωτημα 5
create table DEPT(DEPTNO numeric(2), DNAME varchar(24), LOC char(23));
describe DEPT;

create table JOB(JOBCODE numeric(3), JOB_DESCR varchar(24), SAL numeric(10, 2));
describe JOB;

create table EMP(EMPNO numeric(4), NAME varchar(24), JOBNO numeric(3),
DEPTNO numeric(2), COMM numeric(10, 2));
describe EMP;

# ερωτημα 6
insert into DEPT values (50, "SALES", "ATHENS");
insert into DEPT values (60, "ACCOUNTING", "ATHENS");
insert into DEPT values (70, "PAYROLL", "VOLOS");
select * from DEPT;

insert into JOB values (100, "SALESMAN", 2000);
insert into JOB values (200, "ANALYST", 2000);
insert into JOB values (300, "DBA", 3000);
select * from JOB;

insert into EMP values (10, "CODD", 100, 50, null);
insert into EMP values (20, "NAVATHE", 200, 50, 450);
insert into EMP values (30, "ELMASRI", 300, 60, null);
insert into EMP values (40, "DATE", 100, 50, null);
select * from EMP;
