--ZAD1
CREATE TABLE zwierzeta (
    gatunek VARCHAR(100) NOT NULL,
    jajorodny CHAR(1) NOT NULL CHECK(jajorodny = 'T' OR jajorodny = 'N'),
    liczba_konczyn NUMERIC(2,0) CHECK(liczba_konczyn>0) NOT NULL,
    data_odkrycia DATE NOT NULL
)
----
--ZAD2
CREATE TABLE klienci (
    pesel CHAR(11) PRIMARY KEY,
    adres VARCHAR(100),
    wiek NUMERIC(2,0) NOT NULL,
    wspolpraca_od DATE NOT NULL
)
----
--ZAD3
CREATE TABLE uczelnie (
    id_uczelni NUMERIC(4,0),
    nazwa VARCHAR(100),
    adres VARCHAR(100),
    budzet NUMERIC(10,2) NOT NULL,
    zalozona DATE NOT NULL,
    PRIMARY KEY (id_uczelni),
    UNIQUE (nazwa)
)
----
--ZAD4
CREATE TABLE ksiazki (
    id_ksiazki NUMERIC(10,0) PRIMARY KEY,
    tytul VARCHAR(100) NOT NULL,
    autorzy VARCHAR(100),
    cena NUMERIC(6,2),
    data_wydania DATE
)
----
--ZAD5
CREATE TABLE pokoje (
    numer_pokoju NUMERIC(3,0),
    id_zesp NUMERIC(2,0) REFERENCES zespoly,
    liczba_okien NUMERIC(1,0),
    PRIMARY KEY (numer_pokoju)
)
----
--ZAD6
CREATE TABLE plyty_cd (
    kompozytor CHAR(100) NOT NULL,
    tytul_albumu CHAR(100) NOT NULL,
    data_nagrania DATE,
    data_wydania DATE,
    czas_trwania INTERVAL CHECK(EXTRACT(EPOCH FROM czas_trwania)<82*60),

    CHECK(data_wydania>data_nagrania),
    CONSTRAINT un_ko_ty UNIQUE(kompozytor, tytul_albumu)
)
----
--ZAD7
CREATE TABLE szef_podwladny AS (
SELECT (
    SELECT nazwisko 
    FROM pracownicy 
    WHERE p.id_szefa = id_prac
) "szef", 
nazwisko "podwladny"
FROM pracownicy p
WHERE id_szefa IS NOT NULL
)
----
--ZAD8
CREATE TABLE plyty_cd (
    kompozytor CHAR(100) NOT NULL,
    tytul_albumu CHAR(100) NOT NULL,
    data_nagrania DATE,
    data_wydania DATE,
    czas_trwania INTERVAL CHECK(EXTRACT(EPOCH FROM czas_trwania)<82*60),

    CHECK(data_wydania>data_nagrania),
    CONSTRAINT un_ko_ty UNIQUE(kompozytor, tytul_albumu)
);

ALTER TABLE plyty_cd DROP CONSTRAINT un_ko_ty;
ALTER TABLE plyty_cd ADD CONSTRAINT un_ko_ty PRIMARY KEY(kompozytor, tytul_albumu);
----
--ZAD9
CREATE TABLE plyty_cd (
    kompozytor CHAR(100) NOT NULL,
    tytul_albumu CHAR(100) NOT NULL,
    data_nagrania DATE,
    data_wydania DATE,
    czas_trwania INTERVAL CHECK(EXTRACT(EPOCH FROM czas_trwania)<82*60),

    CHECK(data_wydania>data_nagrania),
    CONSTRAINT un_ko_ty UNIQUE(kompozytor, tytul_albumu)
);
ALTER TABLE plyty_cd DROP CONSTRAINT un_ko_ty;
INSERT INTO plyty_cd VALUES(
    'a', 'b'
);
INSERT INTO plyty_cd VALUES(
    'a', 'b'
);
ALTER TABLE plyty_cd ADD CONSTRAINT un_ko_ty PRIMARY KEY(kompozytor, tytul_albumu);
----
--ZAD10
CREATE TABLE zwierzeta (
    gatunek VARCHAR(100) NOT NULL,
    jajorodny CHAR(1) NOT NULL CHECK(jajorodny = 'T' OR jajorodny = 'N'),
    liczba_konczyn NUMERIC(2,0) CHECK(liczba_konczyn>0) NOT NULL,
    data_odkrycia DATE NOT NULL
);

ALTER TABLE zwierzeta RENAME TO gatunki;
DROP TABLE gatunki;
----
--ZAD11
CREATE TABLE projekty (
    id_projektu NUMERIC(4,0) PRIMARY KEY,
    opis_projektu CHAR(20) NOT NULL UNIQUE,
    data_rozpoczecia DATE DEFAULT NOW(),
    data_zakonczenia DATE CHECK(data_zakonczenia>data_rozpoczecia),
    fundusz NUMERIC(7,2)
)
----
--ZAD12
CREATE TABLE projekty (
    id_projektu NUMERIC(4,0) PRIMARY KEY,
    opis_projektu CHAR(20) NOT NULL UNIQUE,
    data_rozpoczecia DATE DEFAULT NOW(),
    data_zakonczenia DATE CHECK(data_zakonczenia>data_rozpoczecia),
    fundusz NUMERIC(7,2)
);

CREATE TABLE przydzialy (
    id_projektu NUMERIC(4,0) REFERENCES projekty(id_projektu),
    id_prac NUMERIC(4,0) REFERENCES pracownicy(id_prac),
    od DATE DEFAULT NOW(),
    "do" DATE CHECK("do">od),
    stawka NUMERIC(7,2),
    rola CHAR(20) CHECK(rola = 'KIERUJACY' OR rola = 'ANALITYK' OR rola = 'PROGRAMISTA'),

    PRIMARY KEY (id_projektu, id_prac)
)
----
--ZAD13
CREATE TABLE projekty (
    id_projektu NUMERIC(4,0) PRIMARY KEY,
    opis_projektu CHAR(20) NOT NULL UNIQUE,
    data_rozpoczecia DATE DEFAULT NOW(),
    data_zakonczenia DATE CHECK(data_zakonczenia>data_rozpoczecia),
    fundusz NUMERIC(7,2)
);

CREATE TABLE przydzialy (
    id_projektu NUMERIC(4,0) REFERENCES projekty(id_projektu),
    id_prac NUMERIC(4,0) REFERENCES pracownicy(id_prac),
    od DATE DEFAULT NOW(),
    "do" DATE CHECK("do">od),
    stawka NUMERIC(7,2),
    rola CHAR(20) CHECK(rola = 'KIERUJACY' OR rola = 'ANALITYK' OR rola = 'PROGRAMISTA'),

    PRIMARY KEY (id_projektu, id_prac)
);

ALTER TABLE przydzialy ADD godziny NUMERIC;
----
--ZAD15
CREATE TABLE projekty (
    id_projektu NUMERIC(4,0) PRIMARY KEY,
    opis_projektu CHAR(20) NOT NULL UNIQUE,
    data_rozpoczecia DATE DEFAULT NOW(),
    data_zakonczenia DATE CHECK(data_zakonczenia>data_rozpoczecia),
    fundusz NUMERIC(7,2)
);

ALTER TABLE projekty ALTER COLUMN opis_projektu TYPE CHAR(30);
----
--ZAD17
ALTER TABLE pracownicy DROP COLUMN imie;
----
--ZAD18
CREATE TABLE pracownicy_zespoly AS(
SELECT
p.nazwisko,
p.etat,
12*p.placa_pod roczna_placa,
z.nazwa zespol,
z.adres adres_pracy
FROM pracownicy p
JOIN zespoly z ON p.id_zesp = z.id_zesp
)

----

