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

