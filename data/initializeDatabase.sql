drop table if exists user;
drop table if exists user_type;
drop table if exists student;
drop table if exists department;
drop table if exists classname;

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

create table department(
    name varchar(255) primary key,
    number varchar(4)
);

create table classname(
    name varchar(255) primary key,
    number varchar(2),
    department varchar(255),
    constraint foreign key (department) references department(name)
);

create table student(
    number varchar(255) not null primary key,
    name varchar(255) not null,
    birthday date not null,
    department varchar(255),
    classname varchar(255),
    address varchar(255),
    gender varchar(16),
    constraint foreign key (department) references department(name),
    constraint foreign key (classname) references classname(name)
);

insert into user_type(type_id, type_name) VALUES (0, 'administrator'),(1,'user');
insert into department(name, number) values ('Software Department', '8008'), ('Computer Science Department', '9109');
insert into classname(name, number, department) values ('Software 2301', '23', 'Software Department'),
                                                       ('Software 2302', '23', 'Software Department'),
                                                       ('Software 2303', '23', 'Software Department'),
                                                       ('Software 2304', '23', 'Software Department'),
                                                       ('Software 2305', '23', 'Software Department'),
                                                       ('Software 2306', '23', 'Software Department'),
                                                       ('Software 2307', '23', 'Software Department'),
                                                       ('Computer Science 2301', '23', 'Computer Science Department'),
                                                       ('Computer Science 2302', '23', 'Computer Science Department'),
                                                       ('Computer Science 2303', '23', 'Computer Science Department');