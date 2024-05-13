-- select  * from tab;

--rollback

-- CREATE OR REPLACE PROCEDURE raise_salary 
--  (p_id  IN employees.employee_id%TYPE,
--   P_percent IN NUMBER )
-- IS 
-- BEGIN 
--  UPDATE employees
--  SET  salary = salary * (1 + P_percent/100)
--  WHERE employee_id = p_id;
-- END raise_salary;
-- /

-- CREATE OR REPLACE PROCEDURE query_emp
--  (p_id IN employees.employee_id%TYPE,
--   p_name OUT employees.last_name%TYPE,
--   p_salary OUT employees.salary%TYPE) IS 

-- BEGIN 
--   SELECT last_name , salary INTO p_name , p_salary 
--   FROM employees
--   WHERE employee_id = p_id;
-- END query_emp;
-- /

-- DECLARE 
--   v_emp_name employees.last_name%TYPE;
--   v_emp_sal employees.salary%TYPE;
-- BEGIN 
--   query_emp(171,v_emp_name,v_emp_sal);
--   DBMS_OUTPUT.PUT_LINE(v_emp_name||' earns '||
--   to_char(v_emp_sal,'$999,999.00'));
--   END;
-- /

-- CREATE table phone(
--     phone_no VARCHAR2(20),
--     CONSTRAINT pk primary key (phone_no)
-- );

-- CREATE table modified_phone(
--     updated_phone_no VARCHAR2(20),
--     CONSTRAINT up_pk primary key (updated_phone_no)
-- );

-- drop table phone;
-- drop table modified_phone;


-- INSERT INTO phone VALUES('8006330575',1);

-- INSERT INTO phone VALUES('8006330574',2);

-- INSERT INTO phone VALUES('8006330573',3);

-- CREATE OR REPLACE PROCEDURE format_phone
-- (
--   p_phone_no IN OUT VARCHAR2
-- ) IS

-- BEGIN 
--   p_phone_no := '(' || substr(p_phone_no,1,3) || ') ' ||
--                      substr(p_phone_no,4,3) || '-' ||
--                      substr(p_phone_no,7);

--  END format_phone;
-- /


-- DECLARE
--   v_phone_no phone.phone_no%TYPE; 
  
-- BEGIN
--    v_phone_no := '8006330575'; 
--   format_phone(v_phone_no);

--   DBMS_OUTPUT.PUT_LINE('Formatted Phone Number: ' || v_phone_no);
-- END;
-- /

-- select phone_no from phone;


-- DECLARE
--   v_phone_no phone.phone_no%TYPE; 
  
-- BEGIN
--    v_phone_no := '8006330574'; 
--   format_phone(v_phone_no);

--   INSERT INTO modified_phone VALUES(v_phone_no);
-- END;
-- /
 


--  DECLARE
--   v_phone_no phone.phone_no%TYPE; 
  
-- BEGIN
--   SELECT phone_no INTO v_phone_no
--   FROM phone
--   where id = 3;
--   format_phone(v_phone_no);

--   INSERT INTO modified_phone VALUES(v_phone_no);
-- END;
-- /

-- CREATE table modified_phone(
--     updated_phone_no VARCHAR2(20)
-- );


-- CREATE table phone(
--     phone_no VARCHAR2(20),
--     id NUMBER,
--     CONSTRAINT pk primary key (id)
-- );

-- CREATE OR REPLACE function adder(n1 IN number,n2 IN number)
-- RETURN number
-- IS
-- n3 number(8);
-- BEGIN 
-- n3 := n1+n2;
-- return n3;
-- END;
-- /

-- DECLARE

--   n3 number(2);

-- BEGIN

--   n3 := adder(11,22);
--   dbms_output.put_line('Addition:' || n3);

-- END;
-- /

-- CREATE OR REPLACE FUNCTION totalCustomers  
-- RETURN number 
-- IS  
--    total number;  
-- BEGIN  
--    SELECT count(*) into total  
--    FROM customers;  
--     RETURN total;  

-- EXCEPTION
--    WHEN NO_DATA_FOUND THEN
--       -- Handle the case where the customers table is empty
--       RETURN 0;
-- END;  
-- /  

-- DECLARE  
--    c number(2);  
-- BEGIN  
--    c := totalCustomers();  
--    dbms_output.put_line('Total no. of Customers: ' || c);  
-- END;  
-- /  

-- CREATE OR REPLACE FUNCTION get_sal
--  (p_id employees.employee_id%TYPE)
--  return NUMBER 
--  IS 
--   v_sal employees.salary%TYPE ;

-- BEGIN
--   v_sal := 0;
--   select salary
--   INTO v_sal
--   FROM employees
--   WHERE employee_id = p_id;
--   RETURN v_sal;
-- END get_sal; 
-- /

-- EXECUTE dbms_output.put_line(get_sal(100));

-- SELECT get_sal(100) AS emp_salary FROM dual;

-- DECLARE
--   v_salary NUMBER;
-- BEGIN
--   v_salary := get_sal(100);
--   DBMS_OUTPUT.PUT_LINE('Employee Salary: ' || v_salary);
-- END;
-- /

-- select salary As Employee_Salary from employees where employee_id = 100;

-- DECLARE
--   sal employees.salary%type;
-- BEGIN
--   sal := get_sal(101);
--   DBMS_OUTPUT.PUT_LINE('The salary is: '|| sal);
-- END;
-- /

-- CREATE OR REPLACE FUNCTION tax(id IN NUMBER)
--   return NUMBER IS
--   BEGIN
--     RETURN (select (salary+salary*NVL(commission_pct,0)) AS annual_income from employees where employees.employee_id = id);
--   END tax;
-- /

-- CREATE OR REPLACE FUNCTION tax(id IN NUMBER)
--   RETURN NUMBER
-- IS
--   v_annual_income NUMBER;
-- BEGIN
 
--   SELECT (salary + salary * NVL(commission_pct, 0))
--   INTO v_annual_income
--   FROM employees
--   WHERE employee_id = id;

--   RETURN v_annual_income;

-- END tax;
-- /

-- CREATE OR REPLACE FUNCTION tax(c_value IN NUMBER,p_value IN NUMBER)
--   return NUMBER IS
--   BEGIN
--     RETURN ((12 * p_value + 12 * p_value * c_value )*0.08);
--   END tax;
-- /

-- select employee_id,last_name,salary,tax(NVL(commission_pct,0),salary) from employees where employee_id = 100;

-- DECLARE 
--   v_num1 NUMBER:= 5;
--   v_num2 NUMBER:= 1;
--   v_num3 NUMBER:= 7;
--   v_temp NUMBER;
-- BEGIN
--   IF v_num1 > v_num2
--   THEN
--     v_temp := v_num1;

--   IF v_num2 > v_num3
--   THEN
--     v_temp := v_num2;

--   IF v_num3 > v_num1
--   THEN v_temp := v_num3;

--   dbms_output.put_line(v_temp);
-- END;
-- /

-- DECLARE 
--   v_num1 NUMBER := 5;
--   v_num2 NUMBER := 1;
--   v_num3 NUMBER := 7;
--   v_temp NUMBER;
-- BEGIN
  
--   v_temp := v_num1;

--   IF v_num2 > v_temp 
--   THEN
--     v_temp := v_num2;
--   END IF;

--   IF v_num3 > v_temp 
--   THEN
--     v_temp := v_num3;
--   END IF;

--   dbms_output.put_line('Maximum value is: ' || v_temp);
-- END;
-- /



DECLARE
  input VARCHAR2(10):= '&svletter';
  
BEGIN
  
 IF (input >= 'A' AND input <= 'Z')
   THEN dbms_output.put_line('This is a uppercase code');

 ELSIF (input >= 'a' AND input <= 'z')
   THEN dbms_output.put_line('This is a lowercase code');

 ELSE dbms_output.put_line('This is a NUMBER');

 END IF;
END;
/







