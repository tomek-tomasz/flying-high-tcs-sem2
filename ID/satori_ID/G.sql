--ZAD1
CREATE TABLE kategorie (
    id_kategoria SERIAL PRIMARY KEY,
    nazwa VARCHAR(250) NOT NULL UNIQUE,
    vat NUMERIC(3,1) NOT NULL
);

INSERT INTO kategorie (nazwa, vat)
SELECT DISTINCT kategoria, vat
FROM produkty;

ALTER TABLE produkty ADD COLUMN id_kategoria INTEGER;

UPDATE produkty p SET id_kategoria = (
    SELECT id_kategoria 
    FROM kategorie
    WHERE p.kategoria = nazwa
);

ALTER TABLE produkty DROP COLUMN kategoria;
ALTER TABLE produkty DROP COLUMN vat;


ALTER TABLE produkty
ADD CONSTRAINT fk
FOREIGN KEY (id_kategoria)
REFERENCES kategorie (id_kategoria);

ALTER TABLE produkty ALTER COLUMN id_kategoria SET NOT NULL;
----
SELECT * FROM zamowienia
--ZAD2
DROP TABLE IF EXISTS historia_cen;

SELECT kod_produktu, cena_netto,  date('2000-01-01') data_wprowadzenia
INTO historia_cen
FROM produkty;

ALTER TABLE historia_cen ADD PRIMARY KEY (kod_produktu, data_wprowadzenia);
ALTER TABLE historia_cen ALTER COLUMN cena_netto SET NOT NULL;

ALTER TABLE produkty DROP COLUMN cena_netto;

ALTER TABLE historia_cen
ADD CONSTRAINT fk
FOREIGN KEY (kod_produktu)
REFERENCES produkty (kod_produktu);
----
--ZAD3
ALTER TABLE zamowienia ALTER COLUMN id_klienta DROP NOT NULL;

ALTER TABLE zamowienia 
DROP CONSTRAINT fk_zam_kli, 
ADD CONSTRAINT fk_zam_kli 
    FOREIGN KEY (id_klienta) 
    REFERENCES klienci(id_klienta) 
    ON DELETE SET NULL;
ALTER TABLE rabaty_klientow 
DROP CONSTRAINT fk_zam_kli,
ADD CONSTRAINT fk_zam_kli 
    FOREIGN KEY (id_klienta) 
    REFERENCES klienci(id_klienta) 
    ON DELETE CASCADE;
ALTER TABLE rabaty_klientow 
DROP CONSTRAINT fk_zam_pol,
ADD CONSTRAINT fk_zam_pol 
    FOREIGN KEY (id_polecajacego) 
    REFERENCES klienci(id_klienta) 
    ON DELETE CASCADE;



DELETE FROM klienci;

DROP TABLE klienci CASCADE;
----
--ZAD4
ALTER TABLE etaty ADD COLUMN pensja_od numeric(8,2);

ALTER TABLE etaty ADD COLUMN pensja_do numeric(8,2);

UPDATE etaty
SET pensja_od = LEAST(widelki[1], widelki[2]),
    pensja_do = GREATEST(widelki[1], widelki[2])
;

ALTER TABLE etaty ALTER COLUMN pensja_od SET NOT NULL;
ALTER TABLE etaty ALTER COLUMN pensja_do SET NOT NULL;

ALTER TABLE etaty DROP COLUMN widelki;
ALTER TABLE etaty ADD CONSTRAINT min_max CHECK(pensja_od < pensja_do);
----
--ZAD5
ALTER TABLE etaty ADD COLUMN pensja_od numeric(8,2);

ALTER TABLE etaty ADD COLUMN pensja_do numeric(8,2);

UPDATE etaty
SET pensja_od = LEAST(widelki[1], widelki[2]),
    pensja_do = GREATEST(widelki[1], widelki[2])
;

ALTER TABLE etaty ALTER COLUMN pensja_od SET NOT NULL;
ALTER TABLE etaty ALTER COLUMN pensja_do SET NOT NULL;

ALTER TABLE etaty DROP COLUMN widelki;
ALTER TABLE etaty ADD CONSTRAINT min_max CHECK(pensja_od < pensja_do);

UPDATE pracownicy p
SET pensja = (SELECT pensja_od FROM etaty e WHERE e.etat = p.etat)
WHERE pensja < (SELECT pensja_od FROM etaty e WHERE e.etat = p.etat);
----
--ZAD6
ALTER TABLE etaty ADD COLUMN pensja_od numeric(8,2);

ALTER TABLE etaty ADD COLUMN pensja_do numeric(8,2);

UPDATE etaty
SET pensja_od = LEAST(widelki[1], widelki[2]),
    pensja_do = GREATEST(widelki[1], widelki[2])
;

ALTER TABLE etaty ALTER COLUMN pensja_od SET NOT NULL;
ALTER TABLE etaty ALTER COLUMN pensja_do SET NOT NULL;

ALTER TABLE etaty DROP COLUMN widelki;
ALTER TABLE etaty ADD CONSTRAINT min_max CHECK(pensja_od < pensja_do);

UPDATE pracownicy p
SET pensja = (SELECT pensja_od FROM etaty e WHERE e.etat = p.etat)
WHERE pensja < (SELECT pensja_od FROM etaty e WHERE e.etat = p.etat);

INSERT INTO etaty(
SELECT CONCAT(e.etat, ' starszy') etat, pensja_od, 2 * pensja_do pensja_do
FROM etaty e
);

UPDATE pracownicy p
SET etat = CONCAT(etat, ' starszy')
WHERE pensja > (SELECT pensja_do FROM etaty e WHERE e.etat = p.etat);
----
--ZAD7
ALTER TABLE etaty ADD COLUMN pensja_od numeric(8,2);

ALTER TABLE etaty ADD COLUMN pensja_do numeric(8,2);

UPDATE etaty
SET pensja_od = LEAST(widelki[1], widelki[2]),
    pensja_do = GREATEST(widelki[1], widelki[2])
;

ALTER TABLE etaty ALTER COLUMN pensja_od SET NOT NULL;
ALTER TABLE etaty ALTER COLUMN pensja_do SET NOT NULL;

ALTER TABLE etaty DROP COLUMN widelki;
ALTER TABLE etaty ADD CONSTRAINT min_max CHECK(pensja_od < pensja_do);

UPDATE pracownicy p
SET pensja = (SELECT pensja_od FROM etaty e WHERE e.etat = p.etat)
WHERE pensja < (SELECT pensja_od FROM etaty e WHERE e.etat = p.etat);

INSERT INTO etaty(
SELECT CONCAT(e.etat, ' starszy') etat, pensja_od, 2 * pensja_do pensja_do
FROM etaty e
);

UPDATE pracownicy p
SET etat = CONCAT(etat, ' starszy')
WHERE pensja > (SELECT pensja_do FROM etaty e WHERE e.etat = p.etat);

ALTER TABLE etaty ADD COLUMN id_etatu int;

CREATE TEMP SEQUENCE seq START 10 INCREMENT BY 10;   
UPDATE etaty SET id_etatu = nextval('seq');
DROP SEQUENCE seq;

ALTER TABLE etaty ALTER COLUMN id_etatu SET NOT NULL;

ALTER TABLE pracownicy DROP CONSTRAINT pracownicy_etat_fkey;
ALTER TABLE etaty DROP CONSTRAINT etaty_pkey;

ALTER TABLE etaty ADD PRIMARY KEY (id_etatu);

ALTER TABLE pracownicy ADD COLUMN etat_tmp int;

UPDATE pracownicy p
SET etat_tmp = (SELECT id_etatu FROM etaty e WHERE e.etat = p.etat);

ALTER TABLE pracownicy DROP COLUMN etat;
ALTER TABLE pracownicy RENAME COLUMN etat_tmp TO etat;
ALTER TABLE pracownicy ALTER COLUMN etat SET NOT NULL;

ALTER TABLE pracownicy ADD CONSTRAINT pracownicy_etat_fkey 
    FOREIGN KEY (etat) REFERENCES etaty(id_etatu);

----
--ZAD8
ALTER TABLE etaty ADD COLUMN pensja_od numeric(8,2);

ALTER TABLE etaty ADD COLUMN pensja_do numeric(8,2);

UPDATE etaty
SET pensja_od = LEAST(widelki[1], widelki[2]),
    pensja_do = GREATEST(widelki[1], widelki[2])
;

ALTER TABLE etaty ALTER COLUMN pensja_od SET NOT NULL;
ALTER TABLE etaty ALTER COLUMN pensja_do SET NOT NULL;

ALTER TABLE etaty DROP COLUMN widelki;
ALTER TABLE etaty ADD CONSTRAINT min_max CHECK(pensja_od < pensja_do);

UPDATE pracownicy p
SET pensja = (SELECT pensja_od FROM etaty e WHERE e.etat = p.etat)
WHERE pensja < (SELECT pensja_od FROM etaty e WHERE e.etat = p.etat);

INSERT INTO etaty(
SELECT CONCAT(e.etat, ' starszy') etat, pensja_od, 2 * pensja_do pensja_do
FROM etaty e
);

UPDATE pracownicy p
SET etat = CONCAT(etat, ' starszy')
WHERE pensja > (SELECT pensja_do FROM etaty e WHERE e.etat = p.etat);

ALTER TABLE etaty ADD COLUMN id_etatu int;

CREATE TEMP SEQUENCE seq START 10 INCREMENT BY 10;   
UPDATE etaty SET id_etatu = nextval('seq');
DROP SEQUENCE seq;

ALTER TABLE etaty ALTER COLUMN id_etatu SET NOT NULL;

ALTER TABLE pracownicy DROP CONSTRAINT pracownicy_etat_fkey;
ALTER TABLE etaty DROP CONSTRAINT etaty_pkey;

ALTER TABLE etaty ADD PRIMARY KEY (id_etatu);

ALTER TABLE pracownicy ADD COLUMN etat_tmp int;

UPDATE pracownicy p
SET etat_tmp = (SELECT id_etatu FROM etaty e WHERE e.etat = p.etat);

ALTER TABLE pracownicy DROP COLUMN etat;
ALTER TABLE pracownicy RENAME COLUMN etat_tmp TO etat;
ALTER TABLE pracownicy ALTER COLUMN etat SET NOT NULL;

ALTER TABLE pracownicy ADD CONSTRAINT pracownicy_etat_fkey 
    FOREIGN KEY (etat) REFERENCES etaty(id_etatu);


ALTER TABLE pracownicy ADD COLUMN dodatki NUMERIC(8,2);

UPDATE pracownicy p
SET dodatki = (SELECT p.pensja - e.pensja_do FROM etaty e WHERE e.id_etatu = p.etat)
WHERE p.pensja > (SELECT e.pensja_do FROM etaty e WHERE e.id_etatu = p.etat);


UPDATE pracownicy p
SET pensja = (SELECT e.pensja_do FROM etaty e WHERE e.id_etatu = p.etat)
WHERE pensja > (SELECT e.pensja_do FROM etaty e WHERE e.id_etatu = p.etat);
----
--ZAD9
ALTER TABLE etaty ADD COLUMN pensja_od numeric(8,2);

ALTER TABLE etaty ADD COLUMN pensja_do numeric(8,2);

UPDATE etaty
SET pensja_od = LEAST(widelki[1], widelki[2]),
    pensja_do = GREATEST(widelki[1], widelki[2])
;

ALTER TABLE etaty ALTER COLUMN pensja_od SET NOT NULL;
ALTER TABLE etaty ALTER COLUMN pensja_do SET NOT NULL;

ALTER TABLE etaty DROP COLUMN widelki;
ALTER TABLE etaty ADD CONSTRAINT min_max CHECK(pensja_od < pensja_do);

UPDATE pracownicy p
SET pensja = (SELECT pensja_od FROM etaty e WHERE e.etat = p.etat)
WHERE pensja < (SELECT pensja_od FROM etaty e WHERE e.etat = p.etat);

INSERT INTO etaty(
SELECT CONCAT(e.etat, ' starszy') etat, pensja_od, 2 * pensja_do pensja_do
FROM etaty e
);

UPDATE pracownicy p
SET etat = CONCAT(etat, ' starszy')
WHERE pensja > (SELECT pensja_do FROM etaty e WHERE e.etat = p.etat);

ALTER TABLE etaty ADD COLUMN id_etatu int;

CREATE TEMP SEQUENCE seq START 10 INCREMENT BY 10;   
UPDATE etaty SET id_etatu = nextval('seq');
DROP SEQUENCE seq;

ALTER TABLE etaty ALTER COLUMN id_etatu SET NOT NULL;

ALTER TABLE pracownicy DROP CONSTRAINT pracownicy_etat_fkey;
ALTER TABLE etaty DROP CONSTRAINT etaty_pkey;

ALTER TABLE etaty ADD PRIMARY KEY (id_etatu);

ALTER TABLE pracownicy ADD COLUMN etat_tmp int;

UPDATE pracownicy p
SET etat_tmp = (SELECT id_etatu FROM etaty e WHERE e.etat = p.etat);

ALTER TABLE pracownicy DROP COLUMN etat;
ALTER TABLE pracownicy RENAME COLUMN etat_tmp TO etat;
ALTER TABLE pracownicy ALTER COLUMN etat SET NOT NULL;

ALTER TABLE pracownicy ADD CONSTRAINT pracownicy_etat_fkey 
    FOREIGN KEY (etat) REFERENCES etaty(id_etatu);


ALTER TABLE pracownicy ADD COLUMN dodatki NUMERIC(8,2);

UPDATE pracownicy p
SET dodatki = (SELECT p.pensja - e.pensja_do FROM etaty e WHERE e.id_etatu = p.etat)
WHERE p.pensja > (SELECT e.pensja_do FROM etaty e WHERE e.id_etatu = p.etat);


UPDATE pracownicy p
SET pensja = (SELECT e.pensja_do FROM etaty e WHERE e.id_etatu = p.etat)
WHERE pensja > (SELECT e.pensja_do FROM etaty e WHERE e.id_etatu = p.etat);


SELECT 
    p.imie, 
    p.nazwisko, 
    e.etat
FROM pracownicy p
JOIN etaty e 
    ON (p.pensja + COALESCE(p.dodatki, 0)) BETWEEN e.pensja_od AND e.pensja_do
WHERE e.pensja_do = (
    SELECT MAX(e2.pensja_do)
    FROM etaty e2
    WHERE (p.pensja + COALESCE(p.dodatki, 0)) BETWEEN e2.pensja_od AND e2.pensja_do
);
----