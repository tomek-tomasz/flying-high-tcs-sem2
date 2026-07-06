SELECT * FROM schema_.songs s
JOIN schema_.songs_artists sa ON s.id = sa.song_id
NATURAL JOIN schema_.artists a;

SELECT * FROM schema_.users NATURAL JOIN schema_.streams;