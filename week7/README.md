## Songs

1. `SELECT name FROM songs`
2. `SELECT name FROM songs ORDER BY tempo ASC`
3. `SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5`
4. `SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75`
5. `SELECT AVG(energy) FROM songs`
6. 
```sql
SELECT name FROM songs 
WHERE artist_id IN (
SELECT id FROM artists 
WHERE name = "Smashing Pumpkins");
```
7. 
```sql
SELECT AVG(energy) FROM songs 
WHERE artist_id IN (
SELECT id FROM artists 
WHERE name = "Broadcast");
```
8. `SELECT name FROM songs WHERE name LIKE '%feat.%'`
</br>

## Movies

1. `SELECT title FROM movies WHERE year = 2008;`
2. `SELECT birth FROM people WHERE name = "Emma Stone";`
3. `SELECT title FROM movies WHERE year >= 2018 ORDER BY title ASC;`
4. `SELECT COUNT(movie_id) FROM ratings WHERE rating = 10.0;`
5. `SELECT title, year FROM movies WHERE title LIKE 'Harry Potter%' ORDER BY year ASC;`
6. `SELECT AVG(rating) FROM ratings INNER JOIN movies ON movie_id = id WHERE year = 2012;`
7. 
```sql
SELECT title, rating FROM movies 
INNER JOIN ratings ON id = movie_id 
WHERE year = 2010 
ORDER BY rating DESC, title ASC;
```
8. 
```sql
SELECT name FROM people
INNER JOIN stars
ON people.id = person_id
INNER JOIN movies
ON movie_id = movies.id
WHERE title = 'Toy Story';
```
9. 
```sql
select distinct name from people
inner join stars
on people.id = person_id
inner join movies
on movie_id = movies.id
where year = 2004
order by birth
```
10. 
```sql
SELECT name FROM people
INNER JOIN directors
ON people.id = person_id
INNER JOIN ratings
ON directors.movie_id = ratings.movie_id
WHERE rating >= 9.0;
```
11. 
```sql
select title from movies
inner join stars
on movies.id = stars.movie_id
inner join people
on stars.person_id = people.id
inner join ratings
on movies.id = ratings.movie_id
where name = 'Chadwick Boseman'
order by rating DESC limit 5
```
12. 
```sql
-- INTERSECT --
select title from movies
inner join stars
on movies.id = stars.movie_id
inner join people
on stars.person_id = people.id
where name = 'Helena Bonham Carter'
INTERSECT
select title from movies
inner join stars
on movies.id = stars.movie_id
inner join people
on stars.person_id = people.id
where name = 'Johnny Depp'
```
13. 
```sql
select name from people
inner join (
select person_id from stars
inner join (
select id from movies
inner join (
select movie_id from stars
where person_id = (
select people.id from people
where name = 'Kevin Bacon' and birth = 1958))
on id = movie_id)
on movie_id = id)
on people.id = person_id
where name != 'Kevin Bacon'
```
14. 
```sql
select name from people
inner join (
select person_id from stars
inner join (
select id from movies
inner join (
select movie_id from stars
where person_id = (
select people.id from people
where name = 'Kevin Bacon' and birth = 1958))
on id = movie_id)
on movie_id = id)
on people.id = person_id
where name != 'Kevin Bacon'
```
