-- Zadanie: Sklep AGD


DROP TABLE IF EXISTS produkty cascade;
CREATE TABLE produkty (
    id integer PRIMARY KEY,
    cena numeric(8,2) NOT NULL,
    kolor character varying(80) NOT NULL,
    klasa_energetyczna character varying(5) NOT NULL,
    CONSTRAINT ck_cena CHECK (cena > 0)
);

DROP TABLE IF EXISTS lodowki cascade;
CREATE TABLE lodowki (
    id_produktu integer NOT NULL UNIQUE,
    pojemnosc_chlodziarki numeric(4,0) NOT NULL,
    pojemnosc_zamrazarki numeric(4,0) NOT NULL,
    bezszronowa boolean NOT NULL,
    CONSTRAINT ck_pc CHECK (pojemnosc_chlodziarki > 0),
    CONSTRAINT ck_pz CHECK (pojemnosc_zamrazarki > 0),
    CONSTRAINT fk_lodowki_produkty FOREIGN KEY (id_produktu) REFERENCES produkty
);


DROP TABLE IF EXISTS pralki cascade;
CREATE TABLE pralki (
    id_produktu integer NOT NULL UNIQUE,
    pojemnosc_znamionowa numeric(3,1) NOT NULL,
    roczne_zuzycie_wody numeric(6,0) NOT NULL,
    klasa_prania character(1) NOT NULL,
    CONSTRAINT ck_pzn CHECK (pojemnosc_znamionowa > 0),
    CONSTRAINT ck_rzw CHECK (roczne_zuzycie_wody > 0),
    CONSTRAINT ck_klasa_prania CHECK (klasa_prania IN ('A', 'B', 'C')),
    CONSTRAINT fk_pralki_produkty FOREIGN KEY (id_produktu) REFERENCES produkty
);




DROP SEQUENCE IF EXISTS produkty_id_seq cascade;
CREATE SEQUENCE produkty_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE ONLY produkty ALTER COLUMN id SET DEFAULT nextval('produkty_id_seq'::regclass);

COPY produkty (id, cena, kolor, klasa_energetyczna) FROM stdin;
1	900.00	bialy	A+
2	799.00	bialy	A+
3	1399.00	metalic	A+++
4	1899.00	srebrny	A+
5	2599.00	czarny	A++
6	999.00	srebrny	A+
\.


COPY lodowki (id_produktu, pojemnosc_chlodziarki, pojemnosc_zamrazarki, bezszronowa) FROM stdin;
4	210	98	t
5	258	112	t
6	195	116	f
\.


COPY pralki (id_produktu, pojemnosc_znamionowa, roczne_zuzycie_wody, klasa_prania) FROM stdin;
1	5.0	7400	A
2	5.0	6760	A
3	5.0	8800	A
\.




SELECT pg_catalog.setval('produkty_id_seq', 6, true);

