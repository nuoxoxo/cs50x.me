select title from movies
inner join stars
on movies.id = stars.movie_id
inner join people
on stars.person_id = people.id
inner join ratings
on movies.id = ratings.movie_id
where name = 'Chadwick Boseman'
order by rating DESC limit 5