-- Zadanie: Sklep-AGD - Spójność

select * from produkty order by id;
select * from pralki order by id_produktu;
select * from lodowki order by id_produktu;

insert into produkty (cena, kolor, klasa_energetyczna)
    values (800.00, 'biały', 'A');

select * from produkty order by id;
select * from pralki order by id_produktu;
select * from lodowki order by id_produktu;
