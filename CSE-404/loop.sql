
-- DECLARE i := 1 ;

-- BEGIN 
--   LOOP
--        if i < 10 
--        then
--        DBMS_OUTPUT.PUT_LINE(i);
--        i := i + 1;
--        end if;

--     END LOOP;
   
-- END;
--/

-- DECLARE 
--   v NUMBER := 1;
-- BEGIN
--   while v < 10
--   LOOP
--     if mod(v,2) != 0
--     then
--     DBMS_OUTPUT.PUT_LINE(v);
--     end if;
--     v := v + 1;
--   END LOOP;
-- END;
-- /


-- DECLARE 
--   v employees%rowtype ;
--   i NUMBER := &sv_user_num;

-- BEGIN 
--   select * 
--   into v 
--   from employees
--   where employee_id = i;
--   DBMS_OUTPUT.PUT_LINE(v.first_name || v.last_name || ' has an id of ' || i);
-- exception 
--    when no_data_found 
--    then 
--    raise_application_error(-2001,'The student '|| 'is not in the datanbase');
--    end;
--    /                   

-- DECLARE
-- 			CURSOR c_zip IS
-- 			SELECT *
-- 			FROM employees;
-- 			vr_zip c_zip%ROWTYPE;
-- 		BEGIN
-- 			OPEN c_zip;
-- 			LOOP
-- 			FETCH c_zip INTO vr_zip;
-- 			EXIT WHEN c_zip%NOTFOUND;
-- 			DBMS_OUTPUT.PUT_LINE(vr_zip.employee_id || ' ' || vr_zip.first_name || 'commisson ' || (vr_zip.salary+vr_zip.salary*NVL(vr_zip.commission_pct,0)));
-- 			END LOOP;
-- 		END;

-- /

-- DECLARE
--     CURSOR c_zip IS
--         SELECT *
--         FROM employees;
--     vr_zip c_zip%ROWTYPE;
-- BEGIN
--     OPEN c_zip;
--     LOOP
--         FETCH c_zip INTO vr_zip;
--         EXIT WHEN c_zip%FOUND = FALSE; 
--         DBMS_OUTPUT.PUT_LINE(vr_zip.employee_id);
--     END LOOP;
-- END;
-- /


-- DECLARE
--     id NUMBER
--     salary NUMBER
--     CURSOR c_zip IS
--         SELECT *
--         FROM employees;
--     vr_zip c_zip%ROWTYPE;
-- BEGIN
--     OPEN c_zip;
--     FETCH c_zip INTO vr_zip;
--     WHILE c_zip%FOUND LOOP
--        insert into custom values(id,salary);
--        FETCH c_zip INTO vr_zip;
--     END LOOP;
--     CLOSE c_zip;
-- END;
-- /

-- create table custom(
--    id number ,
--    salary number 
-- );

DECLARE
    id NUMBER;
    salary NUMBER;
    CURSOR c_zip IS
        SELECT *
        FROM employees;
    vr_zip c_zip%ROWTYPE;
BEGIN
    OPEN c_zip;
    FETCH c_zip INTO vr_zip;
    WHILE c_zip%FOUND LOOP
        IF vr_zip.salary > 10000 THEN
            id := vr_zip.employee_id;
            salary := vr_zip.salary;
            INSERT INTO custom VALUES (id, salary); 
        END IF;
        FETCH c_zip INTO vr_zip;
    END LOOP;
    CLOSE c_zip;
END;
/




