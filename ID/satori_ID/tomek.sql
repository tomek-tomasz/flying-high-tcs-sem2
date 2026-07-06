

begin;
delete from pracownicy where nazwisko = 'Dolny';

SAVEPOINT S1;
ALTER TABLE etaty ALTER COLUMN nazwa TYPE varchar(20);

ROLLBACK TO SAVEPOINT S1;
commit;





create table test(id int );
alter table test add primary key (id);
begin;
insert into test values(1);
insert into test values(1);
commit;


