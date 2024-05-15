
drop table RESERVES;
drop table BOATS;
 drop table sailors;

create table sailors(
     sid NUMBER primary key,
     SNAME varchar2(10),
     RATING NUMBER,
     AGE number
 );
 
 create table BOATS(
     BID NUMBER primary key,
     BNAME VARCHAR2(10),
     COLOR VARCHAR2(10)
 );
 
 create table RESERVES(
     sid NUMBER,
     bid NUMBER,
     day date,
     CONSTRAINT reserves_Fk FOREIGN KEY (bid) REFERENCES BOATS (bid),
     CONSTRAINT BID_fk FOREIGN KEY (sid) REFERENCES sailors (sid)
 );

 

 

 INSERT INTO sailors VALUES(22,'DUSTIN',7,45.0);
 INSERT INTO SAILORS VALUES(29,'BRUTUS',1,33.0);
 INSERT INTO SAILORS VALUES(31,'LUBBER',8,55.5);
 INSERT INTO SAILORS VALUES(32,'ANDY',8,25.5);
 INSERT INTO SAILORS VALUES(58,'RUSTY',10,35.0);
 INSERT INTO SAILORS VALUES(64,'HORATIO',7,35.0);
 INSERT INTO SAILORS VALUES(71,'ZORBA',10,16.0);
 INSERT INTO SAILORS VALUES(74,'HORATIO',9,35.0);
 INSERT INTO SAILORS VALUES(85,'ART',3,25.5);
 INSERT INTO SAILORS VALUES(95,'BOB',3,63.5);

 INSERT INTO BOATS values(101,'Interlake','blue');
 INSERT INTO BOATS values(102,'Interlake','red');
 INSERT INTO BOATS values(103,'Clipper','green');
 INSERT INTO BOATS values(104,'Marine','red');

 INSERT INTO RESERVES VALUES(22,101,'10-OCT-98');
 INSERT INTO RESERVES VALUES(22,102,'10-OCT-98');
 INSERT INTO RESERVES VALUES(22,103,'10-AUG-98');
 INSERT INTO RESERVES VALUES(22,104,'10-JUL-98');
 INSERT INTO RESERVES VALUES(31,102,'11-OCT-98');
 INSERT INTO RESERVES VALUES(31,103,'11-JUN-98');
 INSERT INTO RESERVES VALUES(31,104,'11-DEC-98');
 INSERT INTO RESERVES VALUES(64,101,'9-MAY-98');
 INSERT INTO RESERVES VALUES(64,102,'9-AUG-98');
 INSERT INTO RESERVES VALUES(74,103,'9-AUG-98');


