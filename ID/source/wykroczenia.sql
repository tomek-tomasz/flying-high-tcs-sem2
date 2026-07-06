BEGIN;

DROP TABLE IF EXISTS kierowcy;
DROP TABLE IF EXISTS wykroczenia;
DROP TABLE IF EXISTS straznicy;

CREATE TABLE kierowcy (
    id integer primary key,
    imie varchar(20) not null,
    nazwisko varchar(30) not null,
    pesel char(11) not null,    
    adres varchar(50) not null,
    data_od date not null,
    data_do date
);

CREATE TABLE wykroczenia (
    id integer primary key,
    nazwa varchar(100) not null,
    punkty integer,
    kwota integer not null,
    recydywa bool
);

CREATE TABLE straznicy (
    id integer primary key,
    imie varchar(20) not null,
    nazwisko varchar(30) not null,
    pesel char(11) not null,
    wynagrodzenie numeric(7, 2) not null,
    premia numeric(6, 2),
    stanowisko varchar(30) not null,
    id_przelozonego integer references straznicy(id)
); 


INSERT INTO kierowcy VALUES
    (1, 'Jan', 'Woźniak', '55080785617', 'ul. Złota 18, Grudziądz', to_date('01-09-1977','DD-MM-YYYY'), to_date('31-08-1987','DD-MM-YYYY') ),
    (2, 'Ewa', 'Stonka', '89060792443', 'ul. Kubusia Puchatka 13/2, Radom', to_date('23-02-2007','DD-MM-YYYY'), NULL),
    (3, 'Anna', 'Trzebyczek', '98071374467', 'al. Niepodległości 18/3, Nowy Targ', to_date('15-01-2022','DD-MM-YYYY'), to_date('14-01-2029','DD-MM-YYYY')),
    (4, 'Marek', 'Kowalski', '77082798859', 'ul. Złota 18, Grudziądz', to_date('08-10-1995','DD-MM-YYYY'), NULL),
    (5, 'Piotr', 'Stary', '52122565413', 'ul. Wesoła 12a/15, Radom', to_date('05-03-1993','DD-MM-YYYY'), to_date('04-03-2003','DD-MM-YYYY')),
    (6, 'Piotr', 'Boruta', '82111689332', 'ul. Górna 163, Nowy Targ', to_date('30-05-2003','DD-MM-YYYY'), to_date('17-09-2023','DD-MM-YYYY')),
    (7, 'Olga', 'Woźniak', '59081763449', 'ul. Sosnowa 17, Grudziądz', to_date('28-02-1987','DD-MM-YYYY'), to_date('02-11-1989','DD-MM-YYYY')),
    (8, 'Iga', 'Nowak', '94102439327', 'ul. Miła 14/167, Radom', to_date('05-01-2024','DD-MM-YYYY'), NULL),
    (9, 'Barbara', 'Paderewska', '52041264626', 'Ryczów 189', to_date('19-05-1977','DD-MM-YYYY'), to_date('16-11-2028','DD-MM-YYYY')),
    (10, 'Łukasz', 'Malec', '49102228596', 'ul. Niespójna 32, Radom', to_date('28-04-1976','DD-MM-YYYY'), to_date('01-09-1977','DD-MM-YYYY')),
    (11, 'Joanna', 'Nieskora', '46100156788', 'ul. Projektowana 1/24, Grudziądz', to_date('04-05-1965','DD-MM-YYYY'), to_date('01-12-1998','DD-MM-YYYY')),
    (12, 'Edmund', 'Wiśniewski', '79070186758', 'Ryczów 14' ,to_date('01-04-2004','DD-MM-YYYY'), to_date('02-04-2004','DD-MM-YYYY')),
    (13, 'Inka', 'Gabriel', '97092831584', 'ul. Ziarnista 27, Nowy Targ', to_date('13-12-2015','DD-MM-YYYY'), to_date('01-09-2030','DD-MM-YYYY')),
    (14, 'Ewa', 'Żebrowska', '61052425966', 'ul. Wesoła 12b/15, Radom', to_date('22-09-1987','DD-MM-YYYY'), to_date('01-09-2026','DD-MM-YYYY')),
    (15, 'Iga', 'Nowak', '77101635963', 'ul. Polna 14, Grudziądz', to_date('14-07-2020','DD-MM-YYYY'), NULL);


INSERT INTO wykroczenia VALUES
    (100, 'Przekroczenie prędkości do 10 km/h', 1, 50, false),
    (110, 'Przekroczenie prędkości o 11-15 km/h', 2, 100, false),
    (120, 'Przekroczenie prędkości o 16-20 km/h', 3, 200, false),
    (130, 'Przekroczenie prędkości o 21-25 km/h', 5, 300, false),
    (140, 'Przekroczenie prędkości o 26-30 km/h', 7, 400, false),
    (150, 'Przekroczenie prędkości o 31-40 km/h', 9, 800, true),
    (160, 'Przekroczenie prędkości o 41-50 km/h', 11, 1000, true),
    (170, 'Przekroczenie prędkości o 51-60 km/h', 13, 1500, true),
    (180, 'Przekroczenie prędkości o 61-70 km/h', 14, 2000, true),
    (190, 'Przekroczenie prędkości o ponad 70 km/h', 15, 2500, true),
    (200, 'Używanie łańcuchów przeciwślizgowych na oponach na drodze niepokrytej śniegiem', NULL, 100, false),
    (210, 'Kierowanie pojazdem nie mając przy sobie wymaganych dokumentów', NULL, 250, false),
    (220, 'Korzystanie przez pieszego z telefonu podczas wchodzenia i przechodzenia przez jezdnię ', NULL, 300, false),
    (230, 'Rozdzielenie kolumny pieszych', NULL, 200, false),
    (240, 'Nieustąpienie pierwszeństwa pieszemu przez kierującego pojazdem podczas włączania się do ruchu', 8, 1500, true),
    (250, 'Naruszenie zakazów cofania w tunelach, na mostach i wiaduktach', 6, 200, false),
    (260, 'Zwiększanie prędkości przez kierującego pojazdem wyprzedzanym', 3, 350, false),
    (270, 'Naruszenie zakazu korzystania podczas jazdy z telefonu wymagającego trzymania słuchawki', 12, 500, false),
    (280, 'Chodzenie po torowisku', NULL, 50, false);


INSERT INTO straznicy VALUES
    (51, 'Józef', 'Balcerek', '72011473412', 4000, 300, 'Aplikant', 54),
    (52, 'Edward', 'Janik', '98071747872', 3900, NULL, 'Aplikant', 54),
    (53, 'Arletta', 'Pasek', '98082527766', 4830, NULL, 'Młodszy strażnik', 56),
    (54, 'Olaf', 'Budka', '02261088854', 5100, 500, 'Strażnik', 56),
    (55, 'Łukasz', 'Malec', '87121969432', 4900, 700, 'Strażnik', 56),
    (56, 'Beata', 'Okrawek', '87030851747', 7500, 1000, 'Kierownik', 57),
    (57, 'Elżbieta', 'Pączek', '68052573484', 8400, NULL, 'Zastępca naczelnika', 58),
    (58, 'Mateusz', 'Kucaj', '69092973995', 9300, 1200, 'Naczelnik', 59),
    (59, 'Ewa', 'Spalska', '58092185783', 18400, NULL, 'Komendant', NULL),
    (60, 'Olga', 'Woźniak', '59081763449', 5300, NULL, 'Strażnik', 56),
    (61, 'Zygmunt', 'Pasterski', '71061631656', 19400, 2000, 'Komendant', NULL),
    (62, 'Ewelina', 'Łuczak', '01321711369', 5100, NULL, 'Młodszy strażnik', 56),
    (63, 'Piotr', 'Boruta', '82111689332', 7800, 1200, 'Kierownik', 57);

COMMIT;
