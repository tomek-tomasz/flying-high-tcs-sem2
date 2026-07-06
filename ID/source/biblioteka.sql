BEGIN;


DROP TABLE IF EXISTS wypozyczenia CASCADE;
DROP TABLE IF EXISTS egzemplarze CASCADE;
DROP TABLE IF EXISTS ksiazki CASCADE;
DROP TABLE IF EXISTS czytelnicy CASCADE;
DROP TABLE IF EXISTS kategorie CASCADE;
DROP TABLE IF EXISTS czytelnik_zainteresowania CASCADE;


CREATE TABLE kategorie (
    id_kategorii SERIAL PRIMARY KEY,
    nazwa VARCHAR(50) NOT NULL
);

CREATE TABLE czytelnicy (
    id_czytelnika SERIAL PRIMARY KEY,
    nazwisko VARCHAR(50) NOT NULL,
    imie VARCHAR(50) NOT NULL,
    kod_pocztowy VARCHAR(8),
    miasto VARCHAR(50),
    adres VARCHAR(50),
    email VARCHAR(50)
);

CREATE TABLE ksiazki (
    id_ksiazki SERIAL PRIMARY KEY,
    tytul VARCHAR(300) NOT NULL,
    autor VARCHAR(300) NOT NULL,
    ISBN VARCHAR(50),
    rok_wydania CHAR(10),
    wydanie CHAR(20),
    id_kategorii INT REFERENCES kategorie(id_kategorii)
);

CREATE TABLE egzemplarze (
    id_egzemplarza SERIAL PRIMARY KEY,
    id_ksiazki INT NOT NULL REFERENCES ksiazki(id_ksiazki)
);

CREATE TABLE wypozyczenia (
    id_wypozyczenia SERIAL PRIMARY KEY,
    id_czytelnika INT NOT NULL REFERENCES czytelnicy(id_czytelnika),
    id_egzemplarza INT NOT NULL REFERENCES egzemplarze(id_egzemplarza),
    data_wypozyczenia DATE NOT NULL,
    data_oddania DATE,
    oczekiwana_data_oddania DATE NOT NULL
	
	CHECK (data_wypozyczenia <= data_oddania)
	CHECK (data_wypozyczenia <= oczekiwana_data_oddania)
);

CREATE TABLE czytelnik_zainteresowania (
	id_czytelnika INT NOT NULL REFERENCES czytelnicy(id_czytelnika),
	id_kategorii INT NOT NULL REFERENCES kategorie(id_kategorii)
);



INSERT INTO kategorie (nazwa) VALUES
    ('Lektury'),
    ('Dla dzieci'),
    ('Fantastyka'),
    ('Science fiction'),
    ('Romans'),
    ('Kryminał');


INSERT INTO czytelnicy (nazwisko, imie, kod_pocztowy, miasto, adres, email) VALUES
    ('Kowalski', 'Jan', '12-345', 'Warszawa', 'ul. Kwiatowa 1', 'jan.kowalski@example.com'),
    ('Nowak', 'Anna', '54-678', 'Kraków', 'ul. Leśnicza 2', 'anna.nowak@example.com'),
    ('Nowak', 'Jan', '00-001', 'Warszawa', 'ul. Kwiatowa 1', 'jan.nowak@example.com'),
    ('Kowalska', 'Anna', '31-234', 'Kraków', 'ul. Leśna 2', 'anna.kowalska@example.com'),
    ('Wiśniewski', 'Piotr', '54-678', 'Wrocław', 'ul. Polna 7', 'piotr.wisniewski@example.com'),
    ('Dąbrowska', 'Maria', '02-345', 'Gdańsk', 'ul. Morza 9', 'maria.dabrowska@example.com'),
    ('Kaczmarek', 'Andrzej', '40-001', 'Poznań', 'ul. Zielona 3', 'andrzej.kaczmarek@example.com'),
    ('Lewandowska', 'Magdalena', '11-111', 'Warszawa', 'ul. Słoneczna 5', 'magdalena.lewandowska@example.com'),
    ('Zieliński', 'Marek', '44-123', 'Katowice', 'ul. Górska 2', 'marek.zielinski@example.com'),
    ('Wójcik', 'Ewa', '03-456', 'Łódź', 'ul. Leśna 7', 'ewa.wojcik@example.com'),
    ('Kowalczyk', 'Tomasz', '30-333', 'Kraków', 'ul. Inna 10', 'tomasz.kowalczyk@example.com'),
    ('Kamińska', 'Katarzyna', '41-111', 'Katowice', 'ul. Długa 4', 'katarzyna.kaminska@example.com'),
    ('Zawisza', 'Mariusz', '50-505', 'Wrocław', 'ul. Rajska 1', 'mariusz.zawisza@example.com'),
    ('Szymańska', 'Agnieszka', '42-222', 'Łódź', 'ul. Ogrodowa 9', 'agnieszka.szymanska@example.com'),
    ('Kowal', 'Paweł', '20-222', 'Lublin', 'ul. Wiosenna 6', 'pawel.kowal@example.com'),
    ('Lis', 'Natalia', '33-333', 'Kraków', 'ul. Leśna 12', 'natalia.lis@example.com'),
    ('Witkowski', 'Kamil', '04-444', 'Warszawa', 'ul. Krótka 2', 'kamil.witkowski@example.com'),
    ('Dudek', 'Monika', '10-555', 'Gdańsk', 'ul. Fala 4', 'monika.dudek@example.com'),
    ('Kurek', 'Marcin', '45-678', 'Poznań', 'ul. Nowa 10', 'marcin.kurek@example.com'),
    ('Mazur', 'Weronika', '51-234', 'Wrocław', 'ul. Morska 3', 'weronika.mazur@example.com'),
    ('Jaworski', 'Karolina', '05-555', 'Warszawa', 'ul. Zielona 8', 'karolina.jaworski@example.com'),
    ('Adamczyk', 'Łukasz', '32-100', 'Kraków', 'ul. Szkolna 1', 'lukasz.adamczyk@example.com'),
    ('Górska', 'Robert', '42-333', 'Katowice', 'ul. Polna 11', 'robert.gorska@example.com');


INSERT INTO ksiazki (tytul, autor, ISBN, rok_wydania, wydanie, id_kategorii) VALUES
    ('Władca Pierścieni', 'J.R.R. Tolkien', '978-83-246-2544-1', '1954', '1', 3),
    ('Władca Pierścieni: Powrót Króla', 'J.R.R. Tolkien', '978-83-246-2546-5', '1955', '3', null),
    ('Złodziejka książek', 'Markus Zusak', '978-83-7659-427-4', '2005', '1', 2),
    ('Hobbit, czyli tam i z powrotem', 'J.R.R. Tolkien', '978-83-246-1740-8', '1937', '2', 3),
    ('Mały Książę', 'Antoine de Saint-Exupéry', '978-83-288-2431-8', '1943', '1', null),
    ('Pan Tadeusz', 'Adam Mickiewicz', '978-83-246-1740-8', '1834', '1', 1),
    ('Harry Potter i Kamień Filozoficzny', 'J.K. Rowling', '978-83-7126-262-9', '1997', '1', 3),
    ('1984', 'George Orwell', '978-83-08-06279-5', '1949', '1', 4),
    ('Dziennik Bridget Jones', 'Helen Fielding', '978-83-7126-262-9', '1996', '1', 5),
    ('Władca Pierścieni: Dwie Wieże', 'J.R.R. Tolkien', '978-83-246-2545-8', '1954', '2', 3),
    ('Zabójstwo Rogera Ackroyda', 'Agatha Christie', '978-83-7659-428-1', '1926', '1', 6),
    ('Hobbit, czyli tam i z powrotem (wyd. 3)', 'J.R.R. Tolkien', '978-83-246-1740-8', '1937', '3', 3),
    ('Opowieści z Narnii', 'C.S. Lewis', '978-83-288-2432-5', '1950', '1', null),
    ('Kubuś Puchatek', 'A.A. Milne', '978-83-246-1741-5', '1926', '1', 2),
    ('Lalka', 'Bolesław Prus', '978-83-246-1742-2', '1890', '1', 1),
    ('Medaliony', 'Zofia Nałkowska', '978-83-7126-262-9', '1946', '1', 1),
    ('Wojna światów', 'H.G. Wells', '978-83-7245-384-7', '1898', '1', 4),
    ('Sherlock Holmes', 'Arthur Conan Doyle', '978-83-246-1743-9', '1892', '1', 6),
    ('Chłopi', 'Władysław Reymont', '978-83-2226-1743-1', '1904', '1', 1);


INSERT INTO egzemplarze (id_ksiazki) VALUES
    (1), (3), (6), (2), (2), (3),
    (4), (4), (5), (5), (6), (6),
    (7), (7), (8), (9), (10), (11),
    (12), (13), (14), (15), (16), (17),
    (1), (2), (3), (4), (5), (6),
    (7), (8), (9), (10), (11), (12),
    (13), (14), (15), (16), (17), (1),
    (2), (3), (4), (5);

INSERT INTO wypozyczenia (id_czytelnika, id_egzemplarza, data_wypozyczenia, data_oddania, oczekiwana_data_oddania) VALUES
    (1, 1, '2023-09-10', '2023-09-13', '2023-09-17'),
    (1, 3, '2023-09-15', '2023-09-25', '2023-09-22'),
    (1, 6, '2023-09-15', '2023-09-25', '2023-09-22'),
    (3, 5, '2023-08-20', '2023-08-27', '2023-08-23'),
    (3, 7, '2023-08-25', '2023-09-01', '2023-09-10'),
    (4, 9, '2023-08-12', '2023-08-15', '2023-08-17'),
    (5, 10, '2023-08-14', null, '2023-08-21'),
    (6, 11, '2023-09-20', null, '2023-09-26'),
    (6, 12, '2023-09-28', '2023-09-30', '2023-09-30'),
    (6, 13, '2023-09-05', '2023-09-10', '2023-09-08'),
    (9, 14, '2023-08-10', null, '2023-08-14'),
    (10, 15, '2023-08-15', '2023-08-20', '2023-08-18'),
    (11, 16, '2023-08-18', '2023-08-23', '2023-08-21'),
    (12, 17, '2023-08-23', '2023-08-30', '2023-08-28'),
    (13, 18, '2023-08-01', '2023-08-05', '2023-08-03'),
    (14, 19, '2023-08-05', null, '2023-08-10'),
    (15, 20, '2023-08-10', '2023-08-15', '2023-08-13'),
    (2, 21, '2023-08-15', null, '2023-08-18'),
    (17, 22, '2023-08-18', '2023-08-25', '2023-08-21'),
    (18, 23, '2023-08-25', '2023-09-01', '2023-08-29'),
    (19, 24, '2023-08-10', '2023-08-13', '2023-08-15'),
    (20, 25, '2023-08-14', null, '2023-08-18'),
    (21, 26, '2023-08-20', '2023-08-26', '2023-08-23'),
    (22, 27, '2023-08-28', '2023-09-01', '2023-08-31'),
    (23, 28, '2023-08-01', '2023-08-05', '2023-08-07'),
    (2, 29, '2023-08-05', null, '2023-08-09'),
    (1 , 8, '2023-03-01', '2023-03-10', '2023-03-15'),
    (1, 10, '2023-03-02', '2023-03-11', '2023-03-12'),
    (1, 12, '2023-03-03', '2023-03-12', '2023-03-14'),
    (1, 14, '2023-03-04', '2023-03-13', '2023-03-11'),
    (1, 16, '2023-02-05', '2023-02-14', '2023-02-16'),
    (1, 18, '2023-03-06', '2023-03-15', '2023-03-13'),
    (1, 20, '2023-03-08', null, '2023-03-19'),
    (1, 22, '2023-03-08', null, '2023-03-15'),
    (1, 24, '2023-03-09', null, '2023-03-18'),
    (1, 26, '2023-03-10', '2023-03-19', '2023-03-17'),
    (1, 28, '2023-03-11', '2023-03-20', '2023-03-23'),
    (1, 30, '2023-03-12', '2023-03-21', '2023-03-20'),
    (1, 32, '2023-03-13', '2023-03-22', '2023-03-26'),
    (1, 34, '2023-03-14', '2023-03-23', '2023-03-22'),
    (1, 36, '2023-04-14', '2023-04-24', '2023-04-27'),
    (1, 38, '2023-03-14', '2023-03-25', '2023-03-24'),
    (1, 40, '2023-03-14', '2023-03-26', '2023-03-29'),
    (1, 42, '2023-03-18', null, '2023-03-26'),
    (1, 44, '2023-03-19', '2023-03-28', '2023-03-31'),
    (1, 4, '2023-03-20', '2023-03-29', '2023-03-28'),
    (1, 1, '2023-03-21', '2023-06-30', '2023-04-02'),
    (2, 3, '2023-01-01', '2023-01-10', '2023-01-15'),
    (2, 5, '2023-03-02', '2023-03-11', '2023-03-12'),
    (2, 7, '2023-03-03', '2023-03-12', '2023-03-14'),
    (2, 9, '2023-03-04', '2023-03-13', '2023-03-11'),
    (2, 11, '2023-02-05', '2023-02-14', '2023-02-16'),
    (2, 13, '2023-03-06', null, '2023-03-13'),
    (2, 15, '2023-03-07', '2023-03-16', '2023-03-19'),
    (2, 17, '2023-03-08', '2023-03-17', '2023-03-15'),
    (2, 19, '2023-03-09', '2023-03-18', '2023-03-18'),
    (2, 21, '2023-03-10', '2023-03-19', '2023-03-17'),
    (3, 23, '2023-03-11', null, '2023-03-23'),
    (2, 25, '2023-03-07', '2023-03-21', '2023-03-21'),
    (9, 27, '2023-03-13', '2023-03-22', '2023-03-26'),
    (2, 29, '2023-03-14', '2023-03-21', '2023-03-22'),
    (9, 31, '2023-03-15', '2023-03-24', '2023-03-27'),
    (2, 33, '2023-03-16', '2023-03-25', '2023-03-24'),
    (9, 35, '2023-03-17', '2023-03-26', '2023-03-29'),
    (2, 37, '2023-03-18', '2023-03-27', '2023-03-26'),
    (8, 39, '2023-03-19', '2023-03-28', '2023-03-31'),
    (1, 41, '2023-03-20', '2023-03-29', '2023-03-28'),
    (1, 3, '2022-03-20', '2022-03-29', '2022-03-28'),
    (2, 43, '2023-03-21', '2023-03-30', '2023-04-02');


INSERT INTO czytelnik_zainteresowania (id_czytelnika, id_kategorii) VALUES
    (1, 2), (1, 3), (2, 3), (2,6),
    (5,1), (5,2), (6,4), (7,1),
    (12,6), (11,1), (11,2), (11,4);

COMMIT;
