# question 2
show databases;
create database personnel;
# question 3
use personnel;
# question 4
show tables;
drop table DEPT;
drop table JOB;
drop table EMP;
# question 5
create table DEPT(DEPTNO int(2) not null, DNAME varchar(30), LOC varchar(30),
primary key(DEPTNO));
describe DEPT;
insert into DEPT values (50, "ΠΟΛΗΣΕΙΣ", "ΑΘΗΝΑ");
insert into DEPT values (60, "ΛΟΓΙΣΤΗΡΙΟ", "ΑΘΗΝΑ");
insert into DEPT values (70, "ΜΙΣΘΟΔΟΣΙΑ", "ΒΟΛΟΣ");
create table JOB(JOBCODE int(3) not null, JOB_DESCR varchar(30), SAL int(4), primary key(JOBCODE));
describe JOB;
insert into JOB values (100, "ΠΩΛΗΤΗΣ", 2200);
insert into JOB values (200, "ΑΝΑΛΥΤΗΣ", 2000);
insert into JOB values (300, "ΧΕΙΡΙΣΤΗΣ", 1000);
create table EMP(EMPNO int(2) not null, NAME varchar(30), JOBNO int(3) not null, DEPTNO int(2) not null, COMM int(3), primary key(EMPNO), foreign key(JOBNO) references JOB (JOBCODE), foreign key(DEPTNO) references DEPT (DEPTNO));
describe EMP;
insert into EMP values (10, 
# question 6