-- Dane dla przykładu Piotra, Pawła i Kuby

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

-- Dane

COPY users (user_id, login, name) FROM stdin;
1	piotr@piotr.pl	Piotr
2	pawel@pawel.pl	Paweł
3	kuba@kuba.pl	Kuba
\.

COPY problems(problem_id, long_name, short_name) FROM stdin;
1	Problem z 2 zadaniami	A
2	Problem z 3 zadaniami	B
\.

COPY tasks (task_id, problem_id, task_name, max_score) FROM stdin;
1	1	zad1	10
2	1	zad2	10
3	2	zad1	5
4	2	zad2	5
5	2	zad3	15
\.

COPY submits (submit_id, problem_id, date, user_id) FROM stdin;
1	1	2024-04-28 09:01:00	1
2	1	2024-04-28 09:10:00	1
3	1	2024-04-28 09:10:00	2
4	2	2024-04-28 09:20:13	2
\.

COPY checks (submit_id, task_id, status, score, cost) FROM stdin;
1	1	OK	10	10.01-100.33
1	2	ANS	3	\N
2	1	TLE	9	123456.65-654321.76
2	2	ANS	8	\N
3	2	OK	10	90.00-231.00
4	5	OK	15	543.19-600.76
\.


