start transaction;
  insert into produkty values (200, 800.00, 'biały', 'A');
commit; -- Błąd: Wykryto abstrakcyjny produkt.

insert into produkty values (200, 800.00, 'biały', 'A'); -- Błąd: Wykryto abstrakcyjny produkt.

insert into lodowki values (1, 5, 7500, true); -- Błąd: Wykryto niejednoznaczny produkt.

select * from produkty order by id;
select * from pralki order by id_produktu;
select * from lodowki order by id_produktu;