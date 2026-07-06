--ZAD1
CREATE OR REPLACE FUNCTION pesel_check() 
    RETURNS TRIGGER AS 
$pesel_check$
DECLARE 
    sum int;
    last_digit int;
BEGIN
    IF LENGTH(NEW.pesel) != 11 THEN
        RAISE EXCEPTION 'Niepoprawny PESEL';
    END IF;
    SELECT 0 INTO sum;
    SELECT ASCII(SUBSTRING(NEW.pesel FROM 11 FOR 1)) - ASCII('0')
    INTO last_digit;
    SELECT 
        (sum + 1 * (ASCII(SUBSTRING(NEW.pesel FROM 1 FOR 1)) - ASCII('0'))) % 10
    INTO sum;
    SELECT 
        (sum + 3 * (ASCII(SUBSTRING(NEW.pesel FROM 2 FOR 1)) - ASCII('0'))) % 10
    INTO sum;
    SELECT 
        (sum + 7 * (ASCII(SUBSTRING(NEW.pesel FROM 3 FOR 1)) - ASCII('0'))) % 10
    INTO sum;
    SELECT 
        (sum + 9 * (ASCII(SUBSTRING(NEW.pesel FROM 4 FOR 1)) - ASCII('0'))) % 10
    INTO sum;
    SELECT 
        (sum + 1 * (ASCII(SUBSTRING(NEW.pesel FROM 5 FOR 1)) - ASCII('0'))) % 10
    INTO sum;
    SELECT 
        (sum + 3 * (ASCII(SUBSTRING(NEW.pesel FROM 6 FOR 1)) - ASCII('0'))) % 10
    INTO sum;
    SELECT 
        (sum + 7 * (ASCII(SUBSTRING(NEW.pesel FROM 7 FOR 1)) - ASCII('0'))) % 10
    INTO sum;
    SELECT 
        (sum + 9 * (ASCII(SUBSTRING(NEW.pesel FROM 8 FOR 1)) - ASCII('0'))) % 10
    INTO sum;
    SELECT 
        (sum + 1 * (ASCII(SUBSTRING(NEW.pesel FROM 9 FOR 1)) - ASCII('0'))) % 10
    INTO sum;
    SELECT 
        (sum + 3 * (ASCII(SUBSTRING(NEW.pesel FROM 10 FOR 1)) - ASCII('0'))) % 10
    INTO sum;
    IF (10 - sum) % 10 != last_digit THEN
        RAISE EXCEPTION 'Niepoprawny PESEL';
    END IF;
    RETURN NEW;
END;
$pesel_check$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER pesel_check BEFORE INSERT OR UPDATE ON pacjenci
FOR EACH ROW EXECUTE PROCEDURE pesel_check();
----
--ZAD2
CREATE OR REPLACE FUNCTION data_zakonczenia()
    RETURNS TRIGGER AS
$data_zakonczenia$
BEGIN
    IF NEW.data_zakonczenia IS NULL THEN 
        SELECT NEW.data_rozpoczecia + INTERVAL '30 minutes'
        INTO NEW.data_zakonczenia;
    END IF;
    RETURN NEW;
END;
$data_zakonczenia$
LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER data_zakonczenia BEFORE INSERT ON wizyty
FOR EACH ROW EXECUTE PROCEDURE data_zakonczenia();
----
--ZAD3
CREATE OR REPLACE FUNCTION last_5_years()
    RETURNS TRIGGER AS
$last_5_years$
BEGIN
    IF OLD.data_rozpoczecia >= NOW() - INTERVAL '5 years' THEN
        RETURN NULL;
    END IF;
    RETURN OLD;
END;
$last_5_years$
LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER last_5_years BEFORE DELETE ON wizyty
FOR EACH ROW EXECUTE PROCEDURE last_5_years();
----
--ZAD4
CREATE OR REPLACE FUNCTION spojnosc()
    RETURNS TRIGGER AS
$spojnosc$
DECLARE
last_date TIMESTAMP;
last_first_date TIMESTAMP;
BEGIN
    IF NEW.data_zakonczenia IS NOT NULL
    AND NEW.data_zakonczenia - NEW.data_rozpoczecia > INTERVAL '1 hour' THEN 
        RETURN NULL;
    END IF;

    SELECT data_zakonczenia
    INTO last_date
    FROM wizyty
    WHERE lekarz = NEW.lekarz
    AND data_zakonczenia = (SELECT MAX(data_zakonczenia) FROM wizyty WHERE lekarz = NEW.lekarz);

    SELECT data_rozpoczecia
    INTO last_first_date
    FROM wizyty
    WHERE lekarz = NEW.lekarz
    AND data_zakonczenia = (SELECT MAX(data_zakonczenia) FROM wizyty WHERE lekarz = NEW.lekarz);

    IF (last_first_date, last_date) OVERLAPS (NEW.data_rozpoczecia, NEW.data_zakonczenia) THEN 
        RETURN NULL;
    END IF;
    RETURN NEW;
END;
$spojnosc$
LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER spojnosc BEFORE INSERT ON wizyty
FOR EACH ROW EXECUTE PROCEDURE spojnosc();
----
--ZAD5
CREATE TABLE lekarze_prowadzacy(
    pesel CHAR(11) NOT NULL REFERENCES pacjenci(pesel),
    lekarz INTEGER NOT NULL REFERENCES lekarze(id),

    PRIMARY KEY (pesel, lekarz)
);

CREATE OR REPLACE FUNCTION tomek()
    RETURNS TRIGGER AS
$tomek$
DECLARE
lekarz INTEGER;
BEGIN
    SELECT l.id
    INTO lekarz
    FROM lekarze l
    JOIN specjalizacje s ON l.id = s.id_lekarza
    LEFT JOIN lekarze_prowadzacy lp
    ON l.id = lp.lekarz
    WHERE s.specjalizacja = 'Medycyna rodzinna'
    GROUP BY l.id
    ORDER BY COUNT(lp.pesel), l.id
    LIMIT 1;

    INSERT INTO lekarze_prowadzacy VALUES(NEW.pesel, lekarz);

    RETURN NEW;
END;
$tomek$
LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER tomek AFTER INSERT ON pacjenci
FOR EACH ROW EXECUTE PROCEDURE tomek();
----
--ZAD6
CREATE OR REPLACE VIEW pediatrzy AS 
SELECT l.* 
FROM lekarze l
JOIN specjalizacje s
ON l.id = s.id_lekarza
WHERE s.specjalizacja = 'Pediatria';

CREATE RULE tomek AS ON INSERT TO pediatrzy DO INSTEAD (
    INSERT INTO lekarze VALUES (NEW.id, NEW.imie, NEW.nazwisko);
    INSERT INTO specjalizacje VALUES (NEW.id, 'Pediatria')
);
----
--ZAD7
CREATE OR REPLACE VIEW chirurdzy AS
SELECT l.*
FROM lekarze l
JOIN specjalizacje s
ON l.id = s.id_lekarza
WHERE s.specjalizacja = 'Chirurgia';

CREATE RULE tomek AS ON DELETE TO chirurdzy DO INSTEAD NOTHING;
----
--ZAD8
CREATE RULE ada AS ON DELETE TO lekarze 
WHERE id = ANY (SELECT id_lekarza
                  FROM specjalizacje 
                  WHERE specjalizacja = 'Chirurgia')
DO INSTEAD NOTHING;
----
--ZAD9
CREATE RULE tomasz AS ON DELETE TO pacjenci DO ALSO (
    DELETE FROM wizyty WHERE pacjent = OLD.pesel
);
----
--ZAD10
CREATE OR REPLACE VIEW terminarz AS
SELECT 
    NULL::CHAR(11) AS pacjent,
    NULL::VARCHAR(80) AS specjalista,
    NULL::TIMESTAMP AS termin_od,
    NULL::TIMESTAMP AS termin_do
WHERE false;

CREATE RULE tomek AS ON INSERT TO terminarz DO INSTEAD(
INSERT INTO wizyty (lekarz, pacjent, data_rozpoczecia, data_zakonczenia)
    SELECT 
        s.id_lekarza, 
        NEW.pacjent, 
        NEW.termin_od, 
        NEW.termin_do
    FROM specjalizacje s
    WHERE s.specjalizacja = NEW.specjalista
    AND NOT EXISTS (
        SELECT 1 
        FROM wizyty w 
        WHERE w.lekarz = s.id_lekarza 
        AND w.data_rozpoczecia < NEW.termin_do 
        AND w.data_zakonczenia > NEW.termin_od
    )
    ORDER BY s.id_lekarza
    LIMIT 1; 
);
----
15:00 
09.06.2026
