select distinct name from people
inner join stars
on people.id = person_id
inner join movies
on movie_id = movies.id
where year = 2004
order by birth