# ερωτημα 2
show databases;
create database if not exists personnel;

# ερωτημα 3
use personnel;

# ερωτημα 4
show tables;
drop table if exists DEPT;
drop table if exists JOB;
drop table if exists EMP;

# ερωτημα 5
create table DEPT(DEPTNO int(2) not null, DNAME varchar(30), LOC varchar(30),
primary key(DEPTNO));
describe DEPT;
insert into DEPT values (50, "ΠΩΛΗΣΕΙΣ", "ΑΘΗΝΑ");
insert into DEPT values (60, "ΛΟΓΙΣΤΗΡΙΟ", "ΑΘΗΝΑ");
insert into DEPT values (70, "ΜΙΣΘΟΔΟΣΙΑ", "ΒΟΛΟΣ");

create table JOB(JOBCODE int(3) not null, JOB_DESCR varchar(30), SAL int(4), primary key(JOBCODE));
describe JOB;
insert into JOB values (100, "ΠΩΛΗΤΗΣ", 2200);
insert into JOB values (200, "ΑΝΑΛΥΤΗΣ", 2000);
insert into JOB values (300, "ΧΕΙΡΙΣΤΗΣ", 1000);

create table EMP(EMPNO int(2) not null, NAME varchar(30), JOBNO int(3) not null,
DEPTNO int(2) not null, COMM int(3), primary key(EMPNO), foreign key(JOBNO)
references JOB (JOBCODE), foreign key(DEPTNO) references DEPT (DEPTNO));
describe EMP;
insert into EMP values (10, "ΣΠΥΡΟΥ", 100, 50, 450);
insert into EMP values (20, "ΧΡΗΣΤΟΥ", 200, 50, null);
insert into EMP values (30, "ΝΙΚΟΥ", 300, 60, null);
insert into EMP values (40, "ΣΠΥΡΟΥ", 200, 50, null);

# ερωτημα 6
select E.EMPNO, E.NAME, J.JOB_DESCR, J.SAL, E.DEPTNO from EMP as E
join JOB as J on E.JOBNO = J.JOBCODE where J.JOB_DESCR = "ΠΩΛΗΤΗΣ";

# ερωτημα 7
select max(J.SAL), min(J.SAL), avg(J.SAL), count(J.SAL), count(E.COMM), count(*) from EMP as E join JOB as J on E.JOBNO = J.JOBCODE

# ερωτημα 8
select max(J.SAL), avg(J.SAL) from JOB as J where J.JOB_DESCR = "ΑΝΑΛΥΤΗΣ" group by J.JOBCODE;

# ερωτημα 9
select E.EMPNO, E.NAME, J.JOB_DESCR, J.SAL, E.DEPTNO from EMP as E join JOB as J on E.JOBNO = J.JOBCODE
where J.SAL >= 1000 and J.SAL <= 2500

# ερωτημα 10
select E.EMPNO, E.NAME, J.JOB_DESCR, J.SAL, E.DEPTNO from EMP as E join JOB as J on E.JOBNO = J.JOBCODE
where E.NAME like "%Ρ%"; 

# ερωτημα 11
select E.EMPNO, E.NAME, J.JOB_DESCR, J.SAL, E.DEPTNO from EMP as E
join JOB as J on E.JOBNO = J.JOBCODE order by E.DEPTNO;

select E.EMPNO, E.NAME, J.JOB_DESCR, J.SAL, E.DEPTNO from EMP as E
join JOB as J on E.JOBNO = J.JOBCODE order by J.SAL;

# ερωτημα 12
select D.DNAME, floor(avg(J.SAL)), count(E.EMPNO) from EMP as E join JOB as J on E.JOBNO = J.JOBCODE
join DEPT as D on E.DEPTNO = D.DEPTNO group by D.DNAME;




