--ZAD1
CREATE SEQUENCE seq START 10 INCREMENT BY 1;    
----
--ZAD2
INSERT INTO klienci 
VALUES 
    (nextval('seq'),
    'Anna',
    'Kowalska'),
    (nextval('seq'),
    'Jan',
    'Kowalski')
;
----
--ZAD3
CREATE UNIQUE INDEX
ON transakcje (z_konta, na_konto, data_zlecenia); 
----
--ZAD4
CREATE OR REPLACE VIEW wplaty_wyplaty AS (
SELECT 
nr_konta "Konto",
(
    SELECT COUNT(*)
    FROM transakcje
    WHERE z_konta = k.nr_konta
) "ilosc_wyplat",
(
    SELECT COUNT(*)
    FROM transakcje
    WHERE na_konto = k.nr_konta
) "ilosc_wplat"
FROM konta k
)
----
--ZAD5
CREATE OR REPLACE VIEW wplaty_wyplaty AS (
SELECT 
nr_konta "Konto",
(
    SELECT COUNT(*)
    FROM transakcje
    WHERE z_konta = k.nr_konta
) "ilosc_wyplat",
(
    SELECT COUNT(*)
    FROM transakcje
    WHERE na_konto = k.nr_konta
) "ilosc_wplat"
FROM konta k
);


SELECT * FROM wplaty_wyplaty;

INSERT INTO transakcje (id, na_konto, kwota)  VALUES(200, 1004, 500.00);


SELECT * FROM wplaty_wyplaty;

DROP VIEW wplaty_wyplaty;
----
--ZAD6
CREATE OR REPLACE FUNCTION  oblicz_koszt(a NUMERIC(11,2))
    RETURNS NUMERIC(11,2) AS
$$
BEGIN
    RETURN ROUND(2 * a / 100,2);
END;
$$
LANGUAGE plpgsql;

--ZAD7
CREATE OR REPLACE FUNCTION  oblicz_koszt(a NUMERIC(11,2))
    RETURNS NUMERIC(11,2) AS
$$
BEGIN
    RETURN ROUND(2 * a / 100,2);
END;
$$
LANGUAGE plpgsql;

SELECT oblicz_koszt(kwota)
FROM transakcje;
----
--ZAD8
CREATE OR REPLACE FUNCTION  bilans_kont()
    RETURNS TABLE(konto numeric(11),
     suma_wplat numeric(11,2),
      suma_wyplat numeric(11,2)) AS
$$
BEGIN
    RETURN QUERY
    SELECT nr_konta,
        (SELECT COALESCE(SUM(kwota), 0) FROM transakcje WHERE na_konto = k.nr_konta),
        (SELECT COALESCE(SUM(kwota), 0) FROM transakcje WHERE z_konta = k.nr_konta)
    FROM konta k;
END;
$$
LANGUAGE plpgsql;
----
--ZAD9

CREATE OR REPLACE FUNCTION  bilans_kont()
    RETURNS TABLE(konto numeric(11),
     suma_wplat numeric(11,2),
      suma_wyplat numeric(11,2)) AS
$$
BEGIN
    RETURN QUERY
    SELECT nr_konta,
        (SELECT COALESCE(SUM(kwota), 0) FROM transakcje WHERE na_konto = k.nr_konta),
        (SELECT COALESCE(SUM(kwota), 0) FROM transakcje WHERE z_konta = k.nr_konta)
    FROM konta k;
END;
$$
LANGUAGE plpgsql;

SELECT konto, suma_wplat - suma_wyplat bilans
FROM bilans_kont();
----
--ZAD10A
CREATE OR REPLACE FUNCTION  silnia(n NUMERIC)
    RETURNS NUMERIC AS
$$
DECLARE 
    m NUMERIC;
    result NUMERIC;
BEGIN
    result = 1;
    m = 0;
    WHILE m != n LOOP
        m = m + 1;
        result = result * m;
    END LOOP;
    RETURN result;
END;
$$
LANGUAGE plpgsql;
----
--ZAD10B
CREATE OR REPLACE FUNCTION  silnia(n NUMERIC)
    RETURNS NUMERIC AS
$$
BEGIN
    IF n = 0 THEN
        RETURN 1;
    ELSE
        RETURN n*silnia(n - 1);
    END IF;
END;
$$
LANGUAGE plpgsql;
----
--ZAD11

CREATE SEQUENCE seq START 1000 INCREMENT BY 10 MAXVALUE 5000;


CREATE OR REPLACE FUNCTION  bilans_kont()
    RETURNS TABLE(konto numeric(11),
     suma_wplat numeric(11,2),
      suma_wyplat numeric(11,2)) AS
$$
BEGIN
    RETURN QUERY
    SELECT nr_konta,
        (SELECT COALESCE(SUM(kwota), 0) FROM transakcje WHERE na_konto = k.nr_konta),
        (SELECT COALESCE(SUM(kwota), 0) FROM transakcje WHERE z_konta = k.nr_konta)
    FROM konta k;
END;
$$
LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION  bonus_swiateczny(p NUMERIC DEFAULT 0.01)
    RETURNS VOID AS
$$
BEGIN
    INSERT INTO transakcje (id, na_konto, kwota) (
        SELECT nextval('seq'), konto, p*suma_wyplat
        FROM bilans_kont()
    );
END;
$$
LANGUAGE plpgsql;

----
--ZAD12
CREATE OR REPLACE FUNCTION stan_konta(konto NUMERIC(11), czas TIMESTAMP)
    RETURNS NUMERIC(11,2) AS
$$
DECLARE
    negative_moments int;
BEGIN
    negative_moments = (SELECT COUNT(*)
                        FROM transakcje
                        WHERE (na_konto = konto OR z_konta = konto)
                        AND data_zlecenia < czas
                        AND stan_konta(konto, data_zlecenia) < 0);
    IF negative_moments > 0 THEN
        RAISE EXCEPTION 'Wykryto ujemny bilans konta';
    END IF;
    RETURN 
    (
        SELECT
            COALESCE(SUM(kwota), 0)
        FROM transakcje
        WHERE na_konto = konto
        AND data_zlecenia <= czas
    ) -
    (
        SELECT
            COALESCE(SUM(kwota), 0)
        FROM transakcje
        WHERE z_konta = konto
        AND data_zlecenia <= czas
    );
END;
$$
LANGUAGE plpgsql;
----
--ZAD13
CREATE OR REPLACE FUNCTION stan_konta(konto NUMERIC(11), czas TIMESTAMP)
    RETURNS NUMERIC(11,2) AS
$$
DECLARE
    negative_moments int;
BEGIN
    negative_moments = (SELECT COUNT(*)
                        FROM transakcje
                        WHERE (na_konto = konto OR z_konta = konto)
                        AND data_zlecenia < czas
                        AND stan_konta(konto, data_zlecenia) < 0);
    IF negative_moments > 0 THEN
        RAISE EXCEPTION 'Wykryto ujemny bilans konta';
    END IF;
    RETURN 
    (
        SELECT
            COALESCE(SUM(kwota), 0)
        FROM transakcje
        WHERE na_konto = konto
        AND data_zlecenia <= czas
    ) -
    (
        SELECT
            COALESCE(SUM(kwota), 0)
        FROM transakcje
        WHERE z_konta = konto
        AND data_zlecenia <= czas
    );
END;
$$
LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION historia_konta(konto NUMERIC(11))
    RETURNS TABLE(
        data TIMESTAMP,
        stan NUMERIC(11,2)) AS
$$
BEGIN
    RETURN QUERY
    SELECT data_zlecenia, stan_konta(konto, data_zlecenia)
    FROM transakcje
    WHERE na_konto = konto OR z_konta = konto
    ORDER BY data_zlecenia;

END;
$$
LANGUAGE plpgsql;
----
--ZAD14

CREATE OR REPLACE FUNCTION stan_konta(konto NUMERIC(11), czas TIMESTAMP)
    RETURNS NUMERIC(11,2) AS
$$
BEGIN
    RETURN 
    (
        SELECT
            COALESCE(SUM(kwota), 0)
        FROM transakcje
        WHERE na_konto = konto
        AND data_zlecenia <= czas
    ) -
    (
        SELECT
            COALESCE(SUM(kwota), 0)
        FROM transakcje
        WHERE z_konta = konto
        AND data_zlecenia <= czas
    );
END;
$$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION moment_rozspojniajacy()
    RETURNS TIMESTAMP AS
$$
DECLARE 
    negative_moments int;
BEGIN
    negative_moments = (
        SELECT COUNT(*)
        FROM transakcje
        WHERE stan_konta(z_konta, data_zlecenia) < 0
        OR    stan_konta(na_konto, data_zlecenia) < 0);
    IF negative_moments = 0 THEN
        RETURN NULL;
    END IF;
    RETURN (
        SELECT data_zlecenia
        FROM transakcje
        WHERE stan_konta(z_konta, data_zlecenia) < 0
        OR    stan_konta(na_konto, data_zlecenia) < 0
        ORDER BY data_zlecenia
        LIMIT 1
    );
END;
$$
LANGUAGE plpgsql;
----