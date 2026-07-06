-- Schemat bazy

-- Czyszczenie bazy
DROP TABLE IF EXISTS problems CASCADE;
DROP TABLE IF EXISTS submits CASCADE;
DROP TABLE IF EXISTS tasks CASCADE;
DROP TABLE IF EXISTS checks CASCADE;
DROP TABLE IF EXISTS users CASCADE;


-- Tworzenie tabel
CREATE TABLE users (
	user_id	int		PRIMARY KEY,
	login	varchar(50) NOT NULL UNIQUE,
	name	varchar(100) NOT NULL 
);

CREATE TABLE problems (
	problem_id	int	PRIMARY KEY,
	long_name	varchar(100),
	short_name	varchar(10) NOT NULL UNIQUE
);

CREATE TABLE submits (
	submit_id	int	PRIMARY KEY,
	problem_id	int	NOT NULL REFERENCES problems,
	date		timestamp NOT NULL,
	user_id		int	NOT NULL REFERENCES users
);

CREATE TABLE tasks (
	task_id		int	PRIMARY KEY,
	problem_id	int	NOT NULL REFERENCES problems,
	task_name	varchar(20)	NOT NULL,
	max_score	int	NOT NULL,
	UNIQUE (problem_id, task_name)
);

CREATE TABLE checks (
	submit_id	int NOT NULL REFERENCES submits,
	task_id		int	NOT NULL REFERENCES tasks,
	status		varchar(20),
	score		int,
	cost		varchar(100),
	PRIMARY KEY (submit_id, task_id)
);

INSERT INTO users VALUES 
	(1,'kowal','Jan Kowalski'), 
	(2,'nowy','Krzysztof Nowak'),
	(3,'malami','Agnieszka Mielecka'),
	(4,'tommy','Tomasz Paluch'),
	(5,'fujfuj','Grzegorz Fujara'),
	(6,'tosia','Antonina Sławecka'),
	(7,'pasterz','Wojciech Pasterski'),
	(8,'signia','Aleksandra Owczarek'),
	(9,'szczepka','Kamila Szczepańska');

INSERT INTO problems VALUES
	(10,'Statki','A'),
	(20,'Kamienie','B'),
	(30,'Quo vadis','C'),
	(40,'Sortowanie','D'),
	(50,'Listonosz','E'),
	(60,'Stolarze','F');

INSERT INTO submits VALUES
	 (1,10,'2024-04-17 15:52:23',1),
	 (2,10,'2024-04-17 16:42:41',2),
	 (3,40,'2024-04-17 17:32:45',2),
	 (4,20,'2024-04-18 15:22:32',3),
	 (5,10,'2024-04-18 15:32:09',2),
	 (6,30,'2024-04-18 15:42:00',5),
	 (7,60,'2024-04-18 15:52:12',9),
	 (8,20,'2024-04-18 16:52:33',8),
	 (9,30,'2024-04-18 17:52:41',2),
	(10,10,'2024-04-18 18:58:52',7),
	(11,40,'2024-04-19 10:01:41',8),
	(12,60,'2024-04-19 11:45:31',4),
	(13,40,'2024-04-19 12:03:15',3),
	(14,20,'2024-04-19 13:14:01',5),
	(15,10,'2024-04-19 14:52:41',4),
	(16,10,'2024-04-19 05:22:51',7),
	(17,60,'2024-04-20 06:50:56',3),
	(18,30,'2024-04-20 07:52:41',9),
	(19,20,'2024-04-20 08:03:14',9),
	(20,10,'2024-04-20 09:17:09',2);

INSERT INTO tasks VALUES
	(101,10,'ZAD1',25),(102,10,'ZAD2',25),(103,10,'ZAD3',25),(104,10,'ZAD4',25),
	(201,20,'ZAD1',20),(202,20,'ZAD2',24),(203,20,'ZAD3',24),(204,20,'ZAD4',32),
	(301,30,'ZAD1',10),(302,30,'ZAD2',10),(303,30,'ZAD3',10),(304,30,'ZAD4',50),(305,30,'ZAD5',20),
	(401,40,'ZAD1',10),(402,40,'ZAD2',20),(403,40,'ZAD3',30),(404,40,'ZAD4',40),
	(501,50,'ZAD1',50),(502,50,'ZAD2',50),
	(601,60,'ZAD1',10),(602,60,'ZAD2',40),(603,60,'ZAD3',50);

INSERT INTO checks VALUES
	(1,101,'ANS',0,'12-340'),(1,102,'NOT FOUND',0,NULL),(1,103,'OK',25,'92-14'),(1,104,'ANS',0,'120-40'),
	(2,101,'OK',25,'45-45'),(2,102,'PART_OK',15,'32-354'),(2,103,'OK',25,'98-897'),(2,104,'OK',25,'98-897'),
	(3,401,'OK',10,'47-143'),(3,402,'OK',20,'82-372'),(3,403,'OK',30,'98-8'),(3,404,'OK',40,'42-511'), 
	(4,201,'OK',20,'46-249'),(4,202,'NOT FOUND',0,NULL),(4,203,'NOT FOUND',0,NULL),(4,204,'NOT FOUND',0,NULL), 
	(5,101,'ANS',0,'61-89'),(5,102,'CME',0,NULL),(5,103,'NOT FOUND',0,NULL),(5,104,NULL,NULL,NULL),
	(6,301,'OK',10,'72-934'),(6,302,'OK',10,'87-892'),(6,303,'NOT FOUND',0,NULL),(6,304,'CME',0,NULL),(6,305,'OK',20,'23-198'),
	(7,601,'OK',10,'102-37'),(7,602,'OK',40,'90-210'),(7,603,'OK',50,'38-921'),
	(8,201,'ANS',0,'52-8'),(8,202,'OK',40,'83-178'),(8,203,'NOT FOUND',0,NULL),(8,204,'NOT FOUND',0,NULL),
	(9,301,'NOT FOUND',0,NULL),(9,302,'OK',10,'76-190'),(9,303,'NOT FOUND',0,NULL),(9,304,'CME',0,'34-912'),(9,305,'OK',20,'34-220'), 
	(10,101,'OK',25,'26-60'),(10,102,'OK',25,'13-67'),(10,103,'OK',25,'92-14'),(10,104,'OK',25,'120-40'), 
	(11,401,'OK',10,'47-143'),(11,402,'OK',20,'82-372'),(11,403,'OK',30,'98-8'),(11,404,'OK',40,'42-511'), 
	(12,601,'OK',10,'102-37'),(12,602,'OK',40,'90-210'),(12,603,'OK',50,'38-921'),
	(13,401,'OK',10,'104-13'),(13,402,'OK',20,'97-73'),(13,403,'OK',30,'111-82'),(13,404,'OK',40,'120-11'), 
	(14,201,'OK',20,'52-8'),(14,202,'OK',24,'83-178'),(14,203,'OK',24,'67-302'),(14,204,'OK',32,'1-981'),
	(15,101,'OK',25,'45-45'),(15,102,'OK',25,'32-354'),(15,103,'OK',25,'98-897'),(15,104,'OK',25,'98-897'),
	(16,101,'OK',25,'151-51'),(16,102,'OK',25,'56-492'),(16,103,'OK',25,'97-102'),(16,104,'OK',25,'101-905'),
	(17,601,NULL,NULL,NULL),(17,602,NULL,NULL,NULL),(17,603,NULL,NULL,NULL),
	(18,301,NULL,NULL,NULL),(18,302,NULL,NULL,NULL),(18,303,NULL,NULL,NULL),(18,304,NULL,NULL,NULL),(18,305,NULL,NULL,NULL),
	(19,201,NULL,NULL,NULL),(19,202,NULL,NULL,NULL),(19,203,NULL,NULL,NULL),(19,204,NULL,NULL,NULL),
	(20,101,NULL,NULL,NULL),(20,102,NULL,NULL,NULL),(20,103,NULL,NULL,NULL),(20,104,NULL,NULL,NULL);
	
