drop table if exists user;
drop table if exists user_type;
drop table if exists student;

create table user_type(
    type_id int not null primary key,
    type_name varchar(255) not null
);

create table user(
    username varchar(255) not null,
    password varchar(255) not null,
    email varchar(255) primary key not null,
    type_id int not null,
    foreign key (type_id) references user_type(type_id)
);

create table student(
    number varchar(255) not null primary key,
    name varchar(255) not null,
    birthday date not null,
    address varchar(255)
);

insert into user_type(type_id, type_name) VALUES (0, 'administrator'),(1,'user');