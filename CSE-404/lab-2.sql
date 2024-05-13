
-- create table taken(
--    student varchar2(20),
--    course  varchar2(30)
-- );

-- create table required(
--    course  varchar2(30)
-- );


-- insert into taken values(
--   'Robert','Databases'
-- );

-- insert into taken values(
--   'Robert','Programming Languages'
-- );

-- insert into taken values(
--   'Susie','Databases'
-- );

-- insert into taken values(
--   'Susie','Operating Systems'
-- );

-- insert into taken values(
--   'Julie','Programming Languages'
-- );

-- insert into taken values(
--   'Julie','Machine Learning'
-- );

-- insert into taken values(
--   'Emilie','Operating Systems'
-- );

-- insert into required values(
--   'Databases'
-- );

-- insert into required values(
--   'Programming Languages'
-- );

-- select student from taken
-- minus
-- select  student from (
--   select student,course from (select student from taken),required
--   minus 
--   select student,course from taken
-- );
-- select student from taken 
-- minus
-- select student from taken
-- where course not in(select course from required);


-- select student from taken 
-- where course in (select course from required)
-- group by student
-- having count(*) = (select count(*) from required);

-- select student , count(course) , group_concat(course) from taken 
-- group by student;

-- select BRANCH_NAME from BRANCH where BRANCH_CITY= 'Brooklyn';

-- select distinct  CUSTOMER_NAME,BRANCH_CITY from DEPOSITOR,ACCOUNT,BRANCH 
-- where DEPOSITOR.ACCOUNT_NUMBER = ACCOUNT.ACCOUNT_NUMBER and ACCOUNT.BRANCH_NAME = BRANCH.BRANCH_NAME and
-- BRANCH_CITY='Brooklyn';

-- select CUSTOMER_NAME , count(*) from DEPOSITOR 
-- where (select distinct BRANCH_NAME from ACCOUNT
--  where ACCOUNT.ACCOUNT_NUMBER = DEPOSITOR.ACCOUNT_NUMBER)
--  in (select  BRANCH_NAME from BRANCH where BRANCH_CITY = 'Brooklyn')
--  group by CUSTOMER_NAME
--  having count(*) = (select count(*) from BRANCH where BRANCH_CITY = 'Brooklyn')
--  ;

-- select BRANCH_NAME from BRANCH where BRANCH_CITY = 'Brooklyn';
select CUSTOMER_NAME from DEPOSITOR
minus(
select CUSTOMER_NAME from (
select CUSTOMER_NAME,BRANCH_NAME from (select BRANCH_NAME from BRANCH where BRANCH_CITY = 'Brooklyn'),(select distinct CUSTOMER_NAME from DEPOSITOR)
minus
(select CUSTOMER_NAME,BRANCH_NAME from DEPOSITOR,ACCOUNT where DEPOSITOR.ACCOUNT_NUMBER = ACCOUNT.ACCOUNT_NUMBER)));