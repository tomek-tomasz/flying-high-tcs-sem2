--ZAD1
CREATE OR REPLACE FUNCTION cast_int(val varchar) 
RETURNS int AS $$
BEGIN
    RETURN val::int;
EXCEPTION WHEN OTHERS THEN
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;
----
--ZAD2
SELECT string_to_array(trim(tab::text, '()'), ',') AS wynik
FROM tab;
----
--ZAD3
CREATE OR REPLACE FUNCTION nulls(VARIADIC arr anyarray) 
RETURNS int AS $$
BEGIN
    RETURN (
        SELECT (count(*) - count(val))::int 
        FROM unnest(arr) AS val
    );
END;
$$ LANGUAGE plpgsql;
----
--ZAD4
CREATE OR REPLACE FUNCTION remove_duplicates(table_name text) 
RETURNS void AS $$
BEGIN
    EXECUTE format(
        'DELETE FROM %I a USING %I b WHERE a.* = b.* AND a.ctid > b.ctid', 
        table_name, 
        table_name
    );
END;
$$ LANGUAGE plpgsql;
----
--ZAD5
CREATE OR REPLACE FUNCTION array_intersect(t1 anyarray, t2 anyarray)
    RETURNS anyarray AS
$$
BEGIN
    RETURN ARRAY(
        SELECT unnest(t1)
        INTERSECT
        SELECT unnest(t2)
        ORDER BY 1
    );
END;
$$
LANGUAGE plpgsql;
----
--ZAD6
CREATE OR REPLACE FUNCTION array_sort(t anyarray)
    RETURNS anyarray AS
$$
BEGIN
    RETURN ARRAY(
        SELECT unnest(t)
        ORDER BY 1
    );
END;
$$
LANGUAGE plpgsql;
----
--ZAD7
SELECT *, (ctid::text::point)[1]::integer AS numer
FROM tab
WHERE (ctid::text::point)[1]::integer % 3 = 1;
----
--ZAD8
SELECT nazwa, rodzaj
FROM zwierzeta
ORDER BY 
    CASE 
        WHEN rodzaj = 'pies' THEN 1
        WHEN rodzaj = 'kot' THEN 2
        ELSE 3
    END,
    nazwa;
----
--ZAD9
ALTER TABLE tab 
DROP CONSTRAINT tab_b_check;
ALTER TABLE tab 
ALTER COLUMN b TYPE boolean 
USING b = 'tak';
----
--ZAD10
SELECT tablename 
FROM pg_catalog.pg_tables 
WHERE schemaname = 'public';
----
--ZAD11
CREATE OR REPLACE FUNCTION remove_all() 
RETURNS void AS $$
DECLARE
    row record;
BEGIN
    FOR row IN (SELECT tablename FROM pg_catalog.pg_tables WHERE schemaname = 'public') LOOP
        EXECUTE 'DROP TABLE ' || quote_ident(row.tablename) || ' CASCADE';
    END LOOP;
END;
$$ LANGUAGE plpgsql;

SELECT remove_all();
----
--ZAD12
SELECT 
    tablename,
    pg_total_relation_size(schemaname || '.' || tablename)
FROM 
    pg_catalog.pg_tables
WHERE 
    schemaname = 'public';
----