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
drop table if exists PROJECT;

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

# ερωτημα 7
alter table EMP add HIREDATE date;
describe EMP;

# ερωτημα 8
update EMP set HIREDATE="2001-01-10" where EMPNO=10;
update EMP set HIREDATE="1999-02-25" where EMPNO=20;
update EMP set HIREDATE="2000-03-17" where EMPNO=30;
update EMP set HIREDATE="1989-06-07" where EMPNO=40;
select * from EMP;

# ερωτημα 9
alter table JOB modify JOB_DESCR varchar(30);
describe JOB;

# ερωτημα 10
alter table DEPT drop LOC;
describe DEPT;

# ερωτημα 11
alter table DEPT change DNAME DEPT_NAME varchar(25);
describe DEPT;

# ερωτημα 12
alter table DEPT add constraint pk_DEPTNO primary key (DEPTNO);
describe DEPT;

# ερωτημα 13
alter table DEPT drop primary key;
describe DEPT;
show create table DEPT;

# ερωτημα 14
alter table DEPT add constraint pk_DEPTNO primary key (DEPTNO);
describe DEPT;

alter table JOB add constraint pk_JOBCODE primary key (JOBCODE);
describe JOB;

alter table EMP add constraint pk_EMPNO primary key (EMPNO);
alter table EMP add constraint fk_JOBNO foreign key(JOBNO) references JOB(JOBCODE);
alter table EMP add constraint fk_DEPTNO foreign key(DEPTNO) references DEPT(DEPTNO);
describe EMP;

# ερωτημα 15
alter table EMP drop foreign key fk_JOBNO;
describe EMP;
show create table EMP;

alter table EMP drop foreign key fk_DEPTNO;
describe EMP;
show create table EMP;

# ερωτημα 16
alter table DEPT alter DEPT_NAME set default "Development";
insert into EMP(EMPNO,NAME,JOBNO,DEPTNO,COMM) values (10, "CODD", 100, 50, NULL);
insert into DEPT(DEPTNO) values (10), (20);
select * from DEPT;
insert into DEPT values (30, "Sales");
select * from DEPT;

# ερωτημα 17
select * from INFORMATION_SCHEMA.TABLE_CONSTRAINTS where CONSTRAINT_SCHEMA="personnel";

# ερωτημα 18
create table PROJECT(P_ID int auto_increment, P_NAME varchar(255), primary key(P_ID));
describe PROJECT;

# ερωτημα 19
insert into PROJECT(P_NAME) values ("Market analysis");
select * from PROJECT;

# ερωτημα 20
alter table PROJECT auto_increment = 200;
insert into PROJECT(P_NAME) values ("Landing page");
select * from PROJECT;




