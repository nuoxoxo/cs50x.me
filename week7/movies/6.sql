-- SELECT AVG(rating) FROM ratings WHERE movie_id = (SELECT id FROM movies WHERE year = 2012);
-- > 7.4

SELECT AVG(rating) FROM ratings INNER JOIN movies ON movie_id = id WHERE year = 2012;
-- > 6.25052023121385 > correct result