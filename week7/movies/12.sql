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
