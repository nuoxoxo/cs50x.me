SELECT name FROM people
INNER JOIN directors
ON people.id = person_id
INNER JOIN ratings
ON directors.movie_id = ratings.movie_id
WHERE rating >= 9.0;