create database angela;
show databases;
use angela;

create table alumno(
id varchar(6) not null,
nombre varchar(20) not null,
paterno varchar(20)
);

show tables;

insert into alumno values("123456","Valerio","Gomez");
insert into alumno values("987653","Maria","Rivarola");
insert into alumno values("234567","Alberto","Baez");
insert into alumno values("098463","Juan","Cardena");
insert into alumno values("537865","Marco","Tito");
insert into alumno values("427465","David","Alvares");
commit;
describe alumno;


c++
-lmysql
